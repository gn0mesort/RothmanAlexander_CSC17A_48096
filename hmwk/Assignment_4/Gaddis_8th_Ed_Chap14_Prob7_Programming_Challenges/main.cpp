/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate Month class
 * Created on November 16, 2016
 */

//System Libraries
#include <iostream>

//User Libraries
#include "month.h"
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    Month m; //A month to play around with

    //Count months forward
    cout << "ALL MONTHS FORWARD:" << endl;
    for(int i = 1; i < 13; ++i){
        cout << m++ << endl;
    }
    cout << endl;

    //Count months backward
    cout << "ALL MONTHS BACKWARD:" << endl;
    for(int i = 1; i < 13; ++i){
        cout << --m << endl;
    }
    cout << endl;

    //Parse month from string input
    do{ //While the input was valid
        cout << "INPUT A MONTH NAME: ";
        cin >> m; //Test inserting by reading in a month
    } while(m.value() == 13);
    cout << "INPUT MONTH WAS: " << m << " OR MONTH #" << static_cast<int>(m.value()) << endl; //Output month

    //Exit
    return 0;
}

