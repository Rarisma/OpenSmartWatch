#include <WiFi.h>
#include <Arduino.h>
#include <System\SystemInfo.h>
#include <Logging\SysLog.h>

void setup() {

}

void loop() {
  Log("Hello - " + String(ReleaseName), LogLevel::Info);
  //Serial.println("Hello - " + String(ReleaseName));
}
