An automated, IoT-integrated lighting system designed to optimize energy consumption and enhance user convenience through motion detection, ambient light sensing, and remote mobile control.

## 1. Overview
[cite_start]This project focuses on building a smart lighting solution using the **ESP32** microcontroller[cite: 95, 109]. [cite_start]It integrates local automation with cloud-based remote control via the **Blynk** platform[cite: 114, 143]. [cite_start]The system is capable of operating in three distinct modes: Manual, Automatic, and Scheduled[cite: 113, 118, 121].

## 2. Key Features
* **Three Operation Modes**:
    * [cite_start]**Manual**: Direct control via the Blynk mobile app or a physical override button[cite: 118, 119, 134].
    * [cite_start]**Automatic**: Lights trigger based on the combined logic of motion (PIR sensor) and low ambient light (Photodiode)[cite: 121, 125].
    * [cite_start]**Scheduled**: Set specific "Time ON" and "Time OFF" intervals using a Real-Time Clock (RTC)[cite: 113, 115].
* [cite_start]**High Responsiveness**: System latency is optimized to be <1 second within local WiFi[cite: 90].
* [cite_start]**Time Synchronization**: Uses NTP (Network Time Protocol) to keep the DS3231 RTC module accurate[cite: 190, 213].
* [cite_start]**Safety & Reliability**: Includes a physical button to ensure functionality even if the internet connection is lost[cite: 81, 93].

## 3. System Architecture
The system uses an ESP32 as the central hub to process sensor data and execute control logic via a relay module.


### Hardware Components
| Component | Purpose |
| :--- | :--- |
| **ESP32-WROOM-32** | [cite_start]Main MCU with integrated Wi-Fi/Bluetooth[cite: 105, 110]. |
| **HC-SR501 PIR Sensor** | [cite_start]Human motion detection (5–7m range)[cite: 91, 96]. |
| **Photodiode Sensor** | [cite_start]Ambient light intensity sensing[cite: 97, 123]. |
| **DS3231 RTC Module** | [cite_start]Precise timekeeping for scheduling[cite: 98, 133]. |
| **Relay Module** | [cite_start]Switches the AC 220V load for the LED light[cite: 100, 135]. |
| **AC-DC 5V Power Supply** | [cite_start]Stable power for the MCU and peripherals[cite: 101]. |

## 4. Software & Tools
* [cite_start]**Programming**: Arduino IDE / PlatformIO[cite: 140].
* [cite_start]**Libraries**: `BlynkSimpleEsp32`, `RTClib`, `WiFi`, `time.h`[cite: 150, 151, 152, 153].
* [cite_start]**Circuit Design**: Fritzing[cite: 141].
* [cite_start]**IoT Platform**: Blynk IoT App[cite: 143].

## 5. Wiring Diagram

[cite_start]The connections involve interfacing the I2C pins for the RTC, digital input pins for the sensors and button, and a digital output pin for the relay control[cite: 129, 157, 158, 159, 160, 161].

## 6. Implementation & Code
[cite_start]The core logic resides in the `loop()` function, which concurrently manages Blynk connectivity, timer routines, physical button polling, and the automatic sensor logic[cite: 329, 330, 331, 332, 333].

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
* [cite_start]**Dimming Control**: Implement PWM to adjust brightness based on environment[cite: 345, 346].
* [cite_start]**Multi-Zone Support**: Expand the system to manage multiple rooms independently[cite: 343, 344].
* [cite_start]**Machine Learning**: Analyze user habits to predict and automate lighting schedules[cite: 351, 352].
* [cite_start]**Advanced Sensors**: Integrate temperature, humidity, and air quality monitoring[cite: 349, 350].

## 8. Authors
* [cite_start]**Ngô Quang Minh** (Lead) [cite: 13]
* [cite_start]**Nguyễn Phạm Thế Hào** [cite: 5]
* [cite_start]**Dương Minh Thông** [cite: 5]
* [cite_start]**Phùng Thanh Triều** [cite: 5]

[cite_start]*This project was developed as part of the Embedded Systems course at Ho Chi Minh City University of Technology and Education (HCMUTE)*[cite: 1, 2, 356].
