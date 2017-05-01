#include <stdio.h>
#include "enc.h"
#include "pin.h"
#include "st/stm32f303xc.h"

#define ENC_GPIO GPIOA
#define ENC_SCLK_PIN 5
#define ENC_MISO_PIN 6
#define ENC_MOSI_PIN 7
#define ENC_CS_PIN 15

void enc_init()
{
  printf("enc_init()\n");
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
  pin_set_alternate_function(ENC_GPIO, ENC_SCLK_PIN, 5);  // PA5 AF5 = SCLK1
  pin_set_alternate_function(ENC_GPIO, ENC_MISO_PIN, 5);  // PA6 AF5 = MISO1
  pin_set_alternate_function(ENC_GPIO, ENC_MOSI_PIN, 5);  // PA7 AF5 = MOSI1
  pin_set_output(ENC_GPIO, ENC_CS_PIN, true);
  pin_set_output_speed(ENC_GPIO, ENC_CS_PIN, 1);  // up to 10 MHz is fine
  pin_set_output_speed(ENC_GPIO, ENC_SCLK_PIN, 1);  // up to 10 MHz is fine
  pin_set_output_speed(ENC_GPIO, ENC_MISO_PIN, 1);  // up to 10 MHz is fine
  pin_set_output_speed(ENC_GPIO, ENC_MOSI_PIN, 1);  // up to 10 MHz is fine
  SPI1->CR1  = SPI_CR1_CPHA |  // clock phase: cpol=0, cpha=1
               SPI_CR1_MSTR |  // master mode
               SPI_CR1_BR_1 |  // baud rate = pclk / 16 = 72/16 = 4.5 MHz
               SPI_CR1_BR_0 ;  // baud rate = pclk / 16 = 72/16 = 4.5 MHz
  SPI1->CR2  = SPI_CR2_DS_3 |
               SPI_CR2_DS_2 |
               SPI_CR2_DS_1 |
               SPI_CR2_DS_0 |  // select 16-bit data size
               SPI_CR2_SSOE ;  // automatically assert SS output as needed
  SPI1->CR1 |= SPI_CR1_SPE  ;  // enable SPI
}

uint16_t enc_poll()
{
  pin_set_output_low(ENC_GPIO, ENC_CS_PIN);
  SPI1->DR;  // make sure we've flushed the RX register
  SPI1->DR = 0xffff;
  while (!(SPI1->SR & SPI_SR_RXNE)) { }  // wait for it...
  pin_set_output_high(ENC_GPIO, ENC_CS_PIN);
  return SPI1->DR & 0x3fff; // returns the result of the previous call
}
