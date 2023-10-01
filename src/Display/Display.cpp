#include "Arduino.h"
#include "DisplayType.h"
#include "OSWBoot\Flags.h"
#include "Logging\SysLog.h"
#include <Adafruit_GFX.h>    //Standard Adafruit Library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

void InitaliseDisplay(){
    switch (Display)
    {
        case DisplayType::AdaST7789: //Standard Adafruit ST7789 Display
            Log("Display initalising as Adafruit ST7789", LogLevel::Info);
            Adafruit_ST7789 ST7789 = Adafruit_ST7789(DisplayCSPin, DisplayDCPin, DisplayRSTPin);
            ST7789.init(240, 280);
            ST7789.fillScreen(ST77XX_BLACK);
            break;
    }

    Log("Display initalised.", LogLevel::Info);
}