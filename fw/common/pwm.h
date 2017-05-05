#ifndef PWM_H
#define PWM_H

#include <stdint.h>

#define PWM_MAX 2047

void pwm_init();
void pwm_set(const uint32_t a, const uint32_t b, const uint32_t c);

#endif
