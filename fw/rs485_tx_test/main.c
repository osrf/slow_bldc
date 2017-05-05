#include <stdio.h>
#include "led.h"
#include "rs485.h"

int main(int argc, char **argv)
{
  printf("hello, world! welcome to rs485_test\r\n");
  uint8_t test_pkt[4] = { 0, 1, 2, 3 };
  while (1) {
    for (volatile int i = 0; i < 1000000; i++) { }
    led_toggle();
    rs485_tx(sizeof(test_pkt), test_pkt);
    rs485_tick();
  }
  return 0;
}
