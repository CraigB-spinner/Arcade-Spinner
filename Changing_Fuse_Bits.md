**Pick an AVR Programmer**  
I used a [USBtinyISP Programmer](Pics/USBtinyISP%20Programmer.jpg) with a custom wire harness.  
Harness is a single 3x2 Female JST connector  
wired into a dual 4x1 Female JST connector, or  
ICSP 6-Pin Cable coverting to Arduino Pro Micro headers.
[See here](Pics/USBtinyISP-Programmer+DIY-Harness.jpg)  

32u4<br/>Pin |Data |wire   |USBtiny<br/>Row/Col
--- |---- |------ |--------
10  |D10  |empty  | - - -
16  |MOSI |Yellow | 1 / 2
14  |MISO |Green  | 2 / 3
15  |SCK  |Blue   | 2 / 2
21  |Vcc  |Red    | 1 / 3
22  |RST  |Blue   | 2 / 1
23  |Gnd  |Black  | 1 / 1
24  |Raw  |empty  | - - -


**On your computer,**  
use program Putty and SSH to your PI's ip address.  
`login: pi`  
`Password: raspberry` *(unless updated by you)*  

**Add:**  
*usbhid.mousepoll=0*  
to *cmdline.txt*

`sudo nano /boot/cmdline.txt`  
on the same line separated from other stuff by spaces  
This parameter enforces a mouse polling rate of 62.5Hz and reduces any quick movement lag.  

`sudo reboot`
Inside the Atmel manual for ATMega32U4 micro-controller, pages: 346 - 348  
[High & Low bits](Pics/ATMega32U4%20-%20Fuse%20bits%20-%20High%20&%20Low.jpg), 
[Extended bits](Pics/ATMega32U4 - Fuse bits - Extended.jpg), 
[Lock bits](Pics/ATMega32U4 - Lock bits.jpg)  



