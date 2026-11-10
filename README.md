# 🤖 Autonomous Obstacle-Avoidance and Environmental Monitoring Robot

An autonomous mobile robot built using **ESP32** that combines **obstacle avoidance, environmental monitoring, and wireless telemetry** into a single integrated robotic platform. The robot uses multiple sensors to detect obstacles, monitor temperature, gas concentration, and ambient light conditions, and transmit real-time status updates over **Bluetooth** while navigating autonomously.

---

## 🚀 Features

- 🚧 Autonomous obstacle avoidance using an ultrasonic sensor
- 🌡️ Real-time temperature monitoring with DHT22
- 🛢️ Gas leak detection using an MQ-2 sensor
- 💡 Ambient light detection using an LDR sensor
- 🔵 Bluetooth-based wireless telemetry and monitoring (HC-05 on ESP32 hardware UART2)
- ⚠️ Environmental anomaly detection (gas leak, high temperature, low/high light)
- 🚗 Differential drive motor control with ESP32 LEDC PWM speed regulation
- 💡 Automatic LED control based on lighting conditions
- 🔧 Modular embedded system architecture for sensor integration

---

## 🛠️ Hardware Components

- ESP32 Dev Module (ESP32 DevKit)
- HC-05 Bluetooth Module
- Ultrasonic Sensor (HC-SR04)
- DHT22 Temperature Sensor
- MQ-2 Gas Sensor
- LDR (Light Dependent Resistor)
- L298N Motor Driver
- DC Motors
- LED Indicator
- Battery Power Supply
- Resistors for voltage dividers (e.g., 1kΩ and 2kΩ)

---

## 📍 Pin Configuration

| Component | Signal | ESP32 GPIO |
|---|---|---|
| HC-05 Bluetooth | RX2 (← HC-05 TX) | 16 |
| HC-05 Bluetooth | TX2 (→ HC-05 RX) | 17 |
| HC-SR04 | TRIG | 5 |
| HC-SR04 | ECHO | 18 |
| MQ-2 | Analog Out | 34 (ADC1) |
| LDR | Analog In | 35 (ADC1) |
| DHT22 | Data | 4 |
| L298N | ENA (PWM) | 25 |
| L298N | ENB (PWM) | 26 |
| L298N | IN1 | 27 |
| L298N | IN2 | 14 |
| L298N | IN3 | 33 |
| L298N | IN4 | 32 |
| LED | Indicator | 23 |

---

## ⚡ Wiring Notes

- The ESP32 runs at **3.3V logic** and its GPIOs are **not 5V tolerant**.
- Use a **voltage divider** (e.g., 1kΩ + 2kΩ) on the HC-SR04 **ECHO** pin.
- Use a voltage divider on the **MQ-2 analog output** if the module is powered from 5V.
- Use a voltage divider on the **HC-05 RX** line (ESP32 TX → HC-05 RX).
- Power the **L298N motor driver from a separate battery supply**, not from the ESP32 3.3V pin.
- Connect **all grounds together** (ESP32, L298N, sensors, battery).
- ADC1 pins (GPIO 34, 35) are used so analog readings keep working even if WiFi is enabled.

---

## ⚙️ Working Principle

The robot continuously measures the distance to obstacles using an ultrasonic sensor. If an obstacle is detected within a predefined threshold (20 cm), the robot stops, pauses briefly, and performs an autonomous right turn to avoid collisions. Simultaneously, it monitors environmental parameters including **temperature, gas concentration, and ambient light intensity**.

Sensor readings are processed by the ESP32 microcontroller, which classifies environmental conditions into **normal or anomaly states** (gas leak, high temperature, low light, or high light). The ESP32's 12-bit ADC readings (0–4095) are scaled down to 10-bit (0–1023) so the same threshold values can be used. All sensor data and robot status messages are transmitted wirelessly to a Bluetooth-connected device for real-time monitoring.

Anomaly priority: **High Temperature > Gas Leak > Light conditions**.

---

## 🎚️ Thresholds

| Parameter | Threshold |
|---|---|
| Obstacle distance | 20 cm |
| Low light (LED turns ON) | ADC > 800 |
| High light | ADC < 100 |
| Gas leak | ADC > 400 |
| High temperature | > 45 °C |
| Motor speed (PWM) | 170 / 255 |

---

## 📡 Example Bluetooth Output
Dist: 34 cm | Gas: 312 | Light: 745 | Temp: 28.5 C | Status: NORMAL
Dist: 18 cm | Gas: 298 | Light: 820 | Temp: 29.1 C | Status: LOW LIGHT ⚠️
Dist: 40 cm | Gas: 465 | Light: 610 | Temp: 30.2 C | Status: GAS LEAK 🚨


---

## 💻 Software Setup

1. Install the **Arduino IDE** and add ESP32 board support (Espressif ESP32 core, v2.x or v3.x both supported).
2. Select **Board: ESP32 Dev Module**.
3. Install these libraries from the Library Manager:
   - **DHT sensor library** (Adafruit)
   - **Adafruit Unified Sensor**
4. Upload the sketch and open a Bluetooth terminal app on your phone.
5. Pair with the HC-05 (default PIN: `1234` or `0000`) and connect at **9600 baud**.

---

## 🎯 Applications

- Indoor autonomous robots
- Warehouse and industrial monitoring
- Hazard detection systems
- Smart environmental monitoring
- Educational robotics projects
- Embedded systems and IoT prototyping

---

## 🧠 Technologies Used

- ESP32 (Embedded C/C++ with Arduino framework)
- Sensor Integration
- LEDC PWM Motor Control
- Hardware UART Bluetooth Communication
- ADC Scaling and Calibration
- Embedded Systems
- Robotics and Autonomous Navigation

---

## 📌 Key Highlights

- Integrated multiple sensors into a single autonomous robotic platform
- Implemented real-time obstacle avoidance and motor control logic
- Developed wireless telemetry for environmental monitoring
- Ported from Arduino Uno to ESP32 with hardware UART, LEDC PWM, and ADC scaling
- Demonstrated embedded systems design, robotics, and electromechanical integration

---

## 👨‍💻 Author

**Vidhessh Jayakumar**
