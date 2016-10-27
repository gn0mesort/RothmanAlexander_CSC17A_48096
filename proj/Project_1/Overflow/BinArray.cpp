/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   BinArray.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for BinArray.h
 * Created on October 24, 2016
 */

#include "BinArray.h"

//BinArray
//The default BinArray constructor

Flow::BinArray::BinArray(){
    _data = 0; //A NULL pointer not integer 0
    _size = 0;
    _read = 0;
    _write = 0;
}

//BinArray
//The copy constructor for a BinArray

Flow::BinArray::BinArray(const BinArray &other){
    _data = new char[other.size()]{
    }; //Allocate and 0 initialize a new data array
    _size = other.size(); //Copy the size
    _read = 0; //Set the read head to 0
    _write = 0; //Set the write head to 0

    for(int i = 0; i < _size; ++i){ //For the entire data array
        _data[i] = other.get(i); //Copy the value at i from other._data to _data
    }
}

//BinArray
//Parameterized BinArray constructor

Flow::BinArray::BinArray(const char *data, unsigned int size){
    _data = new char[size]{
    }; //Allocate and 0 initialize a new data array
    _size = size; //Set the size to the input size
    _read = 0;
    _write = 0;

    for(int i = 0; i < _size; ++i){ //Copy data from the input array to the data array
        _data[i] = data[i];
    }
}

//BinArray
//Parameterized BinArray constructor

Flow::BinArray::BinArray(int size){
    _data = new char[size]{
    }; //Allocate and 0 initialize a new data array
    _size = size; //Set the size of the array to the input
    _read = 0;
    _write = 0;
}

//~BinArray
//BinArray destructor

Flow::BinArray::~BinArray(){
    clear(); //Clear the BinArray memory
}

//size
//Return the size of the BinArray
//Output:
//The value of _size

unsigned int Flow::BinArray::size() const{
    return _size;
}

//tellg
//Return the current position of the read head
//Output:
//The value of _read

unsigned int Flow::BinArray::tellg() const{
    return _read;
}

//tellp
//Return the current position of the write head
//Output:
//The value of _write

unsigned int Flow::BinArray::tellp() const{
    return _write;
}

//seekg
//Move the read head to the correct position
//Input:
//pos
//The position to seek to

void Flow::BinArray::seekg(unsigned int pos){
    _read = pos;
}

//seekp
//Move the write head to the correct position
//Input:
//pos
//The position to seek to

void Flow::BinArray::seekp(unsigned int pos){
    _write = pos;
}

//[]
//BinArray index operator
//Input:
//index
//The index to return the value of
//Output:
//A reference to the char at the position of index in the _data array

char& Flow::BinArray::operator[](unsigned int index){
    return _data[index];
}

//=
//BinArray copy assignment operator
//Input:
//rhs
//The BinArray on the right of the operator
//Output:
//A reference to this BinArray

Flow::BinArray& Flow::BinArray::operator=(const BinArray &rhs){
    if(this != &rhs){ //Check for self assignment
        clear(); //Clear old data

        _data = new char[rhs.size()]; //Allocate new data
        _size = rhs.size(); //Copy size
        _read = 0; //Reset read
        _write = 0; //Reset write

        for(int i = 0; i < _size; ++i){ //Copy array values
            _data[i] = rhs.get(i);
        }
    }
}

//clear
//Private function for clearing array memories

void Flow::BinArray::clear(){
    delete [] _data; //Release _data
    _data = 0; //0 the pointer
}

//get
//Return the char at the given index
//Input:
//index
//The index to return the value of
//Output:
//The value at the given index

char Flow::BinArray::get(unsigned int index) const{
    return _data[index];
}

//set
//Set the value at the index to the given value
//Input:
//index
//The index to set the value of
//value
//The value to set the data at index to

void Flow::BinArray::set(unsigned int index, char value){
    _data[index] = value;
}

//<<
//Insertion operator for BinArrays
//Input:
//rhs
//The input on the right hand side of the operator
//Output:
//A reference to this BinArray

Flow::BinArray& Flow::BinArray::operator<<(const Flow::BinArray &rhs){
    if(_write + rhs.size() - 1 < _size){ //If the write wouldn't go out of bounds
        for(unsigned int i = 0; i < rhs.size(); ++i){ //Write the data from rhs to _data
            _data[_write + i] = rhs.get(i);
        }
        _write += rhs.size(); //Set the write head
    }
    return *this;
}

//>>
//Extraction operator for BinArrays
//Input:
//rhs
//The BinArray on the right hand side of the operator
//Output:
//A reference to this BinArray

Flow::BinArray& Flow::BinArray::operator>>(BinArray &rhs){
    if(_read + rhs.size() - 1 < _size){ //If the read wouldn't go out of bounds
        for(unsigned int i = 0; i < rhs.size(); ++i){ //Read the data from _data to rhs
            rhs.set(i, _data[_read + i]);
        }
        _read += rhs.size(); //Set the read head
    }
    return *this;
}

//write
//Write data to a file stream from this BinArray. Allows writing without giving undue access to _data pointer
//Input:
//out
//An opened fstream object to write to

void Flow::BinArray::write(std::fstream &out){
    if(out.is_open()){ //Check if opened
        out.write(_data, _size); //Write data
    }
}

//read
//Read data from a file stream to this BinArray. Allows reading without giving undue access to _data pointer
//Input:
//in
//An opened fstream object to read from

void Flow::BinArray::read(std::fstream &in){
    if(in.is_open()){ //Check if opened
        in.read(_data, _size); //Read data
    }
}

//toBin
//Convert a string to a BinArray
//Input:
//str
//A string to convert
//Output:
//A binary array containing the length of the string (4 bytes) and the string data (str.size() + 1 bytes)

Flow::BinArray Flow::toBin(const std::string &str){
    unsigned int strSize = str.size() + 1; //Calculate binary size of the string
    BinArray r(sizeof (strSize) + strSize); //Allocate the BinArray

    r << BinArray(reinterpret_cast<char*>(&strSize), sizeof (strSize)); //insert the integer size
    r << BinArray(str.c_str(), strSize); //insert the string

    return r;
}

//toStr
//Convert a BinArray to a string
//Input:
//data
//The binary data to create the string from
//Output:
//The string representation of the data object

std::string Flow::toStr(BinArray &data){
    std::string r = ""; //The return string
    data.seekg(sizeof (unsigned int)); //seek over the size of the string
    while(data[data.tellg()] != '\0'){ //Read until the null terminator
        r += data[data.tellg()]; //Concatinate each character into the string
        data.seekg(data.tellg() + 1); //Seek the read head one byte
    }

    return r;
}

//toInt
//Convert a BinArray to an unsigned int
//Input:
//data
//The binary data to create the unsigned int from
//Output:
//An unsigned int formed from the input data

unsigned int Flow::toInt(BinArray &data){
    unsigned int r = 0; //The return value
    char *buffer = new char[sizeof (r)]; //A buffer to covert from

    for(int i = 0; i < sizeof (r); ++i){ //Copy from the data BinArray to the buffer
        buffer[i] = data[i];
    }
    r = *reinterpret_cast<unsigned int*>(buffer); //Convert the buffer to a unsigned int

    //Clean up the buffer
    delete [] buffer;
    buffer = 0;

    return r;
}