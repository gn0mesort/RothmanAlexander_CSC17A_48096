/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Display a CString in reverse
 * Created on October 16, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <string> //String type and functions
using namespace std;

//Function Prototypes
void reverse(const char*, unsigned int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    string str = ""; //The string to reverse

    //Input
    cout << "ENTER A STRING: ";
    getline(cin, str); //Read in str

    //Output
    cout << "REVERSED STRING: ";
    reverse(str.c_str(), str.size()); //Output reversed string

    //Exit
    return 0;
}

//Reverse
//Print a CString in reverse to stdout
//Input:
//str
//A pointer to a CString
//size
//The size of str in characters

void reverse(const char *str, unsigned int size){
    for(int i = size - 1; i >= 0; --i){ //Start at the last character and work backward
        cout << str[i]; //Output the character at i
    }
}