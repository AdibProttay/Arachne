#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include<SoftwareSerial.h>
SoftwareSerial bluetooth(4,3);

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwmA = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmB = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 0;
char command;
int angles[] = {
    60, 40, 80, 60, 90, 10, 70, 20, -20, 60, 65, 120, 10, 95, 110, 20, 15, 30
};

int anglesUpdate[] = {
    60, 40, 80, 60, 90, 10, 70, 20, -20, 60, 65, 120, 10, 95, 110, 20, 15, 30
};

// angle direction zero means negative, one means positive
int directions[] = {
  1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0
};

//delay integer
int d=500;
void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);

  pwmA.begin();
  pwmB.begin();
  pwmA.setOscillatorFrequency(27000000);
  pwmB.setOscillatorFrequency(27000000);
  pwmA.setPWMFreq(SERVO_FREQ); 
  pwmB.setPWMFreq(SERVO_FREQ); // Analog servos run at ~50 Hz updates
  delay(10);

}
int angletopulse(int ang){
  int pulse= map(ang,0,180,SERVOMIN,SERVOMAX);
  return pulse;
}

// You can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. It's not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;   // 1,000,000 us per second
  pulselength /= SERVO_FREQ;   // Analog servos run at ~60 Hz updates
  Serial.print(pulselength); Serial.println(" us per period"); 
  pulselength /= 4096;  // 12 bits of resolution
  Serial.print(pulselength); Serial.println(" us per bit"); 
  pulse *= 1000000;  // convert input seconds to us
  pulse /= pulselength;
  Serial.println(pulse);
  pwmA.setPWM(n, 0, pulse);
  pwmB.setPWM(n, 0, pulse);
}

void loop() {
  int ang=0;
  int pulselength=0;

  if(bluetooth.available()) {
    command=bluetooth.read();
    Serial.println(command);
  }
  
  if (command=='S'){
     standStill();
  }
  if (command=='F'){
    moveForward3();
    moveForward4();
    
  }
  if (command=='B'){
    moveBackward1();
    moveBackward2();
  }
  if (command=='R'){
    moveRight();
  }
  if (command=='L'){
    moveLeft();
  }
  if (command=='I'){
    //Back_Left();
  }
  if (command=='G'){
    //Back_Right();
  }
  if (command=='H'){
    //Front_Right();
  }
  if (command=='J'){
    //Front_Right();
  } 
  
   
  //standStill();
  //moveForward(5);
  moveForward3();
  moveForward4();
  //delay(10000);
  //moveBackward1();
  //moveBackward2();
  //moveRight();
  //moveLeft();
  //Moveleg1();
  //Moveleg1();
  //Moveleg2();
  //Moveleg3();
  //Moveleg4();
  //Moveleg5();
  //Moveleg6();
  
  // Drive each servo one at a time using setPWM()
  Serial.println(servonum);
  Serial.println(servonum);
    
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

void initialAngle( int pin ) {
  runservo(pin,angles[pin]);
}

void standStill() {
  for (int i=0; i<18; i++) {

    runservo(i,angles[i]);
}
    delay(500);
}

void upmotor(int pin, int angle) {
  if(directions[pin]==1){
    runservo(pin,anglesUpdate[pin]+angle);
  }
  else
  {
    runservo(pin,anglesUpdate[pin]-angle);
  }
 }

void downmotor(int pin, int angle) {
  if(directions[pin]==1){
    runservo(pin,anglesUpdate[pin]-angle);
  }
  else
  {
    runservo(pin,anglesUpdate[pin]+angle);
  }
}

void forwardmotor(int pin, int angle) {
  if(directions[pin]==1){
    runservo(pin,anglesUpdate[pin]+angle);
  }
  else
  {
    runservo(pin,anglesUpdate[pin]-angle);
  }
}

void backwardmotor(int pin, int angle) {
  if(directions[pin]==1){
    runservo(pin,anglesUpdate[pin]-angle);
  }
  else
  {
    runservo(pin,anglesUpdate[pin]+angle);
  }
}

void moveForward1() {
  //step1
  initialAngle(0);
  initialAngle(1);
  initialAngle(2);

  initialAngle(6);
  initialAngle(7);
  initialAngle(8);

  initialAngle(12);
  initialAngle(13);
  initialAngle(14);
  delay(d);
    
  //step2 
    forwardmotor(0,20);
    upmotor(1,30);

    forwardmotor(6,20);
    upmotor(7,30);

    forwardmotor(12,20);
    upmotor(13,30); 
    
    delay(d);
   //step3
    initialAngle(1);

    initialAngle(7);

    initialAngle(13);
    delay(d);

   //step4
    
    upmotor(4,30);

    upmotor(10,30);

    upmotor(16,30);
    
    delay(d);
    
   //step5
    initialAngle(0);

    initialAngle(6);

    initialAngle(12);
    delay(d);

    //step6
    initialAngle(4);

    initialAngle(10);

    initialAngle(16);
    delay(d);
 }

void moveForward2() {
  //step1
    initialAngle(3);
    initialAngle(4);
    initialAngle(5);

    initialAngle(9);
    initialAngle(10);
    initialAngle(11);

    initialAngle(15);
    initialAngle(16);
    initialAngle(17);
    delay(d);
   
   //step2
    forwardmotor(3,20);
    upmotor(4,40);

    forwardmotor(9,20);
    upmotor(10,40);

    forwardmotor(15,20);
    upmotor(16,40);
    delay(d);
    
    //step3
    initialAngle(4);

    initialAngle(10);

    initialAngle(16);  
    
    delay(d);
    //step4
  
    upmotor(1,40);

    upmotor(7,40);

    upmotor(13,40);
    
    delay(d);
    
    //step5
    initialAngle(3);

    initialAngle(9);

    initialAngle(15);
    
    delay(d);
    
    //step6
    initialAngle(1);

    initialAngle(7);

    initialAngle(13);
    
    delay(d);
 
}
void moveBackward1() {
  //step1
  runservo(0,angles[0]);
  runservo(1,angles[1]);
  runservo(2,angles[2]);

  runservo(6,angles[6]);
  runservo(7,angles[7]);
  runservo(8,angles[8]);

  runservo(12,angles[12]);
  runservo(13,angles[13]);
  runservo(14,angles[14]);
    delay(d);
    
  //step2 
    backwardmotor(0,20);
    upmotor(1,40);

    backwardmotor(6,20);
    upmotor(7,40);

    backwardmotor(12,20);
    upmotor(13,40); 
    
    delay(d);
   //step3
    runservo(1,angles[1]);

    runservo(7,angles[7]);

    runservo(13,angles[13]);
    delay(d);

   //step4
    
    upmotor(4,40);

    upmotor(10,40);

    upmotor(16,40);
    
    delay(d);
    
   //step5
    runservo(0,angles[0]);

    runservo(6,angles[6]);

    runservo(12,angles[12]);
    
    delay(d);

    //step6
    runservo(3,angles[3]);
    runservo(4,angles[4]);
    runservo(5,angles[5]);

    runservo(9,angles[9]);
    runservo(10,angles[10]);
    runservo(11,angles[11]);

    runservo(15,angles[15]);
    runservo(16,angles[16]);
    runservo(17,angles[17]);
    
    delay(d);
 }

void moveBackward2() {
  //step1
    runservo(3,angles[3]);
    runservo(4,angles[4]);
    runservo(5,angles[5]);

    runservo(9,angles[9]);
    runservo(10,angles[10]);
    runservo(11,angles[11]);

    runservo(15,angles[15]);
    runservo(16,angles[16]);
    runservo(17,angles[17]);
    
    delay(d);
   //step2
    backwardmotor(3,20);
    upmotor(4,40);

    backwardmotor(9,20);
    upmotor(10,40);

    backwardmotor(15,20);
    upmotor(16,40);
    
    delay(d);
    //step3
    runservo(4,angles[4]);
    
    runservo(10,angles[10]);
    
    runservo(16,angles[16]);  
    
    delay(d);
    //step4
  
    upmotor(1,40);

    upmotor(7,40);

    upmotor(13,40);
    
    delay(d);
    
    //step5
    runservo(3,angles[3]);
    
    runservo(9,angles[9]);
    
    runservo(15,angles[15]);
    
    delay(d);
    
    //step6
    
    runservo(1,angles[1]);
    
    runservo(7,angles[7]);
    
    runservo(13,angles[13]);
    
    delay(d);
 
}

void moveRight() {
    //step1
    for (int i=0; i<18; i++) {
    runservo(i,angles[i]);
    }
    delay(d);

    //step2
    backwardmotor(0,20);
    upmotor(1,30);
    delay(d);
    downmotor(1,30);

    backwardmotor(9,20);
    upmotor(10,30);
    delay(d);
    downmotor(10,30);

    backwardmotor(12,20);
    upmotor(13,30);
    delay(d);
    downmotor(13,30);
  
    forwardmotor(3,20);
    upmotor(4,30);
    delay(d);
    downmotor(4,30);

    forwardmotor(6,20);
    upmotor(7,30);
    delay(d);
    downmotor(7,30);

    forwardmotor(15,20);
    upmotor(16,30);
    delay(d);
    downmotor(16,30);
    
    //step3
    delay(d);
    forwardmotor(0,20);
    forwardmotor(9,20);
    forwardmotor(12,20);

    backwardmotor(3,20);
    backwardmotor(6,20);
    backwardmotor(15,20);

    delay(d);
 }

 void moveLeft() {
    //step1
   for (int i=0; i<18; i++) {
    runservo(i,angles[i]);
    }
    delay(d);

    //step2
    forwardmotor(0,20);
    upmotor(1,30);
    delay(d);
    downmotor(1,30);

    forwardmotor(9,20);
    upmotor(10,30);
    delay(d);
    downmotor(10,30);

    forwardmotor(12,20);
    upmotor(13,30);
    delay(d);
    downmotor(13,30);

    backwardmotor(3,20);
    upmotor(4,30);
    delay(d);
    downmotor(4,30);

    backwardmotor(6,20);
    upmotor(7,30);
    delay(d);
    downmotor(7,30);

    backwardmotor(15,20);
    upmotor(16,30);
    delay(d);
    downmotor(16,30);

    
    //step3
    delay(d);
    backwardmotor(0,20);
    backwardmotor(9,20);
    backwardmotor(12,20);
    
    forwardmotor(3,20);
    forwardmotor(6,20);
    forwardmotor(15,20);
 
    delay(d);
 }

void moveForward3() {
  //step1                          // initial position
   for (int i=0; i<18; i++) {
    runservo(i,angles[i]);
    }
    delay(d);
    
  //step2                          //up and forward leg 1,3,5
    forwardmotor(0,30);
    upmotor(1,30);

    forwardmotor(6,30);
    upmotor(7,30);

    forwardmotor(12,30);
    upmotor(13,30); 
 
    backwardmotor(3,20);             //backward leg 2, 4, 6 
    backwardmotor(9,20);
    backwardmotor(15,20);
    delay(d);
    
   //step3
    initialAngle(1);                //down leg 1, 3, 5
    initialAngle(7);
    initialAngle(13);
    delay(d);

   //step4
    upmotor(4,30);                  //up and forward leg 2, 4, 6
    forwardmotor(3,20);
    upmotor(10,30);
    forwardmotor(9,20);
    upmotor(16,30);
    forwardmotor(15,20);
    delay(d);
    
   //step5
    initialAngle(0);                 //backward leg 1, 3, 5

    initialAngle(6);

    initialAngle(12);
    delay(d);

    //step6
    initialAngle(4);                 //down leg 2, 4, 6

    initialAngle(10);

    initialAngle(16);
    delay(d);
 }

void moveForward4() {
   //step1                           //initial position
    for (int i=0; i<18; i++) {
    runservo(i,angles[i]);
    }
    delay(d);
    
   //step2                           //up and forward leg 2, 4, 6
    forwardmotor(3,30);
    upmotor(4,30);

    forwardmotor(9,30);
    upmotor(10,30);

    forwardmotor(15,30);
    upmotor(16,30);

    backwardmotor(0,15);             //backward leg 1, 3, 5
    backwardmotor(6,20);
    backwardmotor(12,20);
    delay(d);
    
    //step3                           //down leg 2, 4, 6
    initialAngle(4);

    initialAngle(10);

    initialAngle(16);  
    delay(d);
    
    //step4                           //up and forward leg 1, 3, 5
    forwardmotor(0,20);
    upmotor(1,30);
    forwardmotor(6,20);
    upmotor(7,30);
    forwardmotor(12,20);
    upmotor(13,30);
    delay(d);
    
    //step5                           //backward leg 2,3, 4
    initialAngle(3);

    initialAngle(9);

    initialAngle(15);
    
    delay(d);
    
    //step6                            //down leg 1,3,5
    initialAngle(1);

    initialAngle(7);

    initialAngle(13);
    
    delay(d);
 }

 void moveForward(int cycle) {
  //step1                          // initial position
   for (int i=0; i<18; i++) {
    runservo(i,angles[i]);
    }
    delay(d);
    stroke1();
    
    for (int j=0; j<cycle; j++) {
    stroke2();
    stroke3();
    }
    delay(d);
 }
 
 void stroke1(){
     //step2                          //up and forward leg 1,3,5
     forwardmotor(0,30);
     upmotor(1,30);

     forwardmotor(6,30);
     upmotor(7,30);

     forwardmotor(12,30);
     upmotor(13,30); 
 
     backwardmotor(3,30);             //backward leg 2, 4, 6 
     backwardmotor(9,30);
     backwardmotor(15,30);
     delay(d);
    
    //step3
     initialAngle(1);                //down leg 1, 3, 5
     initialAngle(7);
     initialAngle(13);
     delay(d);
    }
  
  void stroke2(){
    //step4
    upmotor(4,30);                  //up and forward leg 2, 4, 6
    forwardmotor(3,60);
    upmotor(10,30);
    forwardmotor(9,60);
    upmotor(16,30);
    forwardmotor(15,60);
    delay(d);
    
   //step5
     backwardmotor(3,60);             //backward leg 1,3,5
     backwardmotor(9,60);
     backwardmotor(15,60);
    delay(d);

    //step6
    initialAngle(4);                 //down leg 2, 4, 6

    initialAngle(10);

    initialAngle(16);
    delay(d);
 }
   
 void stroke3(){
         //step2                          //up and forward leg 1,3,5
        forwardmotor(0,60);
        upmotor(1,30);

        forwardmotor(6,60);
        upmotor(7,30);

        forwardmotor(12,60);
        upmotor(13,30); 
 
        backwardmotor(3,60);             //backward leg 2, 4, 6 
        backwardmotor(9,60);
        backwardmotor(15,60);
        delay(d);
    
      //step3
        initialAngle(1);                //down leg 1, 3, 5
        initialAngle(7);
        initialAngle(13);
        delay(d);
 }






for (int i=0; i<10; i++) {
    moveForward1();
    moveForward2();
    }
for (int i=0; i<3; i++) {
    MoveRight();
    }
for (int i=0; i<6; i++) {
    moveBackward1();
    moveBackward2();
    }    
for (int i=0; i<3; i++) {
    moveLeft();
    }    














 
