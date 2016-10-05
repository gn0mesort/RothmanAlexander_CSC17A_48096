/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Sort an Array object using MarkSort. Using the . operator and pointer notation
 * Created on October 5, 2016
 */


//System Libraries
#include <iostream> //I/O
#include <cstdlib>  //C Standard Library
#include <ctime>    //Date and Time

//User Libraries
#include "Array.h" //Array object from https://github.com/ml1150258/LehrMark_CSC17a_48096/blob/master/Class/MarkSort_Structure/Array.h
using namespace std;

//Function Prototypes
void fillArr(Array&, unsigned char);
void prntArr(const Array&, int);
void sort(Array&);

//Begin Execution

int main(int argc, char** argv) {
    //Declaration and Initialization
    const unsigned char SIZE = 100; //Size of the array
    unsigned char perLine = 10; //Number of values to print per line
    Array arr; //The array object to sort
    
    srand(static_cast<unsigned int>(time(0))); //Seed PRNG
    fillArr(arr, SIZE); //Allocate the array and fill it with random values
    
    //Output
    cout << "INITIAL ARRAY:" << endl;
    prntArr(arr, perLine); //Print the initial array
    cout << endl; 
    sort(arr); //Sort the array
    cout << "SORTED ARRAY:" << endl;
    prntArr(arr, perLine); //Print the sorted array
    
    //Delete the array
    delete [] arr.data;

    //Exit
    return 0;
}

//Print Array
//Print an Array object with the given number of values per line
//Input:
//arr
//The Array to print values from
//perLine
//The number of values to print per line

void prntArr(const Array &arr, int perLine){
    for(int i = 0; i < arr.size; ++i){ //For every element of the array
        cout << *(arr.data + i) << " "; //Output the array value at i
        if(!((i + 1) % perLine)){ //If the next line is over the perLine value
            cout << endl;
        }
    }
}

//Fill Array
//Allocate and fill an Array object
//arr
//The Array to allocate and fill
//size
//The size of the array that should be allocated
//Output:
//The input Array object allocated and filled
void fillArr(Array &arr, unsigned char size){
    arr.data = new int[size]; //Allocate the underlying array
    arr.size = size; //Set the array size
    for(int i = 0; i < arr.size; ++i){ //For every value in the array
        *(arr.data + i) = (rand() % 90) + 10; //Set the value at i to a random number between 10 and 99
    }
}

//Sort
//Sort an Array object using the MarkSort algorithm
//Input:
//arr
//The Array to sort
//Output:
//The sorted Array

void sort(Array &arr){
    for(int i = 0; i < arr.size - 1; ++i){ //For every element of the array
        for(int j = i + 1; j < arr.size; ++j){ //For every element of the array starting at i + 1
            if(*(arr.data + i) > *(arr.data + j)){ //If the value at i is greater than the value at j
                //Swap
                *(arr.data + i) = *(arr.data + i) ^ *(arr.data + j);
                *(arr.data + j) = *(arr.data + i) ^ *(arr.data + j);
                *(arr.data + i) = *(arr.data + i) ^ *(arr.data + j);
            }
        }
    }
}
