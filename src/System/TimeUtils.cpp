#include <Arduino.h>
#include <time.h>

String GetTheTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    //Serial.println("Failed to get time");
    return "ER:OR";
  }
  
  String hr = String(timeinfo.tm_hour);
  String minute = String(timeinfo.tm_min);

  if (hr.length() == 1) { hr = "0" + hr; }
  if (minute.length() == 1) { minute = "0" + minute; }

  return hr + ":" + minute;
}

String GetTheDate(){
    struct tm timeinfo;
    if(!getLocalTime(&timeinfo)){
      //Log("Failed to retrieve time info", LogLevel::Error);
      return "";
    }
    return String(timeinfo.tm_mday) + "/" + String((timeinfo.tm_mon+1)) + "/" + String((timeinfo.tm_year + 1900));
}