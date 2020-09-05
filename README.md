# Arcade-Spinner
Arcade Spinner version 2 - based off 'jmtw000' version

Updated readme from 'jmtw000' version with different component list...

This is an Arduino Pro Micro clone, arcade spinner, with 8 buttons (up to 10) for use with MAME or any other emulator which can use the X axis of the mouse as a paddle/spinner controller. This code should also work on any board which uses the ATmega32U4 as long as the port pins are mapped to the same "digital pins" as the Micro. I created this spinner because I wanted a cheaper alternative to the commercially available ones. I find it works well for ball and paddle games, Tempest, and also makes a decent controller for driving games.

To construct this you will need a 2-phase rotary encoder which can operate at 5v and some momentary switch buttons plus micro controller. 
Rotary encoder used: https://www.amazon.ca/gp/product/B00IJ788AA/ref=ppx_yo_dt_b_asin_title_o07_s00?ie=UTF8&psc=1 
However, any 2-phase 5v one should work. 
You can even use the little 20-30 position encoders that come with a lot of Arduino kits, although you'll have to alter the code and I don't recommend using those. 
Wheel:      https://www.amazon.ca/gp/product/B07DPDJHR6/ref=ppx_yo_dt_b_asin_title_o06_s00?ie=UTF8&psc=1
ATmega32U4: https://www.amazon.ca/gp/product/B01N4TVIQX/ref=ppx_yo_dt_b_asin_title_o02_s00?ie=UTF8&psc=1 
Arcade Box: https://www.amazon.ca/gp/product/B07HRS9BFK/ref=ppx_yo_dt_b_asin_image_o01_s00?ie=UTF8&psc=1

You will also need the Arduino joystick library available at: https://github.com/MHeironimus/ArduinoJoystickLibrary

This device will be detected as both a mouse and a joystick/gamepad. The joystick only has X and Y axes which we don't use. At least one axis is needed by the library to declare the joystick and it was found that 2 were required for the controller to be detected on some systems (RetroPi). We just center the X and Y axes in setup() and forget about them. The spinner controls the mouse X axis which is by default mapped to the analog dial in MAME (don't forget to enable the mouse in MAME under advanced options!). The buttons will work as regular gamepad/joystick buttons. The 2400 different positions (transitions) that can be detected on the 600ppr(pulse per revolution) encoder I'm using are way too many for our purposes so they are halved in the code to 1200. The code uses the Atmega32u4 ports directly because that's faster than using digitalRead/Write. I'm not doing any debouncing of the buttons or encoder as it seems to work great for me as is, but you might want to add debouncing depending on your hardware.
