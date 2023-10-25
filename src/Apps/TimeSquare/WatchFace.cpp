#include <Arduino.h>
#include <Display\Display.h>
#include "Logging\SysLog.h"
#include "System\TimeUtils.h"
#include "WatchFace.h"
#include "WiFi.h"
#include "Location\Geo.h"

//I don't like putting non code related comments here
//but I really wanted to document the fact that I wanted
//a clever name for the watch face so i asked chat gpt for one
//and gave me time square, i asked for an initaliser func name
//and got square up, I really wanna use that.

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
    Log("Printing the time as " + String(type), LogLevel::Info);
    String Time = GetTheTime();
    switch (type)
    {
        case HrsBigMinsMid:
            PrintToDisplay(String(Time[0]), 15, false);
            PrintToDisplay(String(Time[4] + Time[5]), 4, false);
            PrintToDisplay(String(Time[1]), 15, false);
            break;
        case StandardTime:
            String STime = String(Time[0]) + String(Time[1]) + String('\n') + String(Time[3]) + String(Time[4]);
            Log(String("Printing " + STime), LogLevel::Info);
            int WifiColor = WiFi.status() == WL_CONNECTED ? 0x07E0 : 0xFFFF; //Green if connected.
            PrintToDisplay("WiFi",1,false,20,8, WifiColor);
            PrintToDisplay(GetTheDate(), 2, false, 60, 0);
            PrintToDisplay(String(Time[0]) + String(Time[1]), 13, false, 40, 30);
            PrintToDisplay(String(Time[3]) + String(Time[4]), 13, false, 40, 130);
            PrintToDisplay(GetWeather(),1,false,60,240);
    }
}