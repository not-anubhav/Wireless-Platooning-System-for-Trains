void setup() {
  setup_serial();   // Serial communication setup
  setup_blynk();
  setup_motor();
  setup_gps();      // GPS module setup
  setup_ultrasonic(); // Ultrasonic sensor setup
  setup_pid();      // PID controller setup
  setup_speed();
  setup_oled();
  setup_nrf();
}

void loop() {
  disp_oled();
  fetch_gps();    // Fetch GPS coordinates
  run_pid();      // Run the PID control loop for motor speed regulation
  upload_data();  // Upload sensor data to Blynk server
  speed_meas();
  receive();
}


