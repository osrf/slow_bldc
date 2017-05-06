#include <stdint.h>
#include <stdio.h>
#include "console.h"
#include "control.h"
#include "current.h"
#include "enc.h"
#include "led.h"
#include "motor.h"
#include "param.h"
#include "pwm.h"
#include "rs485.h"
#include "stack.h"
#include "st/stm32f303xc.h"
#include "systime.h"

void __libc_init_array(void);  // i'm sure there is declared somewhere?

extern uint32_t _srelocate_flash, _srelocate, _erelocate, _ebss, _sbss;
extern int main(void);

void startup_clock_init_fail(void) { while (1) { } }

void reset_vector(void)
{
  //watchdog_reset_counter();
  g_stack[0] = 0; // need to put a reference in here to the stack array
                  // to make sure the linker brings it in. I'm sure there
                  // is a more elegant way to do this, but this seems to work
  // set up data segment
  uint32_t *pSrc = &_srelocate_flash;
  uint32_t *pDest = &_srelocate;
  if (pSrc != pDest)
    for (; pDest < &_erelocate; )
      *pDest++ = *pSrc++;
  // set up bss segment
  for (pDest = &_sbss; pDest < &_ebss; )
    *pDest++ = 0;
  __libc_init_array();
  FLASH->ACR |= 0x2;  // see datasheet p.13. need 2 wait states when >48 MHz
  RCC->CR |= RCC_CR_HSEON; // enable HSE oscillator (off-chip crystal)
  for (volatile uint32_t i = 0; 
       i < 0x5000 && !(RCC->CR & RCC_CR_HSERDY); i++)
  { } // wait for either timeout or HSE to spin up
  if (!(RCC->CR & RCC_CR_HSERDY))
    startup_clock_init_fail();  // go there and spin forever. BUH BYE
  // HSE crystal frequency is 8 MHz
  // we want:
  // PLLCLK = 72 MHz = HCLK = FHCLK = SYSCLK
  // APB1 = 36 MHz
  // APB2 = 72 MHz
  RCC->CFGR |=
      RCC_CFGR_PLLMUL9           |  // we want PLLCLK to be 8 * 9 = 72 MHz
      RCC_CFGR_PLLSRC_HSE_PREDIV |  // select crystal oscillator as PLL input
      RCC_CFGR_PPRE2_DIV1        |  // apb2 = sysclk = 72 MHz
      RCC_CFGR_PPRE1_DIV2        |  // apb1 = sysclk/2 = 36 MHz
      RCC_CFGR_HPRE_DIV1         ;  // ahb = sysclk = pllclk = 72 MHz
  RCC->CR |= RCC_CR_PLLON;  // start spinning up the PLL
  while (!(RCC->CR & RCC_CR_PLLRDY)) { }  // wait until PLL is spun up
  RCC->CFGR |= RCC_CFGR_SW_PLL;  // select PLL as system clock source
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) { }  // wait for it
  // hooray we're done! we're now running at 72 MHz.
  static char stdout_buf[256];
  setvbuf(stdout, stdout_buf, _IOLBF, sizeof(stdout_buf));
  param_init();
  led_init();
  console_init();
  pwm_init();
  motor_init();
  enc_init();
  rs485_init();
  systime_init();
  control_init();
  /*
  serial_init();
  current_init();
  */
  __enable_irq();
  main(); // jump to application main()
  while (1) { } // hopefully we never get here...
}
