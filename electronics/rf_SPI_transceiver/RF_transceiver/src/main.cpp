#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// CE, CSN pins (change if needed)
RF24 radio(9, 10);

// Must match receiver
const byte address[6] = "00001";

void setup() {
  Serial.begin(115200);

  radio.begin();
  radio.setChannel(76);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(32);

  radio.openWritingPipe(address);
  radio.stopListening();

  Serial.println("Transmitter ready");
}

void loop() {
  const char message[] = "Hello from TX";

  bool ok = radio.write(message, sizeof(message)); // includes '\0'

  Serial.print("Sent: ");
  Serial.println(message);
  Serial.print("Status: ");
  Serial.println(ok ? "OK" : "FAILED");

  delay(1000);
}
