# slow_bldc

## parts selection

### microcontrollers
Goal: Fast Cortex-M with FPU (at least for now). HS USB would be nice for tons of datalogging, but not necessarily required.
  * Selection: STM32F303CCT
  * Other parts considered:
    * STM32F723ZET6: a bit spendy but is fast with HS USB, which is neat.
    * STM32F4
      * Access line: F401, F410, F411, F412, F413 only have one ADC
      * Fancier ones have multiple ADC's which would be nicer.
    * Atmel SAM E / V / S

### motor driver
Goal: something completely-integrated with power capacity comfortable for 1A to 2A.
  * Selection: [TI DRV8312](http://www.ti.com/product/DRV8312)

### encoder
Requirements: SPI interface, relatively high resolution
  * Selection: AMS 5048A
    * 14 bit, SPI, 3.3v single-supply, 11 kHz
  * Other parts considered:
    * AMS AS5047D and AS5047P are intended for high-speed BLDC and automatically compensate for encoder latency
      * super cool, but probably not necessary for super low-speed applications
    * Melexis MLX90316
      * 12 bit, SPI
      * 5V supply
      * 1 kHz
    * MPS MA700
      * 3v3 supply, only 7 mA
      * 11 bit
      * 500 kHz
      * can be mounted off-axis and calibrated for donut magnets
    * Allegro A1335
      * 12 bit, SPI
      * can be mounted off-axis
    * AK7451
      * 12 bit
  * Analog output IC's are pretty difference since they output analog sine/cosine, which allows lots of flexibility would would require high-precision simultaneous-sampling ADC to be awesome
    * NXP KMZ60
    * KMT37
    * NVE AAT00x is super low power and tiny since it just provides the sine/cosine half bridges; you need to supply amps and ADC's
    * AS5115 has differential analog sine/cosine outputs

### comms
  * MCU has USB full-speed (12 mbps)
  * Half-duplex RS-485 IC included for chaining these boards together: SN65HVD75

### power supply
  * assumes a regulated 12V supply to provide both the gate-drive and motor bus voltage
  * onboard Recom DC-DC used to generate local 3.3v supply

### current sense
  * TI INA240 used for inline current measurement on flying series current-sense resistors to each phase lead
