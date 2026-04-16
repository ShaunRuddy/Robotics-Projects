#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


#define CE_pin 8
#define CSN_pin 9

RF24 radio(CE_pin, CSN_pin); // CE, CSN pins

const byte address[6] = "00001";

const int IN1 = 2;
const int IN2 = 3;
const int EN = 5;


const int servo_pin = 10;

Servo Servo1;

void setup(){
    Serial.begin(115200);
    Servo1.attach(servo_pin);

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(EN, OUTPUT);

    int i = radio.begin();
    Serial.println(i);
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_LOW);
    radio.startListening();
}

void loop (){
    if (radio.available()) {
       int speed;
       radio.read(&speed, sizeof(speed));
       Serial.println(speed);  

    if (speed > 0) {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    } else if (speed < 0) {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        speed = -speed;
    } else {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, LOW);
    }
    analogWrite(EN, speed);
    }
}