#include <Logging\SysLog.h>
#include <OSWBoot\Flags.h>
#include <System\SystemState.h>
#include <WiFi.h>
#include <OSWBoot\APIKeys.h>
#include <WifiLocation.h>
#include <HTTPClient.h> //Used for accessing Open Weather Map API
#include <ArduinoJson.h> //Parsing data attained from Open Weather
#include "math.h" //rounding temp to 1dp
#include "Arduino.h"

//Conver GoogleMapsAPIKey to key for some reason we can't just String(GoogleMapsAPIKey)
String Key = String(GoogleMapsAPIKey);
WifiLocation location(Key);
String WeatherCache = ""; //Previously attained Weather.

void GetLocation(){
    if (EnableGeolocation) {
        Log("Geoloc disabled.", LogLevel::Warn);
        return;
    }

    Log("Getting loc...", LogLevel::Info);
    if (WiFi.status() == WL_CONNECTED) {
        location_t loc = location.getGeoFromWiFi();
    }
    else { Log("No WiFi.", LogLevel::Error); }
}

String GetWeather() {
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

            return location/*.substring(0,4)*/ + " " + main_weather + " (" + String(int(temp)) + (char)247 + "C)";
        } 
        else 
        {
            Serial.println("Error: " + httpResponseCode); 
            WeatherCache = "Can't get the weather or location here.";
        }
        http.end();
    }
}