Using 24mm illuminated buttons, I used a DYMO LetraTag with clear labels  
Coin in Large Bold text, Play & Exit in Medium Bold text<br/>
[![A](Pics/Coin-Play-Exit/TNx2/IMG_2036.JPG)](Pics/Coin-Play-Exit/IMG_2036.JPG) <br/>
<sup>Coin(Select), Play(Start), Exit(Hotkey)</sup> <br/>
<sub>Buttons Coin & Play: always-on, while Exit: lite-when-pressed (special wiring)</sub> <br/>
[![1](Pics/Coin-Play-Exit/TN/IMG_2034.JPG)](Pics/Coin-Play-Exit/IMG_2034.JPG) 
[![2](Pics/Coin-Play-Exit/TN/IMG_2035.JPG)](Pics/Coin-Play-Exit/IMG_2035.JPG) <br/> 
<sup>Wiring of Buttons: SPST switch on bottom, +ve/Gnd of LED on top</sup> <br/>
[![B](Pics/Coin-Play-Exit/TNx2/IMG_2038.JPG)](Pics/Coin-Play-Exit/IMG_2038.JPG) <br/>
<sup>Zero Delay USB Encoder CY-822A</sup> <br/>
You will need to add an extra socket (Jst Xh 2.5-2 Pin Connector Plug Female/Male type)  
and wire a parallel chain of power leads 24-26AWG with 2.8mm Female Spade connectors to LED +ve/Gnd contacts.  
<br/>
Lite-when-pressed blue Exit button has special wiring.  
Since Zero Delay USB Encoder uses common +ve, and Key inputs are pulled-low,  
when button is pressed, input signal will short to +5V (high to the MCU glob-top).  
Reverse the SPST switch contacts red & black (with extra yellow lead) wires and connect the yellow wire to LED +ve contact. The LED Gnd will use the black daisy chain wire. What is happening: LED cathode is connected to Gnd (normal), but Anode is connected to input signal which is pulled-low by the MCU. Both side are Gnd and LED does not light. When you press the button, you short input signal to +5V, which is jumpered to LED anode, the LED glows.  
<br/>
More current USB Encoder model(s) may have +5V sockets (red Jst Xh) on board.  

If you are using an Arduino MCU the inputs are pulled-high for input then shorted to Gnd (Pin current limit of 40mA, use a 390Ω - 470Ω resistor to be safe).
Both sides of the LED must be +5V and Button (SPST switch) supplies Gnd to pull the input low and trigger a button-press. Arduino MCUs use common Gnd for inputs which is reverse to Zero Delay USB Encoders. Wiring must adjust to new common.
