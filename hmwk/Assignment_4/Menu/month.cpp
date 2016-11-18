/*
 * File:   month.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for month.h
 * Created on November 16, 2016
 */

//User Libraries
#include "month.h" //Month objects

std::string Month::_names[MONTHS] = {"DECEMBER", "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", "JULY",
                                     "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER"};

//parse
//Parse a month value from a string
//Input:
//name
//The name of the month to get the value of
//Output:
//The numerical value of the input month

unsigned char Month::parse(std::string name) const{
    unsigned char r = 13; //Set r to an impossible value

    for(int i = 0; i < name.size(); ++i){ //Set input to uppercase
        name[i] = toupper(name[i]);
    }

    for(unsigned char i = 0; i < MONTHS; ++i){ //For each month
        if(_names[i] == name){ //If the input matches the current month name
            r = i;
        }
    }

    return r;
}

//-- (prefix)
//Decrement the month
//Output:
//this month after being decremented

Month& Month::operator--(){
    if(_num > 0){ //If the month is greater than 0
        _num = (_num - 1) % 12;
    }
    else{ //If the month is December
        _num = 11; //Set the month to November
    }

    return *this;
}

//>> (Stream extraction)
//Extract a month from an input stream
//Input:
//lhs
//The stream to extract from
//rhs
//The Month object to insert into
//Output:
//lhs after extraction

std::istream& operator>>(std::istream &lhs, Month &rhs){
    std::string r = "";

    lhs >> r; //Extract a string
    rhs.name(r); //Set the name to the string

    return lhs;
}

//<< (Stream insertion)
//Insert a month into an output stream
//Input:
//lhs
//The stream to insert into
//rhs
//The Month object to insert
//Output:
//lhs after insertion

std::ostream& operator<<(std::ostream &lhs, const Month &rhs){
    lhs << rhs.name(); //Insert name into stream

    return lhs;
}