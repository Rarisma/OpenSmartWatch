//SysLog - Deals with logging.

#include "Arduino.h"
#include "LogLevel.h"
#include "Display/Display.h"
#include "System/TimeUtils.h"
#include "OSWBoot/Flags.h"

bool SerialInitalised = false; //Will initalise serial and then set to true.
bool LogToDisplay = false; //Shows log messages on display.

//Logs a message to all available sources.
void Log(String Message, LogLevel level) {

    //Gets relevant prefix.
    String Prefix = "";
    int Color = 0xFFFFFF; //RGB in hex after the 0x part.
    switch (level) {
        case LogLevel::Debug:
            Prefix += "DBG";
            Color = 0x001F;  // Blue
            break;
        case LogLevel::Info:
            Prefix += "INF";
            break;
        case LogLevel::Warn:
            Prefix += "WRN";
            Color = 0xFFE0;  // Yellow
            break;
        case LogLevel::Error:
            Prefix += "ERR";
            Color = 0xF800;  // Red
            break;
        case LogLevel::Fatal:
            Prefix += "FTL";
            Color = 0xF81F;  // Purple (suggested for Fatal)
            break;
    }
    
    //Supress debug logs if enabled.
    if (SupressDebugLogs && level == LogLevel::Debug){ return; }

    if (LogToDisplay)
    {
        ShowLog(Message, Prefix, Color);
    }

    //Start serial if it hasn't already.
    if (!SerialInitalised) 
    {
        Serial.begin(115200);
        SerialInitalised = true;
    }

    //Log to Serial
    Serial.println("[" + Prefix  + "]  -  " + Message );
}