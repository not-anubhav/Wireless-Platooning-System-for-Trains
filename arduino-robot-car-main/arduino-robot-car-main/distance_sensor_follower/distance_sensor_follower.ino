void setup() {
  setup_serial();   // Serial communication setup
  setup_blynk();
  setup_wifi();     // Wi-Fi setup for Blynk
  setup_gps();      // GPS module setup
  setup_ultrasonic(); // Ultrasonic sensor setup
  setup_pid();      // PID controller setup
  setup_speed();
  setup_oled();
}

void loop() {
  fetch_gps();    // Fetch GPS coordinates
  mt_control();   // Control the DC motor based on the state and speed
  run_pid();      // Run the PID control loop for motor speed regulation
  upload_data();  // Upload sensor data to Blynk server
  speed_meas();
  disp_oled();
}


