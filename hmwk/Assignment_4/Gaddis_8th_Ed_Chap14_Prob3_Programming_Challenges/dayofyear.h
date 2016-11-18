/*
 * File:   dayofyear.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a DayOfYear class that represents a single day of a 365 day year
 * Created on November 16, 2016
 */

#ifndef DAYOFYEAR_H
#define DAYOFYEAR_H

//System Libraries
#include <string>
#include <iostream>
#include <sstream>

//DayOfYear
//A class representing a single day of a 365 day year. Does not handle leap years

class DayOfYear{
private:
    static const unsigned char NUM_MON = 12; //The number of months in a year
    static std::string _months[NUM_MON]; //The names of each month
    static unsigned char _monthDays[NUM_MON]; //The number of days of each of the 12 months
    unsigned int _day; //The day of the year
public:

    //DayOfYear
    //Default constructor
    //Output:
    //A new DayOfYear object set to January 1st

    DayOfYear(){
        _day = 1;
    }

    //DayOfYear
    //Parameterized constructor
    //Input:
    //day
    //The date to set the new object to
    //Output:
    //A new DayOfYear object set to the input value % 365

    DayOfYear(unsigned int day){
        _day = day % 365;
    }

    DayOfYear(std::string, unsigned int);

    //day
    //Return the current day value
    //Output:
    //The underlying day value

    unsigned int day(){
        return _day;
    }

    //day
    //Set the current day value
    //Input:
    //nDay
    //The date to set the underlying value to

    void day(unsigned int nDay){
        _day = nDay % 365;
    }

    std::string toString();

    //print
    //Output the string representation of this object to standard out

    void print(){
        std::cout << toString() << std::endl;
    }

    //++ (prefix)
    //Increment the current object and return it
    //Output:
    //this object

    DayOfYear& operator++(){
        _day = (_day + 1) % 365;

        return *this;
    }

    //++ (postfix)
    //Increment the current object and return a copy from before it was incremented
    //Input:
    //x
    //A dummy value
    //Output:
    //A copy of this object before it was incremented

    DayOfYear operator++(int x){
        DayOfYear r = *this; //Copy this

        ++(*this); //Increment this

        return r; //Return the copy
    }

    DayOfYear& operator--();

    //-- (postfix)
    //Decrement the current object and return a copy from before it was decremented
    //Input:
    //x
    //A dummy value
    //Output:
    //A copy of this object before it was decremented

    DayOfYear operator--(int x){
        DayOfYear r = *this; //Copy this

        --(*this); //decrement this

        return r; //Return the copy
    }

    static unsigned char monthLookup(std::string);

};

#endif /* DAYOFYEAR_H */

