/* 
 * File:   main.cpp
 * Author: Alexander Rothman
 * Created on September 12, 2016, 1:07 PM
 * Purpose: MarkSort Algorithm v2
 */

//System Libraries
#include <iostream> //I/O
#include <cstdlib> //C Standard Library
#include <ctime> //Time

using namespace std;

//Function Prototypes
void fillAry(int[], int);
void mrkSort(int[], int);
void prntAry(int[], int, int);

//Begin Execution
int main(int argc, char** argv) {
    //Declare Variables
    const int SIZE = 100, //Size of the array to sort 
              LINES = 10; //Number of values to print per line
    int utilize = SIZE / 2; //The size of the array to actually fill
    int array[SIZE]; //The array to be sorted
    
    //Initialize rand()
    srand(static_cast<int>(time(0)));
    
    //Fill Array
    fillAry(array, utilize);
    //Display Unsorted Array
    prntAry(array, utilize, LINES);
    //Sort Array
    mrkSort(array, utilize);
    //Display Sorted Array
    prntAry(array, utilize, LINES);
        
    //Exit
    return 0;
}

//Fill Array
//Fill an array with random 2 digit numbers
//INPUT:
//a[]
//An array to fill
//n
//The length of the array to fill
//OUTPUT:
//a[]
//The filled array
void fillAry(int a[], int n){
    for(int i = 0; i < n; ++i){
        a[i] = rand() % 90 + 10; //Generate random 2 digit numbers
    }
}

//Print Array
//Print an integer array to standard output
//INPUT:
//a[]
//The array to print
//n
//The length of the array
//perLine
//The number of values to print per line
void prntAry(int a[], int n, int perLine){
    for(int i = 0; i < n; ++i){
        cout << a[i] << " ";
        if(i % perLine == perLine - 1) { cout << endl; }
    }
    cout << endl;
}

//Mark Sort
//Sort an array of integers
//INPUT:
//a[]
//The array to sort
//n
//The length of the array
//OUTPUT:
//a[]
//The sorted array
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

