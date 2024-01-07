#include <Servo.h> 
#include <Adafruit_NeoPixel.h>
#define NUM_LEDS 1
#define DATA_PIN 3
#define PIN 6
#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // neo pixel object that is used to control the LED strip

Servo servo_1; 
int pos = 0; 
int switchState; 
const int CLOSED=110;
const int MIDPOINT=90;


void setColor(int r, int g, int b) {
  pixels.setPixelColor(0, pixels.Color(g,r,b));
  pixels.show();
}

void setup() {   
  //pinMode(10, INPUT); 
  pinMode(10, INPUT_PULLUP);
  digitalWrite(10, HIGH); 
  servo_1.write(CLOSED);
  randomSeed(analogRead(0));   
  pixels.begin();   
} 

//102 = closed
//0 = open (pressing switch)

void loop(){ 
  setColor(128,0,128);
  switchState = digitalRead(10); 
  if(switchState==LOW) { 
    setColor(0,255,0);
    servo_1.attach(9); 
    switch(random(1,5)){
      case 1:
        seqNormal();
        break;
      case 2:
        seqShy();
        break;
      default:
        seqNormal();
        break;
    }
    delay(150);    
    servo_1.detach();
  } 
  delay(5); 
  if(random(1, 6000)==1){
    servo_1.attach(9); 
    peek();
    servo_1.detach();
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
  delay(500);
  moveArm(MIDPOINT+10,5);
  delay(500);
  moveArm(0,0);
  delay(300);
  moveArm(CLOSED,0);
}

void seqNormal(){
  delay(50); 
  moveArm(0,0);
  delay(300); 
  moveArm(CLOSED,5);
}


void moveArm(int newPos, int ms){    
  if(ms>0){
    int curPos = servo_1.read();
    if(newPos>curPos){
      for(pos = curPos; pos < newPos; pos+=2){ 
          servo_1.write(pos); 
          delay(ms); 
        } 
    } else {    
      for(pos = curPos; pos > newPos; pos-=2){ 
        servo_1.write(pos); 
        delay(ms); 
      } 
    }
  } else {
    servo_1.write(newPos);
    delay(50);
  }

}
