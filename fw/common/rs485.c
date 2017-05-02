#include <stdio.h>
#include "led.h"
#include "parser.h"
#include "pin.h"
#include "pwm.h"
#include "rs485.h"

// pin connections
// PB10 = usart3 TX
// PB11 = usart3 RX

#define RS485_GPIO  GPIOB
#define RS485_USART USART3
#define TX_PIN 10
#define RX_PIN 11
#define RE_PIN  1
#define DE_PIN  2

#define RS485_RX_RING_LEN 512
static volatile uint8_t g_rs485_rx_ring[RS485_RX_RING_LEN];
static volatile uint32_t g_rs485_rx_ring_rpos = 0, g_rs485_rx_ring_wpos = 0;

void rs485_init()
{
  printf("rs485_init()\n");
  parser_init();
  RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
  pin_set_output(RS485_GPIO, RE_PIN, false);
  pin_set_output(RS485_GPIO, DE_PIN, false);
  pin_set_alternate_function(RS485_GPIO, TX_PIN, 7);  // PB10 AF7 = USART3 TX
  pin_set_alternate_function(RS485_GPIO, RX_PIN, 7);  // PB11 AF7 = USART3 RX
  RS485_USART->CR1 &= ~USART_CR1_UE;
  RS485_USART->CR1 |=  USART_CR1_TE | USART_CR1_RE;
  // for 1 Mbaud we want USARTDIV = 36M / 1M = 36
  RS485_USART->BRR = 36;
  RS485_USART->CR1 |= USART_CR1_UE;
  NVIC_SetPriority(USART3_IRQn, 1);
  NVIC_EnableIRQ(USART3_IRQn);
}

void rs485_rx(const uint32_t len, const uint8_t *data)
{
  printf("rs485_rx received %d bytes\n", (int)len);
}

void rs485_tx(const uint32_t len, const uint8_t *data)
{
  printf("rs485_tx sending %d bytes\n", (int)len);
  pin_set_output_high(RS485_GPIO, RE_PIN);  // disable receiver
  pin_set_output_high(RS485_GPIO, DE_PIN);  // enable transmitter
  for (volatile int dumb = 0; dumb < 10000; dumb++) { }
  for (uint32_t i = 0; i < len; i++) {
    while (!(RS485_USART->ISR & USART_ISR_TXE)) { } // wait for tx to clear
    RS485_USART->TDR = data[i];
  }
  while (!(RS485_USART->ISR & USART_ISR_TC)) { } // wait for TX to finish
  for (volatile int dumb = 0; dumb < 10000; dumb++) { }
  pin_set_output_low(RS485_GPIO, RE_PIN);  // re-enable receiver
  pin_set_output_low(RS485_GPIO, DE_PIN);  // disable transmitter
}

void usart3_vector()
{
  volatile uint8_t __attribute__((unused)) sr = USART3->ISR;  // clear errors
  volatile uint8_t b = USART3->RDR;  // drain
  g_rs485_rx_ring[g_rs485_rx_ring_wpos] = b;
  if (++g_rs485_rx_ring_wpos >= RS485_RX_RING_LEN)
    g_rs485_rx_ring_wpos = 0;
}

void rs485_tick()
{
  // called during the CPU's idle time
  while (g_rs485_rx_ring_rpos != g_rs485_rx_ring_wpos) {
    parser_process_byte(g_rs485_rx_ring[g_rs485_rx_ring_rpos]);
    if (++g_rs485_rx_ring_rpos >= RS485_RX_RING_LEN)
      g_rs485_rx_ring_rpos = 0;
  }
}
