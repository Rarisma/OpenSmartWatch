#ifndef DISPLAY_TYPE_H
#define DISPLAY_TYPE_H

enum class DisplayType {
    //Displays that support Adafruit ST7789
    AdaST7789  = 0,

    //Don't have a display and want to test, all display calls go to the log instead.
    JustPrintToSerial = 1 
};

#endif // DISPLAY_TYPE_H
