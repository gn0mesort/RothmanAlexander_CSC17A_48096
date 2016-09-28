/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Generate a dynamic array of a variable size.
 * Array is initialized to 0.
 * Created on September 26, 2016
 */

//System Libraries
#include <iostream> //I/O
using namespace std;

//Function Prototypes
int* genArr(int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and initialization
    int length = 0; //The length of the generated array
    int *array = NULL; //The dynamic array

    //Read Input
    do{ //While length is less than 1
        cout << "How many elements should be allocated: ";
        cin >> length; //Read in length
    } while(length < 1);

    array = genArr(length); //Generate the array

    //Output
    cout << "ARRAY POINTER: " << array << endl; //Output the location of the array
    cout << "ARRAY CONTENTS:" << endl; //Output the contents of the array
    for(int i = 0; i < length; ++i){ //For every element in array
        cout << array[i]; //Output the value at i
        if(length > 10){ //Formatting
            if((i + 1) % 10 == 0){
                cout << endl;
            }
            else{
                cout << ", ";
            }
        }
        else{
            if((i + 1) < length){
                cout << ", ";
            }
        }
    }

    //Delete the array
    delete [] array;

    //Exit
    return 0;
}

//Generate Array
//Generate an int array of the given size and initialize it to 0. Array initializer works in C++11 or later otherwise
//uncomment the looping routine to fill the array
//Input:
//length
//The length of the array to generate
//Output:
//A pointer to the generated array

int* genArr(int length){
    return new int[length]{ //Return a new array pointer with the given length
    };
    //If not using C++11 or later
    //    int *r = new int[length];
    //    for(int i = 0; i < length; ++i){
    //        r[i] = 0;
    //    }
    //    return r;
}

