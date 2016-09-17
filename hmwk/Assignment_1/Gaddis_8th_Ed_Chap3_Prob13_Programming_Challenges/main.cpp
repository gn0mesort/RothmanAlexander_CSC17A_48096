/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Euro and Yen currency conversion
 * Created on September 17, 2016
 */

#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, char** argv){
    const float CNV_JPY = 102.28f, //Number of YEN in a DOLLAR as of 11:40AM 9/17/2016
            CNV_EUR = 0.9f; //Number of EUROs in a DOLLAR as of 11:41AM 9/17/2016
    float dollars = 0.0f; //The value to convert

    cout << "INPUT A VALUE TO CONVERT: $";
    cin >> dollars;
    cout << fixed << setprecision(2);
    cout << setw(15) << dollars << " USD" << endl;
    cout << setw(15) << dollars * CNV_JPY << " JPY" << endl;
    cout << setw(15) << dollars * CNV_EUR << " EUR" << endl;

    return 0;
}

