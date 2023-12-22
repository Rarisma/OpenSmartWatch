#include <Arduino.h>
#include "Logging/SysLog.h"
#include "System/SystemInfo.h"
#include "Display/Display.h"
#include "Networking/Networking.h"
#include "OSWBoot/Flags.h"
#include "System/TimeUtils.h"
#include "Apps/TimeSquare/WatchFace.h"
#include <esp_sleep.h>
#include "OSWBoot.h"
#include "System/Input.h"

//This initalises the hardware RTC etc.
void Initalise(){
    Log("Welcome to OpenSmartWatch " + String(Branch) + "\nV: " + String(ReleaseName), LogLevel::Info);

    InitaliseDisplay();
    
    //Log("Hold upper left for config", LogLevel::Info);
    //ButtonManager.ReadButtons.Contains(UL) => ConfigManager
    //delay(500); //Wait 0.5 seconds for any press.
    PrintBootScreen();  //Prints the welcome to OSW message to the disp.
    ShowPowerOnCause();  //Gets why we are here.
    HandleRTC();

    if (DelayBoot)
    {
        Log("BootDelay enabled, press anything to continue", LogLevel::Info);
        AwaitInput();
    }

    Log("Init complete, Downclocking to 80MHz",LogLevel::Info);
    setCpuFrequencyMhz(80);
    
    //esp_sleep_enable_light_sleep_after(100); // this will sleep the cpu after 100ms.

    //Starts TimeSquare app.
    ShowWatchFace();
}

/// @brief prints to log why setup() is running
///I.e power on, wake from sleep, wake from gpio
void ShowPowerOnCause(){
    switch (esp_sleep_get_wakeup_cause()) {
        case ESP_SLEEP_WAKEUP_EXT0:
        Log("Wake Reason: GPIO", LogLevel::Info);
      break;
    case ESP_SLEEP_WAKEUP_TIMER:
        Log("Wake Reason: Power On from sleep", LogLevel::Info);
      break;
    default:
        Log("Wake Reason: Power On", LogLevel::Info);
      break;
  }
}
/// @brief This handles RTC related initalisation, mainly checking if it needs setting.
void HandleRTC(){
    //This attempts to skip NTP stuff, since it takes time.
    //So if we've woke from sleep we can just check the RTC is fine
    //and skip all this and continue the boot sequence.
    struct tm timeinfo;
    if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_UNDEFINED && //Checks wake up isn't from power off
        getLocalTime(&timeinfo) && //Checks we can actually access the RTC
        (timeinfo.tm_year + 1900) < 2023) { //Sanity check, since OSW is a 2023 project.
        Log("RTC appears to be correct, skipping NTP", LogLevel::Info);
    }
    else{
        Log("NTP isn't set, trying NTP", LogLevel::Info);
        ConnectToNetwork(DefaultWiFiSSID,DefaultWiFiPass); 
        GetTime();
    }
    Log("Time:" + GetTheTime() + " Date:" + GetTheDate(), LogLevel::Info);
}