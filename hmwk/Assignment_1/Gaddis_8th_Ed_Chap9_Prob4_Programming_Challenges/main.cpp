/*
 * File:   main.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose: Calculate the average test score and display student names
 * Created on September 27, 2016
 */


//System libraries
#include <iostream> //I/O
#include <iomanip> //Formatting
#include <string> //String type and functions
using namespace std;

//Function Prototypes
void sort(unsigned char[], short[], short);
void prntArr(const unsigned char[], const string[], const short[], short);
unsigned char* mkIndex(short);
float avg(const short[], short);

int main(int argc, char** argv){
    short input = 0,
            length = 0;
    short *scores = NULL;
    unsigned char *index = NULL;
    string *names = NULL;

    do{
        cout << "ENTER THE NUMBER OF TESTS: ";
        cin >> input;
    } while(input < 0);
    length = input;
    if(input > 0){
        scores = new short[length];
        names = new string[length];
        index = mkIndex(length);
        for(int i = 0; i < length; ++i){
            do{
                cout << "ENTER THE NAME FOR TEST #" << i + 1 << ": ";
                cin.ignore();
                getline(cin, names[i]);
                cout << "ENTER THE SCORE FOR TEST #" << i + 1 << ": ";
                cin >> input;
            } while(input < 0);
            scores[i] = input;
        }

        cout << "SORTED SCORES:" << endl;
        //sort(index, scores, length);
        prntArr(index, names, scores, length);
        cout << fixed << setprecision(2);
        cout << "AVERAGE SCORE: " << avg(scores, length) << endl;

        delete [] scores;
        delete [] names;
        delete [] index;
    }

    return 0;
}

unsigned char* mkIndex(short size){
    unsigned char *r = new unsigned char[size];
    for(int i = 0; i < size; ++i){
        r[i] = i;
    }
    return r;
}

void sort(unsigned char index[], short array[], short size){
    short pos = 0;
    while(pos < size){
        if(pos == 0 || array[index[pos]] >= array[index[pos - 1]]){
            ++pos;
        }
        else{
            index[pos] = index[pos] ^ index[pos - 1];
            index[pos - 1] = index[pos] ^ index[pos - 1];
            index[pos] = index[pos] ^ index[pos - 1];
            --pos;
        }
    }
}

void prntArr(const unsigned char index[], const string names[], const short scores[], short size){
    for(int i = 0; i < size; ++i){
        cout << setw(10) << names[index[i]] << " : " << setw(4) << scores[index[i]] << endl;
    }
}

float avg(const short array[], short length){
    float r = 0.0f;

    for(int i = 0; i < length; ++i){
        r += array[i];
    }

    return r / (length * 1.0f);
}
