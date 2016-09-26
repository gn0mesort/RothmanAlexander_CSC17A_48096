/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Generate a dynamic array of a variable size.
 * Array is initialized to 0.
 * Created on September 26, 2016
 */

#include <iostream>
using namespace std;

int* genArr(int);

int main(int argc, char** argv){
    int length = 0;
    int *array = NULL;
    cout << "How many elements should be allocated: ";
    cin >> length;

    array = genArr(length);
    cout << "ARRAY POINTER: " << array << endl;
    cout << "ARRAY CONTENTS:" << endl;
    for(int i = 0; i < length; ++i){
        cout << array[i];
        if(length > 10){
            if((i + 1) % 10 == 0){
                cout << endl;
            }
            else{
                cout << ", ";
            }
        }
        else{
            if((i + 1) < length){
                cout << ", ";
            }
        }
    }

    delete [] array;

    return 0;
}

int* genArr(int length){
    return new int[length]{
    };
    //If not using C++11 or later
    //    int *r = new int[length];
    //    for(int i = 0; i < length; ++i){
    //        r[i] = 0;
    //    }
    //    return r;
}

