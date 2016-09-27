/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on September 27, 2016
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

float median(const int[], int);
void sort(int[], int);
void prntArr(const int[], int);

int main(int argc, char** argv){
    int size = 0;
    int *array = NULL;

    srand(static_cast<int>(time(0)));

    size = rand() % 100;
    array = new int[size];
    for(int i = 0; i < size; ++i){
        array[i] = (rand() % 9) + 1;
    }

    cout << "ARRAY SIZE: " << size << endl;
    cout << "INITIAL ARRAY:" << endl;
    prntArr(array, size);
    sort(array, size);
    cout << "SORTED ARRAY:" << endl;
    prntArr(array, size);
    cout << "MEDIAN: " << median(array, size) << endl;

    delete [] array;

    return 0;
}

float median(const int array[], int size){
    if(size & 1){ //If size is odd
        return array[(size - 1) / 2];
    }
    else{ //If size is even
        int offset = (size - 2) / 2;
        return (array[0 + offset] + array[(size - 1) - offset]) / 2.0f;
    }
}

void sort(int array[], int size){
    int pos = 0;
    while(pos < size){
        if(pos == 0 || array[pos] >= array[pos - 1]){
            ++pos;
        }
        else{
            array[pos] = array[pos] ^ array[pos - 1];
            array[pos - 1] = array[pos] ^ array[pos - 1];
            array[pos] = array[pos] ^ array[pos - 1];
            --pos;
        }
    }
}

void prntArr(const int array[], int size){
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