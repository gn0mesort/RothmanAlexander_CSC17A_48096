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

void sort(int*, int);
int* genArr(int);
int mode(const int*, int);
void prntArr(const int*, int);
int getFreq(const int*, int);

int main(int argc, char** argv){
    const int SIZE = 10;
    int *array = NULL;
    int modeVal = 0;

    srand(static_cast<int>(time(0)));

    array = genArr(SIZE);
    //    array = new int[SIZE] {
    //        0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    //    };
    sort(array, SIZE);
    modeVal = mode(array, SIZE);
    cout << "ARRAY: " << endl;
    prntArr(array, SIZE);
    if(modeVal > -1){
        cout << "THE MODE IS " << modeVal << endl;
    }
    else{
        cout << "NO MODE!" << endl;
    }

    delete [] array;

    return 0;
}

void sort(int *array, int size){
    int pos = 0;
    while(pos < size){
        if(pos == 0 || *(array + pos) >= *(array + (pos - 1))){
            ++pos;
        }
        else{
            *(array + pos) = *(array + pos) ^ *(array + (pos - 1));
            *(array + (pos - 1)) = *(array + pos) ^ *(array + (pos - 1));
            *(array + pos) = *(array + pos) ^ *(array + (pos - 1));
            --pos;
        }
    }
}

int* genArr(int size){
    int *r = new int[size];

    for(int i = 0; i < size; ++i){
        *(r + i) = rand() % 10;
        //r[i] = i;
    }

    return r;
}

void prntArr(const int *array, int size){
    for(int i = 0; i < size; ++i){
        cout << *(array + i);
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

//Returns the highest valued mode rather than all modes in the case of multiple

int mode(const int *array, int size){
    int r = -1,
            freq = getFreq(array, size),
            count = 0,
            pos = 0;
    if(freq > 1){
        for(int i = 0; i < size; ++i){
            if(i > 0 && array[i] != array[i - 1]){
                if(count == freq){
                    r = *(array + (i - 1));
                }
                count = 1;
            }
            else{
                ++count;
            }
            if(i + 1 >= size && count == freq){
                r = *(array + i);
            }
        }
    }

    return r;
}

int getFreq(const int *array, int size){
    int r = 0,
            start = 0;

    for(int current = 0; current < size; ++current){
        if(*(array + start) != *(array + current)){
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