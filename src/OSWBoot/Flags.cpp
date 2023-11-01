//Open Smart Watch Flags.
//Think of these sorta like settings on your phone, these change what OSW
//allows itself to do, such as WiFi, boot timings ect.
//At some point it should be user changable without a recompile.

//While none of these flags are dangerous in the sense that it
//could break your hardware, you should still be careful, or you may need to
//reflash, report odd scenarios when changing flags, these are meant to be changed.
#include <Arduino.h>

//WiFi/Bluetooth Connection Settings
bool AllowWiFi = true; //Enables WiFi
bool AllowBluetooth = true; //Enables Blutooth
bool AllowNetworkTimeProtocol = true; //Automatically get the time using WiFi. (require WiFi Connection)

//Default WiFi SSID and Password, useful for testing
bool UseDefaultCreds = true; //Enables automatic connection
String DefaultWiFiSSID = "DREAMLAND"; // SSID to connect to.
String DefaultWiFiPass = "NIGHTMARE"; // Password to SSID.

//Geolocation Settings
bool EnableGeolocation = true; //Allows triangulation through router names (uses google maps API)
bool EnableWeather = true; //Allows access to weather information (requires Geolocation) (Uses openweathermap)
int GeolocationCooldown = 900; //How often to ping geo api's in the background.

//OSWBoot Settings
int DelayBoot = 5000; //delays boot by value in ms, useful for display testing.
bool ShowSysLogOnDisplay = true; //Shows SysLog messages on screen during boot.

//Time Settings
int GMTOffset = 0; //Seconds offset from GMT (For example GMT+1/CEST would be 3600)
bool DaylightSavings = true; //Set to true if you are in a reigion observing DST/BST ect.

//Experemental Settings 
//Many of these aren't implemented and are more idea's concepts currently
bool EnableOTAMenu = true; //Allows OTA's. //Not implemented.
bool EnableSDCard = true; //Scans for SDCards on boot. // Not Implemented.
int NumberOfButtons = 4; //Ammount of physical buttons //Not Implemented.
bool WriteLogToSD = false; //Saves SysLog messages to the SD. //Not implemented.
bool LogToNetwork = false; //Logs to Network server //not implemented.
//===HARDWARE INFO===
#include <Display\DisplayType.h>
int DisplayWidth = 240;  //Display Width in pixels
int DisplayHeight = 280; //Display Height in pixels
DisplayType Display = DisplayType::AdaST7789; //Display Vendor/Type

//ST7789 Pins
int DisplayCSPin = 21;
int DisplayRSTPin = 2;
int DisplayDCPin = 20;
int DisplaySDPin = 27;