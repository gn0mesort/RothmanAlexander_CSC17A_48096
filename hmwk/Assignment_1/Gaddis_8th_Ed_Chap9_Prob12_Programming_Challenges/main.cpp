/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Shift an array one unit
 * Created on September 27, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <cstdlib> //C standard library
#include <ctime> //Date and Time
using namespace std;

//Function Prototype
void prntArr(const int[], unsigned int);
int* shift(int[], unsigned int&);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int *array = NULL; //The array to shift
    unsigned int length = 0; //The size of the initial array

    srand(static_cast<int>(time(0))); //Seed PRNG

    length = (rand() % 100) + 1; //Generate a random length between 1 and 100
    array = new int[length]; //Allocate array
    for(int i = 0; i < length; ++i){ //Fill the array with random numbers 1 to 9
        array[i] = (rand() % 9) + 1;
    }

    //Output
    cout << "ARRAY LENGTH: " << length << endl; //Output the length
    cout << "INITIAL ARRAY: ";
    if(length > 10){
        cout << endl;
    }
    prntArr(array, length); //Print the initial array
    cout << endl;
    array = shift(array, length); //Shift the array
    cout << "ARRAY LENGTH: " << length << endl; //Output the new length
    cout << "SHIFTED ARRAY: ";
    if(length > 10){
        cout << endl;
    }
    prntArr(array, length); //Print the shifted array

    //Delete the array
    delete [] array;

    //Exit
    return 0;
}

//Shift
//Shift an array one element to the right
//Input:
//array
//The array to shift
//length
//The length of the array to shift
//Output:
//A pointer to the shifted array
//The new augmented length of the array

int* shift(int array[], unsigned int& length){
    int *r = new int[length + 1];

    r[0] = 0;
    for(int i = 0; i < length; ++i){
        r[i + 1] = array[i];
    }
    ++length;

    delete [] array;

    return r;
}

//Print Array
//Print an array to standard output
//Input:
//array
//The array to display
//size
//The size of that array

void prntArr(const int array[], unsigned int size){
    for(int i = 0; i < size; ++i){ //For every element in the array
        cout << array[i]; //Output the array element
        if(size > 10){ //If the size is greater than 10
            if((i + 1) % 10 == 0){ //Add some formatting
                cout << endl;
            }
            else if(i != size - 1){
                cout << ", ";
            }
        }
        else{ //Otherwise
            if(i != size - 1){ //Add some other formatting
                cout << ", ";
            }
        }
    }
    cout << endl;
}