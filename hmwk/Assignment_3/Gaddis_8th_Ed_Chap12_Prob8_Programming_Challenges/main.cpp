/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Allocate a dynamic array and write the array to the disk
 * Created on October 16, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <fstream> //File I/O
using namespace std;

//Function Prototypes
void toFile(const char*, int*, int);
void toArray(const char*, int*, int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    const char *OUTPATH = "out_12_8.dat"; //The output path

    int *array = NULL; //The array to read data into
    unsigned int size; //The size of the array

    //Input
    cout << "ENTER THE SIZE OF THE ARRAY TO ALLOCATE: ";
    cin >> size; //Read in size
    array = new int[size]; //Allocate an array of the input size
    for(int i = 0; i < size; ++i){ //For every element of the array
        cout << "ENTER THE VALUE FOR ARRAY[" << i << "]: ";
        cin >> array[i]; //Read in array[i]
    }
    cout << endl;

    //Write array to disk
    cout << "WRITING ARRAY TO DISK...";
    toFile(OUTPATH, array, size); //Write the array to a file
    for(int i = 0; i < size; ++i){ //Clear the array
        array[i] = 0;
    }
    cout << "DONE!" << endl;

    //Read data back from disk
    cout << "READING ARRAY FROM DISK...";
    toArray(OUTPATH, array, size); //Read the file into the array
    cout << "DONE!" << endl;
    cout << endl;
    for(int i = 0; i < size; ++i){ //Output the array again
        cout << "ARRAY[" << i << "]: " << array[i] << endl;
    }

    //Delete the array
    delete [] array;

    //Exit
    return 0;
}

//To File
//Write an array to a file
//Input:
//path
//The path to write to
//array
//The array to get data from
//size
//The size of the array

void toFile(const char *path, int *array, int size){
    ofstream out; //The output file stream

    out.open(path, ios::binary); //Open the file in binary mode
    for(int i = 0; i < size; ++i){ //For each element of the array
        out.write(reinterpret_cast<char*>(&array[i]), sizeof (array[i])); //Write the value of the current element to the disk
    }
    out.close(); //Close the file
}


///To Array
//Read a file into an array
//Input:
//path
//The path to read from
//array
//The array to read data into
//size
//The size of the array
//Output:
//The array filled with data from the file

void toArray(const char *path, int *array, int size){
    ifstream in; //The input file stream

    in.open(path, ios::binary); //Open the file in binary mode
    for(int i = 0; i < size; ++i){ //For every element of the array
        in.read(reinterpret_cast<char*>(&array[i]), sizeof (array[i])); //Read the value into the current element
    }
    in.close(); //Close the file
}