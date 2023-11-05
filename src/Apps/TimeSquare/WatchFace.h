#ifndef WATCHFACE_H
#define WATCHFACE_H

#include <Arduino.h>
#include "Logging\SysLog.h"
#include "System\TimeUtils.h"

/// @brief Enum for controlling how the clock will display.
enum WatchDisplayType
{
    HrsBigMinsMid = 0, ///< 12:30 would have a big 12 and a small 30 in between the 1 and 2.
    BigTime = 1,       ///< 12:30 would show 12 on the top half and 30 on the bottom half.
    StandardTime = 2, //12:30 would just show 12:30 in large at the top of the screen.
    InformationDense = 3, //Shows as much information as possible.
};

/// @brief Calling this function will do the following:
/// 1) Clear the screen 
/// 2) Unload anything before
/// 3) Show the Watch face.
/// 4) Block Syslog from logging to the display
void ShowWatchFace();

/// @brief Prints the current time to the display.
/// @param type How time will be shown.
void PrintTime(WatchDisplayType type);
void WaitForNextUpdate();
#endif // WATCHFACE_H
