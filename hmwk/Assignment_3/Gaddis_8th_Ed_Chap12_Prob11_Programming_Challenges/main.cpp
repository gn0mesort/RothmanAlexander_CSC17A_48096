/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Save SaleDat objects to a file and load them back
 * Created on October 16, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <fstream> //File I/O
#include <vector> //Vector collections

//User Libraries
#include "SaleDat.h" //SaleDat type
using namespace std;

//Function Prototypes
void getData(SaleDat&);
void save(const char*, SaleDat&);
void load(const char*, vector<SaleDat>&);
void clear(const char*);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    const char *PATH = "salesdata.bin"; //CString containing the save path

    SaleDat north, east, south, west; //SaleDat objects
    vector<SaleDat> data; //Vector to read back data into
    //Set division names
    north.divName = "North";
    east.divName = "East";
    south.divName = "South";
    west.divName = "West";

    //Input Data
    clear(PATH); //Clear salesdata.bin
    cout << "INPUT QUARTERLY SALES DATA" << endl;
    getData(north); //Input data for north
    getData(east); //Input data for east
    getData(south); //Input data for south
    getData(west); //Input data for west
    cout << endl;

    //Write data to disk
    cout << "WRITING DATA TO " << PATH << "...";
    save(PATH, north); //Save north
    save(PATH, east); //Save east
    save(PATH, south); //Save south
    save(PATH, west); //Save west
    cout << "DONE!" << endl;

    //Read back data from disk
    cout << "READING FROM " << PATH << "...";
    load(PATH, data); //Load the written data
    cout << "DONE!" << endl;
    cout << endl;

    //Output Data vector
    for(int i = 0; i < data.size(); ++i){ //For the entire vector
        cout << "DIVISION: " << data[i].divName << endl; //Output the division name
        for(int j = 0; j < SaleDat::SIZE; ++j){ //For all the quarterly data
            cout << "SALES FOR Q" << j + 1 << ": $" << data[i].sales[j] << endl; //Output quarterly data
        }
    }

    //Exit
    return 0;
}

//Save
//Write a record to a file
//Input:
//path
//The path to the file to save to
//data
//The SaleDat object to create a record from

void save(const char *path, SaleDat &data){
    ofstream out; //The output file stream
    int len = data.divName.size() + 1; //The length of the division name for this record + a null terminator

    out.open(path, ios::binary | ios::app); //Open the file in binary mode and append the data to the end of the file
    out.write(reinterpret_cast<char*>(&len), sizeof (len)); //Write the length of the division name
    out.write(data.divName.c_str(), len); //Write the division name
    for(int i = 0; i < SaleDat::SIZE; ++i){ //For each quarter
        out.write(reinterpret_cast<char*>(&data.sales[i]), sizeof (data.sales[i])); //Write the sales data
    }
    out.close(); //Close the file
}

//Load
//Load SaleDat objects from a given file into a vector
//Input:
//path
//The path of the file to read from
//data
//The vector to load data into
//Output:
//The data vector filled with the records found in the given file

void load(const char *path, vector<SaleDat> &data){
    int size = 0; //The size of the file
    ifstream in; //The input file stream

    in.open(path, ios::binary); //Open the file in binary mode
    in.seekg(0, ios::end); //Seek to the end of the file
    size = in.tellg(); //Set the file size
    in.seekg(0, ios::beg); //Seek back to the beginning of the file
    while(in.tellg() < size){ //While the current position is less than the file size
        SaleDat tmp; //Temporary sales data
        int len = 0; //The length of the current record's name
        in.read(reinterpret_cast<char*>(&len), sizeof (len)); //Read the length
        char *buffer = new char[len]; //Create a new CString of len
        in.read(buffer, len); //Read in the the division name
        tmp.divName = buffer; //Set the division name to the buffer storage data
        delete [] buffer; //Release the buffer
        for(int i = 0; i < SaleDat::SIZE; ++i){ //For each quarter
            in.read(reinterpret_cast<char*>(&tmp.sales[i]), sizeof (tmp.sales[i])); //Read in sales data
        }
        data.push_back(tmp); //Push tmp to the data vector
    }
    in.close(); //Close the file
}

//Get Data
//Load sales data into a SaleDat object
//Input:
//data
//The object to load data into
//Output:
//The data object filled with data

void getData(SaleDat &data){
    cout << "DIVISION: " << data.divName << endl; //Output division name
    for(int i = 0; i < SaleDat::SIZE; ++i){ //For each quarter
        int input = 0; //The input value
        do{ //While input is less than 0
            cout << "ENTER SALES FOR Q" << i + 1 << ": $";
            cin >> input; //Read in input
        } while(input < 0);
        data.sales[i] = input; //Set the current quarter's data to the input
    }
}


//Clear
//Clear a file
//Input:
//path
//The file path to clear

void clear(const char *path){
    ofstream out; //The file output stream
    out.open(path, ios::trunc); //Open file in truncate mode
    out.close(); //Close file
}