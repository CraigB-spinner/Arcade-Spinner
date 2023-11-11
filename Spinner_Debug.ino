/*   Arcade Spinner v2.01 
*    Craig B  - (craigbspinner@gmail.com)
*                   Craig B - based on Spinner code from early June 2019 
*    Copyright 2019 Craig B - Updated code from late June 2019, 
*                             Added spinner movement ACCM/DROP, 
*                   Craig B - Added code for spinner movement NORM/ACCS/ACCX, RetroPi fix - July 2019         
*                   Craig B - Debug code for spinner only from Nov 2023    
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

/*   Debug code
*    Pin A/B must send 8 valid quadrature signals to the MCU via pin 2&3
*    If wires fail to be proper connected by bad jumpers (bad crimp, broken wire) 
*    or failure to power with +5V and Gnd through wires
*    or bad voltage drop to wires or insufficient USB power to load
*    will result in improper states (atleast 3.5V required for high state).
*    ATmega32U4 Lo(max) 0.9V, Hi(min) 1.9V but rotary encoder is more sensitive.
*    Rotary encoder may require more voltage closer to 5V to operate.
*    8 invalid quadrature signals will trigger sporadic error messages.
*    There must be atleast a minimal voltage supply to the rotary encoder 
*    to cause an interupt state change on either A or B signal lines.
*    J1 on Pro Micro boards bypass onboard diode and regulator if 
*    full USB voltage is needed. (no safety for over voltage)
*/

// Port Bit/Pin layout   
//      Bit - b76543210 - Silk screen ## - Micro-Controller
#define xPD3 0b00001000 //Digital Pin 0  - Micro/PRO Micro - RX,  INT2
#define xPD2 0b00000100 //Digital Pin 1  - Micro/PRO Micro - TX,  INT3
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
    
//Mouse movement - pick one to compile specific code inside loop()
//#define NORM   //Mouse movement Normal; every interrupt processed; maybe lag in fast movement, 2 pulse = 2 move
//#define DROP   //Mouse movement Drop; drop extra interrupts processed; smooth movement, no lag, 2 - 2n+1 pulse = 1 move
//#define ACCS   //Mouse movement Accelerated; every interrupt processed but accelerated movement, no lag x1, 1 pulse = 1 move 
#define ACCM   //Mouse movement Accelerated; every interrupt processed but accelerated movement, no lag x2, 2 pulse = 1 move
//#define ACCX   //Mouse movement Accelerated; every interrupt processed but accelerated movement, no lag x4, 4 pulse = 1 move

#define pinA 2    //The pins that the rotary encoder's A and B terminals are connected to.
#define pinB 3

#define TEST        //Display info on Serial Monitor
 
//The previous state of the AB pins
volatile int prevQuadratureX = 0;
//Keeps track of how much the encoder has been moved
volatile int rotPositionX = 0;
volatile int rotMultiX = 0;
#ifdef TEST    
volatile int rotPosn = 0;
#endif

void setup() {
  //No need to set the pin modes with DDRx = DDRx | 0b00000000 as we're using all input and that's the initial state of the pins
  
  //Use internal input resistors for all the pins we're using  
  //PORTB = 0b01110111; //Digital pins D8(4), D9(5), D10(6), and D15(1). {D16(2), D14(3)}; D16 requires PB0 set high(master) - (Button 5, 6, 9 & 10)
  //PORTC = 0b01000000; //Digital pin D5(6)  
  //PORTD = 0b10010011; //Digital pins D2(1), D3(0), D4(4), and D6(7).
  //PORTE = 0b01000000; //Digital pin D7(6)
  //PORTF = 0b11000000; //Digital pin A0(7) & A1(6). A2(5), A3(4) 
  //
  PORTB = 0b00000000; //(No Button input)
  PORTC = 0b00000000;
  PORTD = 0b00000011; //Digital Pin 2&3, A/B
  PORTE = 0b00000000;
  PORTF = 0b00000000;

#ifdef TEST
  Serial.begin(9600); //This pipes to the serial monitor
#endif

  //Set up the interrupt handler for the encoder's A and B terminals on digital pins 2 and 3 respectively. Both interrupts use the same handler.
  attachInterrupt(digitalPinToInterrupt(pinA), pinChange, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(pinB), pinChange, CHANGE);

  //Start the mouse
  Mouse.begin();
}

//Interrupt handler
//Digital pins 2 and 3 are used for spinner rotary output as they are interrupt driven.
void pinChange() {
  //Set currQuadratureX to state of rotary encoder terminals A & B from input of PORTD bits 0 & 1 (digital pins 2 and 3)
  //You could do int currQuadratureX = (digitalRead(pinA) << 1) | digitalRead(pinB); to get the same thing, but it would be much slower.
  //Read current state 00AB.
  int currQuadratureX = PIND & xPD_10;

  //Store comboQuadratureX with previous and current quadrature rotary encoder states together. 
  //Combined previous/current states form two groups of four unique bit patterns indicating direction of movement.
  //Shift left 2 bits: 00AB <- AB00 to store current state as previous state.
  int comboQuadratureX  = (prevQuadratureX << 2) | currQuadratureX; 

//Rotate to the right, Clockwise (2, 4, 11, 13) 
  //State 00AB, A leads B. A0 -> AB -> 0B -> 00 0b0010 0b1011 0b1101 0b0100
  if(comboQuadratureX == 0b0010 || comboQuadratureX == 0b1011 ||
     comboQuadratureX == 0b1101 || comboQuadratureX == 0b0100) 
    {rotPositionX++;                   //update the position of the encoder
    #ifdef TEST
     rotPosn++; 
    #endif 
    }
  //Rotate to the left, Counter Clockwise (1, 7, 8, 14) 
  //State 00AB, B leads A. 0B -> AB -> A0 -> 00 0b0001 0b0111 0b1110 0b1000
  if(comboQuadratureX == 0b0001 || comboQuadratureX == 0b0111 ||
     comboQuadratureX == 0b1110 || comboQuadratureX == 0b1000) 
    {rotPositionX--;                   //update the position of the encoder
    #ifdef TEST
     rotPosn--; 
    #endif 
    }
    
  //Not Rotate to right or left - invalid states (0, 3, 5, 6, 9, 10, 12, 15)
  if(comboQuadratureX == 0b0000 || comboQuadratureX == 0b0011 || 
     comboQuadratureX == 0b0101 || comboQuadratureX == 0b0110 || 
     comboQuadratureX == 0b1001 || comboQuadratureX == 0b1010 || 
     comboQuadratureX == 0b1100 || comboQuadratureX == 0b1111){  
  #ifdef TEST
    Serial.print("Cnt: ");
    Serial.print(rotPosn);  
    Serial.print(" -- Error on a/b or low voltage --- ");
    Serial.print(comboQuadratureX);  
    Serial.println(" -- ");  
  #endif
  }
  else 
  //Save the previous state of the A and B terminals for next time
    prevQuadratureX = currQuadratureX;
}

void loop(){ 

//Only a single mouse movement directive needs to be selected at the top
//either 1-1(ACCS), 2-1(ACCM), 4-1(ACCX) with accerated pixel movement 
//or NORM/DROP moves a pixel at a time and keeps or drops extra interrupt counts 
//

#ifdef NORM
  //If the encoder has moved 2 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Smooth movement but lags.
  if(rotPositionX >= 2) {
    Mouse.move(1,0,0);
    rotPositionX -= 2;
  } else if(rotPositionX <= -2) {
    Mouse.move(-1,0,0);
    rotPositionX += 2;
  } 
#endif 

#ifdef DROP
  //If the encoder has moved 2 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Smooth drop extra moves.
  if(rotPositionX >= 2) {
    Mouse.move(1,0,0);
    rotPositionX = 0;
  } else if(rotPositionX <= -2) {
    Mouse.move(-1,0,0);
    rotPositionX = 0;
  } 
#endif 

#ifdef ACCS
  //If the encoder has moved 1 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  if(rotPositionX != 0) {
    Mouse.move(rotPositionX,0,0);
    rotPositionX = 0;
  }
#endif 

#ifdef ACCM
  //If the encoder has moved 2 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  if(rotPositionX >= 2 || rotPositionX <= -2) {
    rotMultiX = rotPositionX >> 1;
    Mouse.move(rotMultiX,0,0);
    rotPositionX -= (rotMultiX << 1);
  }
#endif 

#ifdef ACCX
  //If the encoder has moved 4 or more transitions move the mouse in the appropriate direction 
  //and update the position variable to reflect that we moved the mouse. Accelerated move.
  if(rotPositionX >= 4 || rotPositionX <= -4) {
    rotMultiX = rotPositionX >> 2;
    Mouse.move(rotMultiX,0,0);
    rotPositionX -= (rotMultiX << 2);
  }
#endif 

}
