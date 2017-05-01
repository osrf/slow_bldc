#include <stdio.h>
#include "pin.h"
#include "pwm.h"
#include "st/stm32f303xc.h"

// PB6 = TIM8_CH1 on AF5  = PWMA
// PB8 = TIM8_CH2 on AF10 = PWMB
// PB9 = TIM8_CH3 on AF10 = PWMC

#define PWM_GPIO GPIOB

void pwm_init()
{
  printf("pwm_init()\n");
  // here we shall actually set up the timer peripheral
  RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;  // turn on TIM8 clock
  pin_set_alternate_function(PWM_GPIO, 6,  5);  // PB6 AF5  = TIM8_CH1
  pin_set_alternate_function(PWM_GPIO, 8, 10);  // PB8 AF10 = TIM8_CH2
  pin_set_alternate_function(PWM_GPIO, 9, 10);  // PB9 AF10 = TIM8_CH3
  // inbound clock is 72 MHz / 2 = 36 MHz
  TIM8->ARR = 2047;  // this will give us a 36M/2048 = 17.578 kHz timebase
  TIM8->CCR1 = 1024;  // CH1 PWM level to drive 1/2 bus voltage
  TIM8->CCR2 = 1024;  // CH2 PWM level to drive 1/2 bus voltage
  TIM8->CCR3 = 1024;  // CH3 PWM level to drive 1/2 bus voltage
  TIM8->CCMR1 = TIM_CCMR1_OC1M_1 |  // PWM mode 0 on output compare 1 (OC1)
                TIM_CCMR1_OC1M_2 |  // PWM mode 0 on output compare 1 (OC1)
                TIM_CCMR1_OC1CE  |  // clear output 1 on compare
                TIM_CCMR1_OC2M_1 |  // PWM mode 0 on output compare 2 (OC2)
                TIM_CCMR1_OC2M_2 |  // PWM mode 0 on output compare 2 (OC2)
                TIM_CCMR1_OC2CE  ;  // clear output 2 on compare
  TIM8->CCMR2 = TIM_CCMR2_OC3M_1 |  // PWM mode 0 on output compare 3 (OC3)
                TIM_CCMR2_OC3M_2 |  // PWM mode 0 on output compare 3 (OC3)
                TIM_CCMR2_OC3CE  ;  // clear output 3 on compare
  TIM8->CCER  = TIM_CCER_CC1E    |  // enable compare output 1
                TIM_CCER_CC2E    |  // enable compare output 2
                TIM_CCER_CC3E    ;  // enable compare output 3
  TIM8->CR1   = TIM_CR1_CMS_0    |  // enable center-aligned PWM mode
                TIM_CR1_ARPE     |  // auto-reload preload enable (buffered)
                TIM_CR1_CEN      ;  // enable counter
  TIM8->EGR   = TIM_EGR_UG       ;  // generate update event to load registers
  TIM8->BDTR  = TIM_BDTR_MOE     ;  // master output enable
}

void pwm_set(const uint32_t a, const uint32_t b, const uint32_t c)
{
  // bounds check to avoid bonkers stuff
  const uint32_t MAX_PWM = 2047;
  TIM8->CCR1 = a <= MAX_PWM ? a : MAX_PWM;
  TIM8->CCR2 = b <= MAX_PWM ? b : MAX_PWM;
  TIM8->CCR3 = c <= MAX_PWM ? c : MAX_PWM;
}
