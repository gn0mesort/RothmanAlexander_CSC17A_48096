/*
 * File:   main.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose: Calculate the average test score and display student names
 * Created on September 27, 2016
 */


//System libraries
#include <iostream> //I/O
#include <iomanip> //Formatting
#include <string> //String type and functions
using namespace std;

//Function Prototypes
void sortIdx(unsigned char[], short[], short);
void prntArr(const unsigned char[], const string[], const short[], short);
unsigned char* mkIndex(short);
float mean(const short[], short);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    short input = 0, //The input value
            length = 0; //The length of the score, names, and index arrays
    short *scores = NULL; //The score array
    unsigned char *index = NULL; //The index array
    string *names = NULL; //The names array

    //Input
    do{ //While the input is less than 0
        cout << "ENTER THE NUMBER OF TESTS: ";
        cin >> input; //Read in input
    } while(input < 0);
    length = input; //Set the length of the array
    if(input > 0){ //If the input wasn't 0
        scores = new short[length]; //Allocate the score array
        names = new string[length]; //Allocate the names array
        index = mkIndex(length); //Allocate and fill the index array
        for(int i = 0; i < length; ++i){ //For every element of the score array
            do{ //While the input is less than 0
                cout << "ENTER THE NAME FOR TEST #" << i + 1 << ": ";
                cin.ignore(); //Clear standard input
                getline(cin, names[i]); //Read in the next name
                cout << "ENTER THE SCORE FOR TEST #" << i + 1 << ": ";
                cin >> input; //Read in the next score
            } while(input < 0);
            scores[i] = input; //Set the current score to input
        }

        //Calculate and Output data
        cout << "SORTED SCORES:" << endl;
        sortIdx(index, scores, length); //Sort index by score
        prntArr(index, names, scores, length); //Display score and name data
        cout << fixed << setprecision(2); //Formatting
        cout << "AVERAGE SCORE: " << mean(scores, length) << endl; //Output average score

        //Delete arrays
        delete [] scores;
        delete [] names;
        delete [] index;
    }

    //Exit
    return 0;
}

//Make Index
//Generate an indexing array of a given size and return a pointer to it
//Input:
//size
//The size of the indexing array
//Output:
//A pointer to the indexing array

unsigned char* mkIndex(short size){
    unsigned char *r = new unsigned char[size]; //Allocate return array
    for(int i = 0; i < size; ++i){ //For all the elements of the array
        r[i] = i; //Fill array
    }
    return r;
}

//Sort Index
//Sort the indexing array using values found in the input array
//Input:
//index
//The indexing array to sort
//array
//The array of values to use in sorting
//size
//The size of the input arrays

void sortIdx(unsigned char index[], short array[], short size){
    short pos = 0; //The initial position
    while(pos < size){ //While unsorted
        if(pos == 0 || array[index[pos]] >= array[index[pos - 1]]){ //If the position is 0 or the current value is greater than the last value
            ++pos; //Move up one position
        }
        else{ //Otherwise
            //Swap the current position and the last position
            index[pos] = index[pos] ^ index[pos - 1];
            index[pos - 1] = index[pos] ^ index[pos - 1];
            index[pos] = index[pos] ^ index[pos - 1];
            //Move back one position
            --pos;
        }
    }
}

//Print Array
//Print score and name array together
//Input:
//index
//The indexing array
//names
//The array of names to be printed
//scores
//The score array to be printed
//size
//The size of the arrays

void prntArr(const unsigned char index[], const string names[], const short scores[], short size){
    for(int i = 0; i < size; ++i){ //For every array element
        cout << setw(10) << names[index[i]] << " : " << setw(4) << scores[index[i]] << endl; //Output name/score pair
    }
}

//Mean
//Calculate the average of a given array.
//Input:
//array
//The array to calculate the average of
//length
//The size of that array
//Output:
//The average of the array as a float

float mean(const short array[], short length){
    float r = 0.0f; //The average to be returned

    for(int i = 0; i < length; ++i){ //For each element of the array except the first element
        r += array[i]; //Sum the elements
    }

    return r / (length * 1.0f); //Return the average
}
