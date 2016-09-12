/* 
 * File:   main.cpp
 * Author: Alexander Rothman
 * Created on September 12, 2016, 1:07 PM
 * Purpose: MarkSort Algorithm
 */

//System Libraries
#include <iostream> //I/O
#include <cstdlib> //C Standard Library
#include <ctime> //Time
//User Libraries

using namespace std;

//Global Constants

//Function Prototypes
void fillAry(int[], int);
void mrkSort(int[], int);
void prntAry(int[], int, int);

//Begin Execution
int main(int argc, char** argv) {
    //Declare Variables
    const int SIZE = 100, LINES = 10;
    int array[SIZE]; 
    
    //Initialize rand()
    srand(static_cast<int>(time(0)));
    
    //Input Data
    
    //Fill Array
    fillAry(array, SIZE);
    //Display Unsorted Array
    prntAry(array, SIZE, LINES);
    //Sort Array
    mrkSort(array, SIZE);
    //Display Sorted Array
    prntAry(array, SIZE, LINES);
        
    //Exit
    return 0;
}

void fillAry(int a[], int n){
    for(int i = 0; i < n; ++i){
        a[i] = rand() % 90 + 10; //Generate random 2 digit numbers
    }
}

void prntAry(int a[], int n, int perLine){
    for(int i = 0; i < n; ++i){
        cout << a[i] << " ";
        if(i % perLine == perLine - 1) { cout << endl; }
    }
    cout << endl;
}

void mrkSort(int a[], int n){
    for(int i = 0; i < n - 1; ++i){
        for(int j = i + 1; j < n; ++j){
            if(a[i] > a[j]){
                a[i] = a[i] ^ a[j];
                a[j] = a[i] ^ a[j];
                a[i] = a[i] ^ a[j];
            }
        }
    }
}

