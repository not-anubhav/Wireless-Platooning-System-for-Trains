#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// NRF24L01 settings
RF24 radio(25, 26); // CE, CSN pins

struct DataPacket {
  float reRpm;
  long reDistance;
  float reLat;
  float reLng;
};
DataPacket Data;

void setup_nrf() {
  // NRF24L01 setup
  radio.begin();
  //radio.setRetries(15, 15);
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
  radio.setChannel(0x76);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_1MBPS);
  radio.startListening();
  radio.enableDynamicPayloads();
  radio.powerUp();
}


void receive() {
  if (radio.available()) {
    radio.read(&Data, sizeof(Data));
    
    // Process re data
    Serial.print("received RPM: ");
    Serial.println(Data.reRpm);
    Serial.print("received Distance: ");
    Serial.println(Data.reDistance);
    Serial.print("received Latitude: ");
    Serial.println(Data.reLat);
    Serial.print("received Longitude: ");
    Serial.println(Data.reLng);
  } else {
    Serial.println("No data available");
  }
  
  delay(100); // Check for data every 100ms
}
