/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Stat.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for Stat.h
 * Created on October 11, 2016
 */

//User Libraries
#include "Stat.h" //Statistic Objects

//name
//Return the name of this Stat
//Output:
//The current value of _name

std::string Flow::Stat::name() const{
    return _name;
}

//flName
//Return the full name of this Stat
//Output:
//The current value of _flName

std::string Flow::Stat::flName() const{
    return _flName;
}

//setName
//Set the current name of this Stat
//Input:
//name
//The name to set this Stat's name to

void Flow::Stat::setName(const std::string &name){
    _name = name;
}


//setFlName
//Set the current full name of this Stat
//Input:
//flName
//The full name to set this Stat's full name to

void Flow::Stat::setFlName(const std::string &flName){
    _flName = flName;
}

//BStat
//Default BStat constructor

Flow::BStat::BStat(){
    setName("Stat"); //Set name
    setFlName("Statistic"); //Set flName
    _value = 0; //Set value
}

//BStat
//Copy constructor

Flow::BStat::BStat(const BStat &other){
    setName(other.name());
    setFlName(other.flName());
    _value = other.value();
}

//BStat
//Parameterized constructor

Flow::BStat::BStat(const std::string &nName, const std::string &nFlName, unsigned char nValue){
    setName(nName);
    setFlName(nFlName);
    _value = nValue;
}

//value
//Return the current value of this BStat
//Output:
//The value stored in _value

unsigned char Flow::BStat::value() const{
    return _value;
}

//setValue
//Set the current value of this BStat
//Input:
//value
//The value to set this BStat to

void Flow::BStat::setValue(unsigned char value){
    _value = value;
}

//IStat
//Default IStat constructor

Flow::IStat::IStat(){
    setName("Stat"); //Set name
    setFlName("Statistic"); //Set flName
    _max = 100; //Set max value
    _min = 0; //Set min value
    _value = 0; //Set value
    _absMax = 9999; //Set absolute max value
    _absMin = 0; //Set absolute min value
}

//IStat
//Copy constructor

Flow::IStat::IStat(const IStat &other){
    setName(other.name());
    setFlName(other.flName());
    _max = other._max;
    _min = other._min;
    _value = other._value;
    _absMax = other._absMax;
    _absMin = other._absMin;

}

//IStat
//Parameterized constructor

Flow::IStat::IStat(const std::string &name, const std::string &flName, int value, int max, int min, int absMax, int absMin){
    setName(name);
    setFlName(flName);
    _value = value;
    _max = max;
    _min = min;
    _absMax = absMax;
    _absMin = absMin;
}

//value
//Return the current value of this IStat
//Output:
//The value stored in _value

int Flow::IStat::value() const{
    return _value;
}

//absMax
//Return the absolute maximum value of this IStat
//Output:
//The largest value this IStat is allowed to have

int Flow::IStat::absMax() const{
    return _absMax;
}

//absMin
//Return the absolute minimum value of this IStat
//Output:
//The smallest value this IStat is allowed to have

int Flow::IStat::absMin() const{
    return _absMin;
}

//max
//Return the current maximum value of this IStat
//Output:
//The highest value that _value is allowed to reach currently

int Flow::IStat::max() const{
    return _max;
}

//min
//Return the current minimum value of this IStat
//Output:
//The lowest value that _value is allowed to reach currently

int Flow::IStat::min() const{
    return _min;
}

//setMax
//Set the max value for this IStat
//Input:
//value
//The value to set the max to

void Flow::IStat::setMax(int value){
    if(value >= _absMax){ //max may not exceed absMax
        _max = _absMax;
    }
    else if(value <= _min){ //max may not be less than one more than min
        _max = _min + 1;
    }
    else{
        _max = value;
    }
}

//setMin
//Set the min value for this IStat
//Input:
//value
//The value to set the min to

void Flow::IStat::setMin(int value){
    if(value <= _absMin){ //min may not be less than absMin
        _min = _absMin;
    }
    else if(value >= _max){ //min may not exceed one less than max
        _min = _max - 1;
    }
    else{
        _max = value;
    }
}

//setValue
//Set the current value of this IStat
//Input:
//value
//The value to set this IStat to

void Flow::IStat::setValue(int value){
    if(value >= _max){ //If greater than max then assign the max value
        _value = _max;
    }
    else if(value <= _min){ //If less than min then assign the min value
        _value = _min;
    }
    else{ //Otherwise assign as normal
        _value = value;
    }
}