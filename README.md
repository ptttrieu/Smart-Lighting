An automated, IoT-integrated lighting system designed to optimize energy consumption and enhance user convenience through motion detection, ambient light sensing, and remote mobile control.

## 1. Overview
- This project focuses on building a smart lighting solution using the **ESP32** microcontroller[cite: 95, 109]. -It integrates local automation with cloud-based remote control via the **Blynk** platform[cite: 114, 143]. -The system is capable of operating in three distinct modes: Manual, Automatic, and Scheduled[cite: 113, 118, 121].

## 2. Key Features
* **Three Operation Modes**:
    * **Manual**: Direct control via the Blynk mobile app or a physical override button[cite: 118, 119, 134].
    * **Automatic**: Lights trigger based on the combined logic of motion (PIR sensor) and low ambient light (Photodiode)[cite: 121, 125].
    * **Scheduled**: Set specific "Time ON" and "Time OFF" intervals using a Real-Time Clock (RTC)[cite: 113, 115].
* **High Responsiveness**: System latency is optimized to be <1 second within local WiFi[cite: 90].
* **Time Synchronization**: Uses NTP (Network Time Protocol) to keep the DS3231 RTC module accurate[cite: 190, 213].
* **Safety & Reliability**: Includes a physical button to ensure functionality even if the internet connection is lost[cite: 81, 93].

## 3. System Architecture
The system uses an ESP32 as the central hub to process sensor data and execute control logic via a relay module.


### Hardware Components
| Component | Purpose |
| :--- | :--- |
| **ESP32-WROOM-32** | -Main MCU with integrated Wi-Fi/Bluetooth[cite: 105, 110]. |
| **HC-SR501 PIR Sensor** | -Human motion detection (5–7m range)[cite: 91, 96]. |
| **Photodiode Sensor** | -Ambient light intensity sensing[cite: 97, 123]. |
| **DS3231 RTC Module** | -Precise timekeeping for scheduling[cite: 98, 133]. |
| **Relay Module** | -Switches the AC 220V load for the LED light[cite: 100, 135]. |
| **AC-DC 5V Power Supply** | -Stable power for the MCU and peripherals[cite: 101]. |

## 4. Software & Tools
* **Programming**: Arduino IDE / PlatformIO[cite: 140].
* **Libraries**: `BlynkSimpleEsp32`, `RTClib`, `WiFi`, `time.h`[cite: 150, 151, 152, 153].
* **Circuit Design**: Fritzing[cite: 141].
* **IoT Platform**: Blynk IoT App[cite: 143].

## 5. Wiring Diagram

-The connections involve interfacing the I2C pins for the RTC, digital input pins for the sensors and button, and a digital output pin for the relay control[cite: 129, 157, 158, 159, 160, 161].

## 6. Implementation & Code
-The core logic resides in the `loop()` function, which concurrently manages Blynk connectivity, timer routines, physical button polling, and the automatic sensor logic[cite: 329, 330, 331, 332, 333].

```cpp
void loop() {
  Blynk.run();       // Handle Cloud communication
  timer.run();       // Handle scheduled tasks
  pressButton();     // Check for physical input
  auto_On();         // Run sensor-based automation
  delay(100);
}
```

## 7. Future Enhancements
* **Dimming Control**: Implement PWM to adjust brightness based on environment[cite: 345, 346].
* **Multi-Zone Support**: Expand the system to manage multiple rooms independently[cite: 343, 344].
* **Machine Learning**: Analyze user habits to predict and automate lighting schedules[cite: 351, 352].
* **Advanced Sensors**: Integrate temperature, humidity, and air quality monitoring[cite: 349, 350].
*This project was developed as part of the Embedded Systems course at Ho Chi Minh City University of Technology and Education (HCMUTE)*[cite: 1, 2, 356].
