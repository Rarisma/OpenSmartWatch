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
            Log("Display initalising as ST7789", LogLevel::Info);
            ST7789.init(240, 280);
            ST7789.fillScreen(ST77XX_BLACK);
            break;
    }
    
    Log("Disp initalised.", LogLevel::Info);
    LogToDisplay = true;
}

void PrintHomeScreen(){
    LogToDisplay = false;
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            ST7789.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  
            ST7789.setCursor(40,20);
            break;
    }
}

void PrintBootScreen(){
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            ST7789.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  
            ST7789.setCursor(40,20);
            ST7789.println("OpenSW - " + String(Branch)  + "!");
            ST7789.println(" V: " + String(ReleaseName) + "  " + Version[0] + "." + Version[1] + "." + Version[2]);
            break;
    }
}

/// @brief This prints a line to the display
/// @param Message Message to be shown
void PrintToDisplay (String Message){
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            ST7789.println(Message);
            break;
    }
}

void ClearDisplay(){
    switch (Display){
        case DisplayType::AdaST7789:
            ST7789.setTextColor(0xFFFFFF);
            break;
    }
}


/// @brief This prints a syslog message to the display with coloring.
/// @param Message Message to be shown
void ShowLog (String Message, String Level, int Color){
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            ST7789.print("[");
            ST7789.setTextColor(Color);
            ST7789.print(Level);
            ST7789.setTextColor(0xFFFFFF);
            ST7789.println("] " + Message);
            break;
    }
}