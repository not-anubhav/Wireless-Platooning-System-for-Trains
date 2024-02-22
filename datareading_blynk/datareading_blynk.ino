#define BLYNK_TEMPLATE_ID "TMPL3xg-J70LN"
#define BLYNK_TEMPLATE_NAME "SENSOR DATA READINGS"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 

char auth[] = "dehja3_SAE1mxIsKssqJQZtCqX5_ScTa";
// Replace with your network credentials
const char *ssid = "6412";
const char *password = "opop0909";

int RXPin = 16;
int TXPin = 17;
int GPSBaud = 9600;
// Define the Ultrasonic Sensor pin connections
const int trigPin = 5;  // GPIO5
const int echoPin = 18;  // GPIO18
const int ledPin = 2;
float lat , lng;
//String  lat_str , lng_str;
float duration;
float distance;

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);
WiFiClient client;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  gpsSerial.begin(GPSBaud);
  WiFi.begin(ssid, password);
   Serial.print("Connecting to WiFi ..");
   lcd.print("ConnectingWiFi..");
   while (WiFi.status() != WL_CONNECTED) {
     Serial.print('.');
     delay(500);
   }
   Serial.println("Connected to WiFi!");
   lcd.setCursor(0,1);
   lcd.print("Connected!");
   digitalWrite(ledPin, HIGH);
  //Initialize Blynk
  Blynk.begin(auth, ssid, password);
  Blynk.config(auth);
  lcd.clear();
}
void loop() {
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read())){
      if (gps.location.isValid()){
        lcd.clear();
        Serial.print("Latitude: ");
        //lat = round(gps.location.lat() * 1000000.0) / 1000000.0;
        lat = gps.location.lat();
        //lat_str = String(lat, 4);
        Serial.println(lat, 6);  // Print with 6 decimal places
        lcd.setCursor(0, 0);
        lcd.print("Lt:");
        lcd.print(lat, 4);

        Serial.print("Longitude: ");
        //lng = round(gps.location.lng() * 1000000.0) / 1000000.0;
        lng = gps.location.lng();
        //lng_str = String(lng, 4);
        Serial.println(lng, 6);  // Print with 6 decimal places
        lcd.setCursor(0, 1);
        lcd.print("Lt:");
        lcd.print(lng, 4);
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH);
        // Speed of sound is 343 meters/second or 0.0343 cm/microsecond
        distance = duration*0.017;
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
        lcd.setCursor(11, 0);
        lcd.print(distance);
        lcd.setCursor(14,1);
        lcd.print("cm");
      }
      else{
        Serial.println("Location: Not Available");
        lcd.setCursor(0, 1);
        lcd.print("Location:NA");
      }
      Serial.println();
    delay(100);
    }

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    lcd.setCursor(0, 1);
    lcd.print("NoGPSdetected");
    while(true);
  }
  Blynk.virtualWrite(V0, distance);
  Blynk.virtualWrite(V1, lat);
  Blynk.virtualWrite(V2, lng);
  // Wait for 1 second before the next update
  delay(100);
  Blynk.run();
}