/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Binary String Search
 * Created on September 18, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <string> //String type and functions
#include <fstream> //File I/O
#include <cstdlib> //C Standard Library
#include <ctime> //Time and date
using namespace std;

//Function Prototypes
string toupper(const string&);
void rdData(string[], unsigned char);
void mkIndx(unsigned char[], unsigned char);
int binSrch(const string[], const unsigned char[], unsigned char, const string&);
void sort(string[], unsigned char[], unsigned char);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    const unsigned char SIZE = 20; //The size of the names array
    char loc = 0; //The location at which the key was wound
    unsigned char index[SIZE]; //An indexing array for names
    string names[SIZE]; //An array containing name data read from names.txt
    string key; //The key to search for

    srand(static_cast<int>(time(0))); //Seed PRNG
    rdData(names, SIZE); //Read data into names
    mkIndx(index, SIZE); //Fill the indexing array
    key = names[rand() % SIZE]; //Pick a random name as a key

    //Calculate and Output data
    cout << "SEARCHING FOR: " << key << endl;
    cout << "SORTING...";
    sort(names, index, SIZE); //Sort the indexing array based on names
    cout << "DONE!" << endl;
    cout << "SEARCHING...";
    loc = binSrch(names, index, SIZE, key); //Get the location of the key using a binary search
    cout << "DONE!" << endl;
    if(loc > -1){ //If found
        cout << key << " FOUND AT " << static_cast<int>(loc) << endl;
        cout << "names[" << static_cast<int>(loc) << "] = ";
        cout << names[index[loc]] << endl;
    }
    else{ //If not found
        cout << key << " NOT FOUND!" << endl;
    }
    cout << endl << endl;
    for(int i = 0; i < SIZE; ++i){ //Iterate across and display names
        cout << i << ":" << names[index[i]] << endl;
    }

    //Exit
    return 0;
}

//Binary Search
//Preform a binary search on an array of strings for the given key
//Input:
//data
//The underlying data array
//index
//The indexing array for data (sorted)
//size
//The size of the data and indexing arrays
//key
//The string to search for
//Output:
//An integer representing the position of the key in the indexing array

int binSrch(const string data[], const unsigned char index[],
            unsigned char size, const string &key){
    char first = 0, //The lower bound
            last = size - 1, //The upper bound
            middle, //The midpoint of the bounds
            pos = -1; //The position of the key
    bool found = false; //If the key has been found or not

    while(!found && first <= last){ //While the key hasn't been found and first is not greater than last
        middle = (first + last) / 2; //calculate midpoint
        if(data[index[middle]].compare(key) == 0){ //If the key is found
            found = true;
            pos = middle; //the key was found at the current midpoint
        }
        else if(data[index[middle]].compare(key) > 0){ //If the current value is greater than the key
            last = middle - 1;
        }
        else{ //If the current value is less than the key
            first = middle + 1;
        }
    }

    return pos;
}

//Make Index
//Fills an indexing array for a given size
//Input:
//index
//The array to fill
//size
//The size of the array
//Output:
//The filled indexing array

void mkIndx(unsigned char index[], unsigned char size){
    for(int i = 0; i < size; ++i){ //Iterate across index
        index[i] = i; //Fill each element with i
    }
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

void sort(string data[], unsigned char index[], unsigned char size){
    unsigned char pos = 0; //The initial position

    while(pos < size){ //While unsorted
        if(pos == 0 || data[index[pos]].compare(data[index[pos - 1]]) > 0){ //If the postion is 0 or the current value is greater than the last value
            ++pos; //Move up one position
        }
        else{ //Otherwise
            //Swap the current position and the last position
            index[pos] = index[pos] ^ index[pos - 1];
            index[pos - 1] = index[pos] ^ index[pos - 1];
            index[pos] = index[pos] ^ index[pos - 1];
            pos = pos - 1; //Move back one position
        }
    }
}

//To Upper Case
//Convert a string to upper case characters
//Input:
//str
//The string to convert
//Output:
//The input string with all upper case characters

string toupper(const string &str){
    string r = ""; //The return value

    for(int i = 0; i < str.size(); ++i){ //Iterate across str
        r += toupper(str.at(i)); //add the upper case value of str at i to r
    }

    return r;
}

//Read Data
//Read name data from a file into an array
//Input:
//names
//The array to fill with data
//size
//The size of names
//Output:
//The filled array

void rdData(string names[], unsigned char size){
    ifstream input; //Input stream
    string tmp; //Temporary string storage

    input.open("names.txt"); //Open input stream
    if(input.good()){ //If the input stream is good
        for(int i = 0; i < size; ++i){ //Iterate across names
            getline(input, tmp); //Get the next line of the file
            names[i] = toupper(tmp); //uppercase and store the value in names
        }
    }
    input.close(); //Close input stream
}

