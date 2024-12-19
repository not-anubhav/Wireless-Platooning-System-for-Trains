#define BLYNK_TEMPLATE_ID "TMPL3xg-J70LN"
#define BLYNK_TEMPLATE_NAME "SENSOR DATA READINGS"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

extern float lat, lng;
extern float rpm;
String ipAddress;
// extern const char *ssid, *password;

char auth[] = "fapJBPR2Dkhs_vBUg6y6be-JZrLAp__m";
// Replace with your network credentials
const char *ssid = "Poco";
const char *password = "limitless";

WiFiClient client;

void setup_blynk() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Blynk.begin(auth, ssid, password);
  Blynk.config(auth);
  ipAddress = WiFi.localIP().toString();
}
void upload_data() {
  long distance = read_ultrasonic();
  fetch_gps();
  speed_meas();
  Blynk.virtualWrite(V0, distance);
  Blynk.virtualWrite(V1, lat);
  Blynk.virtualWrite(V2, lng);
  Blynk.virtualWrite(V3, rpm);
  Blynk.run();
}