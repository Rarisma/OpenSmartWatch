#include <Logging\SysLog.h>
#include <OSWBoot\Flags.h>
#include <System\SystemState.h>
#include <WiFi.h>
#include <OSWBoot\APIKeys.h>
#include <WifiLocation.h>
#include <HTTPClient.h> //Used for accessing Open Weather Map API
#include <ArduinoJson.h> //Parsing data attained from Open Weather
#include "math.h" //rounding temp to 1dp

//Conver GoogleMapsAPIKey to key for some reason we can't just String(GoogleMapsAPIKey)
String Key = String(GoogleMapsAPIKey);
WifiLocation location(Key);
String WeatherCache = ""; //Previously attained Weather.

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

void GetWeather(){
    //TODO: ADD GEO TIMER CHECK
    if (WiFi.status() == WL_CONNECTED && EnableGeolocation) {
        location_t loc = location.getGeoFromWiFi();
        HTTPClient http;
        String url = "http://api.openweathermap.org/data/2.5/weather?lat=" + String(loc.lat, 4) + "&lon=" + String(loc.lon, 4) + "&appid=" + OpenWeatherMapAPIKey + "&units=metric";
        http.begin(url);
        int httpResponseCode = http.GET();
        if (httpResponseCode > 0) {
            String payload = http.getString();
            Serial.println(payload);

            DynamicJsonDocument doc(2048);
            deserializeJson(doc, payload);

            float temp = float(doc["main"]["temp"]);
            String location = doc["name"];
            String main_weather = doc["weather"][0]["main"];

            WeatherCache = "   " + location.substring(0,4) + " " + main_weather + " (" + String(int(temp)) + (char)247 + "C)";
        } 
        else 
        {
            Serial.println("Error: " + httpResponseCode); 
            WeatherCache = "     ???? None (0" + String((char)247) + "C)";
        }
        http.end();
    }
}