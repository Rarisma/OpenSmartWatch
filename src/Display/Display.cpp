#include "Arduino.h"
#include "OSWBoot/Flags.h"
#include "Logging/SysLog.h"
#include <SPI.h>
#include <System/SystemInfo.h>
#include "Location/Geo.h"
#include <Adafruit_GFX.h>    //Standard Adafruit Library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

/*  ==Display IDs (i.e Who made your display and what type is it)
    0 - No Display (Just goes to serial)
    1 - Adafruit ST7789 Displays.
*///We use the display ID system to save on compiled code space.

#define DisplayID 1 //Change to value of the display you have.

#ifdef DisplayID == 1
    // Adafruit Display
    Adafruit_ST7789 Display = Adafruit_ST7789(DisplayCSPin, DisplayDCPin, DisplayRSTPin);
#endif


/// @brief This initalises the display.
/// For this to function properly you must have set the correct
/// Display in flags.cpp as OSW WILL NOT detect the display
/// This probably won't be bad if you mess it but I wouldn't.
void InitaliseDisplay(){
    #ifdef DisplayID == 1 //Adafruit ST7789
            Log("Display initalising as ST7789", LogLevel::Info);
            Display.init(240, 280);
            Display.fillScreen(ST77XX_BLACK);
    #else
            Log("Using serial as 'display', this should be for testing only", LogLevel::Warn);
    #endif
    
    Log("Disp initalised.", LogLevel::Info);
    LogToDisplay = true;
}

/// @brief Prints a Welcome to OSW message showing
///the build name and number.
void PrintBootScreen(){
    #ifdef DisplayID == 1 //Adafruit ST7789
        Display.setTextColor(ST77XX_WHITE, ST77XX_BLACK);  
        Display.setCursor(80,10);
        Display.println("OpenSW - " + String(Branch)  + "!");
        Display.println(" V: " + String(ReleaseName) + "  " + Version[0] + "." + Version[1] + "." + Version[2]);
    #else
        Log("OpenSW - " + String(Branch)  + "!",LogLevel::Info);
        Log("Ver: " + String(ReleaseName) + "  " + Version[0] + "." + Version[1] + "." + Version[2], LogLevel::Info);
    #endif
}

/// @brief This prints a line to the display
/// @param Message Message to be shown
/// @param FontSize Text size of message
/// @param NewLine Tack on a \n char?
/// @param X Xcoord where to place it (You should also specify X.)
/// @param Y Ycoord where to place it (You should also specify Y.)
void PrintToDisplay (String Message, int FontSize = 2, bool Newline = true, int X=-1,int Y=-1, int Color=0xFFFFFF){
    #ifdef DisplayID == 1 //Adafruit ST7789
        Display.setTextSize(FontSize);
        Display.setTextColor(Color); //Sets text to color (defaults to white.).
        //Sets cursor if X/Y vars are set.
        if (X != -1 || Y != -1){
            //Fail safe, to use the current x/y coords if only one is set.
            Display.setCursor(X != -1 ? X : Display.getCursorX(), Y != -1 ? Y :Display.getCursorY());
        }

        //Prints message (adds \n if NewLine is true)
        Display.print((Newline) ? Message + "\n" : Message);
    #else
            Log(Message, LogLevel::Warn);
    #endif
}

/// @brief Clears the display and resets cursor to 0,0.
/// @param Color Color to fill display with (defaults to black.)
void ClearDisplay(int Color = 0x00000){
    #ifdef DisplayID == 1 //Adafruit ST7789
        Display.fillScreen(Color);
        Display.setCursor(0,0);
    #else
        Log("Serial doesn't support color calls, attempted to set display to " +  Color, LogLevel::Error);
    #endif
}

/// @brief This prints a syslog message to the display with coloring.
/// @param Message Message to be shown
void ShowLog (String Message, String Level, int Color){
    #ifdef DisplayID == 1; //Adafruit ST7789
        Display.print("[");
        Display.setTextColor(Color);
        Display.print(Level);
        Display.setTextColor(0xFFFF);
        Display.println("] " + Message);
    #else
        Log("Display.ShowLog, Was unhandled!", LogLevel::Warn);
    #endif
}

int GetTextWidth(String Text, int FontSize)
{
    #ifdef DisplayID == 1 //Adafruit ST7789
        int16_t x1, y1;
        uint16_t w, h;
    
        Display.setTextSize(FontSize);
        Display.getTextBounds(Text, 0, 0, &x1, &y1, &w, &h); // Get the bounds of the string
    
      return w; // Return the width of the string in pixels
    #endif
    
}