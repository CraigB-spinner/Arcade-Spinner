/*   Arcade Spinner v2.02
*    Special Mouse version with Left/Centre/Right Buttons or
*            Mouse version without buttons - JustSpin directive.
*     Extra: Mouse x/y axis switch to flip mouse movement between the two axes (Can not be used with No Buttons - JustSpin directive)
*            No JoyStick defined, so, no JoyStick buttons - only Mouse functionality.
*          
*    Craig B  - (craigbspinner@gmail.com)
*    Copyright 2020 Craig B - based on Spinner code from early June 2019 
*                   Craig B - Updated code from late June 2019, 
*                             Added spinner movement ACCM/DROP, 
*                             Optimized code speed by changing if logic to case statement logic for Button validation of port bits.
*                   Craig B - Added code for spinner movement NORM/ACCS/ACCX, RetroPi fix - July 2019         
*                   Craig B - Added code for spinner axis change from early Sept 2020   
*                   Craig B - Special mouse only code - Left, Centre, Right and spinner axis change buttons from early Dec 2020   
*                           - No button mode, JustSpin 
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

//#define JustSpin //Mouse movement only logic - NO BUTTON CODE - Note: Must disable axisFlip or code will not compile properly.

#define pinA 2    //The pins that the rotary encoder's A and B terminals are connected to.
#define pinB 3
#define maxBut 4
#define axisFlip 3  //Special flip button (button offset: 0 thru 3) - comment out if 'x/y-axis' feature not required by you.

//The previous state of the AB pins
volatile int prevQuadratureX = 0;

//Keeps track of how much the encoder has been moved
volatile int rotPositionX = 0;
volatile int rotMultiX = 0;

#ifndef JustSpin
#ifdef axisFlip
volatile int xAxis = 1; 
volatile int yAxis = 0; 

// Last state of 4 buttons (update array for your maxBut buttons)
// Since Button Port Bits are set to 1 to activate(pull-hi input resistors), the press state is low, and not pressed is high.
int lastButtonState[maxBut] = {1,1,1,1};
#endif
#ifndef axisFlip
int lastButtonState[maxBut] = {1,1,1,0};
#endif
#endif

void setup() {
  //No need to set the pin modes with DDRx = DDRx | 0b00000000 as we're using all input and that's the initial state of the pins
  //Setup for three mouse buttons Left, Centre, Right, plus special axisFlip control.
  //Use internal input resistors for all the pins we're using - pull high resistor, when button pressed (short to ground) input on pin is pulled low.
  //Digital pin D# corresponds to silk screen on micro-controller board, (#) corresponds to port bit internal use MSD(7)-to-LSD(0) - you assign button # in code 
#ifdef JustSpin
  PORTD = 0b10010011; //Digital pins D2(1), D3(0)
#endif
#ifndef JustSpin
  PORTD = 0b10010011; //Digital pins D2(1), D3(0), D4(4), and D6(7). (Button Left and Right)
  PORTC = 0b01000000; //Digital pin D5(6)                            (Button Centre)
  PORTE = 0b01000000; //Digital pin D7(6)                            (Button Special)
//PORTB = 0b00010000; //Digital pin D8(4). D9(5), D10(6), D15(1), D14(3), D16(2) requires PB0 set high(master)
//PORTB = 0b01110010; //Digital pins D8(4), D9(5), D10(6), and D15(1). D14(3), D16(2) requires PB0 set high(master)
//PORTB = 0b01110111; //Digital pins D8(4), D9(5), D10(6), and D15(1). D14(3), D16(2) requires PB0 set high(master)
//PORTF = 0b11000000; //Digital pin A0(7) & A1(6). A2(5), A3(4) 
#endif

  //Set up the interrupt handler for the encoder's A and B terminals on digital pins 2 and 3 respectively. Both interrupts use the same handler.
  attachInterrupt(digitalPinToInterrupt(pinA), pinChangeX, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(pinB), pinChangeX, CHANGE);

  //Start the mouse
  Mouse.begin();
  }

//Interrupt handler
//Digital pins 2 and 3 are used for spinner rotary output as they are interrupt driven.
void pinChangeX() {

  //Set currQuadratureX to state of rotary encoder terminals A & B from input of PORTD bits 0 & 1 (digital pins 2 and 3)
  //You could do int currQuadratureX = (digitalRead(pinA) << 1) | digitalRead(pinB); to get the same thing, but it would be much slower.
  //Read current state 00AB.
  int currQuadratureX = PIND & 0b00000011;

  //Store comboQuadratureX with previous and current quadrature rotary encoder states together. 
  //Combined previous/current states form two groups of four unique bit patterns indicating direction of movement.
  //Shift left 2 bits: 00AB <- AB00 to store current state as previous state.
  int comboQuadratureX  = (prevQuadratureX << 2) | currQuadratureX; 

  //Rotate to the right, Clockwise
  //State 00AB, A leads B. A0 -> AB -> 0B -> 00 0b0010 0b1011 0b1101 0b0100
  if(comboQuadratureX == 0b0010 || comboQuadratureX == 0b1011 ||
     comboQuadratureX == 0b1101 || comboQuadratureX == 0b0100) 
    rotPositionX++;                   //update the position of the encoder

  //Rotate to the left, Counter Clockwise
  //State 00AB, B leads A. 0B -> AB -> A0 -> 00 0b0001 0b0111 0b1110 0b1000
  if(comboQuadratureX == 0b0001 || comboQuadratureX == 0b0111 ||
     comboQuadratureX == 0b1110 || comboQuadratureX == 0b1000) 
    rotPositionX--;                   //update the position of the encoder

  //Save the previous state of the A and B terminals for next time
  prevQuadratureX = currQuadratureX;
}

void loop(){ 
#ifndef JustSpin
int currentButtonState;
#endif

#ifdef NORM
  //If the encoder has moved 2 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Smooth movement but lags.
  if(rotPositionX >= 2) {
  #ifdef axisFlip
    Mouse.move(xAxis,yAxis,0);
  #else 
    Mouse.move(1,0,0);
  #endif 
    rotPositionX -= 2;
  } else if(rotPositionX <= -2) {
  #ifdef axisFlip
    Mouse.move(-xAxis,-yAxis,0);
  #else 
     Mouse.move(-1,0,0);
  #endif 
    rotPositionX += 2;
  } 
#endif 

#ifdef DROP
  //If the encoder has moved 2 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Smooth drop extra moves.
  if(rotPositionX >= 2) {
  #ifdef axisFlip
    Mouse.move(xAxis,yAxis,0);
  #else 
    Mouse.move(1,0,0);
  #endif 
    rotPositionX = 0;
  } else if(rotPositionX <= -2) {
  #ifdef axisFlip
    Mouse.move(-xAxis,-yAxis,0);
  #else 
    Mouse.move(-1,0,0);
  #endif 
    rotPositionX = 0;
  } 
#endif 

#ifdef ACCS
  //If the encoder has moved 1 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  if(rotPositionX != 0) {
  #ifdef axisFlip
    int x = (xAxis) ? rotPositionX : 0;
    int y = (yAxis) ? rotPositionX : 0;
    Mouse.move(x,y,0);
  #else 
    Mouse.move(rotPositionX,0,0);
  #endif 
    rotPositionX = 0;
  }
#endif 

#ifdef ACCM
  //If the encoder has moved 2 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  if(rotPositionX >= 2 || rotPositionX <= -2) {
    rotMultiX = rotPositionX >> 1;
  #ifdef axisFlip
    int x = (xAxis) ? rotMultiX : 0;
    int y = (yAxis) ? rotMultiX : 0;
    Mouse.move(x,y,0);
  #else 
    Mouse.move(rotMultiX,0,0);
  #endif 
    rotPositionX -= (rotMultiX << 1);
  }
#endif 

#ifdef ACCX
  //If the encoder has moved 4 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  if(rotPositionX >= 4 || rotPositionX <= -4) {
    rotMultiX = rotPositionX >> 2;
  #ifdef axisFlip
    int x = (xAxis) ? rotMultiX : 0;
    int y = (yAxis) ? rotMultiX : 0;
    Mouse.move(x,y,0);
  #else 
    Mouse.move(rotMultiX,0,0);
  #endif 
    rotPositionX -= (rotMultiX << 2);
  }
#endif 

#ifndef JustSpin
  //Iterate through the 10 buttons (0-3) assigning the current digital state of pin for each button, 
  //HIGH(0b00000001) or LOW(0b00000000), to currentState variable. 
  //Note: Pro Micro boards use various ports to access different digital pins. 
  //Buttons 1-4 used; buttons 5-10 unused
  //Using digital pins 4, 5, 6, and 7 on Pro Micro board. See silk screening.
  //Pins 8, 9, 10, 14, 15 and 16 are free to use.
  //Pins 2 and 3 are used for spinner rotary output as they are interrupt driven.
  int button = 0;
  do {
    switch ( button ) {
      case 0:  //on digital pin 4, PD4 - Mouse Button 1
        currentButtonState = (PIND & 0b00010000) >> 4;
        break;
      case 1:  //on digital pin 5, PC6 - Mouse Button 2
        currentButtonState = (PINC & 0b01000000) >> 6;
        break;
      case 2:  //on digital pin 6, PD7 - Mouse Button 3
        currentButtonState = (PIND & 0b10000000) >> 7;
        break;
    #ifdef axisFlip
      case 3:  //on digital pin 7, PE6 - Mouse Button 4
        currentButtonState = (PINE & 0b01000000) >> 6;
        break;
    #endif
//      case 4:  //on digital pin 8, PB4 - Arcade Button 5
//        currentButtonState = (PINB & 0b00010000) >> 4;
//        break;
//      case 5:  //on digital pin 9, PB5 - Arcade Button 6
//        currentButtonState = (PINB & 0b00100000) >> 5;
//        break;
//      case 6:  //on digital pin 16, PB2 - Special Axis Button (internal function) - requires PB0 set to master or high
//        currentButtonState = (PINB & 0b00000100) >> 2;
//        break; 
//      case 7:  //on digital pin 14, PB3 - 2nd Special Button 
//        currentButtonState = (PINB & 0b00001000) >> 3;
//        break; 
//      case 8:  //on digital pin 10, PB6 - COIN/Select Button 9
//        currentButtonState = (PINB & 0b01000000) >> 6;
//        break;
//      case 9:  //on digital pin 15, PB1 - PLAYER/Start Button 10
//        currentButtonState = (PINB & 0b00000010) >> 1;
//        break; 
      default: //Extra digital pins 16, PB2 and 14, PB3
        currentButtonState = 0b00000000;
        break;
    }
    
//  If the current state of the pin for each button is different than last time, update the mouse button state
    if(currentButtonState != lastButtonState[button]) {

//  button press state is low, and not pressed is high
//  if button and state logic to control Mouse.press() or Mouse.release() activity
      switch ( button ) {
        case 0:  //Left Mouse Button 
          if (currentButtonState == 1) {
            Mouse.release(MOUSE_LEFT);
          } else {
            Mouse.press(MOUSE_LEFT);
          }        
          break;
        case 1:  //Centre Mouse Button
          if (currentButtonState == 1) {
            Mouse.release(MOUSE_MIDDLE);
          } else {
            Mouse.press(MOUSE_MIDDLE);
          }        
          break;
        case 2:  //Right Mouse Button
          if (currentButtonState == 1) {
            Mouse.release(MOUSE_RIGHT);
          } else {
            Mouse.press(MOUSE_RIGHT);
          }        
          break;
      #ifdef axisFlip
        case 3:  //Special Axis Flip Button 
          if (button == axisFlip ) { //change x/y axis
            xAxis = !xAxis;
            yAxis = !yAxis;
          } 
          break;
      #endif
      }
    }

    //Save the last button state for each button for next time
    lastButtonState[button] = currentButtonState;

    ++button;
  } while (button < maxBut);
#endif

}
