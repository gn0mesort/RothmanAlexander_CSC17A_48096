/*
 * File:   stat.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 1, 2016
 */

#include "stat.h"

Flow::BStat::BStat(){
    _value = 0;
}

Flow::BStat::BStat(unsigned char value, const std::string &name, const std::string &flName){
    _value = value;
    _name = name;
    _flName = flName;
}

unsigned char Flow::BStat::value() const{
    return _value;
}

void Flow::BStat::value(unsigned char nValue){
    _value = nValue;
}

unsigned char Flow::BStat::max() const{
    return 255;
}

unsigned char Flow::BStat::min() const{
    return 0;
}

/**********************************************************************************************************************/
/**********************************************************************************************************************/
/**********************************************************************************************************************/

/**
 * Default IStat Constructor
 */
Flow::IStat::IStat(){
    _value = 0;
    _absMax = 0x7FFFFFFF; //Max of a signed 32-bit int
    _absMin = 0x80000000; //Min of a signed 32-bit int
    _max = 100;
    _min = 0;
}

Flow::IStat::IStat(int value, const std::string &name, const std::string &flName, int max, int min, int absMax,
                   int absMin){
    if(absMax <= absMin){
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

int Flow::IStat::absoluteMax() const{
    return _absMax;
}

int Flow::IStat::absoluteMin() const{
    return _absMin;
}

int Flow::IStat::value() const{
    return _value;
}

void Flow::IStat::value(int nValue){
    if(nValue > _max){
        _value = _max;
    }
    else if(nValue < _min){
        _value = _min;
    }
    else{
        _value = nValue;
    }
}

int Flow::IStat::max() const{
    return _max;
}

void Flow::IStat::max(int nMax){
    if(nMax > _absMax){
        _max = _absMax;
    }
    else if(nMax < _min){
        _max = _min + 1;
    }
    else{
        _max = nMax;
    }
}

int Flow::IStat::min() const{
    return _min;
}

void Flow::IStat::min(int nMin){
    if(nMin < _absMin){
        _min = _absMin;
    }
    else if(nMin > _max){
        _min = _max - 1;
    }
    else{
        _min = nMin;
    }
}