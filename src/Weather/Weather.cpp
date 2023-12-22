/* Weather.cpp
    Accesses weather APIs to get the weather.
    This currently relies on OpenWeatherMap.
*/
#include <Arduino.h>

/// @brief This calls the OpenWeatherMap OneCall 3.0 API.
/// @param lon Longnitude of the location
/// @param lat Latitude of the Location.
/// @return 
String OneCall3(String lon, String lat, String APIKey)
{
    String URL = "https://api.openweathermap.org/data/3.0/onecall?lat="+lat+"&lon="+lon+"&exclude={part}&appid="+APIKey+"&units=metric";

    return "";
}

