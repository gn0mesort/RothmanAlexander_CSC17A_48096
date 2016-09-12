/* 
 * File:   main.cpp
 * Author: Alexander Rothman
 * Created on September 12, 2016, 1:07 PM
 * Purpose: MarkSort Algorithm v4
 */

//System Libraries
#include <iostream> //I/O
#include <cstdlib> //C Standard Library
#include <ctime> //Time

using namespace std;

//Function Prototypes
void fillAry(int*, int*, int);
void mrkSort(int*, int*, int);
void prntAry(int*, int, int);
void prntAry(int*, int*, int, int);

//Begin Execution
int main(int argc, char** argv) {
    //Declare Variables
    const int SIZE = 100, //Size of the array to sort  
              LINES = 10; //Number of values to print per line
    int utilize = SIZE / 2; //The size of the array to actually fill
    int array[SIZE], //The array to be sorted
        index[SIZE]; //An indexing array for the array to be sorted
    
    //Initialize rand()
    srand(static_cast<int>(time(0)));
    
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

//Fill Array
//Fill an array with random 2 digit numbers
//INPUT:
//a[]
//An array to fill
//index[]
//An indexing array to fill with the indexes in a[]
//n
//The length of the array to fill
//OUTPUT:
//a[]
//The filled array
//index[]
//The filled indexing array
void fillAry(int *a, int *index, int n){
    for(int i = 0; i < n; ++i){
        *(a + i) = rand() % 90 + 10; //Generate random 2 digit numbers
        *(index + i) = i;
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
void prntAry(int *a, int n, int perLine){
    for(int i = 0; i < n; ++i){
        cout << *(a + i) << " ";
        if(i % perLine == perLine - 1) { cout << endl; }
    }
    cout << endl;
}

//Print Array
//Print an integer array to standard output
//INPUT:
//a[]
//The array to print
//index[]
//The indexing array for the array to print
//n
//The length of the array
//perLine
//The number of values to print per line
void prntAry(int *a, int *index, int n, int perLine){
    for(int i = 0; i < n; ++i){
        cout << *(a + *(index + i)) << " ";
        if(i % perLine == perLine - 1) { cout << endl; }
    }
    cout << endl;
}

//Mark Sort
//Sort an array of integers
//INPUT:
//a[]
//The array containing index[]'s underlying values
//index[]
//The indexing array to sort
//n
//The length of the array
//OUTPUT:
//index[]
//The sorted indexing array
void mrkSort(int *a, int *index, int n){
    for(int i = 0; i < n - 1; ++i){
        for(int j = i + 1; j < n; ++j){
            if(*(a + *(index + i)) > *(a + *(index + j))){
                *(index + i) = *(index + i) ^ *(index + j);
                *(index + j) = *(index + i) ^ *(index + j);
                *(index + i) = *(index + i) ^ *(index + j);
            }
        }
    }
}

