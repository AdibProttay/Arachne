#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>
#include<SoftwareSerial.h>


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
    60, 40, 80, 60, 90, 10, 70, 20, -55, 60, 65, 120, 10, 90, 110, 20, 15, 30
};

int anglesUpdate[] = {
    60, 40, 80, 60, 90, 10, 70, 20, 0, 60, 65, 120, 10, 90, 110, 20, 15, 30
};

// angle direction zero means negative, one means positive
int directions[] = {
  1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0
};

//delay integer
int d=350;
void setup() {
  Serial.begin(9600);
  

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

void upleg(int number, int angle){
    if(number=1){
        upmotor(1,angle);
    }
    if(number=2){
        upmotor(4,angle);
    }
    if(number=3){
        upmotor(7,angle);
    }
    if(number=4){
        upmotor(10,angle);
    }
    if(number=5){
        upmotor(13,angle);
    }
    if(number=6){
        upmotor(16,angle);
    }
}

void downleg(int number, int angle){
    if(number=1){
        downmotor(1,angle);
    }
    if(number=2){
        downmotor(4,angle);
    }
    if(number=3){
        downmotor(7,angle);
    }
    if(number=4){
        downmotor(10,angle);
    }
    if(number=5){
        downmotor(13,angle);
    }
    if(number=6){
        downmotor(16,angle);
    }
}

void forwardleg(int number, int angle){
    if(number=1){
        forwardmotor(0,angle);
    }
    if(number=2){
        forwardmotor(3,angle);
    }
    if(number=3){
        forwardmotor(6,angle);
    }
    if(number=4){
        forwardmotor(9,angle);
    }
    if(number=5){
        forwardmotor(15,angle);
    }
    if(number=6){
        forwardmotor(15,angle);
    }
}

void backwardleg(int number, int angle){
    if(number=1){
        backwardmotor(0,angle);
    }
    if(number=2){
        backwardmotor(3,angle);
    }
    if(number=3){
        backwardmotor(6,angle);
    }
    if(number=4){
        backwardmotor(9,angle);
    }
    if(number=5){
        backwardmotor(12,angle);
    }
    if(number=6){
        backwardmotor(13,angle);
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
    forwardmotor(0,30);
    upmotor(1,30);

    forwardmotor(6,30);
    upmotor(7,30);

    forwardmotor(12,30);
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
    forwardmotor(3,30);
    upmotor(4,40);

    forwardmotor(9,30);
    upmotor(10,40);

    forwardmotor(15,30);
    upmotor(16,40);
    delay(d);
    
    //step3
    initialAngle(4);

    initialAngle(10);

    initialAngle(16);  
    
    delay(d);
    //step4
  
    upmotor(1,30);

    upmotor(7,30);

    upmotor(13,30);
    
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

void moveForward(int angle) {
  //step1                          // initial position
   for (int i=0; i<18; i++) {
    runservo(i,angles[i]);
    }
    delay(d);
    stroke1(angle/2);

    while(true)
    {
      stroke2(angle);
      stroke3(angle);
      if(c!='f')
     {
      break;
     }
    }
    //for (int j=0; j<cycle; j++) {
    //stroke2(angle);
    //stroke3(angle);
    //}
    delay(d);
 }

 void moveBackward(int angle) {
  //step1                          // initial position
   for (int i=0; i<18; i++) {
    runservo(i,angles[i]);
    }
    delay(d);
    bstroke1(angle/2);
    
    while(true)
    {
    bstroke2(angle);
    bstroke1(angle);
    if(c!='b')
     {
      break;
     }
    }
    delay(d);
 }
 
void stroke1(int angle){
     //step2                          //up and forward leg 1,3,5
     forwardmotor(0, angle);
     upmotor(1,30);

     forwardmotor(6,angle);
     upmotor(7,30);

     forwardmotor(12,angle);
     upmotor(13,30); 
 
     backwardmotor(3,angle);             //backward leg 2, 4, 6 
     backwardmotor(9,angle);
     backwardmotor(15,angle);
     delay(d);
    
    //step3
     initialAngle(1);                //down leg 1, 3, 5
     initialAngle(7);
     initialAngle(13);
     delay(d);
    }
  
void stroke2(int angle){
    //step4
    upmotor(4,30);                  //up and forward leg 2, 4, 6
    forwardmotor(3,angle);
    upmotor(10,30);
    forwardmotor(9,angle);
    upmotor(16,30);
    forwardmotor(15,angle);
    
   //step5
     backwardmotor(0,angle);             //backward leg 1,3,5
     backwardmotor(6,angle);
     backwardmotor(12,angle);
    delay(d);

    //step6
    initialAngle(4);                 //down leg 2, 4, 6

    initialAngle(10);

    initialAngle(16);
    delay(d);
 }
   
void stroke3(int angle){
         //step2                          //up and forward leg 1,3,5
         
     forwardmotor(0,angle);
     upmotor(1,30);

     forwardmotor(6,angle);
     upmotor(7,30);

     forwardmotor(12,angle);
     upmotor(13,30); 
     
     backwardmotor(3,angle);             //backward leg 2, 4, 6 
     backwardmotor(9,angle);
     backwardmotor(15,angle);
     delay(d);
    
      //step3
     initialAngle(1);                //down leg 1, 3, 5
     initialAngle(7);
     initialAngle(13);
     delay(d);
 }

 void bstroke1(int angle){
     //step2                          //up and forward leg 1,3,5
     backwardmotor(0, angle);
     upmotor(1,30);

     backwardmotor(6,angle);
     upmotor(7,30);

     backwardmotor(12,angle);
     upmotor(13,30); 
 
     forwardmotor(3,angle);             //backward leg 2, 4, 6 
     forwardmotor(9,angle);
     forwardmotor(15,angle);
     delay(d);
    
    //step3
     initialAngle(1);                //down leg 1, 3, 5
     initialAngle(7);
     initialAngle(13);
     delay(d);
    }
  
void bstroke2(int angle){
    //step4
    upmotor(4,30);                  //up and forward leg 2, 4, 6
    backwardmotor(3,angle);
    upmotor(10,30);
    backwardmotor(9,angle);
    upmotor(16,30);
    backwardmotor(15,angle);
    
   //step5
     forwardmotor(0,angle);             //backward leg 1,3,5
     forwardmotor(6,angle);
     forwardmotor(12,angle);
    delay(d);

    //step6
    initialAngle(4);                 //down leg 2, 4, 6

    initialAngle(10);

    initialAngle(16);
    delay(d);
 }

void MoveRight(int angle) {
     //step1
     forwardmotor(3,angle); 
     upmotor(4,30);

     forwardmotor(15,angle);
     upmotor(16,30);

     backwardmotor(9,angle);
     upmotor(10,30); 
 
     delay(d);
    
     //step2
     initialAngle(4);                
     initialAngle(10);
     initialAngle(16);
     delay(d);
     
     while(1){
     //step3
     forwardmotor(6,angle);
     upmotor(7,30);

     backwardmotor(0,angle);
     upmotor(1,30);

     backwardmotor(12,angle);
     upmotor(13,30); 

     initialAngle(3);                
     initialAngle(9);
     initialAngle(15);
     
 
     delay(d);
    
     //step4
     initialAngle(1);                
     initialAngle(7);
     initialAngle(13);
     

     //step5
     forwardmotor(3,angle);
     upmotor(4,30);

     forwardmotor(15,angle);
     upmotor(16,30);

     backwardmotor(9,angle);
     upmotor(10,30);

     initialAngle(0);                
     initialAngle(6);
     initialAngle(12);
 
     delay(d);
    
     //step2
     initialAngle(4);                
     initialAngle(10);
     initialAngle(16);
     delay(d);
     if(c!='r')
     {
      break;
     }
     }

}

void MoveLeft(int angle) {
     //step1
     forwardmotor(9,angle);
     upmotor(10,30);

     backwardmotor(15,angle);
     upmotor(16,30);

     backwardmotor(3,angle);
     upmotor(4,30); 
 
     delay(d);
    
     //step2
     initialAngle(4);                
     initialAngle(10);
     initialAngle(16);
     delay(d);

     //step3
     while(true){
     forwardmotor(0,angle);
     upmotor(1,30);

     forwardmotor(12,angle);
     upmotor(13,30);

     backwardmotor(6,angle);
     upmotor(7,30); 

     initialAngle(3);                
     initialAngle(9);
     initialAngle(15);
 
     delay(d);
    
     //step4
     initialAngle(1);                
     initialAngle(7);
     initialAngle(13);
     delay(d);

     
     //step1
     forwardmotor(9,angle);
     upmotor(10,30);

     backwardmotor(15,angle);
     upmotor(16,30);

     backwardmotor(3,angle);
     upmotor(4,30); 

     initialAngle(0);                
     initialAngle(6);
     initialAngle(12);
 
     delay(d);
    
     //step2
     initialAngle(4);                
     initialAngle(10);
     initialAngle(16);
     delay(d);
     if(c!='l')
     {
      break;
     }
     }
}

void loop() { 
  if(Serial.available()==0)
  {
    standStill();
  }
  else
  {
    char command=Serial.read();
    char c=command;
    if(command=='s') //WALK FORWARD
    {
      standStill();
    }
    else if(command=='f')
    {
      moveForward(40);
    }
    else if(command=='b')
    {
     moveBackward(40); 
    }
    else if(command=='r')
   {
    MoveRight(20);
   }
   else if(command=='l')
   {
    MoveLeft(20);
   }
    
     
   }
}
