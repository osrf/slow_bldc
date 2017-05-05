#include <stdio.h>
#include "led.h"
#include "rs485.h"

int main(int argc, char **argv)
{
  printf("hello, world! welcome to rs485_test\r\n");
  while (1) {
    rs485_tick();
  }
  return 0;
}
