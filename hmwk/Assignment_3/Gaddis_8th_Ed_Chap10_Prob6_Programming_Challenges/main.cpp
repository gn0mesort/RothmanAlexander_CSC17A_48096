/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Count Vowels and ConsonantsS
 * Created on October 16, 2016
 */

#include <string>
#include <iostream>
using namespace std;

bool isVowel(char);
unsigned int vowels(const char*, unsigned int);
unsigned int cnsnnts(const char*, unsigned int);

int main(int argc, char** argv){
    bool quit = false;
    string str = "";

    cout << "ENTER THE INITIAL TEST STRING" << endl;
    cout << "> ";
    getline(cin, str);
    do{
        string input = "";
        unsigned char select = 0;

        cout << "STRING: " << str << endl;
        cout << "MENU:" << endl;
        cout << "(1) Count the number of vowels in the string" << endl;
        cout << "(2) Count the number of consonants in the string" << endl;
        cout << "(3) Count both the vowels and the consonants in the string" << endl;
        cout << "(4) Enter another string" << endl;
        cout << "(0) Exit" << endl;

        do{
            cout << "> ";
            getline(cin, input);
            select = input[0] - 48;
        } while(select > 4 && select < 0);

        switch(select){
            case 1:
            {
                cout << "VOWELS: " << vowels(str.c_str(), str.size()) << endl;
                break;
            }
            case 2:
            {
                cout << "CONSONANTS: " << cnsnnts(str.c_str(), str.size()) << endl;
                break;
            }
            case 3:
            {
                cout << "VOWELS AND CONSONANTS: ";
                cout << vowels(str.c_str(), str.size()) + cnsnnts(str.c_str(), str.size()) << endl;
                break;
            }
            case 4:
            {
                cout << "ENTER THE NEW STRING" << endl;
                cout << "> ";
                getline(cin, str);
                break;
            }
            case 0:
            {
                quit = true;
                break;
            }
        }
    } while(!quit);


    return 0;
}

bool isVowel(char c){
    c = toupper(c);
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

unsigned int vowels(const char *str, unsigned int size){
    unsigned int r = 0;

    for(int i = 0; i < size; ++i){
        if(isVowel(str[i]) && isalpha(str[i])){
            ++r;
        }
    }

    return r;
}

unsigned int cnsnnts(const char *str, unsigned int size){
    unsigned int r = 0;

    for(int i = 0; i < size; ++i){
        if(!isVowel(str[i]) && isalpha(str[i])){
            ++r;
        }
    }

    return r;
}