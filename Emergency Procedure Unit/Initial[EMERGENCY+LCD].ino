#include <LiquidCrystal_I2C.h>
#define irsensorpin 18
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); //SDA 21 and SCL 22
const int Enable = 2;   // PWM pin for motor speed control
const int IN1 = 4;  // GPIO pin for motor direction control 1
const int IN2 = 5;  // GPIO pin for motor direction control 2

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(irsensorpin, INPUT);
  pinMode(Enable, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Initialize Serial communication for debugging
  Serial.begin(115200);
}

void loop() {
  lcd.setCursor(0, 0);
  int state = digitalRead(irsensorpin);
  if (state == HIGH){
    lcd.print("The obstacle is NOT present");
    Serial.println("The obstacle is NOT present");
    motorForward();
  delay(100);
  }
  else{
    lcd.setCursor(0, 0);
    lcd.print("The obstacle is present!");
    Serial.println("The obstacle is present!");
    motorStop();
  delay(100);
  }
}
 
void motorForward() {
  lcd.setCursor(0, 1);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(Enable, 255);  // Full speed (adjust as needed)
  lcd.print("Train Moving Forward");
  Serial.println("Motor moving forward");
}

void motorStop() {
  lcd.setCursor(0, 1);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(Enable, 0);  // Stop the motor
  lcd.print("Train Stopped!");
  Serial.println("Motor stopped!");
}
