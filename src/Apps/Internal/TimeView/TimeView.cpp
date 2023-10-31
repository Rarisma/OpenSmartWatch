/*  Time View is another view but is focused on getting
    a time for say setting an alarm or date/time.
    Looks like this:

            <Optional Message>
            
            <-      1 8     ->
            <-      0 0     ->

            <Press l+R to set>
*/
#include <array>
#include <Arduino.h>

/// @brief Spawns the TimeView, prompting the user to pick a time.
/// @return an array containing a hours value and a mins val (24hr)
/// i.e [23,59]
std::array<int, 2> GetTimeFromUser() {
    //Todo: add TimePicker code
    delay(9999); //crash code when called more or less.
    return {0,0};
}