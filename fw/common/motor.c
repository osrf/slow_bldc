#include <stdio.h>
#include "motor.h"
#include "pin.h"

void motor_init()
{
  printf("motor_init()\n");
  // here we shall actually set up the timer peripheral
}

void motor_set_pwm(int16_t a, int16_t b, int16_t c)
{
  printf("motor_set_pwm(%d, %d, %d)\n", a, b, c);
  // here we shall actually set the timer values
}
