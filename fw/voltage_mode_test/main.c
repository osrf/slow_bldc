#include <stdio.h>
#include "current.h"
#include "led.h"
#include "motor.h"
#include "pwm.h"
#include "control.h"

int main(int argc, char **argv)
{
  motor_assert_reset(false);
  while (1)
    control_tick();
  return 0;
}
