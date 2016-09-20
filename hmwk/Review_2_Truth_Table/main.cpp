/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Display true or false values for various boolean comparisons
 * Created on September 17, 2016
 */

//System Libraries
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//Function Prototypes
char toChar(bool);
void prntFmt(string);
void prntFmt(char);

int main(int argc, char** argv){
    //Declaration and Initialization
    const unsigned char SIZE = 13; //The size of the header array
    bool x = true, //The value of X in the table
            y = true; //The value of Y in the table
    string header[13] = {"X", "Y", "!X", "!Y", "X&&Y", "X||Y", "X^Y", "X^Y^Y",
        "X^Y^X", "!(X||Y)", "!X&&!Y", "!(X&&Y)", "!X||!Y"}; //The table header

    //Print Table Header
    for(int i = 0; i < SIZE; ++i){
        prntFmt(header[i]);
    }
    cout << endl;
    //Print Table Values
    for(int i = 0; i < 4; ++i){
        if(i == 1){ //If this is the second iteration
            y = false; //Set y to false
        }
        else if(i == 2){ //If this is the third iteration
            x = false; //Set x to false
            y = true; //Set y to true
        }
        else if(i == 3){ //If this is the fourth iteration
            y = false; //Set y to false
        }
        //Print each comparison
        prntFmt(toChar(x));
        prntFmt(toChar(y));
        prntFmt(toChar(!x));
        prntFmt(toChar(!y));
        prntFmt(toChar(x && y));
        prntFmt(toChar(x || y));
        prntFmt(toChar(x ^ y));
        prntFmt(toChar(x ^ y ^ y));
        prntFmt(toChar(x ^ y ^ x));
        prntFmt(toChar(!(x || y)));
        prntFmt(toChar(!x && !y));
        prntFmt(toChar(!(x && y)));
        prntFmt(toChar(!x || !y));
        cout << endl;
    }

    //Exit
    return 0;
}

//Print Formatted (string)
//Prints a string formatted to fit in the truth table
//Input:
//str
//A string to print

void prntFmt(string str){
    cout << setw(8) << str;
}

//Print Formatted (char)
//Prints a character formatted to fit in the truth table
//Input:
//c
//A character to print

void prntFmt(char c){
    cout << setw(8) << c;
}

//To Character
//Converts a boolean value to a character. T for true and F for false.
//Input:
//value
//A boolean value to convert to a character
//Output:
//A character representing the given input

char toChar(bool value){
    return value ? 'T' : 'F';
}

