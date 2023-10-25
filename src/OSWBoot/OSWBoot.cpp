#include <Arduino.h>
#include "Logging\SysLog.h"
#include "System\SystemInfo.h"
#include "Display\Display.h"
#include "Networking\Networking.h"
#include "OSWBoot\Flags.h"
#include "System\TimeUtils.h"
#include "Apps\TimeSquare\WatchFace.h"

//This initalises the hardware RTC etc.
void Initalise(){
    Log("Welcome to OpenSmartWatch " + String(Branch) + "\nV: " + String(ReleaseName), LogLevel::Info);
    InitaliseDisplay();
    PrintBootScreen();
    ConnectToNetwork(DefaultWiFiSSID,DefaultWiFiPass);
    GetTime();
    Log("Time:" + GetTheTime() + " Date:" + GetTheDate(), LogLevel::Info);

    if (DelayBoot != 0)
    {
        Log("BootDelay enabled, waiting " + String(DelayBoot) + "ms", LogLevel::Info);
        delay(DelayBoot);
    }

    //Starts TimeSquare app.
    ShowWatchFace();
}