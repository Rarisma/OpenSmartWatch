#ifndef Flags
#define Flags

// WiFi/Bluetooth Connection Settings
extern bool AllowWiFi;
extern bool AllowBluetooth;
extern bool AllowNetworkTimeProtocol;

// Default WiFi Credentials
extern bool UseDefaultCreds;
extern char* DefaultWiFiSSID;
extern char* DefaultWiFiPass;

// Geolocation Settings
extern bool EnableGeolocation;
extern bool EnableWeather;
extern int GeolocationCooldown;

// Boot Settings
extern int DelayBoot;
extern bool ShowSysLogOnDisplay;

// Experimental Settings
extern bool EnableOTAMenu;
extern bool EnableSDCard;
extern int NumberOfButtons;

#endif // OSW_FLAGS_H
