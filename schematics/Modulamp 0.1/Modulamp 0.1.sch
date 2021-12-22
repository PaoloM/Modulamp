EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
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
L Connector:Conn_01x04_Male J?
U 1 1 61C178B5
P 2600 2050
F 0 "J?" H 2708 2331 50  0000 C CNN
F 1 "Line 1 input" H 2708 2240 50  0000 C CNN
F 2 "" H 2600 2050 50  0001 C CNN
F 3 "~" H 2600 2050 50  0001 C CNN
	1    2600 2050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 61C1A766
P 3100 3050
F 0 "J?" H 3208 3331 50  0000 C CNN
F 1 "Line 2 input" H 3208 3240 50  0000 C CNN
F 2 "" H 3100 3050 50  0001 C CNN
F 3 "~" H 3100 3050 50  0001 C CNN
	1    3100 3050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male J?
U 1 1 61C1B377
P 6900 2700
F 0 "J?" H 7008 2981 50  0000 C CNN
F 1 "Conn_01x04_Male" H 7008 2890 50  0000 C CNN
F 2 "" H 6900 2700 50  0001 C CNN
F 3 "~" H 6900 2700 50  0001 C CNN
	1    6900 2700
	1    0    0    -1  
$EndComp
$Comp
L Relay:G5V-1 K?
U 1 1 61C1DD41
P 4400 2200
F 0 "K?" V 3833 2200 50  0000 C CNN
F 1 "G5V-1" V 3924 2200 50  0000 C CNN
F 2 "Relay_THT:Relay_SPDT_Omron_G5V-1" H 5530 2170 50  0001 C CNN
F 3 "http://omronfs.omron.com/en_US/ecb/products/pdf/en-g5v_1.pdf" H 4400 2200 50  0001 C CNN
	1    4400 2200
	0    -1   1    0   
$EndComp
Text GLabel 4100 2500 0    50   Input ~ 0
LIN1L+
Text GLabel 2800 1950 2    50   Input ~ 0
LIN1L+
Text GLabel 2800 2050 2    50   Input ~ 0
LIN1L-
Text GLabel 2800 2150 2    50   Input ~ 0
LIN1R-
Text GLabel 2800 2250 2    50   Input ~ 0
LIN1R+
Text GLabel 4700 2400 2    50   Output ~ 0
OUTL
Text GLabel 7100 2600 2    50   Output ~ 0
OUTL
$Comp
L power:GNDA #PWR?
U 1 1 61C21E6A
P 4550 4100
F 0 "#PWR?" H 4550 3850 50  0001 C CNN
F 1 "GNDA" H 4555 3927 50  0000 C CNN
F 2 "" H 4550 4100 50  0001 C CNN
F 3 "" H 4550 4100 50  0001 C CNN
	1    4550 4100
	1    0    0    -1  
$EndComp
$EndSCHEMATC
