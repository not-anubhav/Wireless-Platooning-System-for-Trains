#include <Robojax_L298N_DC_motor.h>

// motor 1 settings
#define CHA 0
#define ENA 27  // this pin must be PWM enabled pin if Arduino board is used
#define IN1 32
#define IN2 33


const int CCW = 2;  // do not change
const int CW = 1;   // do not change

#define motor1 1  // do not change


// for single motor
Robojax_L298N_DC_motor motor(IN1, IN2, ENA, CHA);
//Robojax_L298N_DC_motor motor(IN1, IN2, ENA, CHA, true);

// for two motors without debug information // Watch video instruciton for this line: https://youtu.be/2JTMqURJTwg

int motor1Direction = CW;         //default direction of rotation
const int motor1changeStep = 10;  // 10 is 10% every time button is pushed
int motor1Speed = 80;             // variable holding the light output vlaue (initial value) 40 means 40%
const int motor1MinimumSpeed = 40;
const int motor1MaximumSpeed = 100;
int motor1StopState = HIGH;  //Stope state of motor (HIGH means STOP) and LOW means Start


#include "ESP32_L298N_DC_motor_wifi_page.h"



// #include <WiFi.h>
// #include <WiFiClient.h>
#include <WebServer.h>

// const char *ssid = "Poco";
// const char *password = "limitless";

WebServer server(80);

const int led = 13;

void handleRoot() {
  String HTML_page = motorControlHeader_1;

  HTML_page.concat(".bar1 {width: " + String(motor1Speed) + "%;}\n");

  HTML_page.concat(motorControlHeader_2);

  HTML_page.concat(motor1Control_p1);

  if (motor1Direction == CW) {
    if (motor1StopState == HIGH) {
      HTML_page.concat("<strong>Stopped - CW at ");
    } else {
      HTML_page.concat("<strong>Running - CW at ");
    }
  } else {
    if (motor1StopState == HIGH) {
      HTML_page.concat("<strong>Stopped - CCW at ");
    } else {
      HTML_page.concat("<strong>Running - CCW at ");
    }
  }
  HTML_page.concat(motor1Speed);
  HTML_page.concat(motor1Control_p2);
  if (motor1StopState == HIGH) {
    HTML_page.concat("m1START\">START");
  } else {
    HTML_page.concat("m1STOP\">STOP");
  }
  HTML_page.concat(motor1Control_p3);



  HTML_page.concat("</body>\n</html>");

  server.send(200, "text/html", HTML_page);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }

  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup_wifi(void) {
  motor.begin();

  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  // Serial.println("");


  // // Wait for connection
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }

  // Serial.println("");
  // Serial.print("Connected to ");
  // Serial.println(ssid);
  // Serial.print("IP address: ");
  // Serial.println(WiFi.localIP());


  server.on("/", handleRoot);
  server.on("/speed", HTTP_GET, handleMotorSpeed);
  server.on("/direction", HTTP_GET, handleMotorDirection);
  server.on("/stop", HTTP_GET, handleMotorBrake);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void mt_control(void) {
  server.handleClient();

  if (motor1StopState == LOW) {
    motor.rotate(motor1, motor1Speed, motor1Direction);  //run motor1 at motor1Speed% speed in motor1DirectioN
  } else {
    motor.brake(motor1);
  }
}

/*
 * handleMotorSpeed()
 * Slows down or speeds up the motor
 * returns nothing
 * Written by Ahmad Shamshiri on Dec 27, 2019
 * www.Robojax.com
 */
void handleMotorSpeed() {
  if (server.arg("do") == "m1slower") {
    motor1Speed -= motor1changeStep;

    if (motor1Speed < motor1MinimumSpeed) {
      motor1Speed = motor1MinimumSpeed;
    }
  } else if (server.arg("do") == "m1faster") {
    motor1Speed += motor1changeStep;

    if (motor1Speed > motor1MaximumSpeed) {
      motor1Speed = motor1MaximumSpeed;
    }
  } else {
    motor1Speed = 0;
  }

  handleRoot();
}  //handleMotorSpeed() end

/*
 * handleMotorDirection()
 * changes the direction of motor
 * returns nothing
 * Written by Ahmad Shamshiri on Dec 27, 2019
 * www.Robojax.com
 */
void handleMotorDirection() {
  if (server.arg("dir") == "m1CW") {
    motor1Direction = CW;

  } else if (server.arg("dir") == "m1CCW") {
    motor1Direction = CCW;
  }

  handleRoot();
}  //

/*
 * handleMotorBrake()
 * applies brake to the motor
 * returns nothing
 * Written by Ahmad Shamshiri on Dec 27, 2019
 * www.Robojax.com
 */
void handleMotorBrake() {
  if (server.arg("do") == "m1START") {
    motor1StopState = LOW;
  } else if (server.arg("do") == "m1STOP") {
    motor1StopState = HIGH;
  }
  handleRoot();
}  //