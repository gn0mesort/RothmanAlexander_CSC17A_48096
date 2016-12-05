/*
 * File:   stringext.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose: Defines string utility functions
 * Created on November 22, 2016
 */

#ifndef STRINGEXT_H
#define STRINGEXT_H

#include <string>
#include <fstream>

#include "macros.h"

std::string toupper(const std::string&);
std::string tolower(const std::string&);
void writeBinary(const std::string&, std::ofstream&);
std::string readBinary(std::ifstream&);

#endif /* STRINGEXT_H */

