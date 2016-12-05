/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate SortableVector
 * Created on November 28, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <cstdlib> //C Standard Library
#include <ctime> //Time

//User Libraries
#include "sortablevector.h" //SortableVector objects
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    SortableVector<int> srtVec(100); //Create a sized data vector

    srand(static_cast<int>(time(0))); //Seed PRNG

    for(int i = 0; i < srtVec.size(); ++i){ //Generate random data between 10 and 99
        srtVec[i] = rand() % 89 + 10;
    }

    cout << "UNSORTED DATA:" << endl;
    for(int i = 0; i < srtVec.size(); ++i){ //Print vector
        cout << srtVec[i] << " ";
        if((i + 1) % 10 == 0){
            cout << endl;
        }
    }
    cout << endl;
    srtVec.sort(); //Sort data
    cout << "SORTED DATA:" << endl;
    for(int i = 0; i < srtVec.size(); ++i){ //Print vector
        cout << srtVec[i] << " ";
        if((i + 1) % 10 == 0){
            cout << endl;
        }
    }
    cout << endl;
    SortableVector<int> copy(srtVec); //Copy data
    cout << "COPIED DATA:" << endl;
    for(int i = 0; i < copy.size(); ++i){ //Print copied vector
        cout << copy[i] << " ";
        if((i + 1) % 10 == 0){
            cout << endl;
        }
    }
    cout << endl;

    //Exit
    return 0;
}

