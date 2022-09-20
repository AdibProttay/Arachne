// Include the Servo library
#include <Servo.h> 

// Declare the Servo pin
int servoPin1 = 3;
int servoPin2 = 4;
int servoPin3 = 5;

// Create a servo object
Servo Servo1, Servo2, Servo3;

void setup()
{
  Servo1.attach(servoPin1);
  Servo2.attach(servoPin2);
  Servo3.attach(servoPin3);
}

void loop()
{
  // Make servo go to 0 degrees
  Servo1.write(20);
  Servo2.write(120);
  Servo3.write(180);
  delay(1000);
  Servo1.write(90);
  Servo2.write(90);
  Servo3.write(150);
  delay(1000);

}
