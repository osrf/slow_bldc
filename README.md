# slow_bldc

## parts selection

### microcontrollers
Goal: something fast, with FPU (at least for now). HS USB would be nice for tons of datalogging, but not necessarily required.
  * STM32F723ZET6: a bit spendy but is fast with HS USB, which is neat.
  * STM32F4
    * Access line: F401, F410, F411, F412, F413 only have one ADC
    * Fancier ones have multiple ADC's which would be nicer.
  * STM32F3
    * lots of ADC's and should be plenty of FLOPS for our purposes
  * Atmel SAM E / V / S

### motor driver
With integrated power FETs:
  * [TI DRV8312](http://www.ti.com/product/DRV8312)

### encoder
Requirements: SPI interface
  * Digital angle output IC's
    * AMS 5048A [product list](http://ams.com/eng/Products/Magnetic-Position-Sensors/Angle-Position-On-Axis)
      * 14 bit, SPI
      * 3v3 supply
      * 11 kHz
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
