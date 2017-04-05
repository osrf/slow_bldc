EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:stm32
LIBS:circle-cache
EELAYER 26 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L STM32F303CCTx U1
U 1 1 58E54389
P 8200 3600
F 0 "U1" H 6950 5450 50  0000 C CNN
F 1 "STM32F303CCTx" H 7200 5350 50  0000 C CNN
F 2 "Housings_QFP:LQFP-48_7x7mm_Pitch0.5mm" H 15400 5275 50  0001 R TNN
F 3 "" H 8200 3600 50  0001 C CNN
	1    8200 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 1800 8000 1800
$Comp
L +3V3 #PWR01
U 1 1 58E5454C
P 8000 1800
F 0 "#PWR01" H 8000 1650 50  0001 C CNN
F 1 "+3V3" H 8015 1973 50  0000 C CNN
F 2 "" H 8000 1800 50  0001 C CNN
F 3 "" H 8000 1800 50  0001 C CNN
	1    8000 1800
	1    0    0    -1  
$EndComp
$Comp
L VAA #PWR02
U 1 1 58E54586
P 8300 1800
F 0 "#PWR02" H 8300 1650 50  0001 C CNN
F 1 "VAA" H 8317 1973 50  0000 C CNN
F 2 "" H 8300 1800 50  0001 C CNN
F 3 "" H 8300 1800 50  0001 C CNN
	1    8300 1800
	1    0    0    -1  
$EndComp
$Comp
L +3V3 #PWR03
U 1 1 58E545C2
P 3450 7050
F 0 "#PWR03" H 3450 6900 50  0001 C CNN
F 1 "+3V3" H 3465 7223 50  0000 C CNN
F 2 "" H 3450 7050 50  0001 C CNN
F 3 "" H 3450 7050 50  0001 C CNN
	1    3450 7050
	1    0    0    -1  
$EndComp
$Comp
L VAA #PWR04
U 1 1 58E545C8
P 3750 7050
F 0 "#PWR04" H 3750 6900 50  0001 C CNN
F 1 "VAA" H 3767 7223 50  0000 C CNN
F 2 "" H 3750 7050 50  0001 C CNN
F 3 "" H 3750 7050 50  0001 C CNN
	1    3750 7050
	1    0    0    -1  
$EndComp
Connection ~ 8100 1800
Text Notes 5250 6450 0    118  ~ 0
TODO: AS5048
Text Notes 5250 6850 0    118  ~ 0
TODO: DRV8312
$EndSCHEMATC
