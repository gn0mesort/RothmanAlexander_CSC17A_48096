/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate DayOfYear class
 * Created on November 16, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <string> //Strings

//User Libraries
#include "dayofyear.h" //DayOfYear objects
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    DayOfYear date("December", 31); //A DayOfYear object

    for(int i = 0; i < 365; ++i){
        string month = date.toString().substr(0, date.toString().find(' ')); //Get the name of the current month

        cout << setw(month.size()) << (date--).toString() << " "; //Output the current date and decrement afterward
        if(date.toString().substr(0, date.toString().find(' ')) != month){ //Print a line break at the end of each month
            cout << endl << endl;
        }
        else if((i + 1) % 7 == 0){ //Print a line break at the end of each week
            cout << endl;
        }
    }

    //Exit
    return 0;
}

