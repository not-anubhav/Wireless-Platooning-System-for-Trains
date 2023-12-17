#define irsensorpin 18
const int Enable = 2;   // PWM pin for motor speed control
const int IN1 = 4;  // GPIO pin for motor direction control 1
const int IN2 = 5;  // GPIO pin for motor direction control 2

void setup() {
  pinMode(irsensorpin, INPUT);
  pinMode(Enable, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

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
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(Enable, 255);  // Full speed (adjust as needed)
  Serial.println("Motor moving forward");
}

void motorStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(Enable, 0);  // Stop the motor
  Serial.println("Motor stopped");
}
