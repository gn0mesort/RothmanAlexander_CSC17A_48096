/*
 * File:   stringext.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for stringext.h
 * Created on November 22, 2016
 */

#include "stringext.h"

/**
 * Convert a string to upper case characters
 * @param str The string to convert
 * @return The value of str with all the alphabetic characters set to upper case
 */
std::string toupper(const std::string &str){
    std::string r = "";

    for(int i = 0; i < str.size(); ++i){
        r += toupper(str[i]);
    }

    return r;
}

/**
 * Convert a string to lower case characters
 * @param str The string to convert
 * @return The value of str with all the alphabetic characters set to lower case
 */
std::string tolower(const std::string &str){
    std::string r = "";

    for(int i = 0; i < str.size(); ++i){
        r += tolower(str[i]);
    }

    return r;
}

/**
 * Write a string to an output file stream as binary data
 * @param str The string to write
 * @param out The stream to output to
 */
void writeBinary(const std::string &str, std::ofstream &out){
    int length = str.size() + 1; //Calculate binary length

    out.write(to_bin(length), sizeof (length)); //Write the length
    out.write(str.c_str(), length); //Write the string
}

/**
 * Read a string from an input file stream as binary data
 * @param in The input stream
 * @return The string resulting from the binary data read from the stream
 */
std::string readBinary(std::ifstream &in){
    int length = 0; //The length of the string
    char *buffer = 0; //The char* buffer for the string
    std::string r = ""; //The return string

    in.read(to_bin(length), sizeof (length)); //Read the length
    buffer = new char[length]; //Allocate the buffer
    in.read(buffer, length); //Read the string
    r = buffer; //Copy from the buffer to the return value
    delete buffer; //Clear the buffer
    buffer = 0; //Set buffer to 0

    return r;
}