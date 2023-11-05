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
#include"Networking\Networking.h"

struct WeatherData {
  float temperature;
  float feelsLikeTemperature;
  int relativeHumidity;
  String weatherCondition;
  int cloudCoverage;
  float windSpeed;
  int windDirection;
  float precipitationChance;
  float lastHourRainVolume;
  String dateTimeText;
  String cityName;
  int cityPopulation;
  unsigned long sunriseTime;
  unsigned long sunsetTime;
};

//Conver GoogleMapsAPIKey to key for some reason we can't just String(GoogleMapsAPIKey)
String Key = String(GoogleMapsAPIKey);
WifiLocation location(Key);

void GetLocation(){
    if (AllowGeolocation) {
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
    //Connects to WiFi if we've disconnected.
    if (WiFi.status() != WL_CONNECTED) { ConnectToNetwork(DefaultWiFiSSID,DefaultWiFiPass); }

    if (AllowGeolocation && AllowWeather && WiFi.status() == WL_CONNECTED && OpenWeatherMapAPIKey != "") {
        location_t loc = location.getGeoFromWiFi();
        HTTPClient http;
        http.begin("http://api.openweathermap.org/data/2.5/weather?lat=" + String(loc.lat, 4) + "&lon=" + String(loc.lon, 4) + "&appid=" + OpenWeatherMapAPIKey + "&units=metric");
        int httpResponseCode = http.GET();
        if (httpResponseCode > 0) {
            String payload = http.getString();
            DynamicJsonDocument doc(2048);
            deserializeJson(doc, payload);

            float temp = float(doc["main"]["temp"]);
            String location = doc["name"];
            String main_weather = doc["weather"][0]["main"];

            return location.substring(0,4) + " " + main_weather + " (" + String(int(temp)) + (char)247 + "C)";
        } 
        else { Log("Failed to access weather", LogLevel::Info); }
        http.end();
        return "ERROR";
    }
}


/// @brief This gets the next 4 days of weather, hour by hour.
/// @return Returns a Multidimensional array containing the: 
/// Date, Overall Weather and another array containing 
/// The time, weather for that time and temp.
/// Example ["27/10/2023", "Sunny", [["12:00", "Cloudy", "20"],["13:00","Sunny","20"]]
/*
WeatherData getWeatherData() {
  WeatherData weatherDat;
  
  // HTTP GET request
  HTTPClient http;
  http.begin("TODO"); //ToDo: add URL;
  int httpResponseCode = http.GET();
  
  if (httpResponseCode > 0) {
    String payload = http.getString();
    
    // JSON parsing
    StaticJsonDocument<2048> jsonDoc;
    deserializeJson(jsonDoc, payload);

    weatherDat.temperature = jsonDoc["list"][0]["main"]["temp"];
    weatherDat.feelsLikeTemperature = jsonDoc["list"][0]["main"]["feels_like"];
    weatherDat.relativeHumidity = jsonDoc["list"][0]["main"]["humidity"];
    weatherDat.weatherCondition = jsonDoc["list"][0]["weather"][0]["main"];
    weatherDat.cloudCoverage = jsonDoc["list"][0]["clouds"]["all"];
    weatherDat.windSpeed = jsonDoc["list"][0]["wind"]["speed"];
    weatherDat.windDirection = jsonDoc["list"][0]["wind"]["deg"];
    weatherDat.precipitationChance = jsonDoc["list"][0]["pop"];
    weatherDat.lastHourRainVolume = jsonDoc["list"][0]["rain"]["1h"];
    weatherDat.dateTimeText = jsonDoc["list"][0]["dt_txt"];
    weatherDat.cityName = jsonDoc["city"]["name"];
    weatherDat.cityPopulation = jsonDoc["city"]["population"];
    weatherDat.sunriseTime = jsonDoc["city"]["sunrise"];
    weatherDat.sunsetTime = jsonDoc["city"]["sunset"];
  }
  
  http.end();
  
  return weatherDat;
}*/