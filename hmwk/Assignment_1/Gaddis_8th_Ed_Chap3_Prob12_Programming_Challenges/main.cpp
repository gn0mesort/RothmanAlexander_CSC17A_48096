/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Celsius to Fahrenheit conversion
 * Created on September 17, 2016
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char** argv){
    const float CNV_F = 9.0f / 5.0f;
    float cTemp = 0.0f,
            fTemp = 0.0f;

    cout << "INPUT A TEMPERATURE IN CELSIUS: ";
    cin >> cTemp;
    fTemp = (CNV_F * cTemp) + 32;
    cout << fixed << setprecision(2);
    cout << setw(24) << "TEMPERATURE CELSIUS: " << cTemp << endl;
    cout << setw(24) << "TEMPERATURE FAHRENHEIT: " << fTemp << endl;


    return 0;
}

