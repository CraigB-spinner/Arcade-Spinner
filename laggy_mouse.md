**On your computer,**  
use program Putty and SSH to your PI's ip address.  
login: pi  
Password: raspberry *(unless updated by you)*  

**Add:**  
*usbhid.mousepoll=0*  
to *cmdline.txt*

`sudo nano /boot/cmdline.txt`  
on the same line separated from other stuff by spaces  
This parameter enforces a mouse polling rate of 62.5Hz and reduces any quick movement lag.  

`sudo reboot`
