/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Celsius to Fahrenheit conversion
 * Created on September 17, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
using namespace std;

//Begin Execution
int main(int argc, char** argv){
    //Declaration and Initialization
    const float CNV_F = 9.0f / 5.0f; //Celsius to Fahrenheit conversion factor
    float cTemp = 0.0f, //The temperature in Celsius. Input by the user
            fTemp = 0.0f; //The temperature in Fahrenheit

    //Read Input
    cout << "INPUT A TEMPERATURE IN CELSIUS: ";
    cin >> cTemp; //Read in cTemp
    
    //Calculate Output
    fTemp = (CNV_F * cTemp) + 32; //Calculate fTemp using cTemp and CNV_F
    
    //Output Data
    cout << fixed << setprecision(2); //Format output to 2 decimal places
    //Output cTemp and fTemp
    cout << setw(24) << "TEMPERATURE CELSIUS: " << cTemp << endl; 
    cout << setw(24) << "TEMPERATURE FAHRENHEIT: " << fTemp << endl;

    //Exit
    return 0;
}

