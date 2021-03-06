## **Arcade-Spinner** 
Arcade Spinner version 2 - based off earlier 'jmtw000' version <br/><br/>
![Spinner](Pics/IMG_3830.jpg)  
**Using an Arduino Pro Micro - DIY Spinner Controller, plus affordable Rotary Encoder**  
I decided to post my version of code including 'compiler control directive code' for rotary encoder (spinner) movement, and addition of extra buttons that a standard fight box had pre-configured cut holes (6-30mm & 2-24mm). The code works with Arduino Pro Micro style boards made by clone manufacturers. The original code posted by 'jmtw000' has mutated to be used with Arduino Micro, Adafruit Itsy Bitsy, and other style boards that have extra pinouts unused by status LEDs. You will not find pins 11, 12, and 13 (also SS, 3V, Aref, A4, A5 & 2-NCs) on an  Arduino [Pro Micro](Pics/Arduino%20Pro%20Micro%20Atmega32u4.jpg) board (length saving of 0.66") but pins 14, 15, and 16 (MISO/SCLK/MOSI). They appear to be mapped to different ATMega Portx bits.  
A simplified chinese knock-off Rotary Encoder (Optical version) of an industrial Omron E6B2-CWZ6C encoder costing hundreds can be obtained from online stores around $30. Investigate purchase wisely as quality and standardization may vary. Ditto for selection of Arduino Pro Micro boards compatible to Sparkfun board, making sure you get 5V/16MHz version with pre-installed bootloader and pin headers. An USB 2.0 type A-to-MicroB cable of 3 to 6 feet will be needed, and not a two conductor charge cable.  
Here are some brandname Arduino boards:  
* Arduino [Micro](Pics/Arduino%20Micro%20(Adafruit).jpg) by Arduino Srl & Adafruit  
* Arduino [Micro](Pics/Adafruit%20ItsyBitsy%20-%20Arduino%20Micro.jpg), Adafruit ItsyBitsy  
* Arduino [Pro Micro](Pics/Arduino%20Pro%20Micro%20(SparkFun).jpg) by SparkFun

**Sept. 5/20:**  Uploaded my version of code from 2019; sourced June 27/19 and modified/optimized/bug fixed during summer 2019.<br/>
**Sept. 11/20:** Uploaded revised code to allow switching of Spinner's X & Y axis - mod axisFlip directive to setup special button of choice. <br/>
**Dec. 11/20:**  Uploaded new code for Mouse only Spinner operation. Note: all buttons can be inactivated for Spinner-Only operation.  
**Dec. 16/20:**  Uploaded new code for override Joystick directions mod (using buttons for menu)<br/>

This project uses an Arduino Pro Micro clone, arcade spinner, with 8 buttons (up to 10). It maybe used with MAME or any other emulator which can use the mouse X-axis as a paddle/spinner controller. Code should work on any board using an ATmega32U4 as long as port pins are mapped to same “digital pins” as Pro Micro. The DIY spinner was created as a cheaper alternative to commercially available devices. It works well with ball and paddle games, like Arkanoid, ever popular shooter Tempest, driving game like Pitstop and many other non-joystick controller games.

To construct this, you will need a 2-phase rotary encoder which can operate at 5v along with your momentary switches affixed to an Arduino micro-controller like SparkFun Pro Micro - 5V version or similar clone.<br/> 
[**Rotary encoder** used](https://www.amazon.ca/gp/product/B00IJ788AA/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&psc=1) 
[<sub>1</sub>](/Pics/Spinner_600ppr.jpg) 
[<sub>2</sub>](/Pics/Spinner_600ppr_2.jpg) (600 pulses/rev quadrature optical encoder = 2400 pulse spinner)<br/>
[**Wheel** used](https://www.amazon.ca/CNBTR-200mmx6mm-Aluminum-Industrial-Encoder/dp/B073P21D6W/ref=pd_rhf_se_p_img_5?_encoding=UTF8&refRID=NPXGEGRH2GHYJ6V9KG9V&th=1)
[](https://www.amazon.ca/gp/product/B07DPDJHR6/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1) 
[<sub>1</sub>](/Pics/200mm_Aluminum_Wheel.jpg) 
[<sub>2</sub>](/Pics/200mm_Aluminum_Wheel_2.jpg) (Generous 2.5" dia. aluminum/rubber weighted spinner, better than 1" guitar knobs)<br/>
[**ATmega32U4** used](https://www.amazon.ca/gp/product/B01N4TVIQX/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1) (clone of SparkFun Pro Micro)<br/> 
[**Arcade Box** used](https://www.amazon.ca/gp/product/B07HRS9BFK/ref=ppx_yo_dt_b_asin_image_o01_s00?ie=UTF8&psc=1) 
[<sub>1</sub>](/Pics/Fightbox.jpg) (convenient plastic fightstick box)<br/><br/>

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
Vcc (+5V) and Gnd<br/>
Spinner A & B rotary output wires red and green. [see picture](Pics/Inside%20guts%20of%20spinner.jpg) <br/>
Note: resistor used in series to limit current around 10mA (390Ω	- 470Ω)  
I advise you double check Vcc(5-24v power - Wht) and Gnd(Blk) wire colours as some chinese factories are colour blind. {Alternate wiring: *A-Grn, B-Wht, Vcc-Red, Gnd-Blk*}<br/>
Buttons 1-6, plus 9-select(coin), and 10-start(player)<br/>

Pin |Data |Button/wire  |Code  
--- |---- |------------ |----  
2   |D2   |X<sub>A</sub> spinner - Red |PinA  
3   |D3   |X<sub>B</sub> spinner - Green |PinB  
4   |D4   |Button 1 - X
5   |D5   |Button 2 - A
6   |D6   |Button 3 - B
7   |D7   |Button 4 - Y
8   |D8   |Button 5 - L
9   |D9   |Button 6 - R
10  |D10  |Button 9 - Select
15  |D15  |Button 10 - Start
Gnd |     |Gnd - Black/Blk
Vcc |     |+5v - Red/White
16  |D16  |Switch: Axis Flip Opt.
14  |D14  |Switch: Joystick Opt. <br/>

I am using Xbox A/B, X/Y configuration, Nintendo protocol is B/A, Y/X reversed controls. (Japanese cultural differences) 
You can assign buttons to any assignment in RetroArch but it is best to pick a consistent pattern across all controllers to avoid confusion.  
<br/>
My [Finished Spinner](Pics/CraigB's%20Spinner.jpg) assembled within a DIY Fight Stick box.  
Some [trouble shooting](trouble_shoot.md) with your controller  
<br/>
**The Code:**<br/>
There are three versions of code: Pick your code to use
- Standard Mouse and Joystick buttons version  
  - [Spinner_8-Button.ino](Spinner_8-Button.ino)
- Special Mouse only version with & without Mouse buttons - no Joystick buttons  
  - [Spinner_L-C-R-Button_Special.ino](Spinner_L-C-R-Button_Special.ino)
- Standard Mouse and Joystick buttons version - mod Joystick directions (use buttons for menu)
  - [Spinner_8-Button-mod.ino](Spinner_8-Button-mod.ino)<sub> 1.</sub><br/>

<sub>1. Use of TTP223 Capacitive Touch switches to control special functions: the 
"[Touch Switches](Pics/Double%20Touch.jpg)"   
Note: Invert the Touch I/O state by shorting [contact A to Vcc](Pics/TTP223B_chip_side.jpg), and/or contact B to activate on/off toggle mode.</sub>  

**Extra expenses:**  
Dupont connectors 2.54mm pitch JST SM kit (requires special crimper)  
or female Dupont pre-wired bundles (wire jumper) with spare wire 24-28AWG (stranded wire for flexiblity).  
Sanwa - 2.8mm(0.110") or Suzo-Happ - 4.8mm(0.187") female spade crimp connectors for arcade button ends.  
3 - 3x12mm Countersunk Machine Head Screws (sourced from Traxxas 2552 hobby parts); cut to length with dremel; uses same Allen wrench as grub screw with noted wheel.  
Lexan sheet 0.060" thick, size 95x53mm(3.75x2.1") or aluminum/steel sheet cut to same size of Sanwa JLF-P1 mounting plate. I don't recommend using joystick plate as holes are located at 90° and rotary encoder mounts at 120° (28-30mm dia. M3 mounts with 20mm dia. raised bearing hub).  
Clear Lexan makes visibility easier for fabrication.  
Special function switches with [TTP223 Capacitive Touch Switch](https://www.amazon.ca/gp/product/B07JDH7KHN/ref=ppx_yo_dt_b_asin_title_o05_s00?ie=UTF8&psc=1)<br/>

**For the more observant** in pictures ["Inside Spaghetti"](Special%20Testing%20Pics/Inside%20spaghetti.jpg) and ["Arduino Beauty Shot"](Special%20Testing%20Pics/Arduino%20beauty%20shot.jpg) there's an extra wire harness and aligator clip hooking to Gnd. TX0 & RX1 are wired to the y-axis of a proto-type [Trackball](https://www.amazon.ca/gp/product/B00F1YQH6G/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1) setup. Arduino code has been modified, tested and confirmed to work. No stutter or lag as using only USB protocol to RetroPie. No PS/2 Protocol overhead. I will be working on enclosure to finish new controller for games like **Centipede**, **Marble Madness**, **Crystal Castles**, and others.  
See the Trackball project [here](https://craigb-spinner.github.io/Arcade-Trackball/)  

**Video:**  
[**Spinner in Action**](https://www.youtube.com/watch?v=HmqkHAPZHQA) playing **Tempest**<br/>

![RetroPie Logo](Pics/RetroPie%20Logo.png) RetroPie [laggy spinner/trackball](laggy_mouse.md) issues

**More pictures:**  
My Arcade Spinner assembled within a DIY Fight Stick box -  
"[Spin Shadow](Pics/Spin%20Shadow.jpg)", 
"[Spin HiLite](Pics/Spin%20HiLite.jpg)", 
"[Spin](Pics/Spin%20Full.jpg)", 
"[Spin Action Close](Pics/Spin%20Action%20Close.jpg)", 
"[Spin Action](Pics/Spin%20Action%20Full.jpg)"  
