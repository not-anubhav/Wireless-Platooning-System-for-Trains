#include <PID_v1.h>

const int irSensorPin = 15; // IR sensor pin

// Define the PID variables
double input = 0;
double output = 0;
double setpoint = 15;

// Specify the links and initial tuning parameters
double Kp = 24.0, Ki = 3.2, Kd = 4.0;

// Define the PID object
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

unsigned long timer = 0;
unsigned long timerInterval = 50;  // Wait 50ms between pings (about 20 pings/sec).
double minOutput = 100;  // The minimum output to send (plus or minus)

void setup_pid() {
  // Initialize the PID
  myPID.SetMode(AUTOMATIC);          // Set PID to automatic mode
  myPID.SetOutputLimits(-255, 255);  // Set output limits
  myPID.SetSampleTime(100);          // Set sample time

  // Optional: Set PID tunings during runtime if needed
  // myPID.SetTunings(Kp, Ki, Kd);
}

void run_pid() {
  if (millis() - timer >= timerInterval) {
    int state = digitalRead(irSensorPin);
    input = read_ultrasonic();  // Assume this function returns the distance measurement

    if (state == LOW) {  // if ultrasonic cannot detect an object, then it will say 0 cm.
      drive_break();
    } else {
      bool computed = myPID.Compute();
      if (computed) {
        // If the output is computed, apply the control signal
        if (input != setpoint) { // Add this condition to check if input is not equal to setpoint
          if (output > 0) {
            if (output < minOutput) {
              output = minOutput;
            }
            drive_forward(output);
          } else {
            if (output > -minOutput) {
              output = -minOutput;
            }
            drive_backwards(-output);
          }
        } else {
          // If input is equal to setpoint, send no signal to the motor driver
          output = 0;
          drive_break();
        }
      }
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

