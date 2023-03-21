**Amazon Product description section**  
BQLZR 600P/R Incremental Rotary Encoder  
Connection:  
Red = A phase, Green = B phase, White =Vcc power +, Black = power -  
Notice: AB 2phase **output must not be directly connected with VCC**, otherwise, will burn the output triode.  

Transistor(triode) in the rotary encoder has no spec stated for current limit.  
I have seen other SOT23 components with 100mA collector max but I can not makeout any lettering on transistor.  
There is a 10Ω smd resistor in series to the collector and A & B wired phase outputs.  
That is 0.5A @ 5V. Is the transistor rated for 500mA? I played it safe and added another resistor in series. 
You choose if you want to spend another 5¢ - 10¢ on the project. <BR/>

**Part II: Protect your Arduino (ATmega32U4) board.**  
40mA per pin,  
no more than 100mA for a single port,  
PortB, PortD are critical with 5-6 pins, PortC, PortE are single pins  
and no more than 200mA for the whole board. <BR/> <BR/>
**NO Button Mashing**
