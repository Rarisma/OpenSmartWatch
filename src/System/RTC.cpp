#include <Arduino.h>
#include <time.h>

String* GetTime(String (&timeArray)[2]) {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to get time");
    return nullptr;
  }
  
  String hr = String(timeinfo.tm_hour);
  String minute = String(timeinfo.tm_min);

  if (hr.length() == 1) { hr = "0" + hr; }
  if (minute.length() == 1) { minute = "0" + minute; }

  timeArray[0] = hr;
  timeArray[1] = minute;

  return timeArray;
}
