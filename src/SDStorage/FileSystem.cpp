#include "Arduino.h"
#include "SD.h"
#include "System/Flags.h"
#include "Logging/SysLog.h"

void InitaliseSDCard() {
    if (!SD.begin(SDCardPin)) {
        Log("SD init Failed.", LogLevel::Error);
        return;
    }
    else { Log("SD Initalised", LogLevel::Info); }
}