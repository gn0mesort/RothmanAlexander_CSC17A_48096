/* 
 * File:   main.cpp
 * Author: Alexander Rothman
 * Created on September 12, 2016, 1:07 PM
 * Purpose: MarkSort Algorithm v3
 */

//System Libraries
#include <iostream> //I/O
#include <cstdlib> //C Standard Library
#include <ctime> //Time
//User Libraries

using namespace std;

//Global Constants

//Function Prototypes
void fillAry(int[], int[], int);
void mrkSort(int[], int[], int);
void prntAry(int[], int, int);
void prntAry(int[], int[], int, int);

//Begin Execution
int main(int argc, char** argv) {
    //Declare Variables
    const int SIZE = 100, LINES = 10;
    int utilize = SIZE / 2;
    int array[SIZE], index[SIZE]; 
    
    //Initialize rand()
    srand(static_cast<int>(time(0)));
    
    //Input Data
    
    //Fill Array
    fillAry(array, index, utilize);
    //Display Unsorted Array
    cout << "ORIGINAL ARRAY:" << endl;
    prntAry(array, utilize, LINES);
    cout << "ORIGINAL INDEX:" << endl;
    prntAry(index, utilize, LINES);
    cout << "ORIGINAL ARRAY WITH INDEX:" << endl;
    prntAry(array, index, utilize, LINES);
    //Sort Array
    mrkSort(array, index, utilize);
    //Display Sorted Array
    cout << "SORTED ARRAY:" << endl;
    prntAry(array, utilize, LINES);
    cout << "SORTED INDEX:" << endl;
    prntAry(index, utilize, LINES);
    cout << "SORTED ARRAY WITH INDEX:" << endl;
    prntAry(array, index, utilize, LINES);
    //Exit
    return 0;
}

void fillAry(int a[], int index[], int n){
    for(int i = 0; i < n; ++i){
        a[i] = rand() % 90 + 10; //Generate random 2 digit numbers
        index[i] = i;
    }
}

void prntAry(int a[], int n, int perLine){
    for(int i = 0; i < n; ++i){
        cout << a[i] << " ";
        if(i % perLine == perLine - 1) { cout << endl; }
    }
    cout << endl;
}

void prntAry(int a[], int index[], int n, int perLine){
    for(int i = 0; i < n; ++i){
        cout << a[index[i]] << " ";
        if(i % perLine == perLine - 1) { cout << endl; }
    }
    cout << endl;
}

void mrkSort(int a[], int index[], int n){
    for(int i = 0; i < n - 1; ++i){
        for(int j = i + 1; j < n; ++j){
            if(a[index[i]] > a[index[j]]){
                index[i] = index[i] ^ index[j];
                index[j] = index[i] ^ index[j];
                index[i] = index[i] ^ index[j];
            }
        }
    }
}

