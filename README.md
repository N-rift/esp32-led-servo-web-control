# ESP32 LED & Servo Web Control

An ESP32 project that hosts a simple web page for controlling an LED and a servo motor remotely over WiFi.

## 📌 Overview

- Control an **LED** (ON/OFF) from any browser on the same network
- Control a **servo motor** angle (0–180°) via a slider
- No app required — just open the ESP32's IP address in a browser

## 🛠️ Hardware

- ESP32 development board
- LED (+ resistor) on **GPIO 2**
- Servo motor signal wire on **GPIO 13**

## 📦 Requirements

- Arduino IDE with ESP32 board support installed
- **ESP32Servo** library (install via Library Manager)

## ⚙️ Setup

1. Open `esp32_web_control.ino` in Arduino IDE.
2. Update your WiFi credentials:
   ```cpp
   const char* ssid     = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
3. Upload to the ESP32.
4. Open the Serial Monitor (115200 baud) and note the printed IP address.
5. Open that IP address in a browser on a device connected to the same WiFi network.

## 🌐 Web Interface

The page provides:
- **Turn ON / Turn OFF** buttons for the LED
- A **slider (0–180°)** for the servo angle

## 📂 Repository Structure

```
esp32-led-servo-web-control/
├── esp32_web_control.ino
└── README.md
```

## 👤 Author

**[Your Name]**
Methods (الأساليب) — Week 6 Task
