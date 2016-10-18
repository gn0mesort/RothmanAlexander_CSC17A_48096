/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Sentence file filtering. Capitalize the first letter of each sentence
 * Created on October 16, 2016
 */

//System Libraries
#include <fstream> //File I/O
#include <iostream> //I/O
#include <string> //String type and functions
using namespace std;


//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    string inFile = "", //The input file path
            outFile = "", //The output file path
            data = ""; //The string to read lines into
    ifstream in; //The input file stream
    ofstream out; //The output file stream

    //Input
    cout << "ENTER THE INPUT FILE PATH: ";
    getline(cin, inFile); //Read in inFile
    cout << "ENTER THE OUTPUT FILE PATH: ";
    getline(cin, outFile); //Read in outFile

    //Filter file
    in.open(inFile.c_str()); //Open the input file
    out.open(outFile.c_str()); //Open the output file
    while(getline(in, data)){ //While there is more input to read
        bool endSent = true; //Whether or not the program is at the end of a sentence
        for(int i = 0; i < data.size(); ++i){ //For every character in the current line
            if(!endSent && (data[i - 1] == '.' || data[i - 1] == '?' || data[i - 1] == '!')){ //If this is a sentence ending
                endSent = true; //The program is at the end of a sentence
            }
            if(endSent && isalpha(data[i])){ //If we reached the end of a sentence and the next character is a letter
                data[i] = toupper(data[i]); //Uppercase the letter
                endSent = false; //The program is not at a sentence ending
            }
            else{ //Otherwise
                data[i] = tolower(data[i]); //Lowercase the data
            }
        }
        if(!data.empty()){ //If the current line isn't empty
            cout << data << endl; //Output the line to stdout
            out << data << endl; //Output the line to the output file
        }
    }
    in.close(); //Close the input file
    out.close(); //Close the output file

    //Exit
    return 0;
}

