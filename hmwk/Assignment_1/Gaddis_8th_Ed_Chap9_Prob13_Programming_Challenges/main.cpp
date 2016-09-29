/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Collect and display movie statistics.
 * Uses the functions from Mean_Median_Mode rather than the ones
 * described in the book.
 * Created on September 27, 2016
 */

//System Libraries
#include <iostream> //I/O
using namespace std;

//Function Prototypes
float mean(const int[], int);
float median(const int[], int);
void sort(int[], int);
int* mode(const int[], int);
int modeCnt(const int[], int, int);
int getFreq(const int[], int);
int* getMdes(const int[], int, int, int);
void prntArr(const int[], unsigned int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int size = 0; //The number of students who were surveyed
    int *data = NULL, //The actual survey data
            *modes = NULL; //The array containing the mode data

    //Input
    do{ //While size is less than 0
        cout << "ENTER THE NUMBER OF STUDENTS SURVEYED: ";
        cin >> size;
    } while(size < 0);

    if(size > 0){ //If data was collected
        data = new int[size]; //Allocate data array

        for(int i = 0; i < size; ++i){ //For every element of the data array
            do{ //While the input data is less than 0
                cout << "ENTER THE NUMBER OF MOVIES THAT STUDENT " << i + 1 << " WATCHED: ";
                cin >> data[i];
            } while(data[i] < 0);
        }

        //Calculate and Output Data
        cout << "DATA:" << endl;
        prntArr(data, size); //Print the original data
        sort(data, size); //Sort the data
        cout << "MEAN: " << mean(data, size) << endl; //Output the mean
        cout << "MEDIAN: " << median(data, size) << endl; //Output the median
        modes = mode(data, size); //Generate the mode data
        if(modes[1] > 1){ //If modes exist
            cout << "NUMBER OF MODES: " << modes[0] << endl; //Output the number of modes
            cout << "MODE FREQUENCY: " << modes[1] << endl; //Output the frequency of the modes
            cout << "MODES: ";
            for(int i = 2; i < modes[0] + 2; ++i){ //For all the modes found in the mode data array
                cout << modes[i]; //Output the mode
                if(i + 1 < modes[0] + 2){ //Formatting
                    cout << ", ";
                }
                else{
                    cout << endl;
                }
            }
        }
        else{ //Otherwise
            cout << "NO MODE!" << endl;
        }

        //Delete arrays
        delete [] modes;
        delete [] data;
    }

    //Exit
    return 0;
}

//Mode
//Calculate the modes (if any exist) of a given integer array
//Input:
//array
//The array to calculate the modes of
//size
//The size of the input array
//Output:
//A pointer to an array containing the following data
//1. The number of modes found (array[0])
//2. The frequency at which they occurred (array[1])
//3. The values of those modes (array[2 - (n - 1)])

int* mode(const int array[], int size){
    int *r = NULL, //The return array
            *modes = NULL; //The modes found by this function
    int freq = getFreq(array, size), //The frequency of the modes
            numMode = 0; //The number of modes found

    if(freq > 1){ //If modes exist
        numMode = modeCnt(array, size, freq); //Calculate the number of modes
    }
    modes = getMdes(array, size, numMode, freq); //Get the modes
    r = new int[numMode + 2]; //Allocate the return array
    r[0] = numMode; //Set the number of modes
    r[1] = freq; //Set the frequency

    for(int i = 2; i < numMode + 2; ++i){ //For each mode
        r[i] = modes[i - 2]; //Set the element of the return array at i to the mode at i - 2
    }

    //Delete modes array
    delete [] modes;

    return r;
}

//Get Modes
//Get the modes for a given array.
//Input:
//array
//The array to find modes from
//size
//The size of the array
//numMode
//The number of modes found in the array
//freq
//The frequency of the modes in the array
//Output:
//A pointer to an array containing the modes of the input array

int* getMdes(const int array[], int size, int numMode, int freq){
    int *r = new int[numMode]; //Allocate return array
    int count = 0, //The count of the current search value
            pos = 0; //The position in the return array

    for(int i = 0; i < size; ++i){ //For each value in the input array
        if(i > 0 && array[i] != array[i - 1]){ //If the current value has changed from the last value
            if(count == freq){ //If the current count is the same as the frequency
                r[pos++] = array[i - 1]; //place the previous value in the return array and increment the position
            }
            count = 1; //Reset the count
        }
        else{ //Otherwise
            ++count; //Increment the count
        }
        if(i + 1 >= size && count == freq){ //If the last value in the array is a mode
            r[pos] = array[i]; //place it in the current position of the return array
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

int getFreq(const int array[], int size){
    int r = 0, //The frequency to return
            start = 0; //The position of the start of the most recent value in the array

    for(int current = 0; current < size; ++current){ //For each element in the array
        if(array[start] != array[current]){ //If the current value is not the same as the starting value
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

//Mode Count
//Count the number of modes in an array
//Input:
//array
//The array to count the modes of
//size
//The size of that array
//freq
//The frequency of the mode
//Output:
//The number of modes found in the array

int modeCnt(const int array[], int size, int freq){
    int r = 0, //The return mode count
            count = 0; //The number of times the current value has appeared

    for(int i = 0; i < size; ++i){ //For each value in the input array
        if(i > 0 && array[i] != array[i - 1]){ //If the current value has changed from the last value
            if(count == freq){ //If the current count is the same as the frequency
                ++r; //Increment the mode count
            }
            count = 1; //Reset the count
        }
        else{ //Otherwise
            ++count; //Increment the count
        }
        if(i + 1 >= size && count == freq){ //If the last value in the array is a mode
            ++r; //Increment the mode count
        }
    }

    return r;
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

//Mean
//Calculate the mean of an array
//Input:
//array
//The input array
//size
//The size of the array
//Output:
//The mean value of the array as a float

float mean(const int array[], int size){
    int total = 0; //The sum of the array elements
    for(int i = 0; i < size; ++i){ //For each array element
        total += array[i]; //Sum the elements
    }
    return total / (size * 1.0f); //Calculate and return the mean
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

