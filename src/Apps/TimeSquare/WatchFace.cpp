#include <Arduino.h>
#include <Display/Display.h>
#include "Logging/SysLog.h"
#include "System/TimeUtils.h"
#include "WatchFace.h"
#include "WiFi.h"
#include "Location/Geo.h"
#include "OSWBoot/Flags.h"
#include "OSWBoot/APIKeys.h"
#include <esp_sleep.h>
#include "System/Input.h"

String WeatherCache = "";
time_t LastWeatherUpdate = 0;    
/// @brief Calling this function will do the following:
/// 1) Clear the screen 
/// 2) Unload anything before
/// 3) Show the Watch face.
/// 4) Block Syslog from logging to the display
void ShowWatchFace(){
    Log("Welcome to TimeSquare", LogLevel::Info); //Yes this is just a pun.
    LogToDisplay = false; //Stops log messages showing on display.
    delay(1000);
    ClearDisplay(); //Clears logs.
    PrintTime(WatchDisplayType::StandardTime);
}

/// @brief Prints the current time to the display
/// @param type How time will be shown.
void PrintTime(WatchDisplayType type)
{
    String Time = GetTheTime();
    Log("Printing the time as " + Time, LogLevel::Info);
    int WifiColor = WiFi.status() == WL_CONNECTED ? 0x07E0 : 0xFFFF; //Green if connected.
    ClearDisplay(); 

    if (AllowWeather && OpenWeatherMapAPIKey != "") 
    {
        time_t now;
        time(&now); // Obtain current time
        int LastUpdate = now - LastWeatherUpdate;
        Log("LastUpdate is " + String(LastUpdate), LogLevel::Info);
        if (WeatherCache == "" || LastUpdate >= 900)
        {
            Log("WeatherCache is outdated, updating it", LogLevel::Info);
            WeatherCache = GetWeather();
            time(&now);
            LastWeatherUpdate = now; 
        }
    }

    switch (type)
    {
        case HrsBigMinsMid:
            PrintToDisplay(String(Time[0]), 15, false);
            PrintToDisplay(String(Time[4] + Time[5]), 4, false);
            PrintToDisplay(String(Time[1]), 15, false);
            break;
        case BigTime:
            Log(String("Printing " + Time), LogLevel::Info);
            PrintToDisplay("WiFi",1,false,20,8, WifiColor);
            PrintToDisplay(GetTheDate(), 2, false, 60, 0);
            PrintToDisplay(String(Time[0]) + String(Time[1]), 13, false, 40, 30);
            PrintToDisplay(String(Time[3]) + String(Time[4]), 13, false, 40, 130);
            if (AllowWeather) 
            {
                String AlignedWeatherCache = "";
                for (int i = 0; i < ((GetTextWidth(String(Time[3]) + String(Time[4]), 13)  / 5) - (GetTextWidth(WeatherCache, 1) / 5)); ++i) {
                    AlignedWeatherCache =+  " ";
                }
                PrintToDisplay(AlignedWeatherCache + WeatherCache,1,false,60,240);
            }
            break;
        case StandardTime:
            PrintToDisplay("WiFi " + String(WiFi.status() == WL_CONNECTED ? "Connected" : "Disconnected") ,1,false, 50,80, WifiColor);
            PrintToDisplay(Time,5,false,50,100);
            if (AllowWeather) 
            {
                PrintToDisplay(WeatherCache,1,false,85,150);
            }
            break;
    }
    WaitForNextUpdate();
    PrintTime(type);
}

/// @brief Sleeps the code until the next time the display will need 
/// to be updated i.e next minute.
void WaitForNextUpdate() {
        Log("Sleeping OSW till next update needed", LogLevel::Info);
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo)) {
            return;  // Error getting time
        }
    
        // Calculate the number of seconds until 2 seconds past the next minute
        int secondsToSleep = 62 - timeinfo.tm_sec; // 60 seconds plus 2 seconds
        if (secondsToSleep > 62 || secondsToSleep <= 10) {
            secondsToSleep -= 60;
        }
    


    #ifdef UseDelayBasedSleep = true
        msToSleep = secondsToSleep * 1000;
        while (msToSleep != 0)
        {
            AwaitInput(250);
            msToSleep -= 250;
        }
    #else
        uint64_t microsecondsToSleep = secondsToSleep * 1000000ULL;
        esp_sleep_enable_timer_wakeup(microsecondsToSleep);
        //esp_deep_sleep_enable_gpio_wakeup(BIT(D1), ESP_GPIO_WAKEUP_GPIO_HIGH);
        esp_light_sleep_start();
        
        switch(esp_sleep_get_wakeup_cause())
        {
            case ESP_SLEEP_WAKEUP_EXT0 : WeatherCache = "Wakeup caused by external signal using RTC_IO"; break;
            case ESP_SLEEP_WAKEUP_EXT1 : WeatherCache = "Wakeup caused by external signal using RTC_CNTL"; break;
            case ESP_SLEEP_WAKEUP_TIMER : WeatherCache ="Wakeup caused by timer"; break;
            case ESP_SLEEP_WAKEUP_TOUCHPAD : WeatherCache ="Wakeup caused by touchpad"; break;
            case ESP_SLEEP_WAKEUP_ULP : WeatherCache ="Wakeup caused by ULP program"; break;
        }
    #endif
}
