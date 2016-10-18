/*
 * File:   main.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 17, 2016
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv){
    int count = 0;
    string path = "";
    ifstream in;

    cout << "ENTER A FILE NAME: ";
    getline(cin, path);

    in.open(path.c_str());
    if(in.is_open()){
        string data;
        while(getline(in, data)){
            cout << data << endl;
            ++count;
            if((count + 1) % 24 == 0){
                cout << "--MORE--";
                cin.get();
            }
        }
    }
    in.close();

    return 0;
}

