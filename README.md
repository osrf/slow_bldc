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
  * AMS 5047 / 5048 [product list](http://ams.com/eng/Products/Magnetic-Position-Sensors/Angle-Position-On-Axis)
  * Melexis 90316
    * 5V supply
    * SPI
    * 12 bit
    * 1 kHz
  * MPS MA700
    * 3v3 supply, only 7 mA
    * 11 bit
    * 500 kHz
    * can be mounted off-axis and calibrated for donut magnets
hall array:
