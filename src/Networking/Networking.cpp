//OSW Networking
//This file handles networking stuff such as NTP and HTTP Requests.
//Entrusting the Networking Stack to Espressif
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "time.h"
#include "Logging\SysLog.h"
#include "Arduino.h"
#include "OSWBoot\Flags.h"
#include "Arduino.h"
#include "rtc.h"
#include <WiFiClientSecure.h> //Fixes compilation failure relating to WifiLocation, platformIO bug.

/// @brief - This function handles connecting to network
/// @param SSID - SSID of Network 
/// @param Password - Password of Network
void ConnectToNetwork(String SSID, String Password){
    Log("Connecting to ssid " + String(SSID), LogLevel::Info);

    //Connect
    WiFi.mode(WIFI_STA); //Sets chip to connect instead of host.
    WiFi.begin(SSID, Password);

    Log("Connecting...", LogLevel::Info);

    delay(2000);

    Log("Querying...", LogLevel::Info);

    switch (WiFi.status()) {
        case WL_IDLE_STATUS:
            Log("Not Connected.", LogLevel::Info);
            break;
        case WL_NO_SSID_AVAIL:
            Log("SSID '" + String(SSID) + "' not found", LogLevel::Error);
            break;
        case WL_CONNECTED:
            Log("Connected to '" + String(SSID) + "'", LogLevel::Info);
            break;
        case WL_CONNECT_FAILED:
            Log("Failed to connect to '" + String(SSID), LogLevel::Error);
            break;
        case WL_CONNECTION_LOST:
            Log("Connection lost", LogLevel::Warn);
            break;
        case WL_DISCONNECTED:
            Log("Disconnected. (" + String(WiFi.status()) + ")", LogLevel::Warn);
            break;
        default:
            Log("WiFi Status - '" + String(WiFi.status()), LogLevel::Warn);
            break;
    }
    Log("Finished connecting", LogLevel::Info);
}

/// @brief Gets real time via NTP
void GetTime(){
    Log("Setting RTC via NTP", LogLevel::Info);
    if (WiFi.status() == WL_CONNECTED){
        
        //Connect to network
        //configTime(GMTOffset, DaylightSavings ? 3600 : 0, "pool.ntp.org");
        configTime(GMTOffset, 3600, "pool.ntp.org");
        time_t now = time(nullptr);
        //Wait until time has been properly set.
        while (now < 8 * 3600 * 2)
        {
            delay(500);
            now = time(nullptr);
        }

        struct tm timeinfo;
        if(!getLocalTime(&timeinfo)){
            Log("Failed to retrieve time info", LogLevel::Error);
            return;
        }
        char timeString[20]; // Allocate space for the formatted string
        Log("Set time as " + String(timeinfo.tm_hour) + ":" + String(timeinfo.tm_min) + " " + String(timeinfo.tm_mday) 
        + "/" + String(timeinfo.tm_mon++) + "/" + String((timeinfo.tm_year + 1900)), LogLevel::Info);
    }
    else { Log("Can't set NTP without WiFi", LogLevel::Warn); }
}