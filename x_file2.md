<H2 align="center"><b> Atmel ATmega16U4/ATmega32U4 technical doc excerpt </b></H2>

**DC Characteristics** <BR/> <BR/> 
DC Current per I/O Pin ..................................... max  40.0 mA <BR/>
DC Current V<sub>CC</sub> and GND Pins ...................... max 200.0 mA <BR/>

-----------------------------------------------------------------------------------------------------------------------------

**V<sub>OL</sub> Output Low Voltage,** <BR/> 
I<sub>OL</sub> = 10mA, V<sub>CC</sub> = 5V, ............................... max 0.7V <BR/>
I<sub>OL</sub> =  5mA, V<sub>CC</sub> = 3V, ............................... max 0.5V <BR/> 

Although each I/O port can sink more than the test conditions (20mA at V<sub>CC</sub> = 5V, 10mA at V<sub>CC</sub> = 3V) <BR/>
under steady state conditions (non-transient), the following must be observed: ATmega16U4/ATmega32U4: <BR/>
1. The sum of all I<sub>OL</sub>, for ports A0-A7, G2, C4-C7 should not exceed 100 mA. <BR/>
2. The sum of all I<sub>OL</sub>, for ports C0-C3, G0-G1, D0-D7 should not exceed 100 mA. <BR/>
3. The sum of all I<sub>OL</sub>, for ports G3-G5, B0-B7, E0-E7 should not exceed 100 mA. <BR/>
4. The sum of all I<sub>OL</sub>, for ports F0-F7 should not exceed 100 mA. <BR/> 
 
If I<sub>OL</sub> exceeds the test condition, V<sub>OL</sub> may exceed the related specification. <BR/> 
Pins are not guaranteed to sink current greater than the listed test condition. <BR/>

-----------------------------------------------------------------------------------------------------------------------------

**V<sub>OH</sub> Output High Voltage,** <BR/>
I<sub>OH</sub> = -10mA, V<sub>CC</sub> = 5V, ............................... min 4.2V <BR/>
I<sub>OH</sub> =  -5mA, V<sub>CC</sub> = 3V, ............................... min 2.3V <BR/>

Although each I/O port can source more than the test conditions (20mA at V<sub>CC</sub> = 5V, 10mA at V<sub>CC</sub> = 3V) <BR/>
under steady state conditions (non-transient), the following must be observed: ATmega16U4/ATmega32U4: <BR/>
1. The sum of all I<sub>OH</sub>, for ports A0-A7, G2, C4-C7 should not exceed 100 mA. <BR/>
2. The sum of all I<sub>OH</sub>, for ports C0-C3, G0-G1, D0-D7 should not exceed 100 mA. <BR/>
3. The sum of all I<sub>OH</sub>, for ports G3-G5, B0-B7, E0-E7 should not exceed 100 mA. <BR/>
4. The sum of all I<sub>OH</sub>, for ports F0-F7 should not exceed 100 mA. <BR/>
