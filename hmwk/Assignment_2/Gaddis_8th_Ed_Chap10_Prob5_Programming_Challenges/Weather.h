/* 
 * File:   Weather.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Created on October 3, 2016
 */

#ifndef WEATHER_H
#define WEATHER_H

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

struct Weather{
    float tRain;
    float hTemp;
    float lTemp;
    float avTemp;
};

#endif /* WEATHER_H */

