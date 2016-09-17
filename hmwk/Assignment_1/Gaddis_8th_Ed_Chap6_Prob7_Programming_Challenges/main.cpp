/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Celsius Temperature Table
 * Created on September 17, 2016
 */

#include <iostream>
#include <iomanip>
using namespace std;

float celsius(float);

int main(int argc, char** argv){
    cout << fixed << setprecision(2);
    for(int i = 0; i < 21; ++i){
        cout << setw(6) << i << " Fahrenheit = " << setw(6) << celsius(i);
        cout << " Celsius" << endl;
    }

    return 0;
}

float celsius(float tempF){
    return (tempF - 32) * (5.0f / 9.0f);
}

