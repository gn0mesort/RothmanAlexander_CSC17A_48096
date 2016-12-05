/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate Date with exceptions
 * Created on November 28, 2016
 */

//System Libraries
#include <iostream> //I/O

//User Libraries
#include "date.h" //Date objects
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    Date d(1, 1, 1990); //A new Date object set to 1/1/1990

    //Display Day errors
    for(int i = 0; i < 33; ++i){ //Loop from 1/0/1990 to 1/32/1990
        try{ //Try to set the day
            d.day(i); //Set day
            cout << d.toLongString(true) << endl; //Output Date
        }
        catch(Date::InvalidDay e){ //Catch invalid dates
            cerr << "INVALID DAY!" << endl;
        }
    }
    cout << endl;
    //Display Month errors
    for(int i = 0; i < 14; ++i){ //Loop from 0/31/1990 to 13/31/1990
        try{ //Try to set the month
            d.month(i); //Set month
            cout << d.toLongString(true) << endl; //Output Date
        }
        catch(Date::InvalidMonth e){ //Catch invalid months
            cerr << "INVALID MONTH!" << endl;
        }
    }

    //Exit
    return 0;
}

