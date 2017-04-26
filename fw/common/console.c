#include "console.h"
#include "pin.h"

// pin connections
// PA9  = usart1 TX
// PA10 = usart1 RX

#define CONSOLE_GPIO  GPIOA
#define CONSOLE_USART USART1
#define TX_PIN 9
#define RX_PIN 10

static volatile bool s_console_init_complete = false;

// USART1 clock is currently 72 MHz

// TODO: need to sanity-check this

void console_init()
{
  s_console_init_complete = true;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  /*
  pin_set_alternate_function(CONSOLE_GPIO, TX_PIN, 4);  // PB10 AF4 = TX3
  CONSOLE_USART->CR1 &= ~USART_CR1_UE;
  CONSOLE_USART->CR1 |=  USART_CR1_TE;
  // baud rate = F_CK / USARTDIV
  // for 1 Mbaud we want USARTDIV = 72M / 1M = 72
  CONSOLE_USART->BRR  = 72;
  CONSOLE_USART->CR1 |=  USART_CR1_UE;
  */
}

void console_send_block(const uint8_t *buf, uint32_t len)
{
  /*
  if (!s_console_init_complete)
    console_init();
  for (uint32_t i = 0; i < len; i++)
  {
    while (!(CONSOLE_USART->ISR & USART_ISR_TXE)) { } // wait for tx to clear
    CONSOLE_USART->TDR = buf[i];
  }
  while (!(CONSOLE_USART->ISR & USART_ISR_TC)) { } // wait for TX to finish
  */
}
