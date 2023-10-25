#ifndef DISPLAY_H
#define DISPLAY_H

#include "Arduino.h"

void InitaliseDisplay();
void PrintHomeScreen();
void PrintBootScreen();
void PrintToDisplay(String Message, int FontSize = 2, bool NewLine=true, int X=-1,int Y=-1, int Color=0xFFFFFF);
void ShowLog(String Message, String Level, int Color);
void ClearDisplay(int Color = 0x00000);

#endif // DISPLAY_H
