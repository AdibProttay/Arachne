#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwmA = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwmB = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address you want
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);
// you can also call it with a different address and I2C interface
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire);

// Depending on your servo make, the pulse width min and max may vary, you 
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
#define SERVOMIN  150 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // This is the 'maximum' pulse length count (out of 4096)
#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 0;

int angles[] = {
    20, 30, 70, 60, 30, 40, 45, 75, -20, 50, 70, 120, 30, 100, 100, 70, 0, 20
};

// angle direction zero means negative, one means positive
int directions[] = {
  1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0
};


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

void loop() {
  int ang=0;
  int pulselength=0;

  //pwmB.setPWM(1,120));
  //delay(500);
  //pwmB.setPWM(1,100));
  //delay(500);
  //pwmA.setPWM(0,50));
  //delay(500);
  //pwmA.setPWM(0,100));
  //delay(500);
  //standStill();
  moveForward1();
  moveForward2();
  //Moveleg1();
  //moveleg2();
  //moveleg2();
  //moveleg3();
  //moveleg4();
  //moveleg5();
  //moveleg6();
  //leg6
    //servo(15,60);
    //servo(16,20);
    //servo(17,30);
  

    
  
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
}

void servo( int pin ,int angle ) {
  if(pin<=8){
    pwmB.setPWM(pin, 0, angletopulse(angle));
  }
  else
  {
    pwmA.setPWM(pin-9, 0, angletopulse(angle));
  }
}

void standStill() {
  for (int i=0; i<18; i++) {

    runservo(i,angles[i]);
}
    delay(500);
}

void upmotor(int pin, int angle) {
  if(directions[pin]==1){
    runservo(pin,angles[pin]+angle);
  }
  else
  {
    runservo(pin,angles[pin]-angle);
  }
 }

void downmotor(int pin, int angle) {
  if(directions[pin]==1){
    runservo(pin,angles[pin]-angle);
  }
  else
  {
    runservo(pin,angles[pin]+angle);
  }
}

void forwardmotor(int pin, int angle) {
  if(directions[pin]==1){
    runservo(pin,angles[pin]+angle);
  }
  else
  {
    runservo(pin,angles[pin]-angle);
  }
}

void backwardmotor(int pin, int angle) {
  if(directions[pin]==1){
    runservo(pin,angles[pin]-angle);
  }
  else
  {
    runservo(pin,angles[pin]+angle);
  }
}

void Moveleg1() {
    runservo(0,angles[0]);
    runservo(1,angles[1]);
    runservo(2,angles[2]);
    delay(500);
    forwardmotor(0,30);
    upmotor(1,30);
    delay(500);
    runservo(1,angles[1]);
    //downmotor(1,30);
    delay(500);
    runservo(0,angles[0]);
    //backwardmotor(0,30);
    delay(500);
 }

void moveForward1() {
  //step1
  //runservo(i,angles[i]);
    servo(0,20);
    servo(1,30);
    servo(2,80);

    servo(6,45);
    servo(7,75);
    servo(8,-30);

    servo(12,30);
    servo(13,100);
    servo(14,100);
    
    delay(500);
    
  //step2  
    servo(0,50);
    servo(1,60);
    servo(2,80);

    servo(6,15);
    servo(7,45);
    servo(8,-30);
    
    servo(12,60);
    servo(13,130);
    servo(14,100);
    
    delay(500);
   //step3
    
    servo(0,50);
    servo(1,30);
    servo(2,80);

    servo(6,15);
    servo(7,75);
    servo(8,-30);

    servo(12,60);
    servo(13,100);
    servo(14,100);
    
    delay(500);

   //step4
    servo(3,60);
    servo(4,0);
    servo(5,40);

    servo(9,50);
    servo(10,100);
    servo(11,120);

    servo(15,60);
    servo(16,-10);
    servo(17,30);
    
    delay(500);
    
   //step5
    servo(0,20);
    servo(1,30);
    servo(2,80);

    servo(6,45);
    servo(7,75);
    servo(8,-30);

    servo(12,30);
    servo(13,100);
    servo(14,100);
    
    delay(500);

    //step6
    servo(3,60);
    servo(4,60);
    servo(5,40);

    servo(9,50);
    servo(10,70);
    servo(11,120);

    servo(15,60);
    servo(16,20);
    servo(17,30);
    
    
    delay(500);
 }

void moveForward2() {
  //step1
  
    servo(3,60);
    servo(4,30);
    servo(5,40);

    servo(9,50);
    servo(10,70);
    servo(11,120);

    servo(15,60);
    servo(16,20);
    servo(17,30);
     
    
    delay(500);
   //step2
    
    servo(3,30);
    servo(4,0);
    servo(5,40);

    servo(9,80);
    servo(10,100);
    servo(11,120);

    servo(15,30);
    servo(16,-10);
    servo(17,30); 
    
    delay(500);
    //step3
    
    servo(3,30);
    servo(4,30);
    servo(5,40);

    servo(9,80);
    servo(10,70);
    servo(11,120);

    servo(15,30);
    servo(16,20);
    servo(17,30); 
    
    delay(500);
    //step4  
    servo(0,20);
    servo(1,60);
    servo(2,80);

    servo(6,45);
    servo(7,45);
    servo(8,-30);
    
    servo(12,30);
    servo(13,130);
    servo(14,100);
    
    delay(500);
    
    //step5
    
    servo(3,60);
    servo(4,30);
    servo(5,40);

    servo(9,50);
    servo(10,70);
    servo(11,120);

    servo(15,60);
    servo(16,20);
    servo(17,30); 

    delay(500);
    
    //step6
    servo(0,20);
    servo(1,30);
    servo(2,80);

    servo(6,45);
    servo(7,75);
    servo(8,-30);

    servo(12,30);
    servo(13,100);
    servo(14,100);

    delay(500);
 
}

void moveleg1() {
    servo(0,20);
    servo(1,30);
    servo(2,70);
    delay(500);
    servo(0,50);
    servo(1,60);
    servo(2,70);
    delay(500);
    servo(0,50);
    servo(1,30);
    servo(2,70);
    delay(500);
    servo(0,20);
    servo(1,30);
    servo(2,70);
    delay(500);
 }

void moveleg2() {
    servo(3,60);
    servo(4,30);
    servo(5,40);
    delay(500);
    servo(3,30);
    servo(4,0);
    servo(5,40);
    delay(500);
    servo(3,30);
    servo(4,30);
    servo(5,40);
    delay(500);
    servo(3,60);
    servo(4,30);
    servo(5,40);
    delay(500);
 }

 void moveleg3() {
    servo(6,50);
    servo(7,75);
    servo(8,-20);
    delay(500);
    servo(6,20);
    servo(7,45);
    servo(8,-20);
    delay(500);
    servo(6,20);
    servo(7,75);
    servo(8,-20);
    delay(500);
    servo(6,50);
    servo(7,75);
    servo(8,-20);
    delay(500);
 }

 void moveleg4() {
    servo(9,50);
    servo(10,70);
    servo(11,120);
    delay(500);
    servo(9,80);
    servo(10,100);
    servo(11,120);
    delay(500);
    servo(9,80);
    servo(10,70);
    servo(11,120);
    delay(500);
    servo(9,50);
    servo(10,70);
    servo(11,120);
    delay(500);
 }

void moveleg5() {
    servo(12,30);
    servo(13,100);
    servo(14,100);
    delay(500);
    servo(12,60);
    servo(13,130);
    servo(14,100);
    delay(500);
    servo(12,60);
    servo(13,100);
    servo(14,100);
    delay(500);
    servo(12,30);
    servo(13,100);
    servo(14,100);
    delay(500);
 }

void moveleg6() {
    servo(15,60);
    servo(16,10);
    servo(17,20);
    delay(500);
    servo(15,30);
    servo(16,-20);
    servo(17,30);
    delay(500);
    servo(15,30);
    servo(16,10);
    servo(17,20);
    delay(500);
    servo(15,60);
    servo(16,10);
    servo(17,20);
    delay(500);
 }
