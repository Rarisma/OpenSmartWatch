#include <Arduino.h>
#include "Logging\SysLog.h"
#include "System\SystemInfo.h"
#include "Display\Display.h"
#include "Networking\Networking.h"
#include "OSWBoot\Flags.h"
//This initalises the hardware RTC etc.
void Initalise(){
    Log("Welcome to OpenSmartWatch " + String(Branch) + "\nV: " + String(ReleaseName), LogLevel::Info);
    InitaliseDisplay();
    PrintBootScreen();
    ConnectToNetwork(DefaultWiFiSSID,DefaultWiFiPass);
    GetTime();
    
    if (DelayBoot != 0)
    {
        Log("Delay Boot enabled, waiting " + String(DelayBoot) + "ms", LogLevel::Info);
    }
}