#define SENSOR_PIN 18 // ESP32 pin GPIO18 connected to OUT pin of IR obstacle avoidance sensor

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the ESP pin as an input
  pinMode(SENSOR_PIN, INPUT);

}

void loop() {
  // read the state of the the input pin:
  int state = digitalRead(SENSOR_PIN);

  if (state == HIGH){
    Serial.println("The obstacle is present");
    
  }
  else{
    Serial.println("The obstacle is NOT present");
  delay(100);
  }
}
