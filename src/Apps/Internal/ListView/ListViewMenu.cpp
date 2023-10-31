//This shows a terminal like menu
/*== EXAMPLE MENU ==
SETTINGS
CONNECTED IO DEVICES
SLEEP
ALARMS
WEATHER
*/

#include <Arduino.h>
#include "Display\Display.h"
#include "<vector>"

/// @brief Takes list of items, displays them and 
/// lets the user choose an option
/// @param MenuItems - String[] of menu items 
/// @return Returns a int, of the index relating to the MenuItem selected.
int ShowListMenu(String Header, std::vector MenuItems)
{
    PrintToDisplay(Header,2, true, 80,20);

    for (int i = 0; i >= MenuItems.Size(); i++){
        PrintToDisplay("[" + MenuItems[i] + "]")
    }

    //InputManager.WaitForInput(5000)
    return 0;
}
