#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(2, 3); // RX | TX 
char command;
int LED = 8; 
void setup() 
{   
 Serial.begin(9600); 
 MyBlue.begin(9600); 
 pinMode(LED, OUTPUT); 
 Serial.println("Ready to connect\nDefualt password is 1234 or 000"); 
} 
void loop() 
{ 
 if (MyBlue.available()) 
   command = MyBlue.read(); 
 if (command == 'W') 
 { 
   digitalWrite(LED, HIGH); 
   Serial.println("LED On"); 
 } 
 else if (command == 'w') 
 { 
   digitalWrite(LED, HIGH); 
   Serial.println("LED Off"); 
 } 
}  
