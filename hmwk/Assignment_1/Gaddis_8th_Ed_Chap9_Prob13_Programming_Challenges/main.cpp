/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on September 27, 2016
 */

#include <iostream>
using namespace std;

float mean(const int[], int);
float median(const int[], int);
void sort(int[], int);
int* mode(const int[], int);
int modeCnt(const int[], int, int);
int getFreq(const int[], int);
int* getMdes(const int[], int, int, int);
void prntArr(const int[], int);

int main(int argc, char** argv){
    int size = 0;
    int *data = NULL;
    int *modes = NULL;

    do{
        cout << "ENTER THE NUMBER OF STUDENTS SURVEYED: ";
        cin >> size;
    } while(size < 0);
    if(size > 0){
        data = new int[size];

        for(int i = 0; i < size; ++i){
            do{
                cout << "ENTER THE NUMBER OF MOVIES THAT STUDENT " << i + 1 << " WATCHED: ";
                cin >> data[i];
            } while(data[i] < 0);
        }
        cout << "DATA:" << endl;
        prntArr(data, size);
        sort(data, size);
        cout << "MEAN: " << mean(data, size) << endl;
        cout << "MEDIAN: " << median(data, size) << endl;
        modes = mode(data, size);
        if(modes[1] > 1){
            cout << "NUMBER OF MODES: " << modes[0] << endl;
            cout << "MODE FREQUENCY: " << modes[1] << endl;
            cout << "MODES: ";
            for(int i = 2; i < modes[0] + 2; ++i){
                cout << modes[i];
                if(i + 1 < modes[0] + 2){
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


        delete [] modes;
        delete [] data;
    }

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

