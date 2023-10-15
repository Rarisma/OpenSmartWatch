#include <Arduino.h>
#include "Logging\SysLog.h"
#include "System\SystemInfo.h"
#include "Display\Display.h"

//This initalises the hardware RTC etc.
void Initalise(){
    Log("Welcome to OpenSmartWatch " + String(Branch) + "\nVersion: " + String(ReleaseName), LogLevel::Info);
    InitaliseDisplay();
    PrintBootScreen();
    Log("Initalised Display",LogLevel::Info);
        
}