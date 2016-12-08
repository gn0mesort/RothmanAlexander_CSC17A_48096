/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   functions.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 5, 2016
 */

#include "functions.h"

void Flow::rdTxt(const std::string &path){
    std::ifstream in;

    in.open(path.c_str());
    if(in.good()){
        std::string str;
        while(getline(in, str)){
            std::cout << str << std::endl;
        }
    }
    else{
        in.close();
        throw Error::FileException("File Not Found");
    }
    in.close();
}

void Flow::rdTxt(const std::string &path, Collections::LinkedList<std::string> &data){
    std::ifstream in;

    in.open(path.c_str());
    if(in.good()){
        std::string str;
        while(getline(in, str)){
            if(str[str.size() - 1] == '\r'){ //This is needed to clean Windows line endings
                //Windows ends lines with \r\n rather than just \n
                str.erase(str.end() - 1); //Clean line ending
            }
            if(!str.empty()){ //If the input is not an empty string
                data.addBack(str); //Add the input to the vector
            }
        }
    }
    else{
        in.close();
        throw Error::FileException("File Not Found");
    }
    in.close();
}

char Flow::menu(const Collections::LinkedList<std::string> &opts, int perLine){
    std::string input = "";

    do{
        for(int i = 0; i < opts.size(); ++i){
            if(i % perLine != 0 && i != 0){
                std::cout << "     ";
            }
            if(i % perLine == 0){
                std::cout << std::endl;
            }
            std::cout << formatOption(opts[i]) << " ";
        }
        std::cout << std::endl << "> ";
        getline(std::cin, input);
    } while(!isValid(opts, input[0]));

    return std::toupper(input[0]);
}

bool Flow::checkFile(const std::string &path, const int header){
    bool r = false;
    int number = 0;
    std::ifstream in;

    in.open(path.c_str(), std::ios::binary);
    if(in.is_open()){
        in.read(to_bin(number), sizeof (number));
    }
    r = in.is_open() && number == header;
    in.close();

    return r;
}

std::string Flow::formatOption(const std::string &option){
    std::string r = option;

    r.insert(0, 1, '(');
    r.insert(2, 1, ')');

    return r;
}

std::string Flow::formatOption(int option){
    std::stringstream r;

    r << '(' << option << ')';

    return r.str();
}

bool Flow::isValid(const Collections::LinkedList<std::string> &options, char key){
    for(int i = 0; i < options.size(); ++i){ //For every option
        if(std::toupper(options[i][0]) == std::toupper(key)){ //Check the option's first char against the the key
            return true; //If they match return true
        }
    }
}

int Flow::intMenu(const Collections::LinkedList<std::string> &opts, int perLine){
    int r = 0; //The return value
    std::string input = ""; //Input string

    do{ //While r is within the bounds of the options
        std::stringstream convert; //Conversion stringstream
        for(int i = 0; i < opts.size(); ++i){ //Display the menu
            if(i % perLine != 0 && i != 0){ //Insert spacing
                std::cout << "     ";
            }
            if(i % perLine == 0){ //Insert line breaks
                std::cout << std::endl;
            }
            if(i + 1 < opts.size()){ //Display options
                std::cout << formatOption(i + 1) << " " << opts[i];
            }
            else{ //Display final 0 option
                std::cout << formatOption(0) << " " << opts[i];
            }
        }
        std::cout << std::endl << "> "; //Display prompt
        std::getline(std::cin, input); //Get input
        convert << input; //insert input into stream
        convert >> r; //Convert input to int
    } while(r < 0 || r > opts.size() + 1);

    return r;
}
