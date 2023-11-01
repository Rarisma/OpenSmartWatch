#include <OSWBoot\OSWBoot.h>
#include <WiFi.h>
#include <Arduino.h>
#include <System\SystemInfo.h>
#include <Logging\SysLog.h>

/// @brief Calls OSWBoot.Initalise()
void setup() 
{
    Serial.begin(115200);
    Serial.println("RECKLESS TONGUE");
    Initalise();
}


/// @brief Ignore this, follow OSWBoot.Initalise()
void loop() { }