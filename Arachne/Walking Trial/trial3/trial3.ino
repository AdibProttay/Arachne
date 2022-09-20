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
    20, 30, 80, 60, 30, 40, 45, 75, -20, 50, 65, 120, 30, 100, 110, 70, 15, 20
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

  //standStill();
  moveForward1();
  moveForward2();
  //Moveleg1();
  //Moveleg1();
  //Moveleg2();
  //Moveleg3();
  //Moveleg4();
  //Moveleg5();
  //Moveleg6();
  //individual servo test
    //servo(10,70);
    //delay(500);
    //servo(10,65);
    //delay(500);
    //servo(17,30);
  

    
  
  // Drive each servo one at a time using setPWM()
  Serial.println(servonum);
  Serial.println(servonum);
    

 }


void runservo( int pin ,int angle ) {
  if(pin<=2){
    pwmB.setPWM(pin, 0, angletopulse(angle));
  }
  else
  {
    if(pin<=8){
      pwmA.setPWM(pin+6, 0, angletopulse(angle));
    }
    else
    {
      pwmA.setPWM(pin-9, 0, angletopulse(angle));
    }
  }
}

void servo( int pin ,int angle ) {
  if(pin<=2){
    pwmB.setPWM(pin, 0, angletopulse(angle));
  }
  else
  {
    if(pin<=8){
      pwmA.setPWM(pin+6, 0, angletopulse(angle));
    }
    else
    {
      pwmA.setPWM(pin-9, 0, angletopulse(angle));
    }
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

 void Moveleg2() {
    runservo(3,angles[3]);
    runservo(4,angles[4]);
    runservo(5,angles[5]);
    delay(500);
    forwardmotor(3,30);
    upmotor(4,30);
    delay(500);
    runservo(4,angles[4]);
    //downmotor(1,30);
    delay(500);
    runservo(3,angles[3]);
    //backwardmotor(0,30);
    delay(500);
 }

 void Moveleg3() {
    runservo(6,angles[6]);
    runservo(7,angles[7]);
    runservo(8,angles[8]);
    delay(500);
    forwardmotor(6,30);
    upmotor(7,30);
    delay(500);
    runservo(7,angles[7]);
    //downmotor(1,30);
    delay(500);
    runservo(6,angles[6]);
    //backwardmotor(0,30);
    delay(500);
 }

 void Moveleg4() {
    runservo(9,angles[9]);
    runservo(10,angles[10]);
    runservo(11,angles[11]);
    delay(500);
    forwardmotor(9,30);
    upmotor(10,30);
    delay(500);
    runservo(10,angles[10]);
    //downmotor(1,30);
    delay(500);
    runservo(9,angles[9]);
    //backwardmotor(0,30);
    delay(500);
 }

 void Moveleg5() {
    runservo(12,angles[12]);
    runservo(13,angles[13]);
    runservo(14,angles[14]);
    delay(500);
    forwardmotor(12,30);
    upmotor(13,30);
    delay(500);
    runservo(13,angles[13]);
    //downmotor(1,30);
    delay(500);
    runservo(12,angles[12]);
    //backwardmotor(0,30);
    delay(500);
 }

 void Moveleg6() {
    runservo(15,angles[15]);
    runservo(16,angles[16]);
    runservo(17,angles[17]);
    delay(500);
    forwardmotor(15,30);
    upmotor(16,30);
    delay(500);
    runservo(16,angles[16]);
    //downmotor(1,30);
    delay(500);
    runservo(15,angles[15]);
    //backwardmotor(0,30);
    delay(500);
 }

void moveForward1() {
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
    delay(500);
    
  //step2 
    forwardmotor(0,30);
    upmotor(1,30);

    forwardmotor(6,30);
    upmotor(7,30);

    forwardmotor(12,30);
    upmotor(13,30); 
    
    delay(500);
   //step3
    runservo(1,angles[1]);

    runservo(7,angles[7]);

    runservo(13,angles[13]);
    delay(500);

   //step4
    
    upmotor(4,30);

    upmotor(10,30);

    upmotor(16,30);
    
    delay(500);
    
   //step5
    runservo(0,angles[0]);

    runservo(6,angles[6]);

    runservo(12,angles[12]);
    
    delay(500);

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
    
    delay(500);
 }

void moveForward2() {
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
    
    delay(500);
   //step2
    forwardmotor(3,30);
    upmotor(4,30);

    forwardmotor(9,30);
    upmotor(10,30);

    forwardmotor(15,30);
    upmotor(16,30);
    
    delay(500);
    //step3
    runservo(4,angles[4]);
    
    runservo(10,angles[10]);
    
    runservo(16,angles[16]);  
    
    delay(500);
    //step4
  
    upmotor(1,30);

    upmotor(7,30);

    upmotor(13,30);
    
    delay(500);
    
    //step5
    runservo(3,angles[3]);
    
    runservo(9,angles[9]);
    
    runservo(15,angles[15]);
    
    delay(500);
    
    //step6
    
    runservo(1,angles[1]);
    
    runservo(7,angles[7]);
    
    runservo(13,angles[13]);
    
    delay(500);
 
}
 
