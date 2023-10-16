#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"

void InitaliseDisplay();
void PrintHomeScreen();
void PrintBootScreen();
void PrintToDisplay(String Message);
void ShowLog(String Message, String Level, int Color);

#endif // DISPLAY_H
