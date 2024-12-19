#include <TinyGPS++.h>
#include <SoftwareSerial.h>

int RXPin = 16;
int TXPin = 17;

float lat, lng;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup_gps() {
  gpsSerial.begin(9600);
}

float fetch_gps() {
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid()) {
        Serial.print("Latitude: ");
        //lat = round(gps.location.lat() * 1000000.0) / 1000000.0;
        lat = gps.location.lat();
        //lat_str = String(lat, 4);
        Serial.println(lat, 6);  // Print with 6 decimal places
        Serial.print("Longitude: ");
        //lng = round(gps.location.lng() * 1000000.0) / 1000000.0;
        lng = gps.location.lng();
        //lng_str = String(lng, 4);
        Serial.println(lng, 6);  // Print with 6 decimal places
      } 
      else {
        Serial.println("Location: Not Available");
      }
      Serial.println();
    }

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS detected");
    while (true)
    ;
  }
  return lat, lng;
}