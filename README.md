# slow_bldc

## parts selection

### microcontrollers
Goal: something fast, with FPU (at least for now). HS USB would be nice for tons of datalogging, but not necessarily required.
  * STM32F723ZET6
  * STM32F4
    * Access line: F401, F410, F411, F412, F413 only have one ADC
    * Fancier ones have multiple ADC's which would be nicer.
  * Atmel SAM E / V / S

### motor driver
With integrated power FETs:
  * [TI DRV8312](http://www.ti.com/product/DRV8312)

### encoder
hall array:
  * AMS 5047 / 5048 [product list](http://ams.com/eng/Products/Magnetic-Position-Sensors/Angle-Position-On-Axis)
