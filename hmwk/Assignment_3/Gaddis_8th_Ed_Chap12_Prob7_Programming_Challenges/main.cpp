/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 16, 2016
 */

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

string capital(const string&);

int main(int argc, char** argv){
    string inFile = "", outFile = "", data = "";
    ifstream in;
    ofstream out;

    cout << "ENTER THE INPUT FILE PATH: ";
    getline(cin, inFile);
    cout << "ENTER THE OUTPUT FILE PATH: ";
    getline(cin, outFile);

    in.open(inFile.c_str());
    out.open(outFile.c_str());
    while(in.good() && !in.eof()){
        string input;
        bool endSent = true;
        getline(in, input);
        for(int i = 0; i < input.size(); ++i){
            if(!endSent && (input[i - 1] == '.' || input[i - 1] == '?' || input[i - 1] == '!')){
                endSent = true;
            }
            if(endSent && isalpha(input[i])){
                input[i] = toupper(input[i]);
                endSent = false;
            }
            else{
                input[i] = tolower(input[i]);
            }
        }
        if(!input.empty()){
            cout << input << endl;
            out << input << endl;
        }
    }
    in.close();
    out.close();

    return 0;
}

