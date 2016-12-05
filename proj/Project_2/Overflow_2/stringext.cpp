/*
 * File:   stringext.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose: Source file for stringext.h
 * Created on November 22, 2016
 */

#include <fstream>

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

void writeBinary(const std::string &str, std::ofstream &out){
    int length = str.size() + 1;

    out.write(to_bin(length), sizeof (length));
    out.write(str.c_str(), length);
}

std::string readBinary(std::ifstream &in){
    int length = 0;
    char *buffer = 0;
    std::string r = "";

    in.read(to_bin(length), sizeof (length));
    buffer = new char[length];
    in.read(buffer, length);
    r = buffer;
    delete buffer;
    buffer = 0;

    return r;
}