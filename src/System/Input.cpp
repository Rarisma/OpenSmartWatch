#include <Arduino.h>
#include "System/Flags.h"
#include "Logging/SysLog.h"

/// @brief This initalises buttons attached to OSW
void InitaliseInput(){
    Log("Initalising input",LogLevel::Info);
    pinMode(ButtonAPin, INPUT);
    Log("Setting Button A as " + ButtonAPin,LogLevel::Info);
    pinMode(ButtonBPin, INPUT); 
    Log("Setting Button B as " + ButtonBPin,LogLevel::Info);
    Log("Input Initalised.",LogLevel::Info);
}

/// @brief Loops until ButtonA and/or ButtonB are pressed
/// @param Timeout The timeout duration in milliseconds (0 for no timeout).
/// @return An array of booleans, corresponding to if button a or b are pressed.
bool* AwaitInput(int Timeout = 0){
    Log("Waiting for a button press..",LogLevel::Info);
    bool ButtonAVal = false;
    bool ButtonBVal = false;
    
    unsigned long startTime = millis();  // Record the start time
    while (ButtonAVal == false && ButtonBVal == false)
    {
        // Check for button states
        ButtonAVal = (analogRead(ButtonAPin) == 4095);
        ButtonBVal = (analogRead(ButtonBPin) == 4095);

        Log("AVal:" + String(ButtonAVal) + " BVal: " + String(ButtonBVal), LogLevel::Debug);

        // Check for timeout if Timeout is not 0
        if (Timeout > 0 && (millis() - startTime) >= Timeout) {
            Log("Timeout reached!", LogLevel::Info);
            break;  // Exit the loop if timeout has been reached
        }
    }
    Log("Button pressed!",LogLevel::Info);
    return new bool[2] {ButtonAVal, ButtonBVal};
}