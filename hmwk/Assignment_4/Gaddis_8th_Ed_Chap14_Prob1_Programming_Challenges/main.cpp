/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate Numbers class
 * Created on November 15, 2016
 */

//System Libraries
#include <iostream> //I/O

//User Libraries
#include "numbers.h" //Numbers objects
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    Numbers n; //A numbers object
    int input = 0; //An input value

    do{ //While the input is invalid
        cout << "ENTER A NUMBER BETWEEN 0 AND 9999: ";
        cin >> input; //Read in input
    } while(input > 9999 || input < 0);

    n.value(input); //Set the value of n
    n.print(); //Print n

    //Exit
    return 0;
}

