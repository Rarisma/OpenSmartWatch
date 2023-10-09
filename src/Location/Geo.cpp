#include <Logging\SysLog.h>
#include <OSWBoot\Flags.h>
#include <System\SystemState.h>
#include <WiFi.h>
#include <OSWBoot\APIKeys.h>
#include <WifiLocation.h>

WifiLocation location(String(GoogleMapsGeolocationAPIKey));

void GetLocation(){
    if (EnableGeolocation) {
        Log("Geolocation disabled.", LogLevel::Warn);
        return;
    }

    Log("Getting location...", LogLevel::Info);
    if (WiFi.status() == WL_CONNECTED) {
        location_t loc = location.getGeoFromWiFi();
    }
    else { Log("No WiFi connection.", LogLevel::Error); }
}