/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Display a CString in reverse
 * Created on October 16, 2016
 */

#include <iostream>
#include <string>
using namespace std;

void reverse(const char*, unsigned int);

int main(int argc, char** argv){
    string str = "";

    cout << "ENTER A STRING: ";
    getline(cin, str);
    cout << "REVERSED STRING: ";
    reverse(str.c_str(), str.size());

    return 0;
}

void reverse(const char *str, unsigned int size){
    for(int i = size - 1; i >= 0; --i){
        cout << str[i];
    }
}