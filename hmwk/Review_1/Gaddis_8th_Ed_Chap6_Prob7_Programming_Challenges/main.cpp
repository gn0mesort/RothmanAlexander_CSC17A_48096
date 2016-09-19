/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Celsius Temperature Table
 * Created on September 17, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
using namespace std;

//Function Prototypes
float celsius(float);

//Begin Execution
int main(int argc, char** argv){
    //Calculate and Output data
    cout << fixed << setprecision(2); //Format output to 2 decimal places
    for(int i = 0; i < 21; ++i){ //For values 0 to 20
        cout << setw(6) << i << " Fahrenheit = " << setw(6) << celsius(i); //Calculate and output temperature in Celsius
        cout << " Celsius" << endl;
    }
    
    //Exit
    return 0;
}

//Celsius
//Convert a Fahrenheit temperature to a Celsius temperature
//Input:
//tempF
//The temperature in Fahrenheit to convert to Celsius
//Output:
//The input temperature converted to Celsius
float celsius(float tempF){
    return (tempF - 32) * (5.0f / 9.0f);
}

