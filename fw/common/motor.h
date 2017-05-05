#ifndef MOTOR_H
#define MOTOR_H

#include <stdbool.h>
#define MOTOR_POLE_PAIRS 11

void motor_init();
void motor_assert_reset(const bool reset);

#endif
