#include "Arduino.h"
#include "DisplayType.h"
#include "OSWBoot\Flags.h"
#include "Logging\SysLog.h"
#include <Adafruit_GFX.h>    //Standard Adafruit Library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include <System\SystemInfo.h>
#include "Location\Geo.h"

// Adafruit Display
Adafruit_ST7789 ST7789 = Adafruit_ST7789(DisplayCSPin, DisplayDCPin, DisplayRSTPin);

/// @brief This initalises the display.
/// For this to function properly you must have set the correct
/// Display in flags.cpp as OSW WILL NOT detect the display
/// This probably won't be bad if you mess it but I wouldn't.
void InitaliseDisplay(){
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            Log("Display initalising as ST7789", LogLevel::Info);
            ST7789.init(240, 280);
            ST7789.fillScreen(ST77XX_BLACK);
            break;
        case DisplayType::JustPrintToSerial:
            Log("Using serial as 'display', this should be for testing only", LogLevel::Warn);
            break;
    }
    
    Log("Disp initalised.", LogLevel::Info);
    LogToDisplay = true;
}

/// @brief Prints a Welcome to OSW message showing
///the build name and number.
void PrintBootScreen(){
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            ST7789.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  
            ST7789.setCursor(80,10);
            ST7789.println("OpenSW - " + String(Branch)  + "!");
            ST7789.println(" V: " + String(ReleaseName) + "  " + Version[0] + "." + Version[1] + "." + Version[2]);
            break;
        case DisplayType::JustPrintToSerial:
            Log("OpenSW - " + String(Branch)  + "!",LogLevel::Info);
            Log("Ver: " + String(ReleaseName) + "  " + Version[0] + "." + Version[1] + "." + Version[2], LogLevel::Info);
            break;
    }
}

/// @brief This prints a line to the display
/// @param Message Message to be shown
/// @param FontSize Text size of message
/// @param NewLine Tack on a \n char?
/// @param X Xcoord where to place it (You should also specify X.)
/// @param Y Ycoord where to place it (You should also specify Y.)
void PrintToDisplay (String Message, int FontSize = 2, bool Newline = true, int X=-1,int Y=-1, int Color=0xFFFFFF){
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            ST7789.setTextSize(FontSize);
            ST7789.setTextColor(Color); //Sets text to color (defaults to white.).

            //Sets cursor if X/Y vars are set.
            if (X != -1 || Y != -1){
                //Fail safe, to use the current x/y coords if only one is set.
                ST7789.setCursor(X != -1 ? X :ST7789.getCursorX(), Y != -1 ? Y :ST7789.getCursorY());
            }

            //Prints message (adds \n if NewLine is true)
            ST7789.print((Newline) ? Message + "\n" : Message);
            break;
        
        //Serial doesn't support formatting.
        case DisplayType::JustPrintToSerial:
            Log(Message, LogLevel::Warn);
            break;
    }
}

/// @brief Clears the display and resets cursor to 0,0.
/// @param Color Color to fill display with (defaults to black.)
void ClearDisplay(int Color = 0x00000){
    switch (Display){
        case DisplayType::AdaST7789:
            ST7789.fillScreen(Color);
            ST7789.setCursor(0,0);
            break;
        case DisplayType::JustPrintToSerial:
            Log("Serial doesn't support color calls, attempted to set display to " +  Color, LogLevel::Error);
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
            ST7789.setTextColor(0xFFFF);
            ST7789.println("] " + Message);
            break;
        case DisplayType::JustPrintToSerial:
            //do nothing since we've already logged.
            break;
    }
}