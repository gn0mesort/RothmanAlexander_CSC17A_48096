/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Reverse an array
 * Created on September 27, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <cstdlib> //C standard library
#include <ctime> //Date and Time
using namespace std;

//Function Prototypes
int* reverse(int[], unsigned int);
void prntArr(const int[], unsigned int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int *array = NULL; //The array to reverse
    unsigned int length = 0; //The length of that array

    srand(static_cast<int>(time(0))); //Seed PRNG

    length = (rand() % 100) + 1; //Generate random length between 1 and 100
    array = new int[length]; //Allocate the array
    for(int i = 0; i < length; ++i){ //For every element of the array
        array[i] = (rand() % 9) + 1; //Set the value at i to a random number 1 to 9
    }

    //Output
    cout << "ARRAY LENGTH: " << length << endl; //Output the length of the array
    cout << "INITIAL ARRAY: ";
    if(length > 10){ //Formatting
        cout << endl;
    }
    prntArr(array, length); //Output the array in its initial order
    array = reverse(array, length); //Reverse the array
    cout << endl;
    cout << "REVERSED ARRAY: ";
    if(length > 10){ //Formatting
        cout << endl;
    }
    prntArr(array, length); //Output the reversed array

    //Delete the array
    delete [] array;

    //Exit
    return 0;
}

//Reverse
//Reverse an array and return a pointer to the new reversed array. Deletes the input array.
//Input:
//array
//The array to reverse
//length
//The length of the array
//Output:
//A pointer to a new array in reverse order of the input array

int* reverse(int array[], unsigned int length){
    int *r = new int[length]; //Allocate a new array with length elements

    for(int i = 0; i < length; ++i){ //For every element in the new array
        r[i] = array[(length - 1) - i]; //The current element of the new array is equal to the reverse element in the input array
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
