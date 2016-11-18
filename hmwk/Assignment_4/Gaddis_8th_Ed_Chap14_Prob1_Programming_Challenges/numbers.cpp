/*
 * File:   numbers.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for numbers.h
 * Created on November 15, 2016
 */

//User Libraries
#include "numbers.h"

std::string Numbers::_unique[20] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight",
                                    "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
                                    "sixteen", "seventeen", "eighteen", "nineteen"};
std::string Numbers::_tens[8] = {"twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
std::string Numbers::_hundred = "hundred";
std::string Numbers::_thousand = "thousand";

//Numbers
//Parameterized constructor.
//Input:
//value
//The value to set the object to. Must be between 0 and 9999. If it isn't it will be set to the upper or lower bound
//whichever is closer

Numbers::Numbers(int value){
    if(value < 0){ //If outside of lower bound
        _value = 0; //Value is 0
    }
    else if(value > 9999){ //If outside of upper bound
        _value = 9999; //Value is 9999
    }
    else{ //Otherwise
        _value = value; //Set value
    }
}

//value
//Sets the value of the current Numbers object
//Input:
//nValue
//The new value to set. Must be between 0 and 9999. If it isn't it will be set to the upper or lower bound
//whichever is closer

void Numbers::value(int nValue){
    if(nValue < 0){ //If outside of lower bound
        _value = 0; //Value is 0
    }
    else if(nValue > 9999){ //If outside of upper bound
        _value = 9999; //Value is 9999
    }
    else{ //Otherwise
        _value = nValue; //Set value
    }
}

//toString
//Return a string representation of this object
//Output:
//A string representing the underlying value as English words

std::string Numbers::toString(){
    unsigned char nThou = 0, //Number of thousands
            nHund = 0, //Number of hundreds
            nTen = 0; //Number of tens
    int remain = _value; //Remainder
    std::stringstream r; //Conversion stream

    //Calculate thousands
    nThou = remain / 1000;
    remain -= nThou * 1000;
    //Calculate hundreds
    nHund = remain / 100;
    remain -= nHund * 100;
    //Calculate tens
    if(remain > 19){
        nTen = remain / 10;
        remain -= nTen * 10;
    }

    //Create output value
    if(nThou > 0){ //If thousands is not 0
        r << _unique[nThou] << " " << _thousand << " ";
    }
    if(nHund > 0){ //If hundreds is not 0
        r << _unique[nHund] << " " << _hundred << " ";
    }
    if(nTen > 0){ //If tens is not 0
        r << _tens[nTen - 2] << " ";
    }
    if(remain > 0){ //if the remainder is not 0
        r << _unique[remain];
    }

    return r.str();
}