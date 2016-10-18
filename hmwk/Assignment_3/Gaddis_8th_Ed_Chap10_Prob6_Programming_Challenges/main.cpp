/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Count Vowels and Consonants
 * Created on October 16, 2016
 */

//System Libraries
#include <string> //String type and functions
#include <iostream> //I/O
using namespace std;

//Function Prototypes
bool isVowel(char);
unsigned int vowels(const char*, unsigned int);
unsigned int cnsnnts(const char*, unsigned int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    bool quit = false; //If quitting
    string str = ""; //The string to test

    //Input str
    cout << "ENTER THE INITIAL TEST STRING" << endl;
    cout << "> ";
    getline(cin, str); //Read in str
    do{ //While not quitting
        string input = ""; //The current user input
        unsigned char select = 0; //The input as a number

        //Output Menu
        cout << "STRING: " << str << endl;
        cout << "MENU:" << endl;
        cout << "(1) Count the number of vowels in the string" << endl;
        cout << "(2) Count the number of consonants in the string" << endl;
        cout << "(3) Count both the vowels and the consonants in the string" << endl;
        cout << "(4) Enter another string" << endl;
        cout << "(0) Exit" << endl;

        do{ //While input is invalid
            cout << "> ";
            getline(cin, input); //Read in input
            select = input[0] - 48; //Calculate selection
        } while(select > 4 && select < 0);

        switch(select){ //Preform selected choice
            case 1: //Count vowels
            {
                cout << "VOWELS: " << vowels(str.c_str(), str.size()) << endl;
                break;
            }
            case 2: //Count consonants
            {
                cout << "CONSONANTS: " << cnsnnts(str.c_str(), str.size()) << endl;
                break;
            }
            case 3: //Count both
            {
                cout << "VOWELS AND CONSONANTS: ";
                cout << vowels(str.c_str(), str.size()) + cnsnnts(str.c_str(), str.size()) << endl;
                break;
            }
            case 4: //Edit string
            {
                cout << "ENTER THE NEW STRING" << endl;
                cout << "> ";
                getline(cin, str);
                break;
            }
            case 0: //Quit
            {
                quit = true;
                break;
            }
        }
    } while(!quit);


    //Exit
    return 0;
}

//Is Vowel
//Return whether or not a character is a value
//Input:
//c
//The character to test
//Output:
//whether or not c is a vowel

bool isVowel(char c){
    c = toupper(c); //Set c to upper case
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'); //Preform check and return
}


//Vowels
//Count the number of vowels in a CString
//Input:
//str
//A pointer to a CString
//size
//The size of str in characters
//Output:
//The number of vowels in str

unsigned int vowels(const char *str, unsigned int size){
    unsigned int r = 0; //The number of vowels

    for(int i = 0; i < size; ++i){ //For every character in str
        if(isVowel(str[i])){ //If it is a vowel
            ++r; //Increment r
        }
    }

    return r;
}


//Consonants
//Count the number of consonants in a CString
//Input:
//str
//A pointer to a CString
//size
//The size of str in characters
//Output:
//The number of consonants in str

unsigned int cnsnnts(const char *str, unsigned int size){
    unsigned int r = 0; //The number of consonants

    for(int i = 0; i < size; ++i){ //For every character in str
        if(!isVowel(str[i]) && isalpha(str[i])){ //If it isn't a vowel but is alphabetic
            ++r; //increment r
        }
    }

    return r;
}