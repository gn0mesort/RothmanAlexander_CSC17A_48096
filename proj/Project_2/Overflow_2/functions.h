/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   functions.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 5, 2016
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>
#include <fstream>

#include "collections.h"
#include "enums.h"
#include "stringext.h"
#include "flags.h"
#include "structs.h"

namespace Flow{
    void rdTxt(const std::string&);
    void rdTxt(const std::string&, Collections::LinkedList<std::string>&);
    char menu(const Collections::LinkedList<std::string>&, int = 10);
    Config loadConfig(const std::string&);
    void saveConfig(const std::string&, Config);
    bool checkFile(const std::string&, const int);
    bool isValid(const Collections::LinkedList<std::string>&, char);
    int intMenu(const Collections::LinkedList<std::string>&, int = 10);
    std::string formatOption(int);
    std::string formatOption(const std::string&);
}

#endif /* FUNCTIONS_H */

