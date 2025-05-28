# 🌿 Smart Greenhouse Automation System

![Platform](https://img.shields.io/badge/platform-ESP32-blue?logo=espressif)
![WiFi](https://img.shields.io/badge/connectivity-WiFi-green)
![Blynk](https://img.shields.io/badge/app-Blynk-red)
![Status](https://img.shields.io/badge/status-Completed-brightgreen)

A smart greenhouse automation system using **ESP32**, powered by **Blynk IoT platform**, to monitor and control environmental factors like **temperature**, **humidity**, **soil moisture**, **motion**, and **light** — with support for **SMS alerts**, **remote control**, and **real-time data visualization**.

---

## 🌱 Features

- 🌡️ Monitor temperature and humidity (DHT11)
- 🌿 Measure soil moisture and automate irrigation
- 🔆 Detect light levels and control grow lights (LDR + relay)
- 🌀 Ventilation control with automatic fan (humidity/temp based)
- 🚶 Motion detection for security
- 📲 Blynk integration for real-time monitoring and control
- 🛠️ Failsafe WiFi reconnect logic

---

## 🧩 Hardware Components

| Component       | Description                      |
|----------------|----------------------------------|
| ESP32           | Main microcontroller              |
| DHT11           | Temp/Humidity sensor              |
| Soil Sensor     | Analog soil moisture sensor       |
| LDR             | Light sensor                      |
| PIR Sensor      | Motion detection                  |
| SIM800L         | GSM for SMS (optional)            |
| Relay Modules   | For motor, fan, and bulb control  |
| Blynk App       | Real-time dashboard on mobile     |

---

## 📦 Pin Configuration

| Function         | ESP32 Pin |
|------------------|-----------|
| DHT11 Sensor     | GPIO 4    |
| Soil Moisture    | GPIO 34   |
| PIR Motion       | GPIO 5    |
| Fan Relay        | GPIO 27   |
| Bulb Relay       | GPIO 25   |
| Motor Relay      | GPIO 26   |
| LDR Sensor       | GPIO 35   |

---

## 📲 Blynk Virtual Pins

| Data Type          | Virtual Pin |
|--------------------|-------------|
| Humidity           | V0          |
| Temperature        | V1          |
| Soil Moisture      | V2          |
| Motion Alert Text  | V5          |
| Light Sensor (LDR) | V10         |

---

## 🚀 Getting Started

1. **Install Arduino IDE** (with ESP32 board support)
2. **Install Required Libraries**:
   - `Blynk`
   - `WiFi`
   - `DHT`
3. **Configure WiFi and Blynk Tokens** in the code:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
