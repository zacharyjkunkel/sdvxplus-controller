

//these are arduino libraries
#include "Mouse.h"
#include "Keyboard.h"
#include "Encoder.h"

//Keybinds
//binding for up to 10 keys
#define BIND_1 'a'
#define BIND_2 's'
#define BIND_3 'd'
#define BIND_4 'f'
#define BIND_5 'j'
#define BIND_6 'k'
#define BIND_7 'l'
#define BIND_8 ';'
#define BIND_L 'v'
#define BIND_R 'n'
#define BIND_ESC KEY_ESC
#define BIND_RET KEY_RETURN

//alternate binding to include navigation keys
#define BIND2_1 KEY_LEFT_ARROW
#define BIND2_2 KEY_RIGHT_ARROW
#define BIND2_3 'd'
#define BIND2_4 'f'
#define BIND2_5 'j'
#define BIND2_6 'k'
#define BIND2_7 KEY_UP_ARROW
#define BIND2_8 KEY_DOWN_ARROW
#define BIND2_L 'v'
#define BIND2_R 'n'
#define BIND2_ESC KEY_ESC
#define BIND2_RET KEY_RETURN

//bindings to eliminate excess keys for faster response -- from about ~12ms to about ~6ms per loop
#define BIND3_3 'd'
#define BIND3_4 'f'
#define BIND3_5 'j'
#define BIND3_6 'k'
#define BIND3_L 'v'
#define BIND3_R 'n'



//Pinout IN ORDER AROUND THE BOARD COUNTER-CLOCKWISE
//0,1,2,3 for encoders
#define BT_1 4
#define BT_2 5
#define BT_3 6
#define BT_4 7

#define BT_5 8
#define BT_6 9
#define BT_7 10
#define BT_8 16

#define BT_L 14
#define BT_R 15

#define BT_ESC 18
#define BT_RET 19

//used to keep controller from doing anything when plugged in incase of shorts or bad connections
//#define ABORT 23


//Keybind arrays
uint8_t keyBinds[] = { BIND_1, BIND_2, BIND_3, BIND_4, BIND_5, BIND_6, BIND_7, BIND_8, BIND_L, BIND_R, BIND_ESC, BIND_RET };
uint8_t keyBindsNav[] = { BIND2_1, BIND2_2, BIND2_3, BIND2_4, BIND2_5, BIND2_6, BIND2_7, BIND2_8, BIND2_L, BIND2_R, BIND2_ESC, BIND2_RET };
uint8_t keyBindsFast[] = { BIND3_3, BIND3_4, BIND3_5, BIND3_6, BIND3_L, BIND3_R };

uint8_t pinouts[] = { BT_1, BT_2, BT_3, BT_4, BT_5, BT_6, BT_7, BT_8, BT_L, BT_R, BT_ESC, BT_RET};
uint8_t pinoutsFast[] = {BT_3, BT_4, BT_5, BT_6, BT_L, BT_R, BT_ESC, BT_RET};
uint8_t pinoutCount = sizeof(pinouts) / sizeof(pinouts[0]);
uint8_t pinoutCountFast = sizeof(pinoutsFast) / sizeof(pinouts[0]);

//decides what keybinds to use
int whatBind = 0;

//Encoder stuff
#define MOUSE_SENS 35   //default 5
Encoder encL(3, 2), encR(1, 20); //should be 1,0 but pin 0 seems to have stopped working on my board
long knobL = 0;
long knobR = 0;
long prev_knobL = 0;
long prev_knobR = 0;

//used for testing loop time
int prevTime = 0;
int time = 0;



void setup() {
//ABORT
  /*while(ABORT == HIGH){
    delay(3000);
    Serial.print("ABORT is HIGH, delaying start");
  }*/

  //setup pins
  for (int i = 0; i <= pinoutCount; i++) {
    pinMode(pinouts[i], INPUT);
  }
  //pinMode(ABORT, INPUT);

  Serial.begin(9600);
  Keyboard.begin();
  Mouse.begin();
}




void loop() {

  //prevTime = micros();

  //encodering
  knobL = encL.read();
  knobR = encR.read();

  //move mouse if knobs move
  if(knobL != prev_knobL || knobR != prev_knobR){
    //horizontal
    Mouse.move(0, (knobL - prev_knobL) * MOUSE_SENS);
    //vertical
    Mouse.move((knobR - prev_knobR) * MOUSE_SENS, 0);

    //update knob position    
    prev_knobL = knobL;
    prev_knobR = knobR;
  }
  

  //Key Checking
  if (whatBind == 0) {                        //standard binding
    for (int i = 0; i < pinoutCount; i++) {
      if (digitalRead(pinouts[i]) == HIGH) {
        Keyboard.press(keyBinds[i]);        
      } else {
        Keyboard.release(keyBinds[i]);
      }
    }
  } 
  else if (whatBind == 1){                    //alternative with navigation
    for (int i = 0; i < pinoutCount; i++) {
      if (digitalRead(pinouts[i]) == HIGH) {
        Keyboard.press(keyBindsNav[i]);        
      } else {
        Keyboard.release(keyBindsNav[i]);
      }
    }
  } 
  else if (whatBind == 2){                    //fast binding
    for (int i = 0; i < pinoutCountFast; i++) {
      if (digitalRead(pinoutsFast[i]) == HIGH) {
        Keyboard.press(keyBindsFast[i]);        
      } else {
        Keyboard.release(keyBindsFast[i]);
      }
    }
  }
  

  //change binding by holding esc and bt 1
  if (digitalRead(BT_ESC) == HIGH && digitalRead(BT_1) == HIGH){

    //release keys being pressed
    Keyboard.release(BIND_1);
    Keyboard.release(BIND2_1);
    Keyboard.release(BIND_ESC);
    Keyboard.release(BIND2_ESC);

    delay(1000);

    //mouse moves to indicate which mode it switches to
    //up = mode 1; right = mode 2; down = mode 3
    if (whatBind == 0){
      whatBind = 1;
      Serial.println("mode 2: alternative");
      Mouse.move(100, 0); //move right
    } 
    else if (whatBind == 1){
      whatBind = 2;
      Serial.println("mode 3: fast");
      Mouse.move(0, 100); //move down
    }
    else if (whatBind == 2){
      whatBind = 0;
      Serial.println("mode 1: normal");
      Mouse.move(0, -100); //move up
    }
  }


  //time = micros() - prevTime;
  //Serial.println(time);
  
}



//for osu
int checkButtonsFaster(){
  if (digitalRead(BT_4) == HIGH) {
    Keyboard.press(BIND_4);
  } else {
    Keyboard.release(BIND_4);
  }
  if (digitalRead(BT_5) == HIGH) {
    Keyboard.press(BIND_5);
  } else {
    Keyboard.release(BIND_5);
  }
 
  if (digitalRead(BT_ESC) == HIGH) {
    Keyboard.press(BIND_ESC);
  } else {
    Keyboard.release(BIND_ESC);
  }
  if (digitalRead(BT_RET) == HIGH) {
    Keyboard.press(BIND_RET);
  } else {
    Keyboard.release(BIND_RET);
  }
}




