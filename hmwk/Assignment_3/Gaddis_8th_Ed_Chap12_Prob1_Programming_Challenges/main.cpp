/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Read the first ten lines of a file
 * Created on October 17, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <fstream> //File I/O
#include <string> //String type and functions
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    const char *END = "**END OF FILE**"; //A CString to output at the end of a short file

    int count = 0; //The number of lines read
    string path = ""; //The path to read from
    ifstream in; //The input file stream

    //Input
    cout << "ENTER A FILE NAME: ";
    getline(cin, path); //Read in path


    //Read and output file
    in.open(path.c_str()); //Open file
    if(in.is_open()){ //If the file opened properly
        string data; //The current line
        while(getline(in, data) && count < 10){ //While the stream is still good and count is less than 10
            cout << data << endl; //Output the current line
            ++count; //Increment count
        }
        if(count < 10){ //If the count is less than 10 at the end of the file
            cout << END << endl; //Output END
        }
    }
    in.close(); //Close the file

    //Exit
    return 0;
}

