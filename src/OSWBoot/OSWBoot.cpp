#include <Arduino.h>
#include "Logging\SysLog.h"
#include "System\SystemInfo.h"

//This initalises OSW OS
void OSWLoad(){
    Log("Welcome to OpenSmartWatch " + String(Branch) + "\nVersion: " + String(ReleaseName), LogLevel::Info);

}