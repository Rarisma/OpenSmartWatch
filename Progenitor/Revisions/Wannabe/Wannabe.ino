//Open Smart Watch Progenitor (Wannabe)
//All Rights Reserved by Jake (Rarisma) (C) 2023 if recieved privately.
//If publically distributed, please see GNU GPL v3 for your rights.

//Open Smart Watch Flags, some may be user editable.
//TODO: make relevant flags editable past compile time i.e settings app.

//MaviBoot Config Data
String Distribution = "Wannabe"; //Version Information
bool DelayBoot = true;   //Stay on MaviBoot screen to read logs.
bool MaviLogToDisplay = false; //Show MaviLog msgs on display
bool MaviLogToSerial = true; //Show MaviLog messages to serial (debug)
int BootDelayTime = 5000; //How long boot should be delayed for (ms)
bool ShowMaviLogDebugMessages = true; //Shows debug MaviLog Messages (set to false or logs will be cluttered.)
bool ShowLoopDebugMessages = true; //Shows debug for the loop func

//WiFi Releated settings.
bool EnableWiFi = true;  //enables or disables WiFi (and bluetooth)
String WiFiSSID = "DREAMLAND"; // WiFi SSID (Name)
String WiFiPassword = "NIGHTMARE"; //WiFi Password

//Geolocation settings
bool EnableLocationTracking = true; 
String GoogleMapsGeolocationAPIKey = ""; //used to get long/lat
String OpenWeatherMapAPIKey = ""; //used to get weather
int GeolocationAPITimeout = 900; //timeout in sec on how often to ping the geo api.

//Misc.
bool EnableMPU = false; //enables or disables MPU Sensor
//^^^End of Flags
//Start of import

//SD Card 
#include <SPI.h>
#include <SD.h>

//WiFi + NTP server sync.
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "time.h"

//Geolocation
#include <WifiLocation.h>
#include <HTTPClient.h> //Used for accessing Open Weather Map API
#include <ArduinoJson.h> //Parsing data attained from Open Weather
#include "math.h" //rounding temp to 1dp
WifiLocation location(GoogleMapsGeolocationAPIKey);
String WeatherCache;
long LastGeolocationPing;
String latitude;
String longnitude;

//Display + Display Pins
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#define TFT_CS         15
#define TFT_RST        32
#define TFT_DC         14
#define TFT_SD         27

Adafruit_ST7789 Display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
void setup() {
    Serial.begin(115200);

    //WiFi enablement appears to be 'fragile' as in it will just bootloop if enable later.
    //Since there's no display at this point in the boot, we just log to serial.
    Serial.println("Starting WiFi Connectivity");
    if (EnableWiFi)  //WiFi setup
    {
      WiFi.mode(WIFI_STA); //Connects to WiFi
      WiFi.begin(WiFiSSID, WiFiPassword);

      //WiFi Network
      if (WiFi.status() == 6) { Serial.println("WiFi Connected.");}
      else { Serial.println("Couldn't connect to WiFi - (" + String(WiFi.status()) + ")"); }
    }
    else { MaviLog("WARN", "WiFi is disabled in OSW Flags, consider enabling it."); }

    MaviLog("Info","Starting to connect to NTP Servers");

    //NTP Setup
    configTime(0, 3600, "pool.ntp.org");
    time_t now = time(nullptr);

    //Wait for clock to be set correctly.
    while (now < 8 * 3600 * 2) {
      delay(500);
      now = time(nullptr);
    }
    
    //MaviLog("Info","Got time as " + now);

    //Display Init
    Display.init(240, 280);
    Serial.println("Display booted.");
    Display.fillScreen(ST77XX_BLACK);
    Display.println("             Open Smart Watch\n            Version Progenitor\n");
    MaviLog("ok", "Display Initalised.");

    if (!EnableLocationTracking) {MaviLog("WARN", "Geolocation stuff is disabled, consider enabling it."); }

  /*if (!SD.begin(TFT_SD)) {
    Serial.println("SD card initialization failed");
    return;
  }
  
  File root = SD.open("/");
  
  while (true) {
    File entry = root.openNextFile();
    if (!entry) {
      break;
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
    } else {
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
  */
    if (DelayBoot){
      MaviLog("WARN","DelayBoot is enabled, waiting " + String(BootDelayTime) + " ms");
      delay(BootDelayTime);
    }
}

//Logging tool
void MaviLog(String Status, String Message){ 
  if (ShowMaviLogDebugMessages) {Serial.println("MaviLog Initiated with a status of '" + Status + "' and a message of '" +  Message + "'");}
   
  //Displays [STATUS] - MESSAGE on the display
  //Below the status is colored green if its okay or red if not.
  if (MaviLogToDisplay)
  {
    if (ShowMaviLogDebugMessages) {Serial.println("Starting to present message");}
    Display.print("[");
    if (Status == "ok"){ Display.setTextColor(ST77XX_GREEN, ST77XX_BLACK); }
    else if (Status == "WARN"){ Display.setTextColor(ST77XX_YELLOW, ST77XX_BLACK); }
    else { Display.setTextColor(ST77XX_RED, ST77XX_BLACK); }
    Display.print(Status);
    Display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  
    Display.print("] - " + Message + "\n");
    if (ShowMaviLogDebugMessages) {Serial.println("Presented message to display");}
  }


  //Print to serial.
  if (MaviLogToSerial) 
  {
    Serial.println("[" + Status + "] " + Message);
    if (ShowMaviLogDebugMessages) {Serial.println("printed to serial");}
  }
    if (ShowMaviLogDebugMessages) {Serial.println("End of MaviLog func.");}

}

void loop() {
  if (ShowLoopDebugMessages) { Serial.println("Loop() started");}

  Display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  

  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    MaviLog("Error","Failed to retrieve time info");
    return;
  }
  else
  {
    Display.setCursor(40,20);
    String hour = String(timeinfo.tm_hour);
    String minute = String(timeinfo.tm_min);

    //Makes times such as 1 minute into 01.
    if (hour.length() == 1) {hour = "0" + hour;}
    if (minute.length() == 1) {minute = "0" + minute;}

    Display.setTextSize(14);
    Display.fillScreen(ST77XX_BLACK);
    Display.println(hour);
    Display.setCursor(40,150);
    Display.println(minute); //Space to line it up. 
  }


  if (EnableWiFi && WiFi.status())
  {
      Display.setTextColor(ST77XX_GREEN, ST77XX_BLACK); 
  }
  else {  Display.setTextColor(ST77XX_RED, ST77XX_BLACK);  }
  Display.setTextSize(1);
   .setCursor(30, 260);
  Display.print("WiFi");

  if (EnableLocationTracking && (LastGeolocationPing - int(&timeinfo)) >= 900)
  {
      location_t loc = location.getGeoFromWiFi();
      if (WiFi.status() == WL_CONNECTED) {
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
  else {
    Serial.println("time since last weather ping: " + (LastGeolocationPing - int(&timeinfo)));
  }

  Display.print(WeatherCache);

  //Update at the start of the next minute.
  delay((61 - timeinfo.tm_sec) * 1000);
}
