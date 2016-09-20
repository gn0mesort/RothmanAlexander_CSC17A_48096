/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Euro and Yen currency conversion
 * Created on September 17, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
using namespace std;

//Begin Execution
int main(int argc, char** argv){
    //Declaration and Initialization
    const float CNV_JPY = 102.28f, //Number of YEN in a DOLLAR as of 11:40AM 9/17/2016
            CNV_EUR = 0.9f; //Number of EUROs in a DOLLAR as of 11:41AM 9/17/2016
    float dollars = 0.0f; //The value to convert

    //Read Input
    cout << "INPUT A VALUE TO CONVERT: $";
    cin >> dollars;
    
    //Calculate and Output Data
    cout << fixed << setprecision(2); //Format output to 2 decimal places
    cout << setw(15) << dollars << " USD" << endl; //Output DOLLARS
    cout << setw(15) << dollars * CNV_JPY << " JPY" << endl; //Output YEN 
    cout << setw(15) << dollars * CNV_EUR << " EUR" << endl; //Output EUROS

    //Exit
    return 0;
}

