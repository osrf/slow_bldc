#include <stdio.h>
#include "current.h"
#include "led.h"
#include "motor.h"
#include "pwm.h"

int main(int argc, char **argv)
{
  printf("hello, world! I hope this works!\r\n");
  // test the pwm module
  const int16_t pwm[3] = { 1024-200, 1024+200, 1024 };
  motor_assert_reset(false);
  while (1) {
    for (volatile int i = 0; i < 200000; i++) { }
    led_toggle();
    pwm_set(pwm[0], pwm[1], pwm[2]);
  }
  return 0;
}
