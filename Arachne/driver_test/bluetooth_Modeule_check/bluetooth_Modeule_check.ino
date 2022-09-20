#include<SoftwareSerial.h>
SoftwareSerial bluetooth(2,3);
char command;
void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("Hello There!!!");
  pinMode(13, OUTPUT);
}

void loop() {
  if (bluetooth.available()){
    command = bluetooth.read();
    Serial.println(command);
  }
  if (command == 'F'){
    digitalWrite(13, HIGH);
  }
  if (command == 'B'){
    digitalWrite(13, LOW);
  }
}
