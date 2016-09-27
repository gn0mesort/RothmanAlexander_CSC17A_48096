/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on September 27, 2016
 */

#include <iostream>
#include <iomanip>

using namespace std;

void sort(short[], short);
void prntArr(const short[], short);
float avg(const short[], short);

int main(int argc, char** argv){
    short input = 0,
            length = 0;
    short *scores = NULL;

    do{
        cout << "ENTER THE NUMBER OF TESTS: ";
        cin >> input;
    } while(input < 0);
    length = input;
    if(input > 0){
        scores = new short[length];
        for(int i = 0; i < length; ++i){
            do{
                cout << "ENTER THE SCORE FOR TEST #" << i + 1 << ": ";
                cin >> input;
            } while(input < 0);
            scores[i] = input;
        }

        cout << "SORTED SCORES:";
        if(length > 10){
            cout << endl;
        }
        sort(scores, length);
        prntArr(scores, length);
        cout << fixed << setprecision(2);
        cout << "AVERAGE SCORE: " << avg(scores, length) << endl;

        delete [] scores;
    }

    return 0;
}

void sort(short array[], short size){
    short pos = 0;
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

void prntArr(const short array[], short size){
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

float avg(const short array[], short length){
    float r = 0.0f;

    for(int i = 1; i < length; ++i){
        r += array[i];
    }

    return r / ((length - 1) * 1.0f);
}

