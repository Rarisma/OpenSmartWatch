#ifndef Flags
#define Flags
#include <Display\DisplayType.h>

// WiFi/Bluetooth Connection Settings
extern bool AllowWiFi;
extern bool AllowBluetooth;
extern bool AllowNetworkTimeProtocol;

// Default WiFi Credentials
extern bool UseDefaultCreds;
extern String DefaultWiFiSSID;
extern String DefaultWiFiPass;

// Geolocation Settings
extern bool EnableGeolocation;
extern bool EnableWeather;
extern int GeolocationCooldown;

// Boot Settings
extern int DelayBoot;
extern bool ShowSysLogOnDisplay;

//Time Settings
extern int GMTOffset;
extern bool DaylightSavings;

// Experimental Settings
extern bool EnableOTAMenu;
extern bool EnableSDCard;
extern int NumberOfButtons;

//Hardware Info
extern int DisplayWidth;
extern int Displayheight;
extern DisplayType Display;
extern int DisplayCSPin;
extern int DisplayRSTPin;
extern int DisplayDCPin;
extern int DisplaySD;

#endif // OSW_FLAGS_H
