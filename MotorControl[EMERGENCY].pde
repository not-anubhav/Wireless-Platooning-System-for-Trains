#define irsensorpin 18
const int motorPWM = 2;   // PWM pin for motor speed control
const int motorDirection1 = 4;  // GPIO pin for motor direction control 1
const int motorDirection2 = 5;  // GPIO pin for motor direction control 2

void setup() {
  pinMode(irsensorpin, INPUT);
  pinMode(motorPWM, OUTPUT);
  pinMode(motorDirection1, OUTPUT);
  pinMode(motorDirection2, OUTPUT);

  // Initialize Serial communication for debugging
  Serial.begin(115200);
}

void loop() {
  int state = digitalRead(irsensorpin);
  if (state == HIGH){
    Serial.println("The obstacle is NOT present");
    motorForward();
  delay(100);
  }
  else{
    Serial.println("The obstacle is present");
    motorStop();
  delay(100);
  }
}
 
void motorForward() {
  digitalWrite(motorDirection1, HIGH);
  digitalWrite(motorDirection2, LOW);
  analogWrite(motorPWM, 255);  // Full speed (adjust as needed)
  Serial.println("Motor moving forward");
}

void motorStop() {
  digitalWrite(motorDirection1, LOW);
  digitalWrite(motorDirection2, LOW);
  analogWrite(motorPWM, 0);  // Stop the motor
  Serial.println("Motor stopped");
}
