## **Arcade-Spinner** 
Arcade Spinner version 2 - based off earlier Spinner <br/><br/>
[![Spinner](Pics/IMG_3830.jpg)](Pics/IMG_3830a.jpg)  
**Using an Arduino Pro Micro - DIY Spinner Controller, plus affordable Rotary Encoder**  
I decided to post my version of code including 'compiler control directive code' for rotary encoder (spinner) movement, and addition of extra buttons that a standard fight box had pre-configured cut holes (6-30mm & 2-24mm). The code works with Arduino Pro Micro style boards made by clone manufacturers using the Atmel ATmega32U4 MCU with native USB HID support. The original 2019 code was posted by 'jmtw000'. In time, Joe's code mutated to be used with Arduino Micro, Adafruit Itsy Bitsy, and other style boards that have extra pinouts unused by status LEDs. You will not find pins 11, 12, and 13 (also SS, 3V, Aref, A4, A5 & 2-NCs) on an Arduino [Pro Micro](Pics/Arduino%20Pro%20Micro%20Atmega32u4.jpg) board (length saving of 0.66") but pins 14, 15, and 16 (MISO/SCLK/MOSI). They appear to be mapped to different ATMega Portx bits. <br/>
A simplified chinese knock-off Rotary Encoder (Optical version) of an industrial Omron E6B2-CWZ6C encoder costing hundreds can be obtained from online stores around $30. Investigate purchase wisely as quality and standardization may vary. Ditto for selection of Arduino Pro Micro boards compatible to Sparkfun board, making sure you get 5V/16MHz version with pre-installed bootloader and pin headers. An USB 2.0 type A-to-MicroB cable of 3 to 6 feet will be needed, and not a two conductor charge cable. Note: There seems to be two common boot loaders used on clone Pro Micro boards, SparkFun Caterina Pro Micro version and Arduino Leonardo version.  
Here are some brandname Arduino boards:  
* Arduino [Micro](Pics/Arduino%20Micro%20(Adafruit).jpg) by Arduino Srl & Adafruit  
* Arduino [Micro](Pics/Adafruit%20ItsyBitsy%20-%20Arduino%20Micro.jpg), Adafruit ItsyBitsy  
* Arduino [Pro Micro](Pics/Arduino%20Pro%20Micro%20(SparkFun).jpg) by SparkFun

**Sept. 5/20:**  Uploaded my version of code from 2019; sourced June 27/19 and modified/optimized/bug fixed during summer 2019.<br/>
**Sept. 11/20:** Uploaded revised code to allow switching of Spinner's X & Y axis - mod axisFlip directive to setup special button of choice. <br/>
**Dec. 11/20:**  Uploaded new code for Mouse only Spinner operation. Note: all buttons can be inactivated for Spinner-Only operation.  
**Dec. 16/20:**  Uploaded new code for override Joystick directions mod (using buttons for menu)  
**Dec. 11/22:**  Uploaded new code for Mouse only Spinner operation. (Stand alone Arcade Spinner - no LCR mouse or joystick buttons)  
**Dec. 20/22:**  Uploaded new code for Mouse vari-SpinSpeed Spinner (can be used in MiSTer FPGA Cores where device too sensitive)  
**Nov.  2023:**  Uploaded debug code to diagnose wire connections (<sub>Need +5V/Gnd/A or B for error message, power/voltage dropout issues & non-movement</sub>)<br/>
**TBD.  2025:**  Uploaded new code for Rotary Encoders with odd PPR values - Ratio'd (fixed) Input-to-Output Spinners hybrid of vari-SpinSpeed code

This project uses an Arduino Pro Micro clone, arcade spinner, with 8 buttons (up to 10). It maybe used with MAME or any other emulator which can use the mouse X-axis as a paddle/spinner controller. Code should work on any board using an ATmega32U4 as long as port pins are mapped to same “digital pins” as Pro Micro. The DIY spinner was created as a cheaper alternative to commercially available devices. It works well with ball and paddle games, like Arkanoid, ever popular shooter Tempest, driving game like Pitstop and many other non-joystick controller games.

To construct this, you will need a 2-phase rotary encoder which can operate at 5v along with your momentary switches affixed to an Arduino micro-controller like SparkFun Pro Micro - 5V version or similar clone.<br/> 
[**Rotary encoder** used](https://www.amazon.ca/gp/product/B00IJ788AA/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&psc=1) 
[<sub>1</sub>](/Pics/Spinner_600ppr.jpg) 
[<sub>2</sub>](/Pics/Spinner_600ppr_2.jpg) (600 pulses/rev quadrature optical encoder = 2400 pulse spinner)<br/>
[**Wheel** used](https://www.amazon.ca/CNBTR-200mmx6mm-Aluminum-Industrial-Encoder/dp/B073P21D6W/ref=pd_rhf_se_p_img_5?_encoding=UTF8&refRID=NPXGEGRH2GHYJ6V9KG9V&th=1)
[](https://www.amazon.ca/gp/product/B07DPDJHR6/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1) 
[<sub>1</sub>](/Pics/200mm_Aluminum_Wheel.jpg) 
[<sub>2</sub>](/Pics/200mm_Aluminum_Wheel_2.jpg) (Generous 2.5" dia. aluminum/rubber weighted spinner, better than 1" guitar knobs)<br/>
[Alternate **Knob**](https://www.amazon.ca/gp/product/B087M2QCC2?ref=ppx_pt2_dt_b_prod_image)
[<sub>1</sub>](/Pics/Mxuteuk_Black_AL_Knob_Top.jpg) 
[<sub>2</sub>](/Pics/Mxuteuk_Black_AL_Knob_Side.jpg) 
[<sub>3</sub>](/Pics/Mxuteuk_Black_AL_Knob_Bottom.jpg) (1.5" dia. aluminum 32g spinner knob for Breakout/Arkanoid)<br/>
[**ATmega32U4** used](https://www.amazon.ca/gp/product/B01N4TVIQX/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1) 
[<sub>1</sub>](Pics/Arduino%20Pro%20Micro%20Atmega32u4.jpg) (clone of SparkFun Pro Micro) <br/> 
[**Arcade Box** used](https://www.amazon.ca/Acrylic-Arcade-Combination-Fighting-Computer/dp/B0B4X62FK9/ref=sr_1_25?crid=2DW3BTJZ9Q4NV&keywords=Black+Acrylic+Arcade&qid=1679618400&s=toys&sprefix=black+acrylic+arcade%2Ctoys%2C85&sr=1-25)
[](https://www.amazon.ca/gp/product/B07HRS9BFK/ref=ppx_yo_dt_b_asin_image_o01_s00?ie=UTF8&psc=1) 
[<sub>1</sub>](/Pics/Fightbox.jpg) (convenient plastic fightstick box)<br/><br/>

**How does a Spinner work**  
Simple explaination, a spinner is a digital rotary encoder of either x or y axis, acting as quadrature input device. Turning the spinner knob by hand directly twists/turns the rotary encoder. A rotary encoder have dual A & B phases with low/high or high/low signal transistions. One phase will always follow another phase due to a physical offset with a complete cycle producing 4 pulses (A<sub>L→H</sub>, B<sub>L→H</sub>, A<sub>H→L</sub>, B<sub>H→L</sub>, repeat) or quadrature signal. Only two temperal AB states (before/after) require capturing of AB or BA signals to decipher eight valid sequences out of sixteen total combinations. Two sets of four will indicate clockwise or counter-clockwise movement and bring about state machine logic. A signal of AA, BB or similar will suggest invalid transitions or bounce states and should be ignored.  
clockwise   (A<sub>L→H</sub>, B<sub>L→H</sub>, A<sub>H→L</sub>, B<sub>H→L</sub>)  
A<sub>L→H</sub> **:** A<sub>L</sub>B<sub>L</sub>A<sub>H</sub>B<sub>L</sub>, B<sub>L→H</sub> **:** A<sub>H</sub>B<sub>L</sub>A<sub>H</sub>B<sub>H</sub>, 
A<sub>H→L</sub> **:** A<sub>H</sub>B<sub>H</sub>A<sub>L</sub>B<sub>H</sub>, B<sub>H→L</sub> **:** A<sub>L</sub>B<sub>H</sub>A<sub>L</sub>B<sub>L</sub>  
counter-clockwise (B<sub>L→H</sub>, A<sub>L→H</sub>, B<sub>H→L</sub>, A<sub>H→L</sub>)  
B<sub>L→H</sub> **:** A<sub>L</sub>B<sub>L</sub>A<sub>L</sub>B<sub>H</sub>, A<sub>L→H</sub> **:** A<sub>L</sub>B<sub>H</sub>A<sub>H</sub>B<sub>H</sub>,
B<sub>H→L</sub> **:** A<sub>H</sub>B<sub>H</sub>A<sub>H</sub>B<sub>L</sub>, A<sub>H→L</sub> **:** A<sub>H</sub>B<sub>L</sub>A<sub>L</sub>B<sub>L</sub> 
<br/><br/>

You will need Arduino joystick library at: [https://github.com/MHeironimus/ArduinoJoystickLibrary](https://github.com/MHeironimus/ArduinoJoystickLibrary) <br/>
Matthew Heironimus joystick code: [Joystick.cpp](https://github.com/MHeironimus/ArduinoJoystickLibrary/blob/master/src/Joystick.cpp) & 
[Joystick.h](https://github.com/MHeironimus/ArduinoJoystickLibrary/blob/master/src/Joystick.h) or 
Download: [master.zip](https://github.com/MHeironimus/ArduinoJoystickLibrary/archive/master.zip)  
In Arduino IDE:
- Select Sketch 
- Include Library 
- Add .ZIP Library... 
- Browse to downloaded ZIP file 
- Click Open

The Joystick library's examples will now appear under File > Examples > Joystick. <br/><br/>

This device will be detected as both mouse and gamepad/joystick. RetroPie requires joystick X/Y axes to be declared in library call for controller buttons to be detected. Just center X/Y axes in setup() and forget, later code versions use Button/Joystick override for RetroArch menu navigation. The spinner controls X-axis which by default is mapped to the mouse/analog dial in MAME (don't forget to enable mouse in MAME under advanced options!). Buttons will work as regular gamepad/joystick buttons. The spinner produces 2400 Quadrature pulses (transitions) from a 600ppr(pulse per revolution) encoder; that is excessive, so, the code halves the count to 1200. Code uses Atmega32u4 ports directly because that’s faster (over x30) than using digitalRead/Write. No button debouncing is setup, but can be added depending on your hardware issues.<br/><br/>

**Extra info:**<br/>
Wiring: [See diagram](Pics/Spinner%20Sketch_bb.jpg)<br/>
Vcc (+5V) and Gnd, Spinner A & B rotary output wires red and green. [see picture](Pics/Inside%20guts%20of%20spinner.jpg) <br/>
I advise you double check Vcc(5-24v power) & Gnd wire colours as some chinese factories are colour blind. <br/>
<sub>DC Current per I/O Pin ………………………………. max 40.0 mA</sub>  
<sup>DC Current VCC and GND Pins …………………. max 200.0 mA</sup>  
Note: resistor used in series to limit current around 10mA - [**Pop goes the Triode**](x_file.md)  
<sup>Different currents = 5V / RΩ → 22.7mA (220Ω), 18.5mA (270Ω), 15.2mA (330Ω), 12.8mA (390Ω), 10.6mA (470Ω)</sup> <br/>
Heed the manufacture's warning (Atmel Corp. now Microchip) and never short a pin to Gnd or Vcc. It's safer to limit unknown current flow.<br/>
<sup>I have used an USB meter that contradicts any major current change when input pins are pulled high internally by ATmega32U4 MCU and shorted to Gnd.</sup><BR/>

Using rotary encoder H38S360B, 5-24V {wiring: *A-Red, B-Grn, Vcc-Wht, Gnd-Blk*} <br/>
<sup>This rotary encoder was originally shipped in error with wrong specs of 360 ppr, resulting in sluggish/slower top spin.</sup> <br/>

Wire |English |Chinese |Simplified	
---- |------- |------- |---------- 
Vcc	 |White		|白色的	 |白色的	
Gnd	 |Black		|黑色的	 |黑色的	
A/2  |Red			|紅色的	 |红色的	
B/3	 |Green		|綠色的	 |绿色的 
---  |Coloured| 色的  <br/>

<br/>Using rotary encoder HQK38H6-600N-G5-24 {Alternate wiring: *A-Grn, B-Wht, Vcc-Red, Gnd-Blk*} <br/>
<sup>Note: On Pro Micro, J1 may require solder short to bypass diode/regulator, so rotary encoder electronics receive full 5V USB source.</sup> <br/>

Wire |English |Chinese |Simplified	
---- |------- |------- |---------- 
Vcc  |Red			|紅色的	 |红色的	
Gnd	 |Black		|黑色的	 |黑色的	
A/2	 |White		|白色的	 |白色的	
B/3	 |Green		|綠色的	 |绿色的 
---  |Coloured| 色的  <br/>

<br/>Buttons 1-6(turned CW 'S-pattern'), plus 9-select(coin), and 10-start(player)<br/>

Pin |Data |Button/wire  |Code  
--- |---- |------------ |----  
2   |D2   |X<sub>A</sub> spinner - see  |PinA  
3   |D3   |X<sub>B</sub> spinner - above |PinB  
4   |D4   |Button 1 - X
5   |D5   |Button 2 - A
6   |D6   |Button 3 - B
7   |D7   |Button 4 - Y
8   |D8   |Button 5 - L
9   |D9   |Button 6 - R
10  |D10  |Button 9 - Select
15  |D15  |Button 10 - Start
Gnd |     |Gnd - Black/Blk
Vcc |     |+5v - Red/see above
16  |D16  |Switch: Axis Flip Opt.
14  |D14  |Switch: Joystick Opt. <br/>

I am using Xbox A/B, X/Y configuration, Nintendo protocol is B/A, Y/X reversed controls. (Japanese cultural differences) 
You can assign buttons to any assignment in RetroArch but it is best to pick a consistent pattern across all controllers to avoid confusion. I searched the web for button layout, picked an Xbox A/B, X/Y sideways 'S-pattern' starting at top left, yes a fluke.  
<br/>
My [Finished Spinner](Pics/CraigB's%20Spinner.jpg) assembled within a DIY Fight Stick box.  
Some [trouble shooting](trouble_shoot.md) with your controller  
<br/>
**The Code:**<br/>
There are five versions of code: Pick your code to use
- Standard Mouse and Joystick buttons version  
  - [Spinner_8-Button.ino](Spinner_8-Button.ino)
- Special Mouse only version with & without Mouse buttons - no Joystick buttons  
  - [Spinner_L-C-R-Button_Special.ino](Spinner_L-C-R-Button_Special.ino)
- Standard Mouse and Joystick buttons version - mod Joystick directions (use buttons for menu)
  - [Spinner_8-Button-mod.ino](Spinner_8-Button-mod.ino)<sub> 1.</sub>
- Special Mouse only version - no buttons  
  - [Spinner_No-Button.ino](Spinner_No-Button.ino)
- Special Mouse vari-SpinSpeed version - 6 +2 +1 buttons  
  - [Spinner_6-Button-MiSTer.ino](Spinner_6-Button-MiSTer.ino)<br/>
- Standard Mouse and Joystick buttons version - Ratio (non 300/600/1200ppr but eg.360ppr) 
  - [Spinner_8-Button-Ratio.ino](Spinner_8-Button-Ratio.ino)<br/>
  - [Spinner_8-Button-Ratio-mod.ino](Spinner_8-Button-Ratio-mod.ino)<br/>
- Special Debug code - Spinner Error with invalid Quadrature signals  
  - [Spinner_Debug.ino](Spinner_Debug.ino)<br/>

<sub>1. Use of TTP223 Capacitive Touch switches to control special functions: the 
"[Touch Switches](Pics/Double%20Touch.jpg)"   
Note: Invert the Touch I/O state by shorting [contact A to Vcc](Pics/TTP223B_chip_side.jpg), and/or contact B to activate on/off toggle mode.</sub>  

**[Coin, Play & Special Buttons](https://craigb-spinner.github.io/Arcade-Spinner/Coin-Play-Exit.html)**<br/>
<br/>
**Oops - I bricked my [Bootloader](https://craigb-spinner.github.io/Arcade-Trackball/Changing_Fuse_Bits.html)!**  
<sup>Navigate to bottom of page - same title.</sup>

**Extra expenses:**  
Dupont connectors 2.54mm pitch JST SM kit (requires special crimper)  
or female Dupont pre-wired bundles (wire jumper) with spare wire 24-28AWG (stranded wire for flexiblity).  
Sanwa - 2.8mm(0.110") or Suzo-Happ - 4.8mm(0.187") female spade crimp connectors for arcade button ends.  
3 - 3x12mm Countersunk Machine Head Screws (sourced from Traxxas 2552 hobby parts); cut to length with dremel; uses same Allen wrench as grub screw with noted wheel.  
Lexan sheet 0.060" thick, size 95x53mm(3.75x2.1") or aluminum/steel sheet cut to same size of Sanwa JLF-P1 mounting plate. I don't recommend using joystick plate as holes are located at 90° and rotary encoder mounts at 120° (28-30mm dia. M3 mounts with 20mm dia. raised bearing hub).  
Clear Lexan makes visibility easier for fabrication.  
Special function switches with [TTP223 Capacitive Touch Switch](https://www.amazon.ca/gp/product/B07JDH7KHN/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)
<sub>[1](/Pics/Cap_touch.jpg)</sub><br/>

**For the more observant** in pictures ["Inside Spaghetti"](Special%20Testing%20Pics/Inside%20spaghetti.jpg) and ["Arduino Beauty Shot"](Special%20Testing%20Pics/Arduino%20beauty%20shot.jpg) there's an extra wire harness and aligator clip hooking to Gnd. TX0 & RX1 are wired to the y-axis of a proto-type [Trackball](https://www.amazon.ca/gp/product/B00F1YQH6G/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1) setup. Arduino code has been modified, tested and confirmed to work. No stutter or lag as using only USB protocol to RetroPie. No PS/2 Protocol overhead. I will be working on enclosure to finish new controller for games like **Centipede**, **Marble Madness**, **Crystal Castles**, and others.  
See the Trackball project [here](https://craigb-spinner.github.io/Arcade-Trackball/)  

**Video:**  
[**Spinner in Action**](https://www.youtube.com/watch?v=HmqkHAPZHQA) playing **Tempest**<br/>

![RetroPie Logo](Pics/RetroPie%20Logo.png) RetroPie [laggy spinner/trackball](laggy_mouse.md) issues <br/>

How to configure [**MAME Games**](MAME_Game_Config.md) Spinner Sensitivity <br/>

**More pictures:**  
My Arcade Spinner assembled within a DIY Fight Stick box -  
"[Spin Shadow](Pics/Spin%20Shadow.jpg)", 
"[Spin HiLite](Pics/Spin%20HiLite.jpg)", 
"[Spin](Pics/Spin%20Full.jpg)", 
"[Spin Action Close](Pics/Spin%20Action%20Close.jpg)", 
"[Spin Action](Pics/Spin%20Action%20Full.jpg)"  
