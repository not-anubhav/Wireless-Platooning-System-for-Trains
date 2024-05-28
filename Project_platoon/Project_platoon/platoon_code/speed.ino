#include <Arduino.h>
#include <ESP32Encoder.h>

#define ENCODER_PIN 4  // Encoder output pin
#define SLOTS_PER_REVOLUTION 20

float rpm;
volatile int encoderCount = 0;
unsigned long lastTime = 0;
unsigned long rpmUpdateInterval = 1000;  // Update RPM every 1 second

ESP32Encoder encoder;

void IRAM_ATTR handleEncoder() {
  encoderCount++;
}

void setup_speed() {
  // Encoder setup
  pinMode(ENCODER_PIN, INPUT_PULLUP);  // Assuming encoder output is pulled up when not active
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), handleEncoder, RISING);
}

float speed_meas() {
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= rpmUpdateInterval) {
    rpm = (encoderCount * 60000.0) / (rpmUpdateInterval * SLOTS_PER_REVOLUTION);
    Serial.println("RPM: " + String(rpm));
    lastTime = currentTime;
    encoderCount = 0;  // Reset count
  }
  return rpm;
}