#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// CE, CSN pins (change if needed)
RF24 radio(7, 8);

// Must match receiver
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);
  
  radio.begin();
  radio.openWritingPipe(address);

  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

void loop() {
    const char text [] = "Hello World";
    radio.write(&text, sizeof(text));
    delay(1000);
}
