/*
 * File:   main.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 17, 2016
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char** argv){
    const char *END = "**END OF FILE**";

    int count = 0;
    string path = "";
    ifstream in;

    cout << "ENTER A FILE NAME: ";
    getline(cin, path);

    in.open(path.c_str());
    if(in.is_open()){
        string data;
        while(getline(in, data) && count < 10){
            cout << data << endl;
            ++count;
        }
        if(count < 10){
            cout << END << endl;
        }
    }
    in.close();


    return 0;
}

