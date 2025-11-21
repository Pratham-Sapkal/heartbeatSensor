# ❤️ Heartbeat Sensor (KY-039) with Arduino

Measure heart rate using the KY-039 pulse sensor and display live readings on the Serial Monitor.

---

## 📌 Project Overview
This project uses the **KY-039 Heartbeat Sensor** to detect pulses by sensing changes in finger blood flow.  
The Arduino processes the signal and prints the BPM (Beats Per Minute) on the Serial Monitor in real time.

---

## 🛠️ Components Used
- Arduino Uno / Nano
- KY-039 Heartbeat Sensor
- Jumper Wires
- USB Cable

---

## ⚡ Circuit Connection

| KY-039 Pin | Arduino Pin |
|-----------|-------------|
| Analog Out | A0 |
| VCC | 5V |
| GND | GND |

---

## 💻 How It Works
- The KY-039 uses an IR LED and a phototransistor.  
- When the heartbeat pumps blood, the **light absorption changes**.  
- Arduino reads this change in analog values.  
- Peaks in the signal are counted as heartbeats.  
- BPM is calculated using the time difference between peaks.

---

## 📟 Output on Serial Monitor
- Raw pulse readings  
- Calculated BPM  
- Real-time heart rate updates  

---

## 🚀 Features
- Live heartbeat monitoring  
- Simple, low-cost setup  
- Beginner-friendly  
- Easy to extend with IoT or display modules  

---

## 📌 How to Use
1. Connect the sensor as per the circuit.
2. Upload the code to the Arduino.
3. Open Serial Monitor at **9600 baud**.
4. Place your finger gently on the sensor.
5. Read your heart rate live on the serial monitor.

---

## 🔧 Possible Improvements
- Add OLED display for BPM  
- Apply signal filtering for accuracy  
- Send data via Wi-Fi/Bluetooth  
- Make a real-time heart graph in Processing/Python  

---
