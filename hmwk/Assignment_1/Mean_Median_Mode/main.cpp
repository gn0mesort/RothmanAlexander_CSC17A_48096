/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Calculate the mean, median, and mode of a given sequence of numbers
 * Created on September 25, 2016
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

float mean(const int[], int);
float median(const int[], int);
void sort(int[], int);
int* mode(const int[], int);
int modeCnt(const int[], int, int);
int getFreq(const int[], int);
int* getMdes(const int[], int, int, int);
int* genArr(int);
void prntArr(const int[], int);

int main(int argc, char** argv){
    const int SIZE = 10;
    int *array = NULL,
            *modeDat = NULL;

    srand(static_cast<int>(time(0)));

    array = genArr(SIZE);
    cout << "INITIAL ARRAY:" << endl;
    prntArr(array, SIZE);
    cout << "SORTED ARRAY:" << endl;
    sort(array, SIZE);
    prntArr(array, SIZE);
    cout << "MEAN: " << mean(array, SIZE) << endl;
    cout << "MEDIAN: " << median(array, SIZE) << endl;
    modeDat = mode(array, SIZE);
    if(modeDat[1] != 1){
        cout << "NUMBER OF MODES: " << modeDat[0] << endl;
        cout << "MODE FREQUENCY: " << modeDat[1] << endl;
        cout << "MODES: ";
        for(int i = 2; i < modeDat[0] + 2; ++i){
            cout << modeDat[i];
            if(i + 1 < modeDat[0] + 2){
                cout << ", ";
            }
            else{
                cout << endl;
            }
        }
    }
    else{
        cout << "NO MODE!" << endl;
    }

    //prntArr(modeDat, modeDat[0] + 2);

    delete [] array;
    delete [] modeDat;

    return 0;
}

int* mode(const int array[], int size){
    int *r = NULL,
            *modes = NULL;
    int freq = getFreq(array, size),
            numMode = 0;

    if(freq > 1){
        numMode = modeCnt(array, size, freq);
    }
    modes = getMdes(array, size, numMode, freq);
    r = new int[numMode + 2];
    r[0] = numMode;
    r[1] = freq;

    for(int i = 2; i < numMode + 2; ++i){
        r[i] = modes[i - 2];
    }

    delete [] modes;

    return r;
}

int* getMdes(const int array[], int size, int numMode, int freq){
    int *r = new int[numMode];
    int count = 0,
            pos = 0;

    for(int i = 0; i < size; ++i){
        if(i > 0 && array[i] != array[i - 1]){
            if(count == freq){
                r[pos++] = array[i - 1];
            }
            count = 1;
        }
        else{
            ++count;
        }
        if(i + 1 >= size && count == freq){
            r[pos] = array[i];
        }
    }

    return r;
}

int getFreq(const int array[], int size){
    int r = 0,
            start = 0;

    for(int current = 0; current < size; ++current){
        if(array[start] != array[current]){
            int diff = current - start;
            if(diff > r){
                r = diff;
            }
            start = current;
        }
        else if(current + 1 >= size){
            int diff = size - start;
            if(diff > r){
                r = diff;
            }
        }
    }
    return r;
}

int modeCnt(const int array[], int size, int freq){
    int r = 0,
            count = 0;

    for(int i = 0; i < size; ++i){
        if(i > 0 && array[i] != array[i - 1]){
            if(count == freq){
                ++r;
            }
            count = 1;
        }
        else{
            ++count;
        }
        if(i + 1 >= size && count == freq){
            ++r;
        }
    }

    return r;
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

float mean(const int array[], int size){
    int total = 0;
    for(int i = 0; i < size; ++i){
        total += array[i];
    }
    return total / (size * 1.0f);
}

int* genArr(int size){
    int *r = new int[size];

    for(int i = 0; i < size; ++i){
        r[i] = rand() % 10;
        //r[i] = i;
    }

    return r;
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

