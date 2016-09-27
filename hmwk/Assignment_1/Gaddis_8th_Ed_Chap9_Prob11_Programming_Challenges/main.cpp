/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on September 27, 2016
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int* expand(int*, unsigned int);
void prntArr(const int[], unsigned int);

int main(int argc, char** argv){
    int *array = NULL;
    unsigned int length;

    srand(static_cast<int>(time(0)));

    cout << "ENTER THE SIZE OF THE INITIAL ARRAY: ";
    cin >> length;
    array = new int[length];
    cout << "FILLING ARRAY...";
    for(int i = 0; i < length; ++i){
        array[i] = (rand() % 9) + 1;
    }
    cout << "DONE!" << endl;
    cout << "INITIAL ARRAY: ";
    if(length > 10){
        cout << endl;
    }
    prntArr(array, length);
    cout << "EXPANDING ARRAY...";
    array = expand(array, length);
    cout << "DONE!" << endl;
    cout << "EXPANDED ARRAY: ";
    if(length * 2 > 10){
        cout << endl;
    }
    prntArr(array, length * 2);

    delete [] array;

    return 0;
}

int* expand(int *array, unsigned int length){
    int* r = NULL;
    unsigned int nLength = length * 2;

    r = new int[nLength];
    for(int i = 0; i < nLength; ++i){
        if(i < length){
            r[i] = array[i];
        }
        else{
            r[i] = 0;
        }
    }

    delete [] array;
    return r;
}

void prntArr(const int array[], unsigned int size){
    for(int i = 0; i < size; ++i){
        cout << array[i];
        if(size > 10){
            if((i + 1) % 10 == 0){
                cout << endl;
            }
            else if(i != size - 1){
                cout << ", ";
            }
        }
        else{
            if(i != size - 1){
                cout << ", ";
            }
        }
    }
    cout << endl;
}