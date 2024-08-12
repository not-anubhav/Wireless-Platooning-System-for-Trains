#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern long distance;
extern float lat, lng;
extern float rpm;
extern String ipAddress;

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup_oled() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(2);       // Set initial text size
  display.setTextColor(WHITE);  // Set initial text color
  display.setCursor(0, 0);      // Set initial cursor position
  display.display();
}

void disp_oled() {
  read_ultrasonic();
  fetch_gps();
  speed_meas();
  // Clear the display before updating it
  display.clearDisplay();

  // Display the WiFi status and IP address
  display.setCursor(0, 48);
  display.print("IP: ");
  display.println(ipAddress);

  // Display the RPM value
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.print("Dist: ");
  display.println(distance);
  display.setCursor(0, 12);
  display.setTextSize(1);
  display.print("Lat:");
  display.println(lat, 6);
  display.setCursor(0, 24);
  display.setTextSize(1);
  display.print("Lng:");
  display.println(lng, 6);
  display.setCursor(0, 36);
  display.setTextSize(1);
  display.print("RPM:");
  display.println(rpm);
  // Display the changes on the screen

  display.display();
}