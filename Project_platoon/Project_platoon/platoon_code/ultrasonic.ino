long distance = 0;
const byte triggerPin = 13;
const byte echoPin = 14;

int change_counter = 0;


bool firstStart = true;

int pre_distance = 0;

void setup_ultrasonic() {
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  firstStart = true;
  change_counter = 0;
}

long read_ultrasonic() {
  // Function for retreiving the distance

  long duration, cm;
  int change = 0;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPin, LOW);

  // to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
  // convert the time into a distance
  cm = duration / 29 / 2;

  // here we are going to filter the cm results.
  // discard the outlier result that occasionally comes from the ultrasonic
  if (cm <= 550) {
    //distance = cm;
    if (firstStart == true) {
      pre_distance = cm;
      distance = cm;
      firstStart = false;
    }
    // also needs to filter our the result from the ultrasonic sensor.
    // for example if you have 50, the result can't be allowed to jump to 8 or 100

    else {
      change = abs(cm - pre_distance);
      if (change <= 20) {
        distance = cm;
      } else {
        // we can send the previous distance or discard the result entirely
        change_counter++;
        distance = pre_distance;
      }

      // Also don't forget to reset the change_counter so we don't end
      // up with the old data always
      if (change_counter > 3) {
        change_counter = 0;
        distance = cm;
        firstStart = true;
      }
    }

    // update the previous distance
    pre_distance = distance;
    return distance;
  }
}