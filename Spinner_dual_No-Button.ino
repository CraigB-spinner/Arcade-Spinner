/*   Arcade Trackball/Spinner v2.02
*    (new trackball/mouse dual x and y axis - added pinC & pinD - RX1/PD2, TX0/PD3 data pins)
*    Mouse (Arcade Dual Spinner) version with Joystick override using buttons for menu navigation.
* 
*    Craig B  - (craigbspinner@gmail.com)
*    Copyright 2020 Craig B - based on Spinner code from early June 2019 
*                   Craig B - Updated 70% of code, 
*                             Added spinner movement ACCM, 
*                             Optimized code speed by changing if logic to case statement logic for Button validation of port bits.
*                   Craig B - Added code for spinner movement ACCS - End of June 2019         
*                   Craig B - Added code for mouse y-axis and interupt processing from late Aug 2020
*                   Craig B - cleanup code for dual spinner from mid July 2025   
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

// Port Bit/Pin layout   
//      Bit - 76543210 - Silk screen ## - Micro-Controller
#define xPD3 0b00001000 //Digital Pin 0  - Micro/PRO Micro - TX,  INT3
#define xPD2 0b00000100 //Digital Pin 1  - Micro/PRO Micro - RX,  INT2
#define xPD1 0b00000010 //Digital Pin 2  - Micro/PRO Micro - SDA, INT0
#define xPD0 0b00000001 //Digital Pin 3  - Micro/PRO Micro - SCL, INT1
#define xPD_10 (xPD1 | xPD0)
#define xPD_32 (xPD3 | xPD2)
#define xPD4 0b00010000 //Digital Pin 4  - Micro/PRO Micro
#define xPC6 0b01000000 //Digital Pin 5  - Micro/PRO Micro
#define xPD7 0b10000000 //Digital Pin 6  - Micro/PRO Micro
#define xPE6 0b01000000 //Digital Pin 7  - Micro/PRO Micro
#define xPB4 0b00010000 //Digital Pin 8  - Micro/PRO Micro
#define xPB5 0b00100000 //Digital Pin 9  - Micro/PRO Micro
#define xPB6 0b01000000 //Digital Pin 10 - Micro/PRO Micro
#define xPB7 0b10000000 //Digital Pin 11 - Micro
#define xPD6 0b01000000 //Digital Pin 12 - Micro
#define xPC7 0b10000000 //Digital Pin 13 - Micro
#define xPB3 0b00001000 //Digital Pin 14 - PRO Micro
#define xPB1 0b00000010 //Digital Pin 15 - PRO Micro
#define xPB2 0b00000100 //Digital Pin 16 - PRO Micro

//   Arcade Spinner/Mouse requires ACCM movement (2 to 1).
//   2400 pulses/revs divide by two = 1200 ppr
//   Arcade Trackball/Mouse requires ACCS movement (1 to 1).
    
//Mouse movement - pick one to compile specific code inside loop()
//#define ACCS   //Mouse movement Accelerated; every interrupt processed but accelerated movement, no lag x1, 1 pulse = 1 move 
#define ACCM   //Mouse movement Accelerated; every interrupt processed but accelerated movement, no lag x2, 2 pulse = 1 move

#define pinA 2    //The pins that the trackball/mouse x-axis encoder's A and B terminals are connected to.
#define pinB 3
#define pinC 0    //The pins that the trackball/mouse y-axis encoder's C and D terminals are connected to.
#define pinD 1

//The previous state of the AB pins
volatile int prevQuadratureX = 0;
//The previous state of the CD pins
volatile int prevQuadratureY = 0;

//Keeps track of how much the encoder has been moved
volatile int rotPositionX = 0;
volatile int rotMultiX = 0;
volatile int rotPositionY = 0;
volatile int rotMultiY = 0;


//---------------------------------------------------------------------
void setup() {
  //No need to set the pin modes with DDRx = DDRx | 0b00000000 as we're using all input and that's the initial state of the pins
  
  //Use internal input resistors for all the pins we're using - pull high resistor, when button pressed (short to ground) input on pin is pulled low.
  //Digital pin D# corresponds to silk screen on micro-controller board, (#) corresponds to port bit internal use MSD(7)-to-LSD(0) - you assign button # in code
  PORTD = 0b00001111; //Digital pins D2(1), D3(0), D0(2), D1(3). - Trackball x/y-axis

  //Set up the interrupt handler for the encoder's A and B terminals on digital pins 2 and 3 respectively. Both interrupts use the same handler.
  attachInterrupt(digitalPinToInterrupt(pinA), pinChangeX, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(pinB), pinChangeX, CHANGE);
  //Set up the interrupt handler for the encoder's C and D terminals on digital pins 0 and 1 respectively. Both interrupts use the same handler.
  attachInterrupt(digitalPinToInterrupt(pinC), pinChangeY, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(pinD), pinChangeY, CHANGE);

  //Start the mouse
  Mouse.begin();
}


//---------------------------------------------------------------------
//Interrupt handler x-axis
void pinChangeX() {

  //Set currQuadratureX to state of rotary encoder terminals A & B from input of PORTD bits 0 & 1 (digital pins 2 and 3)
  //You could do int currQuadratureX = (digitalRead(pinA) << 1) | digitalRead(pinB); to get the same thing, but it would be much slower.
  //Read current state 00AB.
  int currQuadratureX = PIND & xPD_10;

  //Store comboQuadratureX with previous and current quadrature rotary encoder states together. 
  //Combined previous/current states form two groups of four unique bit patterns indicating direction of movement.
  //Shift left 2 bits: 00AB <- AB00 to store current state as previous state.
  int comboQuadratureX  = (prevQuadratureX << 2) | currQuadratureX; 

  //Rotate to the right, Clockwise
  //State 00AB, A leads B. A0 -> AB -> 0B -> 00 0b0010 0b1011 0b1101 0b0100
  if(comboQuadratureX == 0b0010 || comboQuadratureX == 0b1011 ||
     comboQuadratureX == 0b1101 || comboQuadratureX == 0b0100) {
    rotPositionX++;                   //update the position of the encoder
  }

  //Rotate to the left, Counter Clockwise
  //State 00AB, B leads A. 0B -> AB -> A0 -> 00 0b0001 0b0111 0b1110 0b1000
  if(comboQuadratureX == 0b0001 || comboQuadratureX == 0b0111 ||
     comboQuadratureX == 0b1110 || comboQuadratureX == 0b1000) {
   rotPositionX--;                   //update the position of the encoder
  }

  //Save the previous state of the A and B terminals for next time
  prevQuadratureX = currQuadratureX;
}


//---------------------------------------------------------------------
//Interrupt handler y-axis
void pinChangeY() {

  //Set currQuadratureY to state of rotary encoder terminals A & B from input of PORTD bits 2 & 3 (digital pins 0 and 1) 
  //You could do int currQuadratureY = (digitalRead(pinC) << 1) | digitalRead(pinD); to get the same thing, but it would be much slower.
  //Read current state CD00.
  int currQuadratureY = PIND & xPD_32;

  //Store comboQuadratureY with current and previous quadrature rotary encoder states together. 
  //Combined current/previous states form two groups of four unique bit patterns indicating direction of movement.
  //Shift right 2 bits: CD00 -> 00CD to store current state as previous state.
  int comboQuadratureY  = (prevQuadratureY >> 2) | currQuadratureY; 

  //Rotate to the right, Clockwise
  //State CD00, C leads D. C0 -> CD -> 0D -> 00 0b1000 0b1110 0b0111 0b0001
  if(comboQuadratureY == 0b1000 || comboQuadratureY == 0b1110 || 
     comboQuadratureY == 0b0111 || comboQuadratureY == 0b0001) { 
     rotPositionY++;                   //update the position of the encoder
  }

  //Rotate to the left, Counter Clockwise
  //State CD00, D leads C. 0D -> CD -> C0 -> 00 0b0100 0b1101 0b1011 0b0010
  if(comboQuadratureY == 0b0100 || comboQuadratureY == 0b1101 ||
     comboQuadratureY == 0b1011 || comboQuadratureY == 0b0010) {
     rotPositionY--;                   //update the position of the encoder
  }

  //Save the previous state of the C and D terminals for next time
  prevQuadratureY = currQuadratureY;
}


//---------------------------------------------------------------------
//Process the x/y axis mouse movement using one criteria (ACCS, ACCM)
//must process two edge transistions before moving the mouse/spinner pointer.
void loop(){ 

#ifdef ACCS
  //If the encoder has moved 1 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  if(rotPositionX != 0 || rotPositionY != 0) {
    Mouse.move(rotPositionX,rotPositionY,0);
    rotPositionX = 0;
    rotPositionY = 0;
  }
#endif 

#ifdef ACCM
  //If the encoder has moved 2 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  //Did Spinner 1 move
  if(rotPositionX >= 2 || rotPositionX <= -2) {
    rotMultiX = rotPositionX >> 1;
    rotPositionX -= (rotMultiX << 1);
  }
  //Did Spinner 2 move
  if(rotPositionY >= 2 || rotPositionY <= -2) {
    rotMultiY = rotPositionY >> 1;
    rotPositionY -= (rotMultiY << 1);
  }
  //Move mouse if either Spinner 1 or Spinner 2 moved
  if(rotMultiX != 0 || rotMultiY != 0) {
    Mouse.move(rotMultiX,rotMultiY,0);
    rotMultiX = 0;
    rotMultiY = 0;
  }
#endif 
 
}
