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
    int steering_1 = analogRead(A2);
    int steering_2 = analogRead(A3);

    float percentage = (gas - reverse) / 1023.0;
    int speed = (int)(percentage * 255);
    speed = constrain(speed, -255, 255); // safety clamp

    Serial.println("Speed: " + String(speed) +
                   " Steering 1: " + String(steering_1) +
                   " Steering 2: " + String(steering_2));

    char msg[32];
    snprintf(msg, sizeof(msg), "%d,%d,%d", speed, steering_1, steering_2);
    radio.write(msg, sizeof(msg));
}
