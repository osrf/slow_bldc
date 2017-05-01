#include <stdio.h>
#include "enc.h"
#include "led.h"

int main(int argc, char **argv)
{
  // test the pwm module
  while (1) {
    for (volatile int i = 0; i < 200000; i++) { }
    led_toggle();
    printf("enc: %05d\n", enc_poll());
  }
  return 0;
}
