//Jake (Rarisma) 2023, GNU GPL V3 unless otherwise stated.

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

//OSW Flags
bool BootDelay = true;

void setup() {  
  //Initiate Serial
  Serial.begin(115200);
  Serial.println("OSW - Rev B\nSerial Output Started.");

  MaviInit();

  MaviLog("ok","Showing Home Screen");

  if (BootDelay){
    MaviLog("WARN", "Boot Delay is enabled, waiting 5 seconds.");
    delay(5000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

void MaviInit(){
  MaviLog("ok","MaviInit started");
  InitDisp();
  delay(500);
  
  //Initiate Buttons
  MaviLog("ERROR","No buttons detected");

  //Initalise MPU
  InitMPU();
 
  //InitWiFi();
  
  MaviLog("ok","MaviInit finished.");
}

//Initialises Display
void InitDisp(){
  Display.init(240, 280);
  Serial.println("Display booted.");
  Display.fillScreen(ST77XX_BLACK);
  Display.println("             Open Smart Watch\n            Version Progenitor\n");
  MaviLog("ok", "MaviLog Test.");
  MaviLog("ok", "Display Initalised.");
}

//Initalises MPU
void InitMPU(){
  if (MPU.begin())
  {
    MPUEnabled = true;
    MaviLog("ok", "MPU found and enabled. ");
    MPU.setAccelerometerRange(MPU6050_RANGE_2_G);
    MPU.setGyroRange(MPU6050_RANGE_250_DEG);
    MPU.setFilterBandwidth(MPU6050_BAND_21_HZ);
    MaviLog("ok", "MPU Configured to " + String(MPU.getGyroRange()) + "    "
    + String(MPU.getAccelerometerRange()) + "   " + String(MPU.getFilterBandwidth()));
  }
  else { MaviLog("ERROR","No MPU found"); }
}

//Initalises Wifi
void InitWiFi(){
   MaviLog("ok","Connecting to WiFi...");
   WiFi.mode(WIFI_STA);
   int WifiAttemptCounter = 0;
   WiFi.begin("blanked", "blanked");
   while (WiFi.status() != WL_CONNECTED && WifiAttemptCounter <= 5) {
      delay(500);
      MaviLog("ok","WiFi Connection attempt " + String(WifiAttemptCounter) + " of 5");
      WifiAttemptCounter++;
   }
}

//Logging tool
void MaviLog(String Status, String Message){
  Serial.print("MaviLog Started");
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
