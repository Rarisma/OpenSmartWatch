//Open Smart Watch Progenitor (Wannabe)
//All Rights Reserved by Jake (Rarisma) (C) 2023 if recieved privately.
//If publically distributed, please see GNU GPL v3 for your rights.

//Open Smart Watch Flags, some may be user editable.
//TODO: make relevant flags editable past compile time i.e settings app.

//MaviBoot Config Data
String Distribution = "Wannabe"; //Version Information
bool DelayBoot = true;   //Stay on MaviBoot screen to read logs.
bool MaviLogToDisplay = true; //Show MaviLog msgs on display
bool MaviLogToSerial = true; //Show MaviLog messages to serial (debug)
int BootDelayTime = 5000; //How long boot should be delayed for (ms)

//WiFi Releated settings.
bool EnableWiFi = true;  //enables or disables WiFi (and bluetooth)
String WiFiSSID = "blanked"; // WiFi SSID (Name)
String WiFiPassword = "blanked"; //WiFi Password

//Geolocation settings
bool EnableLocationTracking = true; 
String GoogleMapsGeolocationAPIKey = "blanked"; //used to get long/lat
String BingMapsLocationAPIKey = "blanked"; //used to turn long/lat into addresses.
int GeolocationAPITimeout = 900; //timeout in sec on how often to ping the geo api.

//Misc.
bool EnableMPU = false; //enables or disables MPU Sensor
//^^^End of Flags
//Start of imports

//WiFi + NTP server sync.
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "time.h"

//Geolocation
#include <WifiLocation.h>
#include <bingMapsGeocoding.h>
WifiLocation location(GoogleMapsGeolocationAPIKey);
BingGeoCoding bingGeoCoding(BingMapsLocationAPIKey);
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
      delay(5000); //1 Sec Delay to give a chance for WiFi to be connected.

      //WiFi Network
      if (WiFi.status()) { Serial.println("WiFi Connected.");}
      else { Serial.println("Couldn't connect to WiFi"); }
    }
    else { MaviLog("WARN", "WiFi is disabled in OSW Flags, consider enabling it."); }

    //NTP Setup
    configTime(0, 3600, "pool.ntp.org");
    time_t now = time(nullptr);

    //Wait for clock to be set correctly.
    while (now < 8 * 3600 * 2) {
      delay(500);
      now = time(nullptr);
    }
    
    //Display Init
    Display.init(240, 280);
    Serial.println("Display booted.");
    Display.fillScreen(ST77XX_BLACK);
    Display.println("             Open Smart Watch\n            Version Progenitor\n");
    MaviLog("ok", "MaviLog Test.");
    MaviLog("ok", "Display Initalised.");

    if (EnableLocationTracking)
    {
        location_t loc = location.getGeoFromWiFi();
        Serial.println(location.getSurroundingWiFiJson());
        latitude = String(loc.lat, 7);
        longnitude = String(loc.lon, 7);
        LastGeolocationPing = now;

        bingGeoData_t geoData = bingGeoCoding.getGeoFromPosition (loc.lat, loc.lon);
        Serial.println ("Geocoding result: " + bingGeoCoding.bgStatusStr (bingGeoCoding.getStatus ()));
        Serial.printf ("Address: %s\n", bingGeoCoding.getCompleteAddress (&geoData).c_str ());
    }
    else {MaviLog("WARN", "Geolocation stuff is disabled, consider enabling it."); }

    if (DelayBoot){
      MaviLog("WARN","DelayBoot is enabled, waiting " + String(BootDelayTime) + " ms");
      delay(BootDelayTime);
    }
}

//Logging tool
void MaviLog(String Status, String Message){  
  //Displays [STATUS] - MESSAGE on the display
  //Below the status is colored green if its okay or red if not.
  if (MaviLogToDisplay)
  {
     Display.print("[");
    if (Status == "ok"){ Display.setTextColor(ST77XX_GREEN, ST77XX_BLACK); }
    else if (Status == "WARN"){ Display.setTextColor(ST77XX_YELLOW, ST77XX_BLACK); }
    else { Display.setTextColor(ST77XX_RED, ST77XX_BLACK); }
    Display.print(Status);
    Display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  
    Display.print("] - " + Message + "\n");
  }


  //Print to serial.
  if (MaviLogToSerial) { Serial.println("[" + Status + "] " + Message); }
  
}

void loop() {
  Display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  

  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    MaviLog("Error","Failed to retrieve time info");
    return;
  }
  else
  {
    Display.setCursor(40,20);
    int hour = timeinfo.tm_hour;
    int minute = timeinfo.tm_min;
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
  Display.setCursor(30, 260);
  Display.print("WiFi");

  if (EnableLocationTracking && (LastGeolocationPing - int(&timeinfo)) >= 900)
  {
    
  }
  
  //Update at the start of the next minute.
  delay((61 - timeinfo.tm_sec) * 1000);
}
