#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

int lcdColumns = 16;
int lcdRows = 2;

// set LCD address, number of columns and rows
// if you don't know your display address, run an I2C scanner sketch
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  // 0x27 is LCD address

// Choose two Arduino pins to use for software serial
int RXPin = 16;
int TXPin = 17;

int GPSBaud = 9600;

// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()
{
  // initialize LCD
  lcd.init();
  // turn on LCD backlight                      
  lcd.backlight();
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);

  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    lcd.setCursor(0, 0);
    lcd.print("No GPS detected");
    while(true);
  }
}

void displayInfo()
{
  lcd.clear();
  if (gps.location.isValid())
  {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    lcd.setCursor(0, 0);
    lcd.print("Lt:");
    lcd.print(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    lcd.setCursor(0, 1);
    lcd.print("Ln:");
    lcd.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.println("Location: Not Available");
    lcd.setCursor(0, 0);
  // print message
    lcd.print("Location: Not Available");
  }
  Serial.println();
delay(1000);
}