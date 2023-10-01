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
#include <WiFiClientSecure.h> //Fixes compilation failure relating to WifiLocation, platformIO bug.

/// @brief - This function handles connecting to network
/// @param SSID - SSID of Network 
/// @param Password - Password of Network
void ConnectToNetwork(char* SSID, char* Password){
    Log("Attempting to connect to WiFi Network " + String(SSID), LogLevel::Info);

    //Connect
    WiFi.mode(WIFI_STA); //Sets chip to connect instead of host.
    WiFi.begin(SSID, Password);

    sleep(2000);

    switch (WiFi.status()) {
        case WL_IDLE_STATUS:
            Log("Not Connected to any Wifi", LogLevel::Info);
            break;
        case WL_NO_SSID_AVAIL:
            Log("SSID '" + String(SSID) + "' not found", LogLevel::Error);
            break;
        case WL_CONNECTED:
            Log("Connected to '" + String(SSID) + "'", LogLevel::Info);
            break;
        case WL_CONNECT_FAILED:
            Log("Failed to connect to '" + String(SSID) + "', check the password and any MAC filtering Settings", LogLevel::Error);
            break;
        case WL_CONNECTION_LOST:
            Log("Connection lost", LogLevel::Warn);
            break;
        case WL_DISCONNECTED:
            Log("Not Connected to any Wifi.", LogLevel::Warn);
            break;
        default:
            Log("WiFi Status returned '" + String(WiFi.status()) + "' (Likely unsuccessful)", LogLevel::Warn);
            break;
    }
}

/// @brief Gets real time via NTP
void GetTime(){
    if (WiFi.status() == WL_CONNECTED){
        
        //Connect to network
        configTime(GMTOffset, DaylightSavings ? 3600 : 0, "pool.ntp.org");
        time_t now = time(nullptr);
    
        //Wait until time has been properly set.
        while (now < 8 * 3600 * 2) {
            delay(500);
            now = time(nullptr);
        }
    }
}