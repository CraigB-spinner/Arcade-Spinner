**On your computer,**  
Start **ARDUINO-Genuino IDE**  
Install the joystick library by Matthew Heironimus, and  
SparkFun's Pro Micro, ATmega32U4, micro-controller Arduino driver.  
A) GitHub [SparkFun Arduino boards](https://github.com/sparkfun/Arduino_Boards) source, 
B) [SparkFun Pro Micro](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide?_ga=2.142577458.1245326673.1620345098-474804601.1620345098#installing-windows) page  
Load one of the software Sketches downloaded from my page.  
Under **Tools**: setup `Board`, `Processor`, and `Port`.  
Configure any software Option by right-click  
and select '*Comment/Uncomment*' *#define* compiler directive.  
`Verify/Compile`  
`Upload` when compile is clean  

If upload is sucessful, you can now test your new controller.  
<sup>You may want to upload 
[blink Sketch](https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide?_ga=2.142577458.1245326673.1620345098-474804601.1620345098#example-1-blinkies) 
to confirm communications is working between your computer and Arduino.</sup>

To test your new controller within windows:  
`Start`,  
`Control Panel`,  
in `Search` Type *joy*,  
under `Devices and Printers` Click '*Set up USB game controllers*',  
Click `Properties`  

A button press will light, indicating button activity.  
If button does not respond, confirm button wiring and port. Remember within the code, button activity is active low, due to Arduino MCU hardware pull-up resistor. Low is *On*, High is *Off*.  
When changing assigned button Port/Digital bit, corresponding pull-up resistor must be correctly set.  
If pull-up resistor is set, Port/Digital bit will configure for button Input.  

Mouse pointer movement will confirm Spinner/Trackball activity;  
if there's no movement, validate +ve/-ve power connections along with both A/B connections.  
Quadrature line output require working A/B signal pulses to convey direction and movement (each axis has a pair of signals assigned to either X or Y axes).  
To change movement feel, select a different *#define* compiler directive within the code.
