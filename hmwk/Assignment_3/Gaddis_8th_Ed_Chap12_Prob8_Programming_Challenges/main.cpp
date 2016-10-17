/*
 * File:   main.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 16, 2016
 */

#include <iostream>
#include <fstream>
using namespace std;

void toFile(const char*, int*, int);
void toArray(const char*, int*, int);

int main(int argc, char** argv){
    const char *OUTPATH = "out.dat";
    int *array = NULL;
    unsigned int size;

    cout << "ENTER THE SIZE OF THE ARRAY TO ALLOCATE: ";
    cin >> size;
    array = new int[size];
    for(int i = 0; i < size; ++i){
        cout << "ENTER THE VALUE FOR ARRAY[" << i << "]: ";
        cin >> array[i];
    }
    cout << endl;
    cout << "WRITING ARRAY TO DISK...";
    toFile(OUTPATH, array, size);
    for(int i = 0; i < size; ++i){
        array[i] = 0;
    }
    cout << "DONE!" << endl;
    cout << "READING ARRAY FROM DISK...";
    toArray(OUTPATH, array, size);
    cout << "DONE!" << endl;
    cout << endl;
    for(int i = 0; i < size; ++i){
        cout << "ARRAY[" << i << "]: " << array[i] << endl;
    }

    delete [] array;

    return 0;
}

void toFile(const char *path, int *array, int size){
    ofstream out;

    out.open(path, ios::binary);
    for(int i = 0; i < size; ++i){
        out.write(reinterpret_cast<char*>(&array[i]), sizeof (array[i]));
    }
    out.close();
}

void toArray(const char *path, int *array, int size){
    ifstream in;

    in.open(path, ios::binary);
    for(int i = 0; i < size; ++i){
        in.read(reinterpret_cast<char*>(&array[i]), sizeof (array[i]));
    }
    in.close();
}