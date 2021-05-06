**On your computer,**  
Start **ARDUINO-Genuino IDE**  
Install the joystick library by Matthew Heironimus, and  
SparkFun's Pro Micro, ATmega32U4, micro-controller Arduino driver.  
Load one of the software Sketches downloaded from my page.  
Under **Tools**: setup `Board`, `Processor`, and `Port`.  
Configure any software Option by right-click and select '*Comment/Uncomment*' *#define* compiler directive.  
`Verify/Compile`  
`Upload` when compile is clean  

If upload is sucessful, you can now test your new controller.  
<sup>You may want to upload blink Sketch to confirm communications is working between your computer and Arduino.</sup>

To test your new controller within windows:  
`Start`,  
`Control Panel`,  
in `Search` Type *joy*,  
under `Devices and Printers` Click '*Set up USB game controllers*',  
Click `Properties`  

A button press will indicate activity of a button. If no button response, confirm wiring to button, and port. Remember in the code, button activity is active low due to hardware pull-up resistor used in Arduino MCU chip. Low is *On*, High is *Off*.  
Mouse pointer movement will confirm Spinner/Trackball activity; if there's no movement, validate +ve/-ve power connections along with both A/B connections. Quadrature line output require working A/B signal pulses to convey direction and movement (each axis has a pair of signals assigned to either X or Y axes).  
To change movement feel, select a different *#define* compiler directive within the code.
