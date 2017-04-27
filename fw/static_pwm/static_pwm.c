#include <stdio.h>
#include "current.h"
#include "led.h"
#include "motor.h"

int main(int argc, char **argv)
{
  printf("hello, world! I hope this works!\r\n");
  // set the pwm to something just to get some current flowing
  // and test out current measurement
  const int16_t pwm[3] = { 100, -400, 800 };
  while (1) {
    for (volatile int i = 0; i < 200000; i++) { }
    led_toggle();
    motor_set_pwm(pwm[0], pwm[1], pwm[2]);
  }
  return 0;
}
