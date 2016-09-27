/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Preform a computation using pointers instead of references
 * Created on September 26, 2016
 */

#include <iostream>
using namespace std;


int compute(int*, int*);

int main(int argc, char** argv){
    int xVal = 0,
            yVal = 0;
    int *x = &xVal,
            *y = &yVal;


    cout << "ENTER A VALUE FOR X: ";
    cin >> xVal;
    cout << "ENTER A VALUE FOR Y: ";
    cin >> yVal;
    cout << "X: " << *x << endl;
    cout << "Y: " << *y << endl;
    cout << "compute(X, Y): " << compute(x, y) << endl;
    cout << "X: " << *x << endl;
    cout << "Y: " << *y << endl;

    return 0;
}

int compute(int *x, int *y){
    int temp = *x;
    *x = *y * 10;
    *y = temp * 10;
    return *x + *y;
}

