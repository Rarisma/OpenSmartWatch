//Open Smart Watch Revision C (BEAUTIFUL STAR)
//All Rights Reserved by Jake (rarisma) (C) 2023 if you have recieved this privately.
//This code is licensed under GNU GPL v3 if publically published,

//WiFi + NTP server sync.
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

void setup() {
    Serial.begin(115200);
    Serial.println("Starting WiFi Connectivity");
    WiFi.mode(WIFI_STA);
    WiFi.begin("blanked", "blanked");
    delay(1000);
    if (WiFi.status()) { Serial.begin("WiFi Connected.");}
    else { Serial.begin("Couldn't connect to WiFi"); }
}

void loop() {
  // put your main code here, to run repeatedly:

}
