/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate templated absolute value function
 * Created on November 28, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting

//User Libraries
#include "absolutevalue.h" //abs() function
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Test abs() with ints between -10 and 10
    for(int i = -10; i <= 10; ++i){
        cout << "|" << setw(3) << i << "| = " << abs(i) << endl;
    }
    cout << endl;
    cout << fixed << setprecision(2); //Formatting
    //Test abs() with floats between -1.25 and 1.25
    for(float f = -1.25f; f <= 1.25f; f += 0.25f){
        cout << "|" << setw(5) << f << "| = " << abs(f) << endl;
    }

    //Exit
    return 0;
}
