DC Characteristics <BR/> 
DC Current per I/O Pin ........................... max  40.0 mA  
DC Current VCC and GND Pins....................... max 200.0 mA  
-----------------------------------------------------------------------------------------------------------------------------
**VOL Output Low Voltage**,  
IOL = 10mA, VCC = 5V, ............................... max 0.7V  
IOL =  5mA, VCC = 3V, ............................... max 0.5V  

Although each I/O port can sink more than the test conditions (20mA at VCC = 5V, 10mA at VCC = 3V) under steady state
conditions (non-transient), the following must be observed:
ATmega16U4/ATmega32U4:
1.)The sum of all IOL, for ports A0-A7, G2, C4-C7 should not exceed 100 mA.
2.)The sum of all IOL, for ports C0-C3, G0-G1, D0-D7 should not exceed 100 mA.
3.)The sum of all IOL, for ports G3-G5, B0-B7, E0-E7 should not exceed 100 mA.
4.)The sum of all IOL, for ports F0-F7 should not exceed 100 mA.
If IOL exceeds the test condition, VOL may exceed the related specification. Pins are not guaranteed to sink current greater
than the listed test condition.
-----------------------------------------------------------------------------------------------------------------------------
VOH Output High Voltage,
IOH = -10mA, VCC = 5V, ............................... min 4.2V
IOH =  -5mA, VCC = 3V, ............................... min 2.3V

Although each I/O port can source more than the test conditions (20mA at VCC = 5V, 10mA at VCC = 3V) under steady
state conditions (non-transient), the following must be observed:
ATmega16U4/ATmega32U4:
1)The sum of all IOH, for ports A0-A7, G2, C4-C7 should not exceed 100 mA.
2)The sum of all IOH, for ports C0-C3, G0-G1, D0-D7 should not exceed 100 mA.
3)The sum of all IOH, for ports G3-G5, B0-B7, E0-E7 should not exceed 100 mA.
4)The sum of all IOH, for ports F0-F7 should not exceed 100 mA.
