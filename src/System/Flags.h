// Flags.h - Open Smart Watch Configuration File
#ifndef FLAGS_H
#define FLAGS_H
#include <Arduino.h>

// === OSW Version Information ===
// Don't edit this UNLESS you know what you are doing!
constexpr int Version[] = {1, 2, 0};
constexpr const char* ReleaseName = "Reckless Tongue";
constexpr const char* Branch = "MINIMA";

/* Release Name History.
    All releases are based on song names, generally music I like.
    == Progenitor ==
    0.0.C - Kick Back - Kenshi Yonezu 
    0.0.F - Wannabe

    == MINIMA == 
    1.0.0 - Exhibition Prototype Ultra (K-Rino)
    1.1.0 - Time Out (DJ Hoppa)
    1.2.0 - Reckless Tongue (Airways)       */

// === Feature availability ===
// Allow or disable OSW features like WiFi. This is NOT the same as turning it off.
// If a feature is disabled, trying to use it will just skip the function call.
// Unless you have a good reason, you probably shouldn't disable any of these.
inline bool AllowWiFi = true; // Enables WiFi
inline bool AllowNetworkTimeProtocol = true; // Automatically get the time using WiFi. (requires WiFi)
inline bool AllowGeolocation = true; // Allows triangulation through router names (uses Google Maps API)
inline bool AllowWeather = true; // Allows access to weather information (requires Geolocation) (Uses OpenWeatherMap)
inline bool AllowSD = true;      // Allows SD Card reading.
inline bool ShowSysLogOnDisplay = true; // Shows SysLog messages on screen during boot.

// === User Preferences ===
// Will likely vary depending on the user.
inline bool Metric = true; // Will use Celsius etc if enabled, uses imperial otherwise.
inline int GMTOffset = 0; // Seconds offset from GMT (For example GMT+1/CEST would be 3600)
inline bool DaylightSavings = false; // Set to true if you are in a region observing DST/BST.

// Default WiFi SSID and Password, useful for testing
inline bool UseDefaultCreds = true; // Enables automatic connection
inline String DefaultWiFiSSID = "DREAMLAND"; // SSID to connect to.
inline String DefaultWiFiPass = "NIGHTMARE"; // Password to SSID.

// Geolocation Settings
inline int GeolocationCooldown = 90; // How often to ping geo APIs in the background. (Seconds)

// OSWBoot Settings
inline bool DelayBoot = true; // Delays boot until button pressed.
const inline bool ShowDebugLogs = false; // Debug logs will be ignored. (requires reflash)
// Experimental Settings
// Many of these aren't implemented and are more ideas/concepts currently
inline bool EnableOTAMenu = true; // Allows OTAs. // Not implemented.
inline int NumberOfButtons = 4; // Amount of physical buttons // Not Implemented.
inline bool WriteLogToSD = false; //Unimplemented,  Saves SysLog messages to the SD.
inline bool LogToNetwork = false; //Unimplemented,  Logs to a Network server
inline bool Autoregion = false; //Unimplemented, Use Geoloc and Weather APIs to find DST and timezone
inline bool AllowBluetooth = true; //Unimplemented, Enables Bluetooth

//=== HARDWARE INFO ===
// These are considered read-only, changing these requires a reflash.
const bool UseDelayBasedSleep = true; //Set to false if your ESP model supports wake from GPIO (ESP32-S3 )
const int DisplayWidth = 240;  // Display Width in pixels
const int DisplayHeight = 280; // Display Height in pixels
//To set your display type please go to Display.cpp 
const int SDCardPin = 5;

// ST7789 Pins
const int DisplayCSPin = 21;
const int DisplayRSTPin = 2;
const int DisplayDCPin = 20;

//Button Pins (Currently Limited to 2)
const int ButtonAPin = 3;
const int ButtonBPin = 4;

#endif