#include "systime.h"
#include "stm32f303xc.h"

void systime_init()
{
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  for (volatile int i = 0; i < 1000; i++) { }  // why wait? can't remember :(
  TIM2->PSC = 71;  // we want 1us time tick
  TIM2->ARR = 0xffffffff;  // count as long as possible before rollover
  TIM2->EGR = TIM_EGR_UG;
  TIM2->CR1 = TIM_CR1_CEN;
}
