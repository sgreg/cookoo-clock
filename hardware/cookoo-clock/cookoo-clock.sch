EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "cook'oo clock"
Date "2020-07-11"
Rev "A"
Comp "Sven Gregori <sven@craplab.fi>"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U1
U 1 1 5F09065E
P 6050 3700
F 0 "U1" H 5521 3746 50  0000 R CNN
F 1 "ATtiny85-20PU" H 5521 3655 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 6050 3700 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 6050 3700 50  0001 C CNN
	1    6050 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5F090D13
P 7700 4650
F 0 "C3" H 7815 4696 50  0000 L CNN
F 1 "22pF" H 7815 4605 50  0000 L CNN
F 2 "" H 7738 4500 50  0001 C CNN
F 3 "~" H 7700 4650 50  0001 C CNN
	1    7700 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5F090E27
P 8300 4650
F 0 "C4" H 8415 4696 50  0000 L CNN
F 1 "22pF" H 8415 4605 50  0000 L CNN
F 2 "" H 8338 4500 50  0001 C CNN
F 3 "~" H 8300 4650 50  0001 C CNN
	1    8300 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C1
U 1 1 5F091071
P 1950 3700
F 0 "C1" H 2068 3746 50  0000 L CNN
F 1 "1000uF" H 2068 3655 50  0000 L CNN
F 2 "" H 1988 3550 50  0001 C CNN
F 3 "~" H 1950 3700 50  0001 C CNN
	1    1950 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5F09146B
P 7100 2650
F 0 "R1" H 7170 2696 50  0000 L CNN
F 1 "10k" H 7170 2605 50  0000 L CNN
F 2 "" V 7030 2650 50  0001 C CNN
F 3 "~" H 7100 2650 50  0001 C CNN
	1    7100 2650
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 5F091928
P 8000 4400
F 0 "Y1" H 8000 4668 50  0000 C CNN
F 1 "8.0MHz" H 8000 4577 50  0000 C CNN
F 2 "" H 8000 4400 50  0001 C CNN
F 3 "~" H 8000 4400 50  0001 C CNN
	1    8000 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 5F092523
P 1100 3750
F 0 "BT1" H 1218 3846 50  0000 L CNN
F 1 "CR2032" H 1218 3755 50  0000 L CNN
F 2 "" V 1100 3810 50  0001 C CNN
F 3 "~" V 1100 3810 50  0001 C CNN
	1    1100 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:Jumper JP1
U 1 1 5F092CFF
P 3050 2000
F 0 "JP1" H 3050 2264 50  0000 C CNN
F 1 "Magnets" H 3050 2173 50  0000 C CNN
F 2 "" H 3050 2000 50  0001 C CNN
F 3 "~" H 3050 2000 50  0001 C CNN
	1    3050 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 5F0949C7
P 9750 4950
F 0 "J2" H 9668 4525 50  0000 C CNN
F 1 "SSD1306 OLED" H 9668 4616 50  0000 C CNN
F 2 "" H 9750 4950 50  0001 C CNN
F 3 "~" H 9750 4950 50  0001 C CNN
	1    9750 4950
	1    0    0    1   
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5F0B35E3
P 7100 4650
F 0 "SW1" V 7054 4798 50  0000 L CNN
F 1 "Reset" V 7145 4798 50  0000 L CNN
F 2 "" H 7100 4850 50  0001 C CNN
F 3 "~" H 7100 4850 50  0001 C CNN
	1    7100 4650
	0    1    1    0   
$EndComp
Wire Wire Line
	7700 4500 7700 4400
Wire Wire Line
	7700 4400 7850 4400
Wire Wire Line
	8150 4400 8300 4400
Wire Wire Line
	8300 4400 8300 4500
Wire Wire Line
	8300 3700 8300 4400
Connection ~ 8300 4400
Wire Wire Line
	7700 3800 7700 4400
Connection ~ 7700 4400
Wire Wire Line
	3350 2000 4350 2000
Wire Wire Line
	6050 2000 6050 3100
Connection ~ 6050 2000
Connection ~ 4350 2000
Wire Wire Line
	4350 2000 6050 2000
Wire Wire Line
	2750 2000 1950 2000
Wire Wire Line
	1950 2000 1950 3550
Wire Wire Line
	1950 2000 1100 2000
Wire Wire Line
	1100 2000 1100 3550
Connection ~ 1950 2000
Wire Wire Line
	6650 3800 7700 3800
Wire Wire Line
	6650 3700 8300 3700
Wire Wire Line
	1100 5550 1950 5550
Wire Wire Line
	1950 5550 1950 3850
Wire Wire Line
	4350 5550 1950 5550
Connection ~ 1950 5550
Connection ~ 4350 5550
Wire Wire Line
	7700 4800 7700 5550
Wire Wire Line
	8300 5550 7700 5550
Wire Wire Line
	8300 4800 8300 5550
Connection ~ 7700 5550
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5F12A8D1
P 1100 1850
F 0 "#FLG0101" H 1100 1925 50  0001 C CNN
F 1 "PWR_FLAG" H 1100 2023 50  0000 C CNN
F 2 "" H 1100 1850 50  0001 C CNN
F 3 "~" H 1100 1850 50  0001 C CNN
	1    1100 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 4300 6050 5550
Connection ~ 6050 5550
Wire Wire Line
	6050 5550 7100 5550
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5F13033E
P 1100 5700
F 0 "#FLG0102" H 1100 5775 50  0001 C CNN
F 1 "PWR_FLAG" H 1100 5873 50  0000 C CNN
F 2 "" H 1100 5700 50  0001 C CNN
F 3 "~" H 1100 5700 50  0001 C CNN
	1    1100 5700
	-1   0    0    1   
$EndComp
Wire Wire Line
	4350 5550 6050 5550
Wire Wire Line
	1100 5700 1100 5550
Connection ~ 1100 5550
Wire Wire Line
	1100 3850 1100 5550
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5F131CC9
P 8850 1850
F 0 "#FLG0103" H 8850 1925 50  0001 C CNN
F 1 "PWR_FLAG" H 8850 2023 50  0000 C CNN
F 2 "" H 8850 1850 50  0001 C CNN
F 3 "~" H 8850 1850 50  0001 C CNN
	1    8850 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1850 1100 2000
Connection ~ 1100 2000
Wire Wire Line
	4350 3850 4350 5550
Wire Wire Line
	4350 3550 4350 2000
$Comp
L Device:C C2
U 1 1 5F090C06
P 4350 3700
F 0 "C2" H 4465 3746 50  0000 L CNN
F 1 "100nF" H 4465 3655 50  0000 L CNN
F 2 "" H 4388 3550 50  0001 C CNN
F 3 "~" H 4350 3700 50  0001 C CNN
	1    4350 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3500 9550 3500
Wire Wire Line
	6050 2000 7100 2000
Wire Wire Line
	7100 2800 7100 3900
Wire Wire Line
	7100 4850 7100 5550
Connection ~ 7100 5550
Wire Wire Line
	7100 5550 7700 5550
Wire Wire Line
	6650 3900 7100 3900
Connection ~ 7100 3900
Wire Wire Line
	7100 3900 7100 4450
Wire Wire Line
	7100 3900 9850 3900
Wire Wire Line
	6650 3400 9050 3400
Wire Wire Line
	6650 3600 8950 3600
Wire Wire Line
	7100 2500 7100 2000
Wire Wire Line
	9850 3900 9850 2500
Wire Wire Line
	9650 2500 9650 3400
Wire Wire Line
	9750 2500 9750 3600
Wire Wire Line
	9550 2500 9550 3500
$Comp
L Connector:AVR-ISP-6 J1
U 1 1 5F1A3791
P 9750 2100
F 0 "J1" V 9283 2150 50  0000 C CNN
F 1 "AVR-ISP-6" V 9374 2150 50  0000 C CNN
F 2 "" V 9500 2150 50  0001 C CNN
F 3 " ~" H 8475 1550 50  0001 C CNN
	1    9750 2100
	0    -1   1    0   
$EndComp
Wire Wire Line
	9250 2000 8850 2000
Connection ~ 7100 2000
Wire Wire Line
	10150 2000 10600 2000
Wire Wire Line
	10600 2000 10600 5550
Connection ~ 8300 5550
Wire Wire Line
	9550 4950 8850 4950
Wire Wire Line
	8850 4950 8850 2000
Connection ~ 8850 2000
Wire Wire Line
	8850 2000 7100 2000
Wire Wire Line
	9550 4850 8950 4850
Wire Wire Line
	8950 4850 8950 3600
Connection ~ 8950 3600
Wire Wire Line
	8950 3600 9750 3600
Wire Wire Line
	9550 4750 9050 4750
Wire Wire Line
	9050 4750 9050 3400
Connection ~ 9050 3400
Wire Wire Line
	9050 3400 9650 3400
Wire Wire Line
	8300 5550 8850 5550
Wire Wire Line
	9550 5050 8850 5050
Wire Wire Line
	8850 5050 8850 5550
Connection ~ 8850 5550
Wire Wire Line
	8850 5550 10600 5550
Text Notes 2950 7250 0    100  ~ 0
TODO\n- try ATtiny85V-10 as uC\n- try 8.192MHz crystal
Text Notes 2300 2700 0    50   ~ 0
Pair of neodymium magnets serving as jumper,\ncausing short circuit (in a good way) when\nplaced on a conductive surface.\n\nFor this to work, the magnets themselves\nneed to be conductive, not epoxy or otherwise\ncoated, no matter how cool that looks.
Wire Wire Line
	8850 2000 8850 1850
Text Notes 8850 1550 0    50   ~ 0
During development, the system can be\npowered straight from the programmer,\nso no need for batteries or conductive\nsurfaces for that.
Text Notes 2050 4650 0    50   ~ 0
C1 could go on either side of the magnet jumper.\nPerfboard arrangements made it easier on this side.\n\nHaving the capacitor on this left side won't discharge\nit when the magnet connection is removed, and is left\nalone when powered via programmer. Also, the OLED\nwill straight go off when power is gone, unlike when\nplacing it on the right side of the magnet jumper, in\nwhich case it will slowly fade to black instead.
$EndSCHEMATC
