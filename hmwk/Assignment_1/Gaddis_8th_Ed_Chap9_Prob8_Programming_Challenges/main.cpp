/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Mode function that returns an int as described in the book. Not the same as Mean_Median_Mode
 * Created on September 27, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <cstdlib> //C Standard Library
#include <ctime> //Date and Time
using namespace std;

//Function Prototypes
void sort(int*, int);
int* genArr(int);
int mode(const int*, int);
void prntArr(const int*, int);
int getFreq(const int*, int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    const int SIZE = 10; //The size of the array to find the mode of
    int *array = NULL; //The array to find the mode of
    int modeVal = 0; //The mode that was found

    srand(static_cast<int>(time(0))); //Seed PRNG
    array = genArr(SIZE); //Generate the array

    //Calculate and Output
    sort(array, SIZE); //Sort the array
    modeVal = mode(array, SIZE); //Find the mode
    cout << "ARRAY: " << endl;
    prntArr(array, SIZE); //Output the array
    if(modeVal > -1){ //If the mode was found
        cout << "THE MODE IS " << modeVal << endl; //Output the mode
    }
    else{ //Otherwise
        cout << "NO MODE!" << endl; //Output error
    }

    //Delete the array
    delete [] array;

    //Exit
    return 0;
}

//Sort
//Sorts an array using the gnome sort algorithm
//Input:
//array
//The array to sort
//size
//The size of both arrays
//Output:
//The sorted array

void sort(int *array, int size){
    int pos = 0; //The initial position
    while(pos < size){ //While unsorted
        if(pos == 0 || *(array + pos) >= *(array + (pos - 1))){ //If the position is 0 or the current value is greater than the last value
            ++pos; //Move up one position
        }
        else{ //Otherwise
            //Swap the current position and the last position
            *(array + pos) = *(array + pos) ^ *(array + (pos - 1));
            *(array + (pos - 1)) = *(array + pos) ^ *(array + (pos - 1));
            *(array + pos) = *(array + pos) ^ *(array + (pos - 1));
            //Move back one position
            --pos;
        }
    }
}


//Generate Array
//Generates an array of the given size
//Input:
//size
//The size of the array to generate
//Output:
//The pointer to the generated array

int* genArr(int size){
    int *r = new int[size]; //Allocate the return array

    for(int i = 0; i < size; ++i){ //Generate array values
        *(r + i) = rand() % 10; //Values between 0 and 9
    }

    return r;
}

//Print Array
//Print an array to standard output
//Input:
//array
//The array to display
//size
//The size of that array

void prntArr(const int *array, int size){
    for(int i = 0; i < size; ++i){ //For every element in the array
        cout << *(array + i); //Output the array element
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

//Mode
//Get the mode of a given array
//Returns the highest valued mode rather than all modes in the case of multiple
//Input:
//array
//The array to find the mode of
//size
//The size of the array
//Output:
//The highest mode found or -1 if none exist

int mode(const int *array, int size){
    int r = -1, //The return mode
            freq = getFreq(array, size), //The frequency of the mode
            count = 0, //The number of times the current number occurs
            pos = 0; //The current position
    if(freq > 1){ //If the frequency is greater than 1
        for(int i = 0; i < size; ++i){ //For every element in the array
            if(i > 0 && array[i] != array[i - 1]){ //If the current value has changed from the last value
                if(count == freq){ //If the current count is the same as the frequency
                    r = *(array + (i - 1)); //Set the return value to the last array element
                }
                count = 1; //Reset count
            }
            else{ //Otherwise
                ++count; //Increment the count
            }
            if(i + 1 >= size && count == freq){ //If the last value in the array is a mode
                r = *(array + i); //Set the return value to the current array element
            }
        }
    }

    return r;
}

//Get Frequency
//Get the frequency of the mode of an array
//Input:
//array
//The array to find the mode frequency of
//size
//The size of the array
//Output:
//The frequency of the mode of the array

int getFreq(const int *array, int size){
    int r = 0, //The frequency to return
            start = 0; //The position of the start of the most recent value in the array

    for(int current = 0; current < size; ++current){ //For each element in the array
        if(*(array + start) != *(array + current)){ //If the current value is not the same as the starting value
            int diff = current - start; //Hold the difference in a temporary value
            if(diff > r){ //If the difference is greater than the current return frequency
                r = diff; //Set the return frequency to the difference
            }
            start = current; //Reset the start position
        }
        else if(current + 1 >= size){ //If this is the last element in the array
            int diff = size - start; //Hold the difference in a temporary value
            if(diff > r){ //If the difference is greater than the current return frequency
                r = diff; //Set the return frequency to the difference
            }
        }
    }
    return r;
}