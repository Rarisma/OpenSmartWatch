 t//Open Smart Watch Revision C (BEAUTIFUL STAR)
//All Rights Reserved by Jake (Rarisma) (C) 2023 if you have recieved this privately.
//This code is licensed under GNU GPL v3 if publically published.

//Display
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#define TFT_CS         15
#define TFT_RST        32
#define TFT_DC         14
Adafruit_ST7789 Display = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

//MPU6050
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 MPU;
bool MPUEnabled = false;

//WiFi + NTP server sync.
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

//Open Smart Watch Flags.
bool EnableMPU = false; //enables or disables MPU Sensor.
bool EnableWifi = false;  //enables or disables WiFi (and bluetooth)
bool DelayBoot = false;   //Should boot be delayed?
int BootDelayTime = 5000; //How long boot should be delayed for (ms)

void setup() {
  //Initiate Serial
  Serial.begin(115200);
  Serial.println("OSW - Rev B\nSerial Output Started.");
  MaviBoot();
}

void loop() {
  delay (1000);
  }


void MaviBoot()
{
  MaviLog("OK","MaviBoot Started.");

  if (EnableWifi){
      MaviLog("OK","Starting WiFi Connectivity");
      WiFi.mode(WIFI_STA);
      WiFi.begin("blanked", "blanked");
      delay(1000);
      if (WiFi.status()) { MaviLog("OK", "WiFi Connected.");}
      else { MaviLog("ERROR", "Couldn't connect to WiFi"); }
  }
  else { MaviLog("WARN", "WiFi is disabled in OSW Flags.");  }

  
}



//Logging tool
void MaviLog(String Status, String Message){
  //Displays [STATUS] - MESSAGE on the display
  //Below the status is colored green if its okay or red if not.
  Display.print("[");
  if (Status == "ok"){ Display.setTextColor(ST77XX_GREEN, ST77XX_BLACK); }
  else if (Status == "WARN"){ Display.setTextColor(ST77XX_YELLOW, ST77XX_BLACK); }
  else { Display.setTextColor(ST77XX_RED, ST77XX_BLACK); }
  Display.print(Status);
  Display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  
  Display.print("] - " + Message + "\n");

  //Print to serial.
  Serial.println("[" + Status + "] " + Message);
}
