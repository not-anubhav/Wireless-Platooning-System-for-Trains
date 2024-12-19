const int right_motor_a_pin = 32;     //IN1
const int right_motor_b_pin = 33;     //IN2
const int right_motor_pwm_pin = 27;  //ENA

void setup_motor() {
  pinMode(right_motor_a_pin, OUTPUT);
  digitalWrite(right_motor_a_pin, LOW);
  pinMode(right_motor_b_pin, OUTPUT);
  digitalWrite(right_motor_b_pin, LOW);
  pinMode(right_motor_pwm_pin, OUTPUT);
  analogWrite(right_motor_pwm_pin, 0);
}

// 0-255
void drive_forward(int right_motor_pwm) {
  digitalWrite(right_motor_a_pin, HIGH);
  digitalWrite(right_motor_b_pin, LOW);

  analogWrite(right_motor_pwm_pin, right_motor_pwm);
}

// 0-255
void drive_backwards(int right_motor_pwm) {
  digitalWrite(right_motor_b_pin, HIGH);
  digitalWrite(right_motor_a_pin, LOW);

  analogWrite(right_motor_pwm_pin, right_motor_pwm);
}

void drive_break() {
  digitalWrite(right_motor_b_pin, HIGH);
  digitalWrite(right_motor_a_pin, HIGH);

  analogWrite(right_motor_pwm_pin, 0);
}
