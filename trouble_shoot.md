**On your computer,**  
Start **ARDUINO-Genuino IDE**  
Install the joystick liabrary by Matthew Heironimus, and  
SparkFun's Pro Micro, ATmega32U4, micro-controller Arduino driver.  
Load one of the software Sketches downloaded from my page.  
Under **Tools**: setup `Board`, `Processor`, and `Port`.  
Configure any software Option by right-click and select Comment/Uncomment *#define* compiler directive.  
`Verify/Compile`  
`Upload` when compile is clean  

If upload is sucessful, you can now test your new controller.  
You may want to upload the blink Sketch to confirm communications is working between your computer and Arduino.

To test your new controller within windows:  
`Start`,  
`Control panel`,  
in `Search Type:` *joy*,  
Under `Devices and Printers:` Click on *Set up USB game controllers* then Properties  




**Add:**  
*usbhid.mousepoll=0*  
to *cmdline.txt*

`sudo nano /boot/cmdline.txt`  
on the same line separated from other stuff by spaces  
This parameter enforces a mouse polling rate of ? 62.5Hz ? and reduces any quick movement lag.  
**0** or **1** - 1000Hz, **2** - 500Hz, **4** - 250Hz, **8** - 125Hz, **16** - 62.5Hz  
(Micro-controller is updating mouse as fast as main loop() and any axes interrupt(s) being serviced. avg 40 - 100 µS)  

`sudo reboot`
