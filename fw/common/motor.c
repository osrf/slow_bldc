#include <stdio.h>
#include "motor.h"
#include "pin.h"
#include "st/stm32f303xc.h"

// motor-drive related pins:
#define OTW_GPIO GPIOB
#define OTW_PIN 3

#define FAULT_GPIO GPIOB
#define FAULT_PIN 5

#define RSTA_GPIO GPIOB
#define RSTA_PIN 4

#define RSTB_GPIO GPIOC
#define RSTB_PIN 13

#define RSTC_GPIO GPIOB
#define RSTC_PIN 7

void motor_init()
{
  printf("motor_init()\n");
  pin_set_input(OTW_GPIO, OTW_PIN, false);  // no internal pullup needed
  pin_set_input(FAULT_GPIO, FAULT_PIN, false);
  pin_set_output(RSTA_GPIO, RSTA_PIN, false);
  pin_set_output(RSTB_GPIO, RSTB_PIN, false);
  pin_set_output(RSTC_GPIO, RSTC_PIN, false);
  motor_assert_reset(true);
}

void motor_assert_reset(const bool reset)
{
  pin_set_output_state(RSTA_GPIO, RSTA_PIN, reset ? 0 : 1);
  pin_set_output_state(RSTB_GPIO, RSTB_PIN, reset ? 0 : 1);
  pin_set_output_state(RSTC_GPIO, RSTC_PIN, reset ? 0 : 1);
}
