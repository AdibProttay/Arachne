
#include <Servo.h>


//leg 6 motors
int servoPin1 = 2; 
int servoPin2 = 3; 
int servoPin3 = 4; 
//create servo objects
Servo Servo1, Servo2, Servo3;


void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");



  //define leg6
  Servo1.attach(servoPin1); 
  Servo2.attach(servoPin2); 
  Servo3.attach(servoPin3); 
}

void loop() {
  
  Servo1.write(105);
  Servo1.write(75);
  
  

 }
