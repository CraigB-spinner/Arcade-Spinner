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
`Control Panel`,  
in `Search` Type *joy*,  
under `Devices and Printers` Click *Set up USB game controllers*,  
Click `Properties`  


a
<br/>
b

**Add:**  
*usbhid.mousepoll=0*  
to *cmdline.txt*

This parameter enforces a mouse polling rate of ? 62.5Hz ? and reduces any quick movement lag.  
