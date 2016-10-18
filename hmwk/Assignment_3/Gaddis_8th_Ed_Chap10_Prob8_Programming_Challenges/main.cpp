/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Sum the digits in a string
 * Created on October 16, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <string> //String type and functions
using namespace std;

//Function Prototypes
unsigned int strSum(const string&);
unsigned char high(const string&);
unsigned char low(const string&);
int toInt(unsigned char);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    string str = ""; //The string to sum

    //Input
    cout << "ENTER A STRING TO SUM: ";
    getline(cin, str); //Read in str

    //Output
    cout << "SUM: " << strSum(str) << endl; //Output sum
    cout << "HIGHEST DIGIT: " << toInt(high(str)) << endl; //Output highest digit
    cout << "LOWEST DIGIT: " << toInt(low(str)) << endl; //Output lowest digit

    //Exit
    return 0;
}

//String Sum
//Sum all the digits in a string. Ignores characters that aren't digits
//Input:
//str
//The string to sum
//Output:
//The sum of all digits in the string

unsigned int strSum(const string &str){
    unsigned int r = 0; //The sum

    for(int i = 0; i < str.size(); ++i){ //For every character in str
        if(isdigit(str[i])){ //If the character is a digit
            r += str[i] - 48; //Calculate value and add it to the total
        }
    }

    return r;
}

//High
//Find the highest digit in a string
//Input:
//str
//The string to find the highest digit of
//Output:
//The highest digit in str

unsigned char high(const string &str){
    unsigned char r = 0; //The highest digit

    for(int i = 0; i < str.size(); ++i){ //For every character in str
        if(isdigit(str[i]) && str[i] - 48 > r){ //If the character is a digit and is higher than r
            r = str[i] - 48; //The highest digit is the numeric value of the current character
        }
    }

    return r;
}

//Low
//Find the lowest digit in a string
//Input:
//str
//The string to find the lowest digit of
//Output:
//The lowest digit in str

unsigned char low(const string &str){
    unsigned char r = 255; //The lowest digit. Set to 2^8 - 1

    for(int i = 0; i < str.size(); ++i){ //For every character in str
        if(isdigit(str[i]) && str[i] - 48 < r){ //If the character is a digit and is lower than r
            r = str[i] - 48; //The lowest digit is the numeric value of the current character
        }
    }

    return r;
}

//To Int
//Convert a unsigned char to an int without having to write out the static_cast
//Input:
//c
//The unsigned char to covert
//Output:
//The value of c static_cast to an int

int toInt(unsigned char c){
    return static_cast<int>(c);
}