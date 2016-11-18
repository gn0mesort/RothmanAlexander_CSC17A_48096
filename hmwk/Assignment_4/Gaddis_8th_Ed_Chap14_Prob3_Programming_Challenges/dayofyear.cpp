/*
 * File:   dayofyear.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for dayofyear.h
 * Created on November 16, 2016
 */

#include "dayofyear.h"

std::string DayOfYear::_months[NUM_MON] = {"January", "February", "March", "April", "May", "June", "July", "August",
                                           "September", "October", "November", "December"};

unsigned char DayOfYear::_monthDays[NUM_MON] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//monthLookup
//Return the number of a given month
//Input:
//month
//The name of a month
//Output:
//A value representing the input month

unsigned char DayOfYear::monthLookup(std::string month){
    unsigned char r = NUM_MON; //Set r to an out of bounds value

    for(unsigned char i = 0; i < NUM_MON; ++i){ //For each month
        if(_months[i] == month){ //If month is equal to the current month name
            r = i; //Set r to i
        }
    }

    return r;
}

//DayOfYear
//Parameterized Constructor
//Input:
//month
//The name of a month
//day
//The day of the given month
//Output:
//A new DayOfYear object representing the given month and day

DayOfYear::DayOfYear(std::string month, unsigned int day){
    _day = day % 365;

    for(int i = 0; i < monthLookup(month); ++i){
        _day = (_day + _monthDays[i]) % 365;
    }
}

//-- (prefix)
//Decrement the object and return it
//Output:
//This object after being decremented

DayOfYear& DayOfYear::operator--(){
    if(_day > 0){ //If the day is greater than 0
        --_day; //Decrement
    }
    else{ //Otherwise
        _day = 364; //Set day to 364
    }

    return *this;
}

//toString
//Generate a string representation of this object
//Output:
//The string name of the current month and the day of that month

std::string DayOfYear::toString(){
    std::stringstream r; //Conversion stream

    if(_day == 0){ //If December 31
        r << _months[11] << " " << 31;
    }
    else{ //Otherwise
        unsigned char month = 0; //The number of the current month
        unsigned int total = 0; //The total number of days so far

        for(int i = 0; total < _day; total += _monthDays[i++]){ //While the total is less than the current day
            month = i; //Set the current month to i
        }
        total -= _monthDays[month]; //Go back one month
        r << _months[month] << " " << _day - total; //Generate output
    }

    return r.str();
}