/*
 * File:   numbers.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a class for converting integer values into English text
 * Created on November 15, 2016
 */

#ifndef NUMBERS_H
#define NUMBERS_H

//System Libraries
#include <iostream> //I/O
#include <string> //Strings
#include <sstream> //String streams


//Numbers
//A class for storing numbers and converting them into their English representation.
//Only stores numbers between 0 and 9999

class Numbers{
private:
    static std::string _unique[20]; //Unique number names 0-19
    static std::string _tens[8]; //Unique names for tens places 20-90
    static std::string _hundred; //Text for "hundred"
    static std::string _thousand; //Text for "thousand"

    int _value; //The actual value of this object
public:

    //Numbers
    //Default constructor
    //Output:
    //A number object with a value of 0

    Numbers(){
        _value = 0;
    }

    Numbers(int);

    //value
    //Return the current value of this object
    //Output:
    //The current underlying int value

    int value() const{
        return _value;
    }

    void value(int nValue);

    std::string toString() const;

    //print
    //Print the string representation of this Numbers object to standard output

    void print() const{
        std::cout << toString() << std::endl;
    }
};

#endif /* NUMBERS_H */

