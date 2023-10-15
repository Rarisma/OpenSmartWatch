#include "Arduino.h"
#include "DisplayType.h"
#include "OSWBoot\Flags.h"
#include "Logging\SysLog.h"
#include <Adafruit_GFX.h>    //Standard Adafruit Library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <System\SystemInfo.h>

// Adafruit Display
Adafruit_ST7789 ST7789 = Adafruit_ST7789(DisplayCSPin, DisplayDCPin, DisplayRSTPin);

void InitaliseDisplay(){
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            Log("Display initalising as Adafruit ST7789", LogLevel::Info);
            ST7789.init(240, 280);
            ST7789.fillScreen(ST77XX_BLACK);
            break;
    }

    Log("Display initalised.", LogLevel::Info);
}

void PrintHomeScreen(){
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            ST7789.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  
            ST7789.setCursor(40,20);
            ST7789.println("Hello!");
            break;
    }
}

void PrintBootScreen(){
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            ST7789.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  
            ST7789.setCursor(40,20);
            ST7789.println("Welcome to OpenSW - " + String(Branch)  + "!");
            ST7789.println("Ver: " + String(ReleaseName) + "  " + Version[0] + "." + Version[1] + "." + Version[2]);
            break;
    }

}