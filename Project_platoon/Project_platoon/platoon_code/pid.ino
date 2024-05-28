#include <PID_v1.h>

const int irSensorPin = 15; // IR sensor pin

// Define the PID variables
double input = 0;
double output = 0;
double setpoint = 25;

// Specify the links and initial tuning parameters
double Kp = 24.0, Ki = 3.2, Kd = 4.0;

// Define the PID object
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

unsigned long timer = 0;
unsigned long timerInterval = 50;  // Wait 50ms between pings (about 20 pings/sec).
double minOutput = 100;            // The minimum output to send (plus or minus)



void setup_pid() {
  pinMode(irSensorPin, INPUT); // IR sensor pin as input
  // Initialize the PID
  myPID.SetMode(AUTOMATIC);          // Set PID to automatic mode
  myPID.SetOutputLimits(-255, 255);  // Set output limits
  myPID.SetSampleTime(100);          // Set sample time

  // Optional: Set PID tunings during runtime if needed
  // myPID.SetTunings(Kp, Ki, Kd);
}

void run_pid() {
  // Handle PID control
  if (millis() - timer >= timerInterval) {
    // Read the state of the "START" button from the web server
    bool startButtonPressed = motor1StopState == LOW;

    // If the "START" button is pressed, proceed with PID control
    if (startButtonPressed) {
      int state = digitalRead(irSensorPin);
      input = read_ultrasonic();  // Read distance from ultrasonic sensor

      // Check IR sensor state before PID control
      if (state == LOW) {  // Obstacle detected by IR sensor
        motor.brake(1);      // Stop the motor immediately
      } else {
        bool computed = myPID.Compute();  // Compute PID
        if (computed) {
          if (input != setpoint) {  // Check if input is not equal to setpoint
            if (output > 0) {
              if (output < minOutput) {
                output = minOutput;
              }
              motor.rotate(1, output, 2);  // Run motor forward with computed output
            } else {
              if (output > -minOutput) {
                output = -minOutput;
              }
              motor.rotate(1, -output, 1);  // Run motor backward with computed output
            }
          } else {
            // If input is equal to setpoint, stop the motor
            output = 0;
            motor.brake(1);
          }
        }
      }
    } else {
      // If the "START" button is not pressed, stop the motor
      output = 0;
      motor.brake(1);
    }

    // Debugging output, replace with your own debugging or logging if needed
    Serial.print("Input: ");
    Serial.print(input);
    Serial.print(" | Output: ");
    Serial.print(output);
    Serial.print(" | Setpoint: ");
    Serial.println(setpoint);

    timer = millis();
  }
}
