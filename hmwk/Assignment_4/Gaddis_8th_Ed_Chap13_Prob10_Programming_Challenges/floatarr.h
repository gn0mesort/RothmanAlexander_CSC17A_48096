/*
 * File:   floatarr.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a type for handling arrays of float values
 * Created on November 15, 2016
 */

#ifndef FLOATARR_H
#define FLOATARR_H

//System Libraries
#include <limits>

//FloatArr
//Defines a floating point array. Contains both array data and size data

class FloatArr{
private:
    float *_data; //The data array
    unsigned int _size; //The size of _data
public:

    //FloatArr
    //Basic constructor for FloatArr's. Creates a new object with the given size
    //Input:
    //size
    //The size to set the new array to
    //Output:
    //A new FloatArr object with the input size

    FloatArr(unsigned int size){
        _data = new float[size];
        _size = size;
    }

    //~FloatArr
    //Destructor for FloatArrs. Releases _data memory and sets _data pointer to null

    ~FloatArr(){
        delete [] _data;
        _data = 0;
    }

    //set
    //Set a value in the FloatArr at the given index
    //Input:
    //index
    //The index to set
    //value
    //The value to set the element at index to

    void set(unsigned int index, float value){
        _data[index] = value;
    }

    //get
    //Get a value in the FloatArr
    //Input:
    //index
    //The index to get from the underlying array
    //Output:
    //The value of the floating point number at the input index

    float get(unsigned int index){
        return _data[index];
    }

    //size
    //Return the size of the FloatArr's underlying array
    //Output:
    //The size of the array

    unsigned int size(){
        return _size;
    }

    float high();
    float low();
    float avg();
};

#endif /* FLOATARR_H */

