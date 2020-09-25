# Arcade-Spinner
Arcade Spinner version 2 - based off 'jmtw000' version <br/><br/>
**Sept. 5/20** Uploaded my version of code from 2019 <br/>
**Sept. 11/20** Uploaded revised code to allow switching of Spinner's X & Y axis - mod axisFlip directive to setup special button of choice. <br/><br/>
I decided to post my version of code including 'compiler control directive code' for rotary encoder (spinner) movement, and addition of extra buttons that a standard fight box had pre-configured cut holes (6-30mm & 2-24mm). The code is for a Arduino Pro Micro style boards made by a clone manufacturer. The original code posted by 'jmtw000' has mutated to be used with Arduino Micro, Adafruit Itsy Bitsy, and other style boards that have extra pinouts unused by status LEDs. You will not find pins 11, 12, and 13 on a   Arduino Pro Micro board but pins 14, 15, and 16. They appear to be mapped to different ATMega Port bits. 

Updated readme from 'jmtw000' version with different component list...

This is an Arduino Pro Micro clone, arcade spinner, with 8 buttons (up to 10) for use with MAME or any other emulator which can use the X axis of the mouse as a paddle/spinner controller. This code should also work on any board which uses the ATmega32U4 as long as the port pins are mapped to the same "digital pins" as the Micro. I created this spinner because I wanted a cheaper alternative to the commercially available ones. I find it works well for ball and paddle games, Tempest, and also makes a decent controller for driving games.

To construct this you will need a 2-phase rotary encoder which can operate at 5v and some momentary switch buttons plus Arduino micro controller.<br/> 
[**Rotary encoder** used](https://www.amazon.ca/gp/product/B00IJ788AA/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&psc=1)<br/>
However, any 2-phase 5v one should work. You can even use the little 20-30 position encoders that come with a lot of Arduino kits, although you'll have to alter the code and I don't recommend using those.<br/> 
[**Wheel** used](https://www.amazon.ca/gp/product/B07DPDJHR6/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1)<br/>
[**ATmega32U4** used](https://www.amazon.ca/gp/product/B01N4TVIQX/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1)<br/> 
[**Arcade Box** used](https://www.amazon.ca/gp/product/B07HRS9BFK/ref=ppx_yo_dt_b_asin_image_o01_s00?ie=UTF8&psc=1)<br/><br/>

You will also need the Arduino joystick library available at: https://github.com/MHeironimus/ArduinoJoystickLibrary<br/><br/>

This device will be detected as both a mouse and a joystick/gamepad. The joystick only has X and Y axes which we don't use. At least one axis is needed by the library to declare the joystick and it was found that 2 were required for the controller to be detected on some systems (RetroPi). We just center the X and Y axes in setup() and forget about them. The spinner controls the mouse X axis which is by default mapped to the analog dial in MAME (don't forget to enable the mouse in MAME under advanced options!). The buttons will work as regular gamepad/joystick buttons. The 2400 different positions (transitions) that can be detected on the 600ppr(pulse per revolution) encoder I'm using are way too many for our purposes so they are halved in the code to 1200. The code uses the Atmega32u4 ports directly because that's faster than using digitalRead/Write. I'm not doing any debouncing of the buttons or encoder as it seems to work great for me as is, but you might want to add debouncing depending on your hardware.<br/><br/>

**Extra info:**<br/>
Wiring: <br/>
Vcc (+5V) and Gnd<br/>
Spinner A & B rotary output wires red and green. see picture <br/>
Note: resistor used in series to limit current around 10mA (390Ω	- 470Ω)  
I advise you double check Vcc(5-24v power - Wht) and Gnd(Blk) wire colours as some chinese factories are colour blind.<br/>
Buttons 1-6, plus 9-select(coin), and 10-start(player)<br/>
Pin |Button/wire
--- |-----------
2   |A spinner
3   |B spinner
4   |Button 1 - X
5   |Button 2 - A
6   |Button 3 - B
7   |Button 4 - Y
8   |Button 5 - L
9   |Button 6 - R
10  |Button 9 - Select
15  |Button 10 - Start
Gnd |Gnd
Vcc |+5v  <br/>

I am using Xbox A/B, X/Y configuration, Nintendo protocol is B/A, Y/X reversed controls (Japanese cultural differences)  
You can assign buttons to any assignment in RetroArch but it is best to pick a consistent pattern across all controllers to avoid confusion.  <br/>
 
**Extra expenses:**  
Dupont connectors 2.54mm pitch JST SM kit (requires special crimper)  
or female Dupont pre-wired bundles with spare wire 24-28AWG (stranded wire for flexiblity)  
Sanwa - 2.8mm(0.110") or Suzo-Happ - 4.8mm(0.187") female spade crimp connectors for arcade button ends 
<br/><br/>
**For the more observant** in pictures "Inside Spaghetti" and "Arduino Beauty Shot" there's an extra wire harness and aligator clip hooking to Gnd. TX0 & RX1 are wired to the y-axis of a proto-type [Trackball](https://www.amazon.ca/gp/product/B00F1YQH6G/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1) setup. Arduino code has been modified, tested and confirmed to work. No stutter or lag as using only USB protocol to RetroPi. No PS/2 Protocol overhead. I will be working on enclosure to finish new controller for games like **Centipede**, **Marble Madness**, **Crystal Castles**, and others.  
