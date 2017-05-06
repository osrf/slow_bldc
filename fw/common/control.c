#include <stdio.h>
#include "control.h"
#include "enc.h"
#include "motor.h"
#include "param.h"
#include "pwm.h"
#include "systime.h"
#include "tables.h"

// define a float32 literal for pi:
#define PI 3.1415926f

#define CONTROL_MODE_IDLE     0
#define CONTROL_MODE_VOLTAGE  1
#define CONTROL_MODE_POSITION 2
static uint32_t g_control_mode = CONTROL_MODE_POSITION;
static uint32_t g_control_encoder_offset = 500;
#define ENC_TICKS_PER_ELEC_REV (ENC_COUNTS / MOTOR_POLE_PAIRS)
static volatile float g_voltage_target = 2.0;
static volatile float g_position_target = 0.6;
static volatile float g_position_kp = 20.0;
static volatile float g_position_kd = 0.4;
static volatile float g_position_kd_alpha = 0.2;
static uint32_t g_control_prev_t = 0;
//static uint32_t g_control_enc_prev = 0;

void control_init()
{
  printf("control_init()\n");
  param_add("control_mode", PARAM_TYPE_INT, &g_control_mode);
  param_add("encoder_offset", PARAM_TYPE_INT, &g_control_encoder_offset);
  param_add("voltage_target", PARAM_TYPE_FLOAT, &g_voltage_target);
  param_add("position_target", PARAM_TYPE_FLOAT, &g_position_target);
  param_add("position_kp", PARAM_TYPE_FLOAT, &g_position_kp);
  param_add("position_kd", PARAM_TYPE_FLOAT, &g_position_kd);
}

void control_tick()
{
  const uint32_t enc_ticks = enc_poll() + g_control_encoder_offset;
  const uint32_t elec_angle_ticks = enc_ticks % ENC_TICKS_PER_ELEC_REV;

  /*
  int32_t enc_diff = 0;
  if (g_control_prev_t != 0)  // avoid wallop on first time through
    enc_diff = enc_ticks - g_control_enc_prev;
  if (enc_diff > ENC_COUNTS / 2)
    enc_diff -= ENC_COUNTS;  // wrap
  else if (enc_diff < -ENC_COUNTS / 2)
    enc_diff += ENC_COUNTS;  // wrap
  float enc_diff_rad_sec = enc_diff * 2.0f * PI / ENC_COUNTS / (1.0e-6 * dt);
  */
  const uint32_t t_now = SYSTIME_USECS;
  uint32_t dt = t_now - g_control_prev_t;
  g_control_prev_t = t_now;
  if (dt > 10000)
    dt = 10000; // clamp dt to 10ms, in case it's gone totally bonkers

  float v_a = 0, v_b = 0, v_c = 0;  // relative to 1/2 bus voltage

  if (g_control_mode == CONTROL_MODE_POSITION) {
    const float enc_radians = enc_ticks * 2.0f * PI / ENC_COUNTS;
    float pos_error = g_position_target - enc_radians;
    if (pos_error > PI)
      pos_error -= 2.0f * PI;
    else if (pos_error < -PI)
      pos_error += 2.0f * PI;

    static float prev_error = 0;
    float d_error_est = (pos_error - prev_error) / (1.0e-6 * dt);
    static float d_error = 0;
    d_error =  g_position_kd_alpha * d_error_est +
              (1.0f - g_position_kd_alpha) * d_error;
    prev_error = pos_error;

    g_voltage_target = -g_position_kp * pos_error - g_position_kd * d_error;
  }

  if (g_control_mode == CONTROL_MODE_VOLTAGE ||
      g_control_mode == CONTROL_MODE_POSITION) {
    // calculate the indices of the A, B, C voltages (120 degrees apart)
    uint16_t th_a = elec_angle_ticks;
    if (th_a < 0)
      th_a += ENC_TICKS_PER_ELEC_REV;  // in case the offset is negative
    if (th_a >= ENC_TICKS_PER_ELEC_REV)
      th_a -= ENC_TICKS_PER_ELEC_REV;  // wrap back, in case offset wrapped us

    uint16_t th_b = th_a + TABLE_120_DEG;
    if (th_b >= ENC_TICKS_PER_ELEC_REV)
      th_b -= ENC_TICKS_PER_ELEC_REV;  // wrap

    uint16_t th_c = th_a + 2 * TABLE_120_DEG;
    if (th_c >= ENC_TICKS_PER_ELEC_REV)
      th_c -= ENC_TICKS_PER_ELEC_REV;  // wrap

    v_a = g_voltage_target * g_tables_motor_modulation[th_a];
    v_b = g_voltage_target * g_tables_motor_modulation[th_b];
    v_c = g_voltage_target * g_tables_motor_modulation[th_c];
  }

  const float PWM_MID = PWM_MAX / 2.0f;
  if (g_control_mode == CONTROL_MODE_IDLE) {
    pwm_set(PWM_MID, PWM_MID, PWM_MID);
  }
  else {
    const float BUS_VOLTAGE = 12.0f;
    int32_t pwm_a = (int32_t)(PWM_MID * v_a / BUS_VOLTAGE + PWM_MID);
    int32_t pwm_b = (int32_t)(PWM_MID * v_b / BUS_VOLTAGE + PWM_MID);
    int32_t pwm_c = (int32_t)(PWM_MID * v_c / BUS_VOLTAGE + PWM_MID);
    // clamp to sane values
    pwm_a = pwm_a < 0 ? 0 : pwm_a;
    pwm_b = pwm_b < 0 ? 0 : pwm_b;
    pwm_c = pwm_c < 0 ? 0 : pwm_c;
    pwm_a = pwm_a >= PWM_MAX ? PWM_MAX : pwm_a;
    pwm_b = pwm_b >= PWM_MAX ? PWM_MAX : pwm_b;
    pwm_c = pwm_c >= PWM_MAX ? PWM_MAX : pwm_c;
    pwm_set(pwm_a, pwm_b, pwm_c);
  }
}
