#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>



#define CE_pin 8
#define CSN_pin 9

RF24 radio(CE_pin, CSN_pin); // CE, CSN pins

const byte address[6] = "00001";
void setup() {
  Serial.begin(115200);
  int i = radio.begin();
  Serial.print(i); // 1-> init success, 0-> init failure
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}


//Speed is determined by two potentiometers. On potentiometer is to simulate gas and the other to simulate breaking. The gas - break determines the speed.
void loop() {
      int gas = analogRead(A0);
      int reverse = analogRead(A1);
      
      float percentage_go = (gas - reverse) / 1023.0;

      int speed = (int)(percentage_go * 255);
      Serial.println((String)"Forward: " + gas + " Reverse: " + reverse +  "  Actual Speed: " + speed);
      radio.write(&speed, sizeof(speed));
}

