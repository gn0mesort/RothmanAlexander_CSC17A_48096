/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Binary String Search
 * Created on September 18, 2016
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

string toupper(const string&);
void rdData(string[], unsigned char);
void mkIndx(unsigned char[], unsigned char);
int binSrch(const string[], const unsigned char[], unsigned char, const string&);
void sort(string[], unsigned char[], unsigned char);

int main(int argc, char** argv){
    const unsigned char SIZE = 20;
    char loc = 0;
    unsigned char index[SIZE];
    string names[SIZE];
    string key;

    srand(static_cast<int>(time(0)));

    rdData(names, SIZE);
    mkIndx(index, SIZE);
    key = names[rand() % SIZE];
    cout << "SEARCHING FOR: " << key << endl;
    cout << "SORTING...";
    sort(names, index, SIZE);
    cout << "DONE!" << endl;
    cout << "SEARCHING...";
    loc = binSrch(names, index, SIZE, key);
    cout << "DONE!" << endl;
    if(loc > -1){
        cout << key << " FOUND AT " << static_cast<int>(loc) << endl;
        cout << "names[" << static_cast<int>(loc) << "] = ";
        cout << names[index[loc]] << endl;
    }
    else{
        cout << key << " NOT FOUND!" << endl;
    }
    cout << endl << endl;
    for(int i = 0; i < SIZE; ++i){
        cout << i << ":" << names[index[i]] << endl;
    }
    return 0;
}

int binSrch(const string data[], const unsigned char index[],
            unsigned char size, const string &key){
    char first = 0,
            last = size - 1,
            middle,
            pos = -1;
    bool found = false;

    while(!found && first <= last){
        middle = (first + last) / 2;
        if(data[index[middle]].compare(key) == 0){
            found = true;
            pos = middle;
        }
        else if(data[index[middle]].compare(key) > 0){
            last = middle - 1;
        }
        else{
            first = middle + 1;
        }
    }
    return pos;
}

void mkIndx(unsigned char index[], unsigned char size){
    for(int i = 0; i < size; ++i){
        index[i] = i;
    }
}

void sort(string data[], unsigned char index[], unsigned char size){
    unsigned char pos = 0;
    while(pos < size){
        if(pos == 0 || data[index[pos]].compare(data[index[pos - 1]]) > 0){
            ++pos;
        }
        else{
            index[pos] = index[pos] ^ index[pos - 1];
            index[pos - 1] = index[pos] ^ index[pos - 1];
            index[pos] = index[pos] ^ index[pos - 1];
            pos = pos - 1;
        }
    }
}

string toupper(const string &str){
    string r = "";
    for(int i = 0; i < str.size(); ++i){
        r += toupper(str.at(i));
    }
    return r;
}

void rdData(string names[], unsigned char size){
    ifstream input;
    string tmp;

    input.open("names.txt");
    if(input.good()){
        for(int i = 0; i < size; ++i){
            getline(input, tmp);
            names[i] = toupper(tmp);
        }
    }
    input.close();
}

