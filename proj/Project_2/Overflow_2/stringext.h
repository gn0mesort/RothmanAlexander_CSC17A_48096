/*
 * File:   stringext.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Defines string utility functions
 * Created on November 22, 2016
 */

#ifndef STRINGEXT_H
#define STRINGEXT_H

//System Libraries
#include <string> //Strings
#include <fstream> //File I/O

//User Libraries
#include "macros.h" //Preprocessor macros

std::string toupper(const std::string&);
std::string tolower(const std::string&);
void writeBinary(const std::string&, std::ofstream&);
std::string readBinary(std::ifstream&);

#endif /* STRINGEXT_H */

