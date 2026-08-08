# 🤖 Autonomous Obstacle-Avoidance and Environmental Monitoring Robot

An autonomous mobile robot built using **Arduino** that combines **obstacle avoidance, environmental monitoring, and wireless telemetry** into a single integrated robotic platform. The robot uses multiple sensors to detect obstacles, monitor temperature, gas concentration, and ambient light conditions, and transmit real-time status updates over **Bluetooth** while navigating autonomously.

---

## 🚀 Features

- 🚧 Autonomous obstacle avoidance using an ultrasonic sensor
- 🌡️ Real-time temperature monitoring with DHT22
- 🛢️ Gas leak detection using an MQ-2 sensor
- 💡 Ambient light detection using an LDR sensor
- 🔵 Bluetooth-based wireless telemetry and monitoring
- ⚠️ Environmental anomaly detection (gas leak, high temperature, low/high light)
- 🚗 Differential drive motor control with PWM speed regulation
- 💡 Automatic LED control based on lighting conditions
- 🔧 Modular embedded system architecture for sensor integration

---

## 🛠️ Hardware Components

- Arduino Uno
- HC-05 Bluetooth Module
- Ultrasonic Sensor (HC-SR04)
- DHT22 Temperature Sensor
- MQ-2 Gas Sensor
- LDR (Light Dependent Resistor)
- L298N Motor Driver
- DC Motors
- LED Indicator
- Battery Power Supply

---

## ⚙️ Working Principle

The robot continuously measures the distance to obstacles using an ultrasonic sensor. If an obstacle is detected within a predefined threshold, the robot stops and performs an autonomous turn to avoid collisions. Simultaneously, it monitors environmental parameters including **temperature, gas concentration, and ambient light intensity**.

Sensor readings are processed by the Arduino microcontroller, which classifies environmental conditions into **normal or anomaly states** (gas leak, high temperature, low light, or high light). All sensor data and robot status messages are transmitted wirelessly to a Bluetooth-connected device for real-time monitoring.

---

## 📡 Example Bluetooth Output

```
Dist: 34 cm | Gas: 312 | Light: 745 | Temp: 28.5 C | Status: NORMAL
Dist: 18 cm | Gas: 298 | Light: 820 | Temp: 29.1 C | Status: LOW LIGHT
Dist: 40 cm | Gas: 465 | Light: 610 | Temp: 30.2 C | Status: GAS LEAK
```

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

- Arduino (Embedded C/C++)
- Sensor Integration
- PWM Motor Control
- Bluetooth Communication
- Embedded Systems
- Robotics and Autonomous Navigation

---

## 📌 Key Highlights

- Integrated multiple sensors into a single autonomous robotic platform
- Implemented real-time obstacle avoidance and motor control logic
- Developed wireless telemetry for environmental monitoring
- Demonstrated embedded systems design, robotics, and electromechanical integration

---

## 👨‍💻 Author

**Vidhessh Jayakumar**
