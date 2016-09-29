/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Calculate the median of an array
 * Created on September 27, 2016
 */

//System Libraries
#include <cstdlib> //C Standard Libarary
#include <iostream> //I/O
#include <ctime> //Date and Time
using namespace std;

//Function Prototypes
float median(const int[], int);
void sort(int[], int);
void prntArr(const int[], int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int size = 0; //The size of the array
    int *array = NULL; //The array to find the median of

    srand(static_cast<int>(time(0))); //Seed PRNG
    size = rand() % 100; //Generate a random size between 0 and 99
    array = new int[size]; //Allocate array
    for(int i = 0; i < size; ++i){ //For each array elements
        array[i] = (rand() % 9) + 1; //Set the current element to a random number between 1 and 9
    }

    //Calculate and Output
    cout << "ARRAY SIZE: " << size << endl;
    cout << "INITIAL ARRAY:" << endl;
    prntArr(array, size); //Output array
    sort(array, size); //Sort array
    cout << "SORTED ARRAY:" << endl;
    prntArr(array, size); //Output sorted array
    cout << "MEDIAN: " << median(array, size) << endl; //Output median

    //Delete array
    delete [] array;

    //Exit
    return 0;
}


//Median
//Calculate the median of a sorted array
//Input:
//array
//The array to calculate the median of
//size
//The size of the array
//Output:
//The median of the array as a float

float median(const int array[], int size){
    if(size & 1){ //If size is odd
        return array[(size - 1) / 2];
    }
    else{ //If size is even
        int offset = (size - 2) / 2; //Calculate median offset
        return (array[0 + offset] + array[(size - 1) - offset]) / 2.0f;
    }
}

//Sort
//Sorts an array based using the gnome sort algorithm
//Input:
//array
//The array to sort
//size
//The size of both arrays
//Output:
//The sorted array

void sort(int array[], int size){
    int pos = 0; //The initial position
    while(pos < size){ //While unsorted
        if(pos == 0 || array[pos] >= array[pos - 1]){ //If the position is 0 or the current value is greater than the last value
            ++pos; //Move up one position
        }
        else{ //Otherwise
            //Swap the current position and the last position
            array[pos] = array[pos] ^ array[pos - 1];
            array[pos - 1] = array[pos] ^ array[pos - 1];
            array[pos] = array[pos] ^ array[pos - 1];
            //Move back one position
            --pos;
        }
    }
}

//Print Array
//Print an array to standard output
//Input:
//array
//The array to display
//size
//The size of that array

void prntArr(const int array[], int size){
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