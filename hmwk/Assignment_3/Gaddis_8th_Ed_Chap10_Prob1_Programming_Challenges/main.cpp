/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Length of a CString
 * Created on October 16, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <string> //String type and functions
using namespace std;

//Function Prototypes
unsigned int length(const char*);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    string input = ""; //The string to measure

    //Input
    cout << "ENTER A STRING: ";
    getline(cin, input); //Read in input

    //Output
    cout << "LENGTH: " << length(input.c_str()) << endl; //Output length
    if(length(input.c_str()) == input.size()){ //If the calculated length is the same as input.size()
        cout << "CHECK!" << endl; //Output that they match
    }

    //Exit
    return 0;
}

//Length
//Calculate the length of a CString
//Input:
//str
//A pointer to a CString
//Output:
//The length of that string

unsigned int length(const char *str){
    unsigned int r = 0; //The return value

    while(str[r] != '\0'){ //While the current character is not a null terminator
        ++r; //increment r
    }

    return r;
}

