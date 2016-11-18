/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a class that displays dates in 3 different formats
 * Created on November 17, 2016
 */

//System Libraries
#include <iostream> //I/O

//User Libraries
#include "date.h" //Date objects
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    unsigned short day = 0, //The value of the day
            month = 0, //The value of the month
            year = 0; //The value of the year

    //Input
    do{ //While the day input isn't valid
        cout << "INPUT THE DAY OF THE MONTH: ";
        cin >> day; //Read in the day
    } while(day > 31 || day < 1);
    do{ //While the month isn't valid
        cout << "INPUT THE NUMBER OF THE MONTH: ";
        cin >> month; //Read in the month
    } while(month < 1 || month > 12);
    cout << "INPUT THE YEAR: ";
    cin >> year; //Read in the year
    //It's assumed that the year will be at least 4 characters long but there's no restriction on it.
    //If you input a number like 8 you'll get 0008 and if you input something like 12345 you'll get 12345.
    cout << endl;

    //Output
    Date d(day, month, year); //Create the Date object with the input values

    cout << d.toString() << endl; //Output regular date string (MM/DD/YYYY)
    cout << d.toLongString() << endl; //Output long date string (DD Month YYYY)
    cout << d.toLongString(true) << endl; //Output alternate long date string (Month DD, YYYY)

    //Exit
    return 0;
}

