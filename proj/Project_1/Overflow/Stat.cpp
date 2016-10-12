/*
 * File:   Stat.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on October 11, 2016
 */

#include <sstream>

#include "Stat.h"


//BStat

Flow::BStat::BStat(){
    name = "Stat";
    flName = "Statistic";
    value = 0;
}

Flow::BStat::BStat(const BStat &other){
    name = other.name;
    flName = other.flName;
    value = other.value;
}

Flow::BStat::BStat(const std::string &nName, const std::string &nFlName, unsigned char nValue){
    name = nName;
    flName = nFlName;
    value = nValue;
}

std::string Flow::BStat::toString() const{
    std::stringstream r;

    r << name << ": " << static_cast<int>(value.get());

    return r.str();
}

//IStat

Flow::IStat::IStat(){
    name = "Stat";
    flName = "Statistic";
    _max = 100;
    _min = 0;
    _value = 0;
    _absMax = 9999;
    _absMin = 0;
}

Flow::IStat::IStat(const IStat &other){
    name = other.name;
    flName = other.flName;
    _max = other._max;
    _min = other._min;
    _value = other._value;
    _absMax = other._absMax;
    _absMin = other._absMin;
}

Flow::IStat::IStat(const std::string &nName, const std::string &nFlName, int value, int max, int min, int absMax, int absMin){
    name = nName;
    flName = nFlName;
    _value = value;
    _max = max;
    _min = min;
    _absMax = absMax;
    _absMin = absMin;
}

int Flow::IStat::absMax() const{
    return _absMax;
}

int Flow::IStat::absMin() const{
    return _absMin;
}

int Flow::IStat::max() const{
    return _max;
}

int Flow::IStat::min() const{
    return _min;
}

void Flow::IStat::setMax(int value){
    if(value >= _absMax){
        _max = _absMax;
    }
    else if(value <= _min){
        _max = _min + 1;
    }
    else{
        _max = value;
    }
}

void Flow::IStat::setMin(int value){
    if(value <= _absMin){
        _min = _absMin;
    }
    else if(value >= _max){
        _min = _max - 1;
    }
    else{
        _max = value;
    }
}

void Flow::IStat::setVal(int value){
    if(value >= _max){
        _value = _max;
    }
    else if(value <= _min){
        _value = _min;
    }
    else{
        _value = value;
    }
}

std::string Flow::IStat::toString() const{
    std::stringstream r;

    r << name << ": " << _value << "/" << _max;

    return r.str();
}