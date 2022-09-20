/*************************************************** 
  This is an example for our Adafruit 16-channel PWM & Servo driver
  Servo test - this will drive 8 servos, one after the other on the
  first 8 pins of the PCA9685

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/815
  
  These drivers use I2C to communicate, 2 pins are required to  
  interface.

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
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

//leg 6 motors
int servoPin1 = 2; 
int servoPin2 = 3; 
int servoPin3 = 4; 
//create servo objects
Servo Servo1, Servo2, Servo3;

int angleToPulse(int ang)
{
    int pulse=map(ang,0,180,SERVOMIN,SERVOMAX);
    return pulse;
  }

void setup() {
  Serial.begin(9600);
  Serial.println("8 channel Servo test!");

  pwm.begin();
  /*
   * In theory the internal oscillator (clock) is 25MHz but it really isn't
   * that precise. You can 'calibrate' this by tweaking this number until
   * you get the PWM update frequency you're expecting!
   * The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
   * is used for calculating things like writeMicroseconds()
   * Analog servos run at ~50 Hz updates, It is importaint to use an
   * oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
   * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
   *    the I2C PCA9685 chip you are setting the value for.
   * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
   *    expected value (50Hz for most ESCs)
   * Setting the value here is specific to each individual I2C PCA9685 chip and
   * affects the calculations for the PWM update frequency. 
   * Failure to correctly set the int.osc value will cause unexpected PWM results
   */
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  //standStill();
  delay(10);

  //define leg6
  Servo1.attach(servoPin1); 
  Servo2.attach(servoPin2); 
  Servo3.attach(servoPin3); 
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
  pwm.setPWM(n, 0, pulse);
}

void loop() {
  int ang=0;
  int pulselength=0;

  
  //standStill();
    moveForward1();
  moveForward2();
  //moveleg1();
  //moveleg2();
  //moveleg3();
  //moveleg4();
  //moveleg5();
  //moveleg6();
  //delay(1000);
  // Drive each servo one at a time using setPWM()
  Serial.println(servonum);
  Serial.println(servonum);
    

 }

 void standStill() {
  //leg1
    pwm.setPWM(0, 0, angletopulse(20));
    pwm.setPWM(1, 0, angletopulse(30));
    pwm.setPWM(2, 0, angletopulse(70));
  //leg2
    pwm.setPWM(3, 0, angletopulse(30));
    pwm.setPWM(4, 0, angletopulse(70));
    pwm.setPWM(5, 0, angletopulse(40));
  //leg3
    pwm.setPWM(6, 0, angletopulse(45));
    pwm.setPWM(7, 0, angletopulse(75));
    pwm.setPWM(8, 0, angletopulse(-20));

  //leg4
    pwm.setPWM(9, 0, angletopulse(50));
    pwm.setPWM(10, 0, angletopulse(70));
    pwm.setPWM(11, 0, angletopulse(120));
  //leg5
    pwm.setPWM(12, 0, angletopulse(30));
    pwm.setPWM(13, 0, angletopulse(100));
    pwm.setPWM(14, 0, angletopulse(100));
  //leg6
    Servo1.write(105); 
    Servo2.write(35); 
    Servo3.write(120);
  delay(5000);
  
 }

 void standStillTEST() {
  //leg1
    pwm.setPWM(0, 0, angletopulse(20));
    pwm.setPWM(1, 0, angletopulse(30));
    pwm.setPWM(2, 0, angletopulse(70));
  //leg2
    //pwm.setPWM(3, 0, angletopulse(30));
    //pwm.setPWM(4, 0, angletopulse(70));
    //pwm.setPWM(5, 0, angletopulse(40));
  //leg3
    //pwm.setPWM(6, 0, angletopulse(45));
    //pwm.setPWM(7, 0, angletopulse(75));
    //pwm.setPWM(8, 0, angletopulse(-20));

  //leg4
    //pwm.setPWM(9, 0, angletopulse(50));
    //pwm.setPWM(10, 0, angletopulse(70));
    //pwm.setPWM(11, 0, angletopulse(120));
  //leg5
    //pwm.setPWM(12, 0, angletopulse(30));
    //pwm.setPWM(13, 0, angletopulse(100));
    //pwm.setPWM(14, 0, angletopulse(100));
  //leg6

  delay(5000);
  
 }

 void moveleg1() {
    pwm.setPWM(0, 0, angletopulse(20));
    pwm.setPWM(1, 0, angletopulse(30));
    pwm.setPWM(2, 0, angletopulse(70));
    delay(500);
    pwm.setPWM(0, 0, angletopulse(50));
    pwm.setPWM(1, 0, angletopulse(60));
    pwm.setPWM(2, 0, angletopulse(70));
    delay(500);
    pwm.setPWM(0, 0, angletopulse(50));
    pwm.setPWM(1, 0, angletopulse(30));
    pwm.setPWM(2, 0, angletopulse(70));
    delay(500);
    pwm.setPWM(0, 0, angletopulse(20));
    pwm.setPWM(1, 0, angletopulse(30));
    pwm.setPWM(2, 0, angletopulse(70));
 }

void moveleg2() {
    pwm.setPWM(3, 0, angletopulse(30));
    pwm.setPWM(4, 0, angletopulse(70));
    pwm.setPWM(5, 0, angletopulse(40));
    delay(500);
    pwm.setPWM(3, 0, angletopulse(0));
    pwm.setPWM(4, 0, angletopulse(40));
    pwm.setPWM(5, 0, angletopulse(40));
    delay(50);
    pwm.setPWM(3, 0, angletopulse(0));
    pwm.setPWM(4, 0, angletopulse(70));
    pwm.setPWM(5, 0, angletopulse(40));
    delay(500);
    pwm.setPWM(3, 0, angletopulse(30));
    pwm.setPWM(4, 0, angletopulse(70));
    pwm.setPWM(5, 0, angletopulse(40));
 }

 void moveleg3() {
    pwm.setPWM(6, 0, angletopulse(45));
    pwm.setPWM(7, 0, angletopulse(75));
    pwm.setPWM(8, 0, angletopulse(-20));
    delay(500);
    pwm.setPWM(6, 0, angletopulse(15));
    pwm.setPWM(7, 0, angletopulse(45));
    pwm.setPWM(8, 0, angletopulse(-20));
    delay(500);
    pwm.setPWM(6, 0, angletopulse(15));
    pwm.setPWM(7, 0, angletopulse(75));
    pwm.setPWM(8, 0, angletopulse(-20));
    delay(500);
    pwm.setPWM(6, 0, angletopulse(45));
    pwm.setPWM(7, 0, angletopulse(75));
    pwm.setPWM(8, 0, angletopulse(-20));
 }

 void moveleg4() {
    pwm.setPWM(9, 0, angletopulse(50));
    pwm.setPWM(10, 0, angletopulse(70));
    pwm.setPWM(11, 0, angletopulse(120));
    delay(500);
    pwm.setPWM(9, 0, angletopulse(80));
    pwm.setPWM(10, 0, angletopulse(100));
    pwm.setPWM(11, 0, angletopulse(120));
    delay(500);
    pwm.setPWM(9, 0, angletopulse(80));
    pwm.setPWM(10, 0, angletopulse(70));
    pwm.setPWM(11, 0, angletopulse(120));
    delay(500);
    pwm.setPWM(9, 0, angletopulse(50));
    pwm.setPWM(10, 0, angletopulse(70));
    pwm.setPWM(11, 0, angletopulse(120));
 }
void moveleg5() {
    pwm.setPWM(12, 0, angletopulse(30));
    pwm.setPWM(13, 0, angletopulse(100));
    pwm.setPWM(14, 0, angletopulse(100));
    delay(500);
    pwm.setPWM(12, 0, angletopulse(60));
    pwm.setPWM(13, 0, angletopulse(130));
    pwm.setPWM(14, 0, angletopulse(100));
    delay(500);
    pwm.setPWM(12, 0, angletopulse(60));
    pwm.setPWM(13, 0, angletopulse(100));
    pwm.setPWM(14, 0, angletopulse(100));
    delay(500);
    pwm.setPWM(12, 0, angletopulse(30));
    pwm.setPWM(13, 0, angletopulse(100));
    pwm.setPWM(14, 0, angletopulse(100));
 }

 void moveleg6() {
    Servo1.write(105); 
    Servo2.write(35); 
    Servo3.write(120);
    //delay(1000);
    Servo1.write(75); 
    Servo2.write(0); 
    Servo3.write(120);
    delay(1000);
    Servo1.write(75); 
    Servo2.write(35); 
    Servo3.write(120);
    delay(1000);
    Servo1.write(105); 
    Servo2.write(35); 
    Servo3.write(120);
    
 }

 void moveForward1() {
  //step1
    pwm.setPWM(0, 0, angletopulse(20));
    pwm.setPWM(1, 0, angletopulse(30));
    pwm.setPWM(2, 0, angletopulse(70));

    pwm.setPWM(6, 0, angletopulse(45));
    pwm.setPWM(7, 0, angletopulse(75));
    pwm.setPWM(8, 0, angletopulse(-20));

    pwm.setPWM(12, 0, angletopulse(30));
    pwm.setPWM(13, 0, angletopulse(100));
    pwm.setPWM(14, 0, angletopulse(100));
    
    delay(500);
    
  //step2  
    pwm.setPWM(0, 0, angletopulse(50));
    pwm.setPWM(1, 0, angletopulse(60));
    pwm.setPWM(2, 0, angletopulse(70));

    pwm.setPWM(6, 0, angletopulse(15));
    pwm.setPWM(7, 0, angletopulse(45));
    pwm.setPWM(8, 0, angletopulse(-20));
    
    pwm.setPWM(12, 0, angletopulse(60));
    pwm.setPWM(13, 0, angletopulse(130));
    pwm.setPWM(14, 0, angletopulse(100));
    
    delay(500);
   //step3
    
    pwm.setPWM(0, 0, angletopulse(50));
    pwm.setPWM(1, 0, angletopulse(30));
    pwm.setPWM(2, 0, angletopulse(70));

    pwm.setPWM(6, 0, angletopulse(15));
    pwm.setPWM(7, 0, angletopulse(75));
    pwm.setPWM(8, 0, angletopulse(-20));

    pwm.setPWM(12, 0, angletopulse(60));
    pwm.setPWM(13, 0, angletopulse(100));
    pwm.setPWM(14, 0, angletopulse(100));
    
    delay(500);
   //step4
    pwm.setPWM(0, 0, angletopulse(20));
    pwm.setPWM(1, 0, angletopulse(30));
    pwm.setPWM(2, 0, angletopulse(70));

    pwm.setPWM(6, 0, angletopulse(45));
    pwm.setPWM(7, 0, angletopulse(75));
    pwm.setPWM(8, 0, angletopulse(-20));

    pwm.setPWM(12, 0, angletopulse(30));
    pwm.setPWM(13, 0, angletopulse(100));
    pwm.setPWM(14, 0, angletopulse(100));
    
    delay(500);
 }


void moveForward2() {
  //step1
  
    pwm.setPWM(3, 0, angletopulse(30));
    pwm.setPWM(4, 0, angletopulse(70));
    pwm.setPWM(5, 0, angletopulse(40));

    pwm.setPWM(9, 0, angletopulse(50));
    pwm.setPWM(10, 0, angletopulse(70));
    pwm.setPWM(11, 0, angletopulse(120));

    Servo1.write(105); 
    Servo2.write(35); 
    Servo3.write(120);
    
    delay(500);
   //step2
    
    pwm.setPWM(3, 0, angletopulse(0));
    pwm.setPWM(4, 0, angletopulse(40));
    pwm.setPWM(5, 0, angletopulse(40));

    pwm.setPWM(9, 0, angletopulse(80));
    pwm.setPWM(10, 0, angletopulse(100));
    pwm.setPWM(11, 0, angletopulse(120));

    Servo1.write(75); 
    Servo2.write(0); 
    Servo3.write(120);
    
    delay(500);
    //step3
    
    pwm.setPWM(3, 0, angletopulse(0));
    pwm.setPWM(4, 0, angletopulse(70));
    pwm.setPWM(5, 0, angletopulse(40));

    pwm.setPWM(9, 0, angletopulse(80));
    pwm.setPWM(10, 0, angletopulse(70));
    pwm.setPWM(11, 0, angletopulse(120));

    Servo1.write(75); 
    Servo2.write(35); 
    Servo3.write(120);
    
    delay(500);
    //step4
    
    pwm.setPWM(3, 0, angletopulse(30));
    pwm.setPWM(4, 0, angletopulse(70));
    pwm.setPWM(5, 0, angletopulse(40));

    pwm.setPWM(9, 0, angletopulse(50));
    pwm.setPWM(10, 0, angletopulse(70));
    pwm.setPWM(11, 0, angletopulse(120));

    Servo1.write(105); 
    Servo2.write(35); 
    Servo3.write(120);

    delay(500);
 
}
 
