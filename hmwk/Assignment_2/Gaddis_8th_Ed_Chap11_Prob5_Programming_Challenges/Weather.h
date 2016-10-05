/* 
 * File:   Weather.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Store weather data and define Month enumeration
 * Created on October 3, 2016
 */

#ifndef WEATHER_H
#define WEATHER_H

//Month
//Define months of the year as an enumeration from 0 to 11
enum Month {
    JANUARY = 0,
    FEBRUARY = 1,
    MARCH = 2,
    APRIL = 3,
    MAY = 4,
    JUNE = 5,
    JULY = 6,
    AUGUST = 7,
    SEPTEMBER = 8,
    OCTOBER = 9,
    NOVEMBER = 10,
    DECEMBER = 11
};

//Weather
//Stores data about the weather for a single month
struct Weather{
    float tRain; //The total rain in inches
    float hTemp; //The high temperature in Fahrenheit
    float lTemp; //The low temperature in Fahrenheit
    float avTemp; //The average temperature in Fahrenheit
};

#endif /* WEATHER_H */

