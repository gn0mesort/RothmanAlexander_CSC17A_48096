/* 
 * File:   main.cpp
 * Author: Alexander Rothman
 * Purpose: Use array class to do a sort
 * Created on October 24, 2016
 */

//System Libraries
#include <iostream>

#include "Array.h"
using namespace std;

int main(int argc, char** argv) {
    Array a(100); //The data array 
    
    //Initialize PRNG
    srand(static_cast<int>(time(0)));
    
    //Fill the array
    a.fillRand();
    //Output the initial array
    cout << "INITIAL ARRAY:" << endl;
    a.print();
    //Sort
    a.sort();
    //Output the sorted array
    cout << "SORTED ARRAY:" << endl;
    a.print();
    
    return 0;
}

