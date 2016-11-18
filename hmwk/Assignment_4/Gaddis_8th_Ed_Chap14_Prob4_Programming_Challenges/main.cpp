/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate NumDays class
 * Created on November 16, 2016
 */

//System Libraries
#include <iostream> //I/O

//User Libraries
#include "numdays.h" //NumDays objects
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    NumDays nd1(12), nd2(8), nd3, nd4; //Initialize some NumDays objects

    //Test constructors and functions
    cout << "1st NumDays = " << nd1.hours() << " hours or " << nd1.days() << " days." << endl;
    cout << "2nd NumDays = " << nd2.hours() << " hours or " << nd2.days() << " days." << endl;
    //Test addition
    nd3 = nd1 + nd2;
    cout << "1st + 2nd = " << nd3.hours() << " hours or " << nd3.days() << " days." << endl;
    //Test subtraction
    nd4 = nd1 - nd2;
    cout << "1st - 2nd = " << nd4.hours() << " hours or " << nd4.days() << " days." << endl;
    //Test increment and decrement
    ++nd1;
    --nd2;
    cout << "1st incremented = " << nd1.hours() << " hours or " << nd1.days() << " days." << endl;
    cout << "2nd decremented = " << nd2.hours() << " hours or " << nd2.days() << " days." << endl;

    //Exit
    return 0;
}

