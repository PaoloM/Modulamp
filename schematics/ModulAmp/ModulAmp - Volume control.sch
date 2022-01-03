EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
Title "ModulAmp"
Date ""
Rev "1.0"
Comp "Paolo Marcucci"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 2500 4050 0    50   Input ~ 0
LINEIN_L
Text HLabel 2500 4150 0    50   Input ~ 0
LINEIN_G
Text HLabel 2500 4250 0    50   Input ~ 0
LINEIN_R
Text HLabel 9500 4050 2    50   Input ~ 0
LINEOUT_L
Text HLabel 9500 4150 2    50   Input ~ 0
LINEOUT_G
Text HLabel 9500 4250 2    50   Input ~ 0
LINEOUT_R
Text HLabel 4300 1750 1    50   Input ~ 0
+5V
Text HLabel 4400 1750 1    50   Input ~ 0
GND
Text HLabel 5650 1750 1    50   Input ~ 0
+5Va
Text HLabel 5750 1750 1    50   Input ~ 0
GNDA
Text HLabel 5550 6100 3    50   Input ~ 0
CS
Text HLabel 5650 6100 3    50   Input ~ 0
SDI
Text HLabel 5750 6100 3    50   Input ~ 0
SCLK
Text HLabel 5850 6100 3    50   Input ~ 0
SDO
$Comp
L SparkFun-Capacitors:10UF-POLAR-RADIAL-2.5MM-25V-20% C?
U 1 1 61DD0793
P 7050 2350
AR Path="/61D3C794/61DD0793" Ref="C?"  Part="1" 
AR Path="/61D3C777/61DD0793" Ref="C2"  Part="1" 
F 0 "C2" H 7178 2395 45  0000 L CNN
F 1 "10UF-POLAR-RADIAL-2.5MM-25V-20%" H 7178 2311 45  0000 L CNN
F 2 "CPOL-RADIAL-2.5MM-5MM" H 7050 2600 20  0001 C CNN
F 3 "" H 7050 2350 50  0001 C CNN
F 4 "CAP-08440" H 7178 2216 60  0000 L CNN "Field4"
	1    7050 2350
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Capacitors:10UF-POLAR-RADIAL-2.5MM-25V-20% C?
U 1 1 61DD079A
P 5750 2800
AR Path="/61D3C794/61DD079A" Ref="C?"  Part="1" 
AR Path="/61D3C777/61DD079A" Ref="C1"  Part="1" 
F 0 "C1" H 5878 2845 45  0000 L CNN
F 1 "10UF-POLAR-RADIAL-2.5MM-25V-20%" H 5878 2761 45  0000 L CNN
F 2 "CPOL-RADIAL-2.5MM-5MM" H 5750 3050 20  0001 C CNN
F 3 "" H 5750 2800 50  0001 C CNN
F 4 "CAP-08440" H 5878 2666 60  0000 L CNN "Field4"
	1    5750 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 2200 7050 2250
Wire Wire Line
	7050 2600 7050 2550
Wire Wire Line
	5750 3000 6500 3000
Wire Wire Line
	7300 3000 7300 2000
Wire Wire Line
	6400 2800 6400 3150
Wire Wire Line
	5500 3150 6400 3150
Wire Wire Line
	5750 2500 5750 2700
NoConn ~ 6000 2300
Connection ~ 5750 2500
Wire Wire Line
	5500 2500 5500 3150
Wire Wire Line
	7300 2000 6800 2000
Wire Wire Line
	6000 2500 5750 2500
Wire Wire Line
	6800 2600 7050 2600
Wire Wire Line
	6800 2200 7050 2200
$Comp
L Regulator_SwitchedCapacitor:MAX1044 U?
U 1 1 61DD078C
P 6400 2300
AR Path="/61D3C794/61DD078C" Ref="U?"  Part="1" 
AR Path="/61D3C777/61DD078C" Ref="U1"  Part="1" 
F 0 "U1" H 6400 2867 50  0000 C CNN
F 1 "MAX1044" H 6400 2776 50  0000 C CNN
F 2 "" H 6500 2200 50  0001 C CNN
F 3 "http://datasheets.maximintegrated.com/en/ds/ICL7660-MAX1044.pdf" H 6500 2200 50  0001 C CNN
	1    6400 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 2500 5750 2500
Wire Wire Line
	5750 1750 5750 2500
Wire Wire Line
	5650 1750 5650 2000
Wire Wire Line
	5650 2000 6000 2000
Wire Wire Line
	6400 3150 6400 3350
Connection ~ 6400 3150
Wire Wire Line
	6500 3000 6500 3350
Connection ~ 6500 3000
Wire Wire Line
	6500 3000 7300 3000
$EndSCHEMATC
