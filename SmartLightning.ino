#define BLYNK_TEMPLATE_ID "TMPL6YrfNnyHw"
#define BLYNK_TEMPLATE_NAME "Smart Light"
#define BLYNK_AUTH_TOKEN "Zyy6bulwDE-MQRLXX2Aol5udluU3CNGq"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <RTClib.h>
#include <time.h>
#include <string.h>

#define LED_PIN        2
#define LIGHT_SENSOR   5
#define MOTION_SENSOR  19
#define BUTTON         4

char ssid[] = "MinhThong";
char pass[] = "Thong@123";

BlynkTimer timer;
RTC_DS3231 rtc;

bool scheduleMode = false;
bool manualMode = false;
bool autoMode = false;
bool button_state = false;

int timeOn = -1;
int timeOff = -1;
int currentSec = -1;

const unsigned long NTP_UPDATE_INTERVAL = 86400; //Thời gian 1 ngày
unsigned long lastSync = 0;

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(MOTION_SENSOR, INPUT);
  pinMode(BUTTON, INPUT);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  syncTime(); //Đồng bộ thời gian khi có Wifi
  timer.setInterval(500L, scheduleCheck);
  Blynk.virtualWrite(V3, timeOn);
  Blynk.virtualWrite(V4, timeOff);
}

void loop() {
  if (millis() - lastSync >= NTP_UPDATE_INTERVAL * 1000UL) {
    syncTime();
  }
  Blynk.run();
  timer.run();
  pressButton();
  auto_On();
}

// ------------------- ĐỒNG BỘ THỜI GIAN -------------------
void timeCheck() {
  time_t inow = time(nullptr);
  struct tm *t = localtime(&inow);
  
  //Cập nhật thời gian cho RTC
  rtc.adjust(DateTime(1900 + t->tm_year, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec));
  }

void syncTime() {
  if (WiFi.status() == WL_CONNECTED) {
    configTime(7 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    Serial.print("NTP Synchronizing...");
    struct tm timeinfo;
    int retry = 0;
    while (!getLocalTime(&timeinfo) && retry < 10){
      delay(500);
      retry++;
    }
    if (retry < 10){
      rtc.adjust(DateTime(1900 + timeinfo.tm_year, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec));
      Serial.println("Synced successfully");
      lastSync = millis();
      timeCheck();
    } 
    else{
      Serial.println("NTP error!");
    }
  } 
  else{
    Serial.println("No Internet Connection!");
  }
}

// Hàm điều khiển đèn
void setLed(int state) {
  digitalWrite(LED_PIN, state ? HIGH : LOW);
}

// ------------------- BLYNK DATA -------------------
BLYNK_WRITE(V1) { 
  scheduleMode = param.asInt(); 
  if(scheduleMode)   
    setMode(1); 
}
BLYNK_WRITE(V2) { 
  manualMode = param.asInt(); 
  setLed(manualMode); 
  setMode(2); 
}
BLYNK_WRITE(V5) { 
  autoMode = param.asInt(); 
  if(autoMode)  
    setMode(3); 
}
BLYNK_WRITE(V3) { 
  timeOn  = param.asInt(); 
  Serial.print("Time ON (s): "); 
  Serial.println(timeOn); 
}
BLYNK_WRITE(V4) { 
  timeOff = param.asInt(); 
  Serial.print("Time OFF (s): "); 
  Serial.println(timeOff); 
}

void setMode(int mode) {
  if(mode == 0){
    manualMode = false;
    scheduleMode = false;
    autoMode = false;
  }
  if(mode == 1) {
    manualMode = false;
    autoMode = false;
    Serial.println("Schedule Mode");
  }
  if(mode == 2) {
    scheduleMode = false;
    autoMode = false;
  }
  if(mode == 3) {
    manualMode = false;
    scheduleMode = false;
    Serial.println("Automatic Mode");
  }

  // Cập nhật lên app
  Blynk.virtualWrite(V1, scheduleMode);
  Blynk.virtualWrite(V2, manualMode);
  Blynk.virtualWrite(V5, autoMode);
}

// ------------------- BUTTON -------------------
void pressButton() {
  int new_button_state = digitalRead(BUTTON);
  if (new_button_state == 1 && button_state == 0){
    manualMode = !manualMode;
    setLed(manualMode);
    if(!manualMode){
      setMode(3); //Trở về mode Tự động
    }
  }
  button_state = new_button_state;
}

// ------------------- AUTO MODE -------------------
void auto_On() {
  if(!autoMode) return;
  else{
    int l = digitalRead(LIGHT_SENSOR);
    int r = digitalRead(MOTION_SENSOR);
    if (l == 1 && r == 1) {
      Serial.println("Dark and motion is detected -> Turn on the light");
      setLed(1);
      delay(5000); //Duy trì sáng 5 giây
    } else {
      setLed(0);
    }
  }
}

// ------------------- SCHEDULE MODE -------------------
void scheduleCheck() {
  if (!scheduleMode) return;
  DateTime now = rtc.now();
  currentSec = now.hour() * 3600 + now.minute() * 60 + now.second();
  if (timeOn >= 0 && timeOff >= 0) {
    if (currentSec >= timeOn && currentSec < timeOff) {
      setLed(1);
      Blynk.virtualWrite(V2, 1);
      Serial.println("Automatic on scheduling");
    } 
    else if (currentSec >= timeOff) {
      setLed(0);
      setMode(3);
      Serial.println("Automatic off scheduling");
    }
  }
  else Serial.println("Time Invalid!");
}
