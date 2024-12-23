# Wireless Platooning System for Trains

This project involves the design and implementation of a wireless platooning system for trains. The system leverages real-time data communication between trains to enhance safety, reduce energy consumption, and increase the overall efficiency of railway networks.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Hardware Components](#hardware-components)
- [Software Components](#software-components)
- [System Architecture](#system-architecture)
- [Setup and Installation](#setup-and-installation)
- [Usage](#usage)

## Introduction

This project aims to develop a wireless platooning system that allows multiple trains to operate on the same track with improved efficiency and safety. The system uses V2V (vehicle-to-vehicle) communication, enabling trains to maintain safe distances, synchronize speeds, and coordinate actions such as joining or leaving a platoon. The project leverages the ESP32 microcontroller, ultrasonic and IR sensors, GPS modules, NRF24L01 communication modules, and the Blynk Cloud platform for data communication and monitoring.

## Features

- **Distance Maintenance:** Ultrasonic sensors maintain a safe distance between trains.
- **Obstacle Detection:** IR sensors detect obstacles and trigger emergency braking.
- **Speed and Location Tracking:** GPS modules provide real-time speed and location data.
- **Wireless Communication:** NRF24L01 modules enable V2V communication for data exchange.
- **Dynamic Speed Adjustment:** Trains automatically adjust speed based on received data.
- **Blynk Integration:** The Blynk Cloud platform is used for data communication, monitoring, and control.

## Hardware Components

- ESP32 microcontroller (38 pins)
- HC-SR04 Ultrasonic sensor
- IR sensor for obstacle detection
- NEO-6M GPS module
- NRF24L01 wireless communication module
- L298N motor driver
- 16x2 LCD display with I2C interface
- DC dual-shaft motor
- Power supply (e.g., 9V battery)
- Miscellaneous: resistors, capacitors, transistors, wiring, and breadboards

## Software Components

- Arduino IDE with necessary libraries:
  - `WiFi.h` for Wi-Fi functionality
  - `BlynkSimpleEsp32.h` for Blynk integration
  - `RF24.h` for NRF24L01 communication
  - `TinyGPSPlus.h` for GPS data processing
- Blynk Cloud platform for data monitoring and control
- Blynk mobile app for remote access and control

## System Architecture

1. **Initialization:** All components, including sensors, GPS, and communication modules, are initialized.
2. **Connection Establishment:** The ESP32 connects to the Wi-Fi network and the Blynk Cloud platform.
3. **Data Collection:** Sensors measure distance, detect obstacles, and track speed and location.
4. **Data Transmission:** Sensor data is sent to other trains via NRF24L01 and logged to the Blynk platform.
5. **Data Reception:** Each train receives data from others and adjusts its speed or takes necessary actions.
6. **Monitoring and Control:** The Blynk platform allows remote monitoring and control of the trains.

## Setup and Installation

1. **Clone the Repository:**
   ```sh
   git clone https://github.com/your-username/train-platooning-system.git
   cd train-platooning-system
  Install Arduino Libraries:

2.Install necessary libraries for ESP32, Blynk, NRF24L01, and GPS modules from the Arduino Library Manager:
    WiFi.h
    BlynkSimpleEsp32.h
    RF24.h
    TinyGPSPlus.h
    Upload Code:
    
3.Open the Arduino IDE.
    Load the .ino file from the repository.
    Set up your Wi-Fi credentials and Blynk authentication token.
    Upload the code to your ESP32 microcontroller.
    
4.Blynk Setup:
    Set up a new project on the Blynk mobile app.
    Add widgets such as buttons, value displays, and gauges for real-time monitoring.
    Link the project to your Blynk authentication token.
    
## Usage
  Power On: Power on all the components.
  Connection: The trains will automatically connect to the Blynk Cloud platform.
  Real-Time Monitoring: Distance, speed, and obstacle data will be continuously monitored and adjusted based on the platooning logic.
  Remote Control: Use the Blynk app to view real-time data and control the trains remotely.

