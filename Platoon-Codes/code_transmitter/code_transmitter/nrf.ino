#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// NRF24L01 settings
RF24 radio(25, 26); // CE, CSN pins

struct DataPacket {
  float rpm;
  long distance;
  float lat;
  float lng;
};
DataPacket data;

extern float rpm;


void setup_nrf() {
  // NRF24L01 setup
  radio.begin();
  //radio.setRetries(15, 15);
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.setChannel(0x76);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.stopListening();
  radio.enableDynamicPayloads();
  radio.powerUp();
  Serial.println("Starting to send");
}


void send() {
  // Set data to be sent
  data.rpm = speed_meas();
  data.distance = read_ultrasonic();  // Implement this function to read from the ultrasonic sensor
  data.lat = fetch_gps();
  data.lng = fetch_gps();

  // Send data to the follower
  radio.stopListening();
  bool ok = radio.write(&data, sizeof(data));
  if (ok) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Failed to send data");
  }
  radio.startListening();

  delay(100); // Send data every 100ms
}
