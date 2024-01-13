/************************************************************
 * Useless box with LED and some personality
 *
 * NOTE: This sketch should work with a regular Arduino as
 * well as an ESP32-based Arduino.
 ************************************************************/

//Add the servo library
#ifdef ESP32  
  #include "EspEasyServo.h";
#else
  #include <Servo.h> 
#endif

//...and the NeoPixel library
#include <Adafruit_NeoPixel.h>

//Configure the board parameters
#define LED_PIN A0
#define SWITCH_PIN 10

//Configure the LEDs
#define LED_COUNT 1
Adafruit_NeoPixel pixels(LED_COUNT, LED_PIN, NEO_RGB + NEO_KHZ800);
//...and set up some colors
uint32_t COLOR_IDLE    = pixels.Color(255,20,147);
uint32_t COLOR_RUNNING = pixels.Color(0,0,128);
uint32_t COLOR_ANGRY_1 = pixels.Color(0,0,128);
uint32_t COLOR_ANGRY_2 = pixels.Color(255,255,255);

//Configure the Servo
#ifdef ESP32
  EspEasyServo servo_1(LEDC_CHANNEL_0, GPIO_NUM_9);  
#else
  Servo servo_1; 
#endif
//...and define parameters (may vary by device)
const int CLOSED=140;
const int MIDPOINT=70;
const int OPEN=0;

//Set some basics
int lastServoPosition = CLOSED;
void setServo(int position){
  #if ESP32
    servo_1.setServo(position);
  #else
    servo_1.write(position);
  #endif
}

void setColor(int r, int g, int b){
  setColor(pixels.Color(r,g,b));
}

void setColor(uint32_t c) {  
  setColor(c,255);
}

void setColor(uint32_t c, int brightness){
  pixels.setPixelColor(0, c);
  pixels.setBrightness(brightness);
  pixels.show();
}


void setup() {       
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  digitalWrite(SWITCH_PIN, HIGH);   
  randomSeed(analogRead(0));   
  setServo(CLOSED);
  pixels.begin(); 
} 



bool ascending=true;
int nRun=0;
int nBrightness = 128;
int brightnessDelta = 1;

void loop(){   
  setColor(COLOR_IDLE, nBrightness);
  if(digitalRead(SWITCH_PIN)==LOW) { 
    nRun++;
    setColor(COLOR_RUNNING);
    if(nRun<3){
      seqNormal();
    } else {
      switch(random(1,6)){
        case 1:
        case 2:
          seqShy();
          break;
        case 3:
          seqAngry();
          break;      
        default:
          seqNormal();
          break;
      }
    }
    setColor(COLOR_IDLE, nBrightness);
    delay(150);        
  } 

  nBrightness += brightnessDelta;
  if(nBrightness>254){
    brightnessDelta=-1;
  }
  if(nBrightness<64){
    brightnessDelta=1;
  }  

  delay(20); 
  if(random(1, 6000)==1){    
    peek();    
  }
}

void peek(){
  delay(50);
  moveArm(MIDPOINT,10);
  delay(750);
  moveArm(CLOSED,0);
}

void seqShy(){
  delay(50);
  moveArm(MIDPOINT,5);
  delay(250);
  moveArm(MIDPOINT+10,0);
  delay(150);
  moveArm(0,0);
  delay(250);
  moveArm(CLOSED,0);
}

void seqAngry(){  
  delay(50);
  moveArm(OPEN,0);  
  delay(250);  
  
  for(int n = 0; n < 3; n++){ 
    setColor(COLOR_ANGRY_1);
    moveArm(40,5);
    setColor(COLOR_ANGRY_2);
    moveArm(0,0);
    delay(50);
  }

  moveArm(CLOSED,0);  
}

void seqNormal(){
  delay(50); 
  moveArm(OPEN,0);
  delay(300); 
  moveArm(CLOSED,5);
}


void moveArm(int newPos, int ms){      
  if(ms>0){    
    if(newPos>lastServoPosition){
      for(int pos = lastServoPosition; pos < newPos; pos+=2){ 
          setServo(pos);          
          delay(ms); 
        } 
    } else {    
      for(int pos = lastServoPosition; pos > newPos; pos-=2){ 
        setServo(pos);
        delay(ms); 
      } 
    }
  } else {
    setServo(newPos);
    delay(50);
  }  

  //Note that a better approach would be to ask the servo for its last position
  //but ESP32's library doesn't support querying the servo so we just keep track
  //of the last requested position
  lastServoPosition=newPos;
}
