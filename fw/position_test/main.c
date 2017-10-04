#include <stdio.h>
#include "motor.h"
#include "control.h"
#include "systime.h"
#include "param.h"

int main(int argc, char **argv)
{
  motor_assert_reset(false);
  uint32_t t_prev_pos = 0, t_prev_control = 0;
  const int num_position_targets = 2;
  const float position_targets[2] = { 0.6f, -1.0f };
  const float position_target_travel_times[2] = { 2.0f, 2.0f };
  int position_target_idx = 0;
  while (1) {
    uint32_t t_now = SYSTIME_USECS;

    uint32_t control_dt = t_now - t_prev_control;
    if (control_dt > 1000) {  // run controller at 1 kHz to reduce enc noise
      control_tick();
      t_prev_control = t_now;
    }

    float dt_frac = (0.000001f * (t_now - t_prev_pos)) /
        position_target_travel_times[position_target_idx];  // todo: wrap
    uint32_t next_idx = (position_target_idx + 1) % num_position_targets;
    if (dt_frac > 1.0f)
      dt_frac = 1.0f;
    float pos_tgt = (1.0f - dt_frac) * position_targets[position_target_idx] +
                     dt_frac * position_targets[next_idx];
    param_set_float("position_target", pos_tgt);
    if (dt_frac >= 1.0f) {
      position_target_idx++;
      if (position_target_idx >= num_position_targets)
        position_target_idx = 0;
      //const float position_target = position_targets[position_target_idx];
      t_prev_pos = t_now;
    }
  }
  return 0;
}
