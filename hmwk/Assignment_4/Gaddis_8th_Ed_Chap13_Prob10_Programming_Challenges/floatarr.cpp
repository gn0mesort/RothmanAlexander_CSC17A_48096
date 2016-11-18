/*
 * File:   floatarr.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for floatarr.h
 * Created on November 15, 2016
 */

//User Libraries
#include "floatarr.h"

//high
//Get the highest value in the array
//Output:
//The highest value found in the array

float FloatArr::high(){
    float r = std::numeric_limits<float>::min(); //Set r to the lowest possible float

    for(unsigned int i = 0; i < _size; ++i){ //For every element of the array
        if(_data[i] > r){ //If the the current value is greater than r
            r = _data[i]; //Set r to the current value
        }
    }

    return r;
}

//low
//Get the lowest value in the array
//Output:
//The lowest value found in the array

float FloatArr::low(){
    float r = std::numeric_limits<float>::max(); //Set r to the highest possible float

    for(unsigned int i = 0; i < _size; ++i){ //For every element of the array
        if(_data[i] < r){ //If the current value is less than r
            r = _data[i]; //Set r to the current value
        }
    }

    return r;
}

//avg
//Get the average of the values in the array
//Output:
//The average value of the values in the array

float FloatArr::avg(){
    float r = 0.0f; //Set r to 0

    for(unsigned int i = 0; i < _size; ++i){ //For every element of the array
        r += _data[i]; //Sum the array
    }
    r /= _size; //Divide by the size of the array

    return r;
}