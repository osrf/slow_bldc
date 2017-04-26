#ifndef MOTORS_H
#define MOTORS_H

#include <stdint.h>
#include "st/stm32f303xc.h"

void motor_init();
void motor_set_pwm(int16_t a, int16_t b, int16_t c);

#endif
