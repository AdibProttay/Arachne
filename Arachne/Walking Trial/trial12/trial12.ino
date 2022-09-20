#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include<SoftwareSerial.h>
SoftwareSerial bluetooth(4,3);

Adafruit_PWMServoDriver pwmA = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmB = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates


char command;
int Speed;

int angles[] = {
    60, 40, 80, 60, 90, 10, 70, 20, -20, 60, 65, 120, 10, 90, 110, 20, 15, 30
};

int anglesUpdate[] = {
    60, 40, 80, 60, 90, 10, 70, 20, -20, 60, 65, 120, 10, 90, 110, 20, 15, 30
};

// angle direction zero means negative, one means positive
int directions[] = {
  1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0
};


//delay integer
int d=350;


void setup() {
  pwmA.begin();
  pwmB.begin();
  pwmA.setOscillatorFrequency(27000000);
  pwmB.setOscillatorFrequency(27000000);
  pwmA.setPWMFreq(SERVO_FREQ); 
  pwmB.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
  delay(10);

  Serial.begin(9600);
  bluetooth.begin(9600);
}

int angletopulse(int ang){
  int pulse= map(ang,0,180,SERVOMIN,SERVOMAX);
  return pulse;
}

void runservo( int pin ,int angle ) {
  if(pin<=8){
    pwmB.setPWM(pin, 0, angletopulse(angle));
  }
  else
  {
    pwmA.setPWM(pin-9, 0, angletopulse(angle));
  }
  anglesUpdate[pin]=angle;
}

void loop() {
  if(bluetooth.available()) {
    command=bluetooth.read();
    Serial.println(command);
  }

  
  if (command=='S'){
    //Stop();
  }
  if (command=='F'){
//    standStill();
  }
  if (command=='B'){
    //Forward();
  }
  if (command=='R'){
    //Right();
  }
  if (command=='L'){
   // Left();
  }
  if (command=='I'){
   // Back_Left();
  }

   runservo(0,40);
  
}
