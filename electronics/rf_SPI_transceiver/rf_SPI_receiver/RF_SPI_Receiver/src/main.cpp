#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// CE, CSN pins (change if needed)
RF24 radio(9, 10);

// Must match transmitter
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);

  radio.begin();
  radio.setChannel(76);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(32);

  radio.openReadingPipe(0, address);
  radio.startListening();

  Serial.println("Receiver ready");
}

void loop() {
  if (radio.available()) {
    char message[32] = {0};   // zero-init = safe string

    radio.read(message, sizeof(message));

    Serial.print("Received: ");
    Serial.println(message);
  }
}
