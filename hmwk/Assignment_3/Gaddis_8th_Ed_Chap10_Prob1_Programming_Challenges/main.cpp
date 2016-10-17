/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Length of a CString
 * Created on October 16, 2016
 */

#include <iostream>
#include <string>
using namespace std;

unsigned int length(const char*);

int main(int argc, char** argv){
    string input = "";

    cout << "ENTER A STRING: ";
    getline(cin, input);
    cout << "LENGTH: " << length(input.c_str()) << endl;
    if(length(input.c_str()) == input.size()){
        cout << "CHECK!" << endl;
    }

    return 0;
}

unsigned int length(const char *str){
    unsigned int r = 0;

    while(str[r] != '\0'){
        ++r;
    }

    return r;
}

