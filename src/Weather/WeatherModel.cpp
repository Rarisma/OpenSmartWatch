#include "Arduino.h"

/// @brief The time this forcast is for 
DateTime ForcastTime;

/// @brief Temperature at the time of forcast
float Temp;

/// @brief Pressure at the time of forcast
float Pressure;

/// @brief What the temperature really feels like, taking into account wind temp etc.
float FeelsLikeTemp;

/// @brief Humidity at the time of forecast.
float Humidity;

/// @brief Percentage of clouds.
float CloudPercent;

/// @brief UV index at the time of forecast.
float UVIndex;

/// @brief Average visibility at the time of forecast.
float Visibility;

/// @brief Wind Speed a the time of forecast.
float WindSpeed;

/// @brief Angle the wind is blowing at.
float WindDegree;

/// @brief Description of current weather. (i.e snow)
String Condtion;

/// @brief More indepth description of weather (i.e light rain and snow)
String ExtendedConditon;


/*
    string RainFall; // Amount of rainfall in 1h
    string SnowFall; // Ammount of snowfall in 1h
*/