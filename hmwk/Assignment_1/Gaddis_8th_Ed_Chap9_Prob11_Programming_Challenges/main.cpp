/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Expand an array to twice its size
 * Created on September 27, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <cstdlib> //C standard library
#include <ctime> //Date and Time
using namespace std;

//Function Prototypes
int* expand(int*, unsigned int);
void prntArr(const int[], unsigned int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int *array = NULL; //The array to expand
    unsigned int length; //The length of the array

    srand(static_cast<int>(time(0))); //Seed PRNG

    //Input
    do{ //While length is less than 1
        cout << "ENTER THE SIZE OF THE INITIAL ARRAY: ";
        cin >> length; //Read in length
    } while(length < 1);
    array = new int[length]; //Allocate array
    cout << "FILLING ARRAY...";
    for(int i = 0; i < length; ++i){ //For every element in the array
        array[i] = (rand() % 9) + 1; //Set the value at i to a random number 1 to 9
    }
    cout << "DONE!" << endl;
    cout << "INITIAL ARRAY: ";
    if(length > 10){
        cout << endl;
    }
    prntArr(array, length); //Output the initial array
    cout << "EXPANDING ARRAY...";
    array = expand(array, length); //Expand the array
    cout << "DONE!" << endl;
    cout << "EXPANDED ARRAY: ";
    if(length * 2 > 10){
        cout << endl;
    }
    prntArr(array, length * 2); //Print the expanded array

    //Delete the array
    delete [] array;

    //Exit
    return 0;
}

//Expand
//Double the size of the input array and return a pointer to the expanded array. Deletes the input array.
//Input:
//array
//The array to expand
//length
//The size of the input array
//Output:
//A pointer to the new expanded array

int* expand(int *array, unsigned int length){
    int* r = NULL; //The return array pointer
    unsigned int nLength = length * 2; //The length of the new array

    r = new int[nLength]; //Allocate the return array
    for(int i = 0; i < nLength; ++i){ //For the entire expanded array
        if(i < length){ //When i is less than the original length
            r[i] = array[i]; //set the return array value to the original array value at i
        }
        else{ //Otherwise
            r[i] = 0; //set the return array value at i to 0
        }
    }

    //Delete the input array
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