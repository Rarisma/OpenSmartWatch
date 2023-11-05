// OSWConfig.h - Open Smart Watch Configuration Header
#ifndef FLAGS_H
#define FLAGS_H

#include <Arduino.h>

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
inline int GeolocationCooldown = 90; // How often to ping geo APIs in the background.

// OSWBoot Settings
inline int DelayBoot = 5000; // Delays boot by value in ms, useful for display testing.

// Experimental Settings
// Many of these aren't implemented and are more ideas/concepts currently
inline bool EnableOTAMenu = true; // Allows OTAs. // Not implemented.
inline int NumberOfButtons = 4; // Amount of physical buttons // Not Implemented.
inline bool WriteLogToSD = false; //Unimplemented,  Saves SysLog messages to the SD.
inline bool LogToNetwork = false; //Unimplemented,  Logs to a Network server
inline bool Autoregion = false; //Unimplemented, Use Geoloc and Weather APIs to find DST and timezone
inline bool AllowBluetooth = true; //Unimplemented, Enables Bluetooth

//=== HARDWARE INFO ===
// These are considered read-only.
// To change these you will need to reflash OSW.
const int DisplayWidth = 240;  // Display Width in pixels
const int DisplayHeight = 280; // Display Height in pixels
//To set your display type please go to Display.cpp 

// SD Card Pins
const int DisplaySDPin = 5;

// ST7789 Pins
const int DisplayCSPin = 21;
const int DisplayRSTPin = 2;
const int DisplayDCPin = 20;

#endif // OSWCONFIG_H
