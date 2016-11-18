/*
 * File:   date.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for date.h
 * Created on November 17, 2016
 */

//User Libraries
#include "date.h" //Date objects

unsigned char Date::_lengths[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //Month lengths

//Date
//A parameterized constructor for Date objects
//Input:
//day
//The day to set
//month
//The month to set
//year
//The year to set
//Output:
//A new Date object with the given values

Date::Date(unsigned short day, unsigned char month, unsigned short year){
    _day = day;
    _month = month;
    _year = year;
    fixDate(); //Wrap date if needed
}

//fixDate
//Rolls a date over into the next month (or year) if necessary. Allows for weird inputs like January 3650, 1993
//This is called anytime the date is set

void Date::fixDate(){
    while(_day > _lengths[_month - 1]){ //While the date is greater than the length of the current month
        _day -= _lengths[_month - 1]; //Subtract the month length
        _month = (_month + 1) % 13; //Add one to the year and wrap after December
        if(_month == 0){ //Since there is no 0 month
            ++_month; //Set the month to January
            ++_year; //Roll into the next year
        }
    }
}

//toString
//Return a string representation of the date in the MM/DD/YYYY format
//Output:
//A string representing this Date

std::string Date::toString() const{
    std::stringstream r; //Conversion stream for return

    r << std::setfill('0'); //Fill fields with 0s if they're too short
    r << std::setw(2) << toUInt(_month) << "/" << std::setw(2) << _day << "/" << std::setw(4) << _year; //Convert to string

    return r.str();
}

//toLongString
//Return either regular or alternate long string representations of the date based on input value
//The regular format is DD Month YYYY
//The alternate format is Month DD, YYYY
//Input:
//style
//boolean indicating which style should be used toLongString(false) is equivalent to toLongString()

std::string Date::toLongString(bool style) const{
    std::stringstream r; //Conversion stream for return

    r << std::setfill('0'); //Fill fields with 0s if they're too short
    if(!style){ //If regular
        r << std::setw(2) << _day << " " << monthString(_month) << " " << std::setw(4) << _year; //Convert to string
    }
    else{ //If alternate
        r << monthString(_month) << " " << std::setw(2) << _day << ", " << std::setw(4) << _year; //Convert to string
    }

    return r.str();
}

//monthString
//Return the name of a month based on the month's number
//Input:
//month
//A value 1-12 representing the month to return the name of. Values outside 1-12 will return an empty string
//Output:
//The name of the selected month or an empty string

std::string Date::monthString(unsigned char month){
    std::string r = ""; //String to return

    switch(month){ //Set r based on input
        case 1:
        {
            r = "January";
            break;
        }
        case 2:
        {
            r = "February";
            break;
        }
        case 3:
        {
            r = "March";
            break;
        }
        case 4:
        {
            r = "April";
            break;
        }
        case 5:
        {
            r = "May";
            break;
        }
        case 6:
        {
            r = "June";
            break;
        }
        case 7:
        {
            r = "July";
            break;
        }
        case 8:
        {
            r = "August";
            break;
        }
        case 9:
        {
            r = "September";
            break;
        }
        case 10:
        {
            r = "October";
            break;
        }
        case 11:
        {
            r = "November";
            break;
        }
        case 12:
        {
            r = "December";
            break;
        }
    }

    return r;
}