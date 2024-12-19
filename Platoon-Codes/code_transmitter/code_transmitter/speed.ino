#include <Arduino.h>
#include <ESP32Encoder.h>

#define ENCODER_PIN 4  // Encoder output pin
#define SLOTS_PER_REVOLUTION 20

float rpm;
volatile int encoderCount = 0;
unsigned long lastTime = 0;
unsigned long rpmUpdateInterval = 1000;  // Update RPM every 1 second

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

ESP32Encoder encoder;

void IRAM_ATTR handleEncoder() {
  portENTER_CRITICAL_ISR(&mux);
  encoderCount++;
  portEXIT_CRITICAL_ISR(&mux);
}

void setup_speed() {
  // Encoder setup
  pinMode(ENCODER_PIN, INPUT_PULLUP);  // Assuming encoder output is pulled up when not active
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), handleEncoder, RISING);
}

float speed_meas() {
  unsigned long currentTime = millis();
  if (currentTime - lastTime >= rpmUpdateInterval) {
    portENTER_CRITICAL(&mux);
    rpm = (encoderCount * 60000.0) / (rpmUpdateInterval * SLOTS_PER_REVOLUTION);
    encoderCount = 0;  // Reset encoder count
    portEXIT_CRITICAL(&mux);
    Serial.println("RPM: " + String(rpm));
    lastTime = currentTime;
  }
  return rpm;
}
