// Useless Arduino by SjFleischmann
// https://www.thingiverse.com/thing:415296
// Comments and schematics by BrainlessSteel.NL

#include <Servo.h> // include library to controll the servo

Servo servo_1; // defining a servo
int pos = 0; // defining a a variable for the position of the servo
int switchState; // defining a a variable for the  position of the switch

// ----------------------------------- SETUP -----------------------------------
void setup(){
  servo_1.attach(9); // setting the pin for the servo
  pinMode(10, INPUT); // setting the pin for the switch
  digitalWrite(10, HIGH); // make sure inputpin is HIGH if switch is not active. (set it as PULL UP)
  servo_1.write(102); // bring servo to rest position
}

// --------------------------------- MAIN LOOP ---------------------------------
void loop(){
  switchState = digitalRead(10); // get the state of the switch
  if(switchState==LOW){ // check if the switch is flipt [if (condition)]
    delay(100); // wait 100 milliseconds [delay(wait time in milliseconds)]
    servo_1.write(0); // move servo to push the switch
    delay(300); // wait 300 milliseconds

    // slwoly bring servo back to rest position using a for loop
    for(pos = 0; pos < 102; pos+=2){ // start a for loop [for (Set or define the used variable; condition; increment)]
      servo_1.write(pos); // move servo to position pos
      delay(5); // wait 5 milliseconds
    }
  }
  delay(5); // wait 5 milliseconds
}
