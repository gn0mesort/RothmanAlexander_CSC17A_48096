/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   stat.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for stat.h
 * Created on December 1, 2016
 */

#include "stat.h"

/**
 * Default BStat constructor
 */
Flow::BStat::BStat(){
    _value = 0;
}

/**
 * Parameterized BStat constructor
 * @param value The value of the BStat
 * @param name The short name of the BStat
 * @param flName The full name of the BStat
 */
Flow::BStat::BStat(unsigned char value, const std::string &name, const std::string &flName){
    _value = value;
    _name = name;
    _flName = flName;
}

/**
 * Get the value of the BStat
 * @return The value of the BStat
 */
unsigned char Flow::BStat::value() const{
    return _value;
}

/**
 * Set the value of the BStat
 * @param nValue The value to set the BStat to
 */
void Flow::BStat::value(unsigned char nValue){
    _value = nValue;
}

/**
 * Get the maximum value of the BStat
 * @return 255
 */
unsigned char Flow::BStat::max() const{
    return 255;
}

/**
 * Get the minimum value of the BStat
 * @return 0
 */
unsigned char Flow::BStat::min() const{
    return 0;
}

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/

/**
 * Default IStat constructor
 */
Flow::IStat::IStat(){
    _value = 0;
    _absMax = 0x7FFFFFFF; //Max of a signed 32-bit int
    _absMin = 0x80000000; //Min of a signed 32-bit int
    _max = 100;
    _min = 0;
}

/**
 * Parameterized IStat constructor
 * @param value The value of the IStat
 * @param name The short name of the IStat
 * @param flName The full name of the IStat
 * @param max The max value of the IStat
 * @param min The min value of the IStat
 * @param absMax The absolute maximum of the IStat
 * @param absMin The absolute minimum of the IStat
 */
Flow::IStat::IStat(int value, const std::string &name, const std::string &flName, int max, int min, int absMax,
                   int absMin){
    if(absMax <= absMin){ //Prevent overflow or underflow of absolute bounds
        throw Error::ArgumentException("Absolute Max cannot be less than or equal to Absolute Min");
    }
    else if(absMin >= absMax){
        throw Error::ArgumentException("Absolute Min cannot be greater than or equal to Absolute Max");
    }
    _name = name;
    _flName = flName;
    _absMax = absMax;
    _absMin = absMin;
    this->max(max);
    this->min(min);
    this->value(value);
}

/**
 * Get the absolute maximum of the IStat
 * @return The absolute maximum of the IStat
 */
int Flow::IStat::absoluteMax() const{
    return _absMax;
}

/**
 * Get the absolute minimum of the IStat
 * @return The absolute minimum of the IStat
 */
int Flow::IStat::absoluteMin() const{
    return _absMin;
}

/**
 * Get the value of the IStat
 * @return The value of the IStat
 */
int Flow::IStat::value() const{
    return _value;
}

/**
 * Set the value of the IStat
 * @param nValue The new value to set
 */
void Flow::IStat::value(int nValue){
    if(nValue > _max){ //If nValue is greater than the max value
        _value = _max; //Value is the max value
    }
    else if(nValue < _min){ //If nValue is less than the min value
        _value = _min; //Value is the min value
    }
    else{ //Otherwise
        _value = nValue;
    }
}

/**
 * Get the max value of the IStat
 * @return The max value of the IStat
 */
int Flow::IStat::max() const{
    return _max;
}

/**
 * Set the max value of the IStat
 * @param nMax The new max to set
 */
void Flow::IStat::max(int nMax){
    if(nMax > _absMax){ //If nMax is greater than the absolute max
        _max = _absMax; //The max is the absolute max
    }
    else if(nMax < _min){ //If nMax is less than the min value
        _max = _min + 1; //The max is the min + 1
    }
    else{ //Otherwise
        _max = nMax;
    }
}

/**
 * Get the min value of the IStat
 * @return The min value of the IStat
 */
int Flow::IStat::min() const{
    return _min;
}

/**
 * Set the min value of the IStat
 * @param nMin The new min to set
 */
void Flow::IStat::min(int nMin){
    if(nMin < _absMin){ //If nMin is less than the absolute min
        _min = _absMin; //The min value is the absolute min
    }
    else if(nMin > _max){ //If nMin is greater than the max value
        _min = _max - 1; //The min is the max - 1
    }
    else{ //Otherwise
        _min = nMin;
    }
}