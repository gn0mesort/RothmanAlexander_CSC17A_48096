/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Calculate the average test score
 * Created on September 27, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
using namespace std;

//Function Prototypes
void sort(short[], short);
void prntArr(const short[], short);
float avg(const short[], short);


//Begin Execution
int main(int argc, char** argv){
    //Declaration and Initialization
    short input = 0, //The input value
            length = 0; //The length of the score array
    short *scores = NULL; //The score array

    //Input
    do{ //While the input is less than 0
        cout << "ENTER THE NUMBER OF TESTS: ";
        cin >> input; //Read in input
    } while(input < 0);
    length = input; //Set the length of the array
    if(input > 0){ //If the input wasn't 0
        scores = new short[length]; //Allocate the score array
        for(int i = 0; i < length; ++i){ //For every element of the score array
            do{ //While the input is less than 0
                cout << "ENTER THE SCORE FOR TEST #" << i + 1 << ": ";
                cin >> input; //Read in input
            } while(input < 0);
            scores[i] = input; //Set the current score to input
        }

        //Calculate and Output data
        cout << "SORTED SCORES:";
        if(length > 10){ //Formatting
            cout << endl;
        }
        sort(scores, length); //Sort the scores
        prntArr(scores, length); //Output the sorted scores
        cout << fixed << setprecision(2); //Formatting
        cout << "AVERAGE SCORE: " << avg(scores, length) << endl; //Output the average score

        //Delete the score array
        delete [] scores;
    }

    //Exit
    return 0;
}

//Sort
//Sorts an indexing array based on string values found in a data array using the
//gnome sort algorithm
//Input:
//data
//The string data array
//index
//The indexing array for data to be sorted
//size
//The size of both arrays
//Output:
//The sorted indexing array
void sort(short array[], short size){
    short pos = 0; //The initial position
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
void prntArr(const short array[], short size){
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

//Average
//Calculate the average of a given array
//Input:
//array
//The array to calculate the average of
//length
//The size of that array
//Output:
//The average of the array as a float
float avg(const short array[], short length){
    float r = 0.0f; //The average to be returned

    for(int i = 0; i < length; ++i){ //For each element of the array
        r += array[i]; //Sum the elements
    }

    return r / (length * 1.0f); //Return the average
}