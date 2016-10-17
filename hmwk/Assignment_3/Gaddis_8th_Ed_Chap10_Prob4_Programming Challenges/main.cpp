/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Count words in text and find the average number of letters as both a string and cstring
 * Created on October 16, 2016
 */


#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

unsigned int count(const char*, unsigned int);
unsigned int count(const string&);
float avgAlph(const char*, unsigned int, unsigned int);
float avgAlph(const string&, unsigned int);

int main(int argc, char** argv){
    ifstream in;
    string text = "";
    unsigned int lines = 0;

    in.open("data.txt");
    cout << fixed << setprecision(2);
    cout << "Line#" << endl;
    while(in.good() && !in.eof()){
        getline(in, text);
        cout << setw(5) << lines++ << " " << text << endl;
        cout << "      " << "WORD COUNT AS STRING:  " << setw(6) << count(text) << endl;
        cout << "      " << "WORD COUNT AS CSTRING: " << setw(6) << count(text.c_str(), text.size()) << endl;
        cout << "      " << "AVERAGE LETTERS AS STRING:   " << setw(6) << avgAlph(text, count(text)) << endl;
        cout << "      " << "AVERAGE LETTERS AS CSTRING:  " << setw(6);
        cout << avgAlph(text.c_str(), text.size(), count(text.c_str(), text.size())) << endl;
        cout << endl;
    }
    in.close();

    return 0;
}

unsigned int count(const char *str, unsigned int size){
    unsigned int r = 0;
    bool word = false;

    for(int i = 0; i < size; ++i){
        if(word && i + 1 >= size){
            ++r;
        }
        else if(isprint(str[i]) && isalpha(str[i])){
            word = true;
        }
        else if(word){
            ++r;
            word = false;
        }
    }

    return r;
}

unsigned int count(const string &str){
    unsigned int r = 0;
    bool word = false;

    for(int i = 0; i < str.size(); ++i){
        if(word && i + 1 >= str.size()){
            ++r;
        }
        else if(isprint(str[i]) && isalpha(str[i])){
            word = true;
        }
        else if(word){
            ++r;
            word = false;
        }
    }

    return r;
}

float avgAlph(const char *str, unsigned int size, unsigned int count){
    float r = 0.0f;
    unsigned int total = 0;

    if(count){
        for(int i = 0; i < size; ++i){
            if(isalpha(str[i])){

                ++total;
            }
        }
        r = total / (count * 1.0f);
    }

    return r;
}

float avgAlph(const string &str, unsigned int count){
    float r = 0.0f;
    unsigned int total = 0;

    if(count > 0){
        for(int i = 0; i < str.size(); ++i){
            if(isalpha(str[i])){
                ++total;
            }
        }
        r = total / (count * 1.0f);
    }

    return r;
}