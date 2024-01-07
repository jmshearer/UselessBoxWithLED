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
const int MIDPOINT=70;


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

int nCol = 128;
bool ascending=true;
int nRun=0;

void loop(){ 
  setColor(nCol,0,nCol);
  switchState = digitalRead(10); 
  if(switchState==LOW) { 
    nRun++;
    setColor(0,255,0);
    servo_1.attach(9);
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
    setColor(nCol,0,nCol);        
    delay(150);    
    servo_1.detach();
  } 
  if(ascending){
    nCol+=1;
  } else {
    nCol-=1;
  }
  if(nCol>254){    
    ascending=false;
  }
  if(nCol<129){
    ascending=true;
  }
  delay(20); 
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
  delay(250);
  moveArm(MIDPOINT+10,0);
  delay(150);
  moveArm(0,0);
  delay(250);
  moveArm(CLOSED,0);
}

void seqAngry(){  
  
  delay(50);
  moveArm(0,0);  
  delay(250);  
  
  setColor(255,0,0);
  moveArm(40,5);
  setColor(0,255,0);
  moveArm(0,0);
  delay(50);

  setColor(255,0,0);
  moveArm(40,5);
  setColor(0,255,0);
  moveArm(0,0);
  delay(50);

  setColor(255,0,0);
  moveArm(40,5);
  setColor(0,255,0);
  moveArm(0,0);
  delay(50);
  
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
