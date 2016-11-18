/*
 * File:   date.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a Date object for a 365 day year
 * Created on November 17, 2016
 */

#ifndef DATE_H
#define DATE_H

//System Libraries
#include <string>
#include <sstream>
#include <iomanip>


//Date
//Defines a date for a 365 day year (no leap years). This class will handle situations where you input dates like
//February 31 by rolling the date over into the next month (Feb 31 becomes March 3 etc)

class Date{
private:
    static const unsigned char MONTHS = 12; //The number of months
    static unsigned char _lengths[MONTHS]; //An array holding the length of each month

    unsigned short _day; //The current day value
    //Day is a short to handle values like 344 which are valid but will cause some amount of date wrapping to occur
    unsigned char _month; //The current month value (1-12)
    unsigned short _year; //The current year value (Only bounded by the limits of a short)

    //toUInt
    //Convert a character to an integer
    //Input:
    //value
    //The character to convert
    //Output:
    //An integer equal to value

    unsigned int toUInt(unsigned char value){
        return static_cast<unsigned int>(value);
    }

    void fixDate();
public:
    Date(unsigned short = 1, unsigned char = 1, unsigned short = 1);

    //day
    //Return the current day value
    //Output:
    //The current day value of this object

    unsigned short day(){
        return _day;
    }

    //day
    //Set the current day value. If the value is greater than the current days in the month the date will wrap as
    //is appropriate
    //Input:
    //day
    //The day to set the current object to

    void day(unsigned short day){
        _day = day; //Set the day
        fixDate(); //Fix the date if necessary
    }

    //month
    //Return the current month value
    //Output:
    //The current month value of this object

    unsigned char month(){
        return _month;
    }

    //month
    //Set the current month value of this object
    //Input:
    //month
    //The month to set this object to

    void month(unsigned char month){
        _month = month;
    }

    //year
    //Return the current year value of this object
    //Output:
    //The current year value

    unsigned short year(){
        return _year;
    }

    //year
    //Set the current year value of this object
    //Input:
    //year
    //The year value to set the current year to

    void year(unsigned short year){
        _year = year;
    }

    std::string toString();
    std::string toLongString(bool = false);

    static std::string monthString(unsigned char);
};

#endif /* DATE_H */

