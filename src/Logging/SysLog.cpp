//SysLog - Deals with logging.

#include "Arduino.h"
#include "LogLevel.h"

bool SerialInitalised = false; //Will initalise serial and then set to true.
bool LogToDisplay = false; //Shows log messages on display.

//Logs a message to all available sources.
void Log(String Message, LogLevel level) {

    //Gets relevant prefix.
    String Prefix = "[";
    switch (level) {
        case LogLevel::Debug:
            Prefix += "DBUG";
            break;
        case LogLevel::Info:
            Prefix += "INFO";
            break;
        case LogLevel::Warn:
            Prefix += "WARN";
            break;
        case LogLevel::Error:
            Prefix += "ERRO";
            break;
        case LogLevel::Fatal:
            Prefix += "FTAL";
            break;
    }

    //Get time, then build a MM/DD HH:MM timestamp.
    struct tm timeinfo;
    String Timestamp = String(timeinfo.tm_mday) + "/" + String(timeinfo.tm_mon) + " " + 
    String(timeinfo.tm_hour) + ":" + String(timeinfo.tm_min) + ":" + String(timeinfo.tm_sec);

    //Start serial if it hasn't already.
    if (!SerialInitalised) 
    {
        Serial.begin(115200);
        SerialInitalised = true;
    }

    //Log to Serial
    Serial.println(Prefix + " " + Timestamp + "]  -  " + Message );
}