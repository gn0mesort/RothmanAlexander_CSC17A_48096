/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Preform a computation using pointers instead of references
 * Created on September 26, 2016
 */

//System Libraries
#include <iostream> //I/O
using namespace std;

//Function Prototypes
int compute(int*, int*);

//Begin Execution

int main(int argc, char** argv){
    int xVal = 0, //Value of X
            yVal = 0; //Value of Y
    int *x = &xVal, //Pointer to X
            *y = &yVal; //Pointer to Y


    //Input Data
    cout << "ENTER A VALUE FOR X: ";
    cin >> xVal; //Read in xVal
    cout << "ENTER A VALUE FOR Y: ";
    cin >> yVal; //Read in yVal

    //Calculate and Output
    cout << "X: " << *x << endl; //Output value of X
    cout << "Y: " << *y << endl; //Output value of Y
    cout << "compute(X, Y): " << compute(x, y) << endl; //Output computation of X and Y
    cout << "X: " << *x << endl; //Output value of X
    cout << "Y: " << *y << endl; //Output value of Y

    //Exit
    return 0;
}

//Compute
//Preform an arbitrary computation using pointers. Should return (10 * X) + (10 * Y) and swap the values of X and Y

int compute(int *x, int *y){
    int temp = *x; //A temporary value
    *x = *y * 10;
    *y = temp * 10;
    return *x + *y;
}

