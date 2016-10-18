/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Count words in text and find the average number of letters as both a string and cstring
 * Created on October 16, 2016
 */


//System Libraries
#include <string> //String type and functions
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <fstream> //File I/O
using namespace std;

//Function Prototypes
unsigned int count(const char*, unsigned int);
unsigned int count(const string&);
float avgAlph(const char*, unsigned int, unsigned int);
float avgAlph(const string&, unsigned int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    ifstream in; //File input stream
    string text = ""; //The current line of text
    unsigned int lines = 0; //The number of lines read


    in.open("data_10_4.txt"); //Open file for reading
    cout << fixed << setprecision(2); //Format output
    cout << "Line#" << endl; //Line number heading
    while(getline(in, text)){ //While there are more lines to read
        cout << setw(5) << lines++ << " " << text << endl; //Output line number
        //Calculate and output data
        cout << "      " << "WORD COUNT AS STRING:  " << setw(6) << count(text) << endl;
        cout << "      " << "WORD COUNT AS CSTRING: " << setw(6) << count(text.c_str(), text.size()) << endl;
        cout << "      " << "AVERAGE LETTERS AS STRING:   " << setw(6) << avgAlph(text, count(text)) << endl;
        cout << "      " << "AVERAGE LETTERS AS CSTRING:  " << setw(6);
        cout << avgAlph(text.c_str(), text.size(), count(text.c_str(), text.size())) << endl;
        cout << endl;
    }
    in.close(); //Close file

    //Exit
    return 0;
}

//Count
//Count the number of words in a CString
//Input:
//str
//A pointer to a CString
//size
//The size of str in characters
//Output:
//The number of words in the input CString

unsigned int count(const char *str, unsigned int size){
    unsigned int r = 0; //The word count
    bool word = false; //If the program is currently in a word

    for(int i = 0; i < size; ++i){ //For all the characters in str
        if(word && i + 1 >= size){ //If the line ends on a word
            ++r; //Increment word count
        }
        else if(isprint(str[i]) && isalpha(str[i])){ //If the current character is printable and in the alphabet
            word = true; //The program is in a word
        }
        else if(word){ //Otherwise if the program was in a word
            ++r; //Increment word count
            word = false; //The program is not in a word
        }
    }

    return r;
}

//Count
//Count the number of words in a string
//Input:
//str
//a string to count the words in
//Output:
//The number of words in the input string

unsigned int count(const string &str){
    unsigned int r = 0; //The word count
    bool word = false; //If the program is currently in a word

    for(int i = 0; i < str.size(); ++i){ //For all the characters in str
        if(word && i + 1 >= str.size()){ //If the line ends on a word
            ++r; //Increment word count
        }
        else if(isprint(str[i]) && isalpha(str[i])){ //If the current character is printable and in the alphabet
            word = true; //The program is in a word
        }
        else if(word){ //Otherwise if the program was in a word
            ++r; //Increment word count
            word = false; //The program is not in a word
        }
    }

    return r;
}

//Average Alphabetic Characters
//Calculates the average number of alphabetic characters in a CString based on a word count
//Input:
//str
//A pointer to a CString
//size
//The size of that CString
//count
//The word count of the input CString
//Output:
//A float value representing the average number of alphabetic characters

float avgAlph(const char *str, unsigned int size, unsigned int count){
    float r = 0.0f; //The average
    unsigned int total = 0; //The running total of characters

    if(count > 0){ //If the CString actually contains some words
        for(int i = 0; i < size; ++i){ //For every character
            if(isalpha(str[i])){ //If the current character is alphabetic
                ++total; //Increment the total
            }
        }
        r = total / (count * 1.0f); //Calculate the average
    }

    return r;
}

//Average Alphabetic Characters
//Calculates the average number of alphabetic characters in a string based on a word count
//Input:
//str
//A string to calculate the average characters of
//count
//The word count of the input string
//Output:
//A float value representing the average number of alphabetic characters

float avgAlph(const string &str, unsigned int count){
    float r = 0.0f; //The average
    unsigned int total = 0; //The running total of characters

    if(count > 0){ //If the string actually contains some words
        for(int i = 0; i < str.size(); ++i){ //For every character
            if(isalpha(str[i])){ //If the current character is alphabetic
                ++total; //Increment the total
            }
        }
        r = total / (count * 1.0f); //Calculate the average
    }

    return r;
}