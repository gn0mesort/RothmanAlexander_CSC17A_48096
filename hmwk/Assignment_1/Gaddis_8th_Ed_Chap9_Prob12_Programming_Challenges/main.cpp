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

void prntArr(const int[], unsigned int);
int* shift(int[], unsigned int&);

int main(int argc, char** argv){
    int *array = NULL;
    unsigned int length = 0;

    srand(static_cast<int>(time(0)));

    length = (rand() % 100) + 1;
    array = new int[length];
    for(int i = 0; i < length; ++i){
        array[i] = (rand() % 9) + 1;
    }

    cout << "ARRAY LENGTH: " << length << endl;
    cout << "INITIAL ARRAY: ";
    if(length > 10){
        cout << endl;
    }
    prntArr(array, length);
    cout << endl;
    array = shift(array, length);
    cout << "ARRAY LENGTH: " << length << endl;
    cout << "SHIFTED ARRAY: ";
    if(length > 10){
        cout << endl;
    }
    prntArr(array, length);

    delete [] array;

    return 0;
}

int* shift(int array[], unsigned int& length){
    int *r = new int[length + 1];

    r[0] = 0;
    for(int i = 0; i < length; ++i){
        r[i + 1] = array[i];
    }
    ++length;

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