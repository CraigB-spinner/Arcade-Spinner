/*   Arcade Spinner v2.01
*    Copyright 2018 Joe W (jmtw000 a/t gmail.com)
*                   Craig B - based on Spinner code from early June 2019 
*                   Craig B - Updated code from late June 2019, 
*                             Added spinner movement ACCM/DROP, 
*                             Optimized code speed by changing if logic to case statement logic for Button validation of port bits.
*                   Craig B - Added code for spinner movement NORM/ACCS/ACCX, RetroPi fix - July 2019         
*                   Craig B - Added code for spinner axis change from early Sept 2020   
*    
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Mouse.h"
#include <Joystick.h>

/*   RetroPie mods - Arduino IDE -> Tools, Get Board Info
*    VID: 1B4F
*    PID: 9206
*    Add the following to /boot/cmdline.txt -- just add a space to the end of the existing entry, so it is all on one line):
*    usbhid.quirks=0x16c0:0x05e1:0x040
*    The first two numbers are the vendor ID 16c0 and product ID 05e1.
*/

//Mouse movement - pick one to compile specific code inside loop()
//#define NORM   //Mouse movement Normal; every interrupt processed; maybe lag in fast movement, 2 pulse = 2 move
//#define DROP   //Mouse movement Drop; drop extra interrupts processed; smooth movement, no lag, 2 - 2n+1 pulse = 1 move
//#define ACCS   //Mouse movement Accelerated; every interrupt processed but accelerated movement, no lag x1, 1 pulse = 1 move 
#define ACCM   //Mouse movement Accelerated; every interrupt processed but accelerated movement, no lag x2, 2 pulse = 1 move
//#define ACCX   //Mouse movement Accelerated; every interrupt processed but accelerated movement, no lag x4, 4 pulse = 1 move

#define pinA 2    //The pins that the rotary encoder's A and B terminals are connected to.
#define pinB 3
#define maxBut 10
#define axisFlip 6  //Special flip button (button offset: 0 thru 9) - comment out if 'x/y-axis' feature not required by you.

//Create a Joystick object.
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  maxBut, 0,             // Button Count, Hat Switch Count
  true, true, false,    // X, but no Y or Z Axis. We need at least one axis even though it's not really used.
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering;


//The previous state of the AB pins
volatile int previousReading = 0;

//Keeps track of how much the encoder has been moved
volatile int rotPosition = 0;
volatile int rotMulti = 0;
#ifdef axisFlip
volatile int xAxis = 1; 
volatile int yAxis = 0; 

// Last state of 10 buttons (update array for your maxBut buttons)
int lastButtonState[maxBut] = {1,1,1,1,1,1,0,1,1,1};
#endif
#ifndef axisFlip
int lastButtonState[maxBut] = {1,1,1,1,1,1,0,0,1,1};
#endif


void setup() {
  //No need to set the pin modes with DDRx = DDRx | 0b00000000 as we're using all input and that's the initial state of the pins
  
  //Use internal input resistors for all the pins we're using  
  PORTD = 0b10010011; //Digital pins D2(1), D3(0), D4(4), and D6(7).
  PORTB = 0b01110111; //Digital pins D8(4), D9(5), D10(6), and D15(1). D14(3), D16(2) requires PB0 set high(master)
  PORTC = 0b01000000; //Digital pin D5(6)
  PORTE = 0b01000000; //Digital pin D7(6)
//PORTF = 0b11000000; //Digital pin A0(7) & A1(6). A2(5), A3(4) 

  //Start the joystick
  Joystick.begin();
  
  //Center the X axis on the joystick (Raspberry Pi/RetroPi requires two axises to be defined)
  Joystick.setXAxis(511);
  Joystick.setYAxis(511);

  //Set up the interrupt handler for the encoder's A and B terminals on digital pins 2 and 3 respectively. Both interrupts use the same handler.
  attachInterrupt(digitalPinToInterrupt(pinA), pinChange, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(pinB), pinChange, CHANGE);

  //Start the mouse
  Mouse.begin();
  }

//Interrupt handler
//Digital pins 2 and 3 are used for spinner rotary output as they are interrupt driven.
void pinChange() {

  //Set the currentReading variable to the current state of encoder terminals A and B which are conveniently 
  //located in bits 0 and 1 (digital pins 2 and 3) of PortB
  //This will give us a nice binary number, eg. 0b00000011, representing the current state of the two terminals.
  //You could do int currentReading = (digitalRead(pinA) << 1) | digitalRead(pinB); to get the same thing, but it would be much slower.
  
  //Read current state 00AB.
  int currentReading = PIND & 0b00000011;

  //Take the nice binary number we got last time there was an interrupt and shift it to the left by 2 then OR it with the current reading.
  //This will give us a nice binary number, eg. 0b00001100, representing the former and current state of the two encoder terminals.
  //Shift left 2 bits: 00AB -> AB00 to hold last current state as prior state.
  int combinedReading  = (previousReading << 2) | currentReading; 

  //Now that we know the previous and current state of the two terminals we can determine which direction the rotary encoder is turning.

  //Rotate to the right, Clockwise
  //State 00AB, A leads B. A0 -> AB -> 0B -> 00 
  if(combinedReading == 0b0010 || 
     combinedReading == 0b1011 ||
     combinedReading == 0b1101 || 
     combinedReading == 0b0100) {
     rotPosition++;                   //update the position of the encoder
  }

  //Rotate to the left, Counter Clockwise
  //State 00AB, B leads A. 0B -> AB -> A0 -> 00
  if(combinedReading == 0b0001 ||
     combinedReading == 0b0111 ||
     combinedReading == 0b1110 ||
     combinedReading == 0b1000) {
     rotPosition--;                   //update the position of the encoder
  }

  //Save the previous state of the A and B terminals for next time
  previousReading = currentReading;
}

void loop(){ 
  int currentButtonState;

#ifdef NORM
  //If the encoder has moved 2 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Smooth movement but lags.
  if(rotPosition >= 2) {
#ifdef axisFlip
    Mouse.move(xAxis,yAxis,0);
#endif 
#ifndef axisFlip
    Mouse.move(1,0,0);
#endif 
    rotPosition -= 2;
  } else if(rotPosition <= -2) {
#ifdef axisFlip
    Mouse.move(-xAxis,-yAxis,0);
#endif 
#ifndef axisFlip
    Mouse.move(-1,0,0);
#endif 
    rotPosition += 2;
  } 
#endif 

#ifdef DROP
  //If the encoder has moved 2 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Smooth drop extra moves.
  if(rotPosition >= 2) {
#ifdef axisFlip
    Mouse.move(xAxis,yAxis,0);
#endif 
#ifndef axisFlip
    Mouse.move(1,0,0);
#endif 
    rotPosition = 0;
  } else if(rotPosition <= -2) {
#ifdef axisFlip
    Mouse.move(-xAxis,-yAxis,0);
#endif 
#ifndef axisFlip
    Mouse.move(-1,0,0);
#endif 
    rotPosition = 0;
  } 
#endif 

#ifdef ACCS
  //If the encoder has moved 1 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  if(rotPosition != 0) {
#ifdef axisFlip
    int x = (xAxis) ? rotPosition : 0;
    int y = (yAxis) ? rotPosition : 0;
    Mouse.move(x,y,0);
#endif 
#ifndef axisFlip
    Mouse.move(rotPosition,0,0);
#endif 
    rotPosition = 0;
  }
#endif 

#ifdef ACCM
  //If the encoder has moved 2 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  if(rotPosition >= 2 || rotPosition <= -2) {
    rotMulti = rotPosition >> 1;
#ifdef axisFlip
    int x = (xAxis) ? rotMulti : 0;
    int y = (yAxis) ? rotMulti : 0;
    Mouse.move(x,y,0);
#endif 
#ifndef axisFlip  
    Mouse.move(rotMulti,0,0);
#endif 
    rotPosition -= (rotMulti << 1);
  }
#endif 

#ifdef ACCX
  //If the encoder has moved 4 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  if(rotPosition >= 4 || rotPosition <= -4) {
    rotMulti = rotPosition >> 2;
#ifdef axisFlip
    int x = (xAxis) ? rotMulti : 0;
    int y = (yAxis) ? rotMulti : 0;
    Mouse.move(x,y,0);
#endif 
#ifndef axisFlip
    Mouse.move(rotMulti,0,0);
#endif 
    rotPosition -= (rotMulti << 2);
  }
#endif 

  //Iterate through the 10 buttons (0-9) assigning the current digital state of pin for each button, 
  //HIGH(0b00000001) or LOW(0b00000000), to currentState variable. 
  //Note: Pro Micro boards use various ports to access different digital pins. 
  //Buttons 1-6, plus 9-select(coin), and 10-start(player) used; buttons 7 & 8 unused
  //Using digital pins 4, 5, 6, 7, 8, 9, 10, and 15 on Pro Micro board. See silk screening.
  //Pins 16 and 14 are free to use.
  //Pins 2 and 3 are used for spinner rotary output as they are interrupt driven.
  int button = 0;
  do {
    switch ( button ) {
      case 0:  //on digital pin 4, PD4 - Arcade Button 1
        currentButtonState = (PIND & 0b00010000) >> 4;
        break;
      case 1:  //on digital pin 5, PC6 - Arcade Button 2
        currentButtonState = (PINC & 0b01000000) >> 6;
        break;
      case 2:  //on digital pin 6, PD7 - Arcade Button 3
        currentButtonState = (PIND & 0b10000000) >> 7;
        break;
      case 3:  //on digital pin 7, PE6 - Arcade Button 4
        currentButtonState = (PINE & 0b01000000) >> 6;
        break;
      case 4:  //on digital pin 8, PB4 - Arcade Button 5
        currentButtonState = (PINB & 0b00010000) >> 4;
        break;
      case 5:  //on digital pin 9, PB5 - Arcade Button 6
        currentButtonState = (PINB & 0b00100000) >> 5;
        break;
#ifdef axisFlip
      case 6:  //on digital pin 16, PB2 - Special Axis Button (internal function) - requires PB0 set to master or high
        currentButtonState = (PINB & 0b00000100) >> 2;
        break; 
#endif
//      case 7:  //on digital pin 14, PB3 - 2nd Special Button 
//        currentButtonState = (PINB & 0b00001000) >> 3;
//        break; 
      case 8:  //on digital pin 10, PB6 - COIN/Select Button 9
        currentButtonState = (PINB & 0b01000000) >> 6;
        break;
      case 9:  //on digital pin 15, PB1 - PLAYER/Start Button 10
        currentButtonState = (PINB & 0b00000010) >> 1;
        break; 
      default: //Extra digital pins 16, PB2 and 14, PB3
        currentButtonState = 0b00000000;
        break;
    }

    //If the current state of the pin for each button is different than last time, update the joystick button state
    if(currentButtonState != lastButtonState[button])
#ifdef axisFlip
      if (button == axisFlip ) { //change x/y axis
        xAxis = !xAxis;
        yAxis = !yAxis;
      } else
#endif
        Joystick.setButton(button, !currentButtonState);
      
    //Save the last button state for each button for next time
    lastButtonState[button] = currentButtonState;

    ++button;
  } while (button < maxBut);

}
