/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Turn a file into 24 line pages in a manner similar to less
 * Created on October 17, 2016
 */

//System Libraries
#include <string> //String type and functions
#include <iostream> //I/O
#include <fstream> //File I/O
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int count = 0; //The number of lines read
    string path = ""; //The path to read from
    ifstream in; //The input file stream

    //Input
    cout << "ENTER A FILE NAME: ";
    getline(cin, path); //Read in path

    //Read and output data
    in.open(path.c_str()); //Open file
    if(in.is_open()){ //If file opened correctly
        string data; //The current file line
        while(getline(in, data)){ //While there are more lines to read
            cout << data << endl; //Output the data
            ++count; //Increment the count
            if((count + 1) % 24 == 0){ //If the next line is the 24th line since the last break
                cout << "--MORE--"; //Output page break message
                cin.get(); //Hold terminal open for input
            }
        }
    }
    in.close(); //Close file

    //Exit
    return 0;
}

