#include <stdio.h>
#include "led.h"
#include "pwm.h"
#include "pin.h"
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

void rs485_init()
{
  printf("rs485_init()\n");
  /*
  pin_set_output(RS485_GPIO
  */
}

void rs485_rx(const uint8_t *data, const uint16_t len)
{
  printf("rs485_rx received %d bytes\n", len);
}

void rs485_tx(const uint8_t *data, const uint16_t len)
{
  printf("rs485_tx sending %d bytes\n", len);
  // todo: assert rs485 DE
  // wait a bit
  // send all the bytes
  // wait a bit
  // de-assert rs485 DE
}

