/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   functions.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define loose functions for Overflow
 * Created on December 5, 2016
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

//System Libraries
#include <string> //Strings
#include <iostream> //I/O
#include <fstream> //File I/O

//User Libraries
#include "collections.h" //LinkedLists
#include "enums.h" //Enumeration types
#include "stringext.h" //String extensions
#include "flags.h" //Flag constants
#include "structs.h" //Game structs

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

