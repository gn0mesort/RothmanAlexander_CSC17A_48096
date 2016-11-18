/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate the FloatArr class
 * Created on November 15, 2016
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>

//User Libraries
#include "floatarr.h"
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    const unsigned char SIZE = 10; //Size of the array to create
    FloatArr arr(SIZE); //Create a new FloatArr of SIZE elements

    srand(static_cast<int>(time(0))); //Seed PRNG

    //Fill and Display arr
    for(int i = 0; i < arr.size(); ++i){ //For every element of arr
        arr.set(i, (rand() % 1000) / 10.0f); //Set the value at i to a random number
        cout << "arr[" << i << "] = " << arr.get(i) << endl; //Output arr[i]
    }
    //Output calculated values
    cout << "HIGH:    " << arr.high() << endl; //Find and output the highest value
    cout << "LOW:     " << arr.low() << endl; //Find and output the lowest value
    cout << "AVERAGE: " << arr.avg() << endl; //Calculate and output the average

    //Exit
    return 0;
}

