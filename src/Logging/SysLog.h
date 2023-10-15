// SysLog.h

#ifndef SysLog_h
#define SysLog_h

#include "Arduino.h"

enum class LogLevel {
    Debug,
    Info,
    Warn,
    Error,
    Fatal
};

extern bool LogToDisplay;

void Log(String Message, LogLevel level);

#endif
