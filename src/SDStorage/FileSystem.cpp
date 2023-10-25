#include "Arduino.h"
#include "SD.h"
#include "OSWBoot\Flags.h"
#include "Logging\SysLog.h"

void InitaliseSDCard() {
    if (!SD.begin(DisplaySDPin)) {
        Log("SD init Failed.", LogLevel::Error);
        return;
    }
    else { Log("SD Initalised", LogLevel::Info); }
}