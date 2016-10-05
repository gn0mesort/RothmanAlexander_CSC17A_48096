/* 
 * File:   Weather.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Store weather data
 * Created on October 3, 2016
 */

#ifndef WEATHER_H
#define WEATHER_H

//Weather
//Stores data about the weather for a single month
struct Weather{
    float tRain; //The total rain in inches
    float hTemp; //The high temperature in Fahrenheit
    float lTemp; //The low temperature in Fahrenheit
    float avTemp; //The average temperature in Fahrenheit
};

#endif /* WEATHER_H */

