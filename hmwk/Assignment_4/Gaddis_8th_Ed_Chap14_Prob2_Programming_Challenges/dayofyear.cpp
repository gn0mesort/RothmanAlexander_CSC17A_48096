/*
 * File:   dayofyear.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for dayofyear.h
 * Created on November 16, 2016
 */

//User Libraries
#include "dayofyear.h" //DayOfYear objects

std::string DayOfYear::_months[NUM_MON] = {"January", "February", "March", "April", "May", "June", "July", "August",
                                           "September", "October", "November", "December"};

unsigned char DayOfYear::_monthDays[NUM_MON] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//toString
//Generate a string representation of this object
//Output:
//The string name of the current month and the day of that month

std::string DayOfYear::toString() const{
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