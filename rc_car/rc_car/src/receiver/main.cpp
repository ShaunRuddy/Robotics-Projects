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

const int servo_pin = 7;

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

void loop() {
    if (radio.available()) {
        char msg[32];
        radio.read(msg, sizeof(msg));

        int speed, steering_1, steering_2;
        sscanf(msg, "%d,%d,%d", &speed, &steering_1, &steering_2);

        Serial.println("Speed: " + String(speed) +
                       " Steering 1: " + String(steering_1) +
                       " Steering 2: " + String(steering_2));

        // Direction control
        if (speed > 0) {
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
        } else if (speed < 0) {
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            speed = -speed; // make positive for analogWrite
        } else {
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, LOW);
        }

        analogWrite(EN, constrain(speed, 0, 255));

        int angle = map(steering_2, 0, 1023, 0, 180);
        angle = constrain(angle, 50, 130);
        Servo1.write(angle);
    }
}

