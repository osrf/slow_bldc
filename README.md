# slow_bldc

## parts selection

### microcontrollers
Goal: something fast, ideally with FPU, and with HS USB for streaming data fast enough for nice tuning.
  * STM32F723ZET6
  * STM32F4 (doesn't have HS USB on-chip though)
  * Atmel SAM E / V / S

### motor driver
With integrated power FETs:
  * [TI DRV8312](http://www.ti.com/product/DRV8312)

### encoder
hall array:
  * AMS 5047 / 5048 [product list](http://ams.com/eng/Products/Magnetic-Position-Sensors/Angle-Position-On-Axis)
