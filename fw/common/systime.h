#ifndef SYSTIME_H
#define SYSTIME_H

#include <stdint.h>
#include "stm32f303xc.h"

void systime_init();
#define SYSTIME_USECS (TIM2->CNT)

#endif

