/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Sum the digits in a string
 * Created on October 16, 2016
 */

#include <iostream>
#include <string>
using namespace std;

unsigned int strSum(const string&);
unsigned char high(const string&);
unsigned char low(const string&);
int toInt(unsigned char);

int main(int argc, char** argv){
    string str = "";

    cout << "ENTER A STRING TO SUM: ";
    getline(cin, str);
    cout << "SUM: " << strSum(str) << endl;
    cout << "HIGHEST DIGIT: " << toInt(high(str)) << endl;
    cout << "LOWEST DIGIT: " << toInt(low(str)) << endl;


    return 0;
}

unsigned int strSum(const string &str){
    unsigned int r = 0;

    for(int i = 0; i < str.size(); ++i){
        if(isdigit(str[i])){
            r += str[i] - 48;
        }
    }

    return r;
}

unsigned char high(const string &str){
    unsigned char r = 0;

    for(int i = 0; i < str.size(); ++i){
        if(isdigit(str[i]) && str[i] - 48 > r){
            r = str[i] - 48;
        }
    }

    return r;
}

unsigned char low(const string &str){
    unsigned char r = 255;

    for(int i = 0; i < str.size(); ++i){
        if(isdigit(str[i]) && str[i] - 48 < r){
            r = str[i] - 48;
        }
    }

    return r;
}

int toInt(unsigned char c){
    return static_cast<int>(c);
}