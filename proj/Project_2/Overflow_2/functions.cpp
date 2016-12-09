/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   functions.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for functions.h
 * Created on December 5, 2016
 */

#include "functions.h"

/**
 * Read a text file and display it using cout
 * @param path The path of the file to read
 */
void Flow::rdTxt(const std::string &path){
    std::ifstream in; //Input stream

    in.open(path.c_str()); //Open the file
    if(in.good()){ //If the file is alright
        std::string str; //A temporary string value
        while(getline(in, str)){ //While there are more lines
            std::cout << str << std::endl; //Output the line
        }
    }
    else{ //Otherwise
        in.close(); //Close the file
        throw Error::FileException("File Not Found"); //Throw a FileException
    }
    in.close(); //Close the file
}

/**
 * Read a text file and use the data to construct a LinkedList
 * @param path The path of the file to read
 * @param data The LinkedList to fill with data
 */
void Flow::rdTxt(const std::string &path, Collections::LinkedList<std::string> &data){
    std::ifstream in; //The input stream

    in.open(path.c_str()); //Open the file
    if(in.good()){ //If the stream is good
        std::string str; //Create a temporary string
        while(getline(in, str)){ //Get every line from the file
            if(str[str.size() - 1] == '\r'){ //This is needed to clean Windows line endings
                //Windows ends lines with \r\n rather than just \n
                str.erase(str.end() - 1); //Clean line ending
            }
            if(!str.empty()){ //If the input is not an empty string
                data.addBack(str); //Add the input to the LinkedList
            }
        }
    }
    else{ //Otherwise
        in.close(); //Close the file
        throw Error::FileException("File Not Found"); //Throw a FileException
    }
    in.close(); //Close the file
}

/**
 * Do menu processing for a set of options
 * @param opts The options for this menu
 * @param perLine The number of options to display per line
 * @return A character representing the first character of a valid menu input. Always uppercase
 */
char Flow::menu(const Collections::LinkedList<std::string> &opts, int perLine){
    std::string input = ""; //The input string

    do{ //While the input is not valid
        for(int i = 0; i < opts.size(); ++i){ //Create the menu
            if(i % perLine != 0 && i != 0){ //Add spacing
                std::cout << "     ";
            }
            if(i % perLine == 0){ //Add line breaks
                std::cout << std::endl;
            }
            std::cout << formatOption(opts[i]) << " "; //Output options
        }
        std::cout << std::endl << "> "; //Output prompt
        getline(std::cin, input); //Get the input
    } while(!isValid(opts, input[0]));

    return std::toupper(input[0]);
}

/**
 * Check that a file is valid
 * @param path The path of the file to check
 * @param header The header value to check for
 * @return true if the file is valid. Otherwise false
 */
bool Flow::checkFile(const std::string &path, const int header){
    bool r = false; //The return value
    int number = 0; //The header value read from the file
    std::ifstream in; //An input stream

    in.open(path.c_str(), std::ios::binary); //Open the file in binary mode
    if(in.is_open()){ //If the file opened
        in.read(to_bin(number), sizeof (number)); //Read the header value
    }
    r = in.is_open() && number == header; //Return whether or not the file opened and whether or not the header
    //was correct
    in.close(); //Close the file

    return r;
}

/**
 * Format an option by wrapping it in ()
 * @param option The option to format
 * @return The input option with () wrapped around the first character
 */
std::string Flow::formatOption(const std::string &option){
    std::string r = option;

    r.insert(0, 1, '(');
    r.insert(2, 1, ')');

    return r;
}

/**
 * Format an option by wrapping it in ()
 * @param option The option to format
 * @return The input option with () wrapped around the value
 */
std::string Flow::formatOption(int option){
    std::stringstream r;

    r << '(' << option << ')';

    return r.str();
}

/**
 * Check if an option is valid for a menu
 * @param options The menu options to check
 * @param key The input value to check
 * @return true if the key was found in options. Otherwise false
 */
bool Flow::isValid(const Collections::LinkedList<std::string> &options, char key){
    for(int i = 0; i < options.size(); ++i){ //For every option
        if(std::toupper(options[i][0]) == std::toupper(key)){ //Check the option's first char against the the key
            return true; //If they match return true
        }
    }
}

/**
 * Menu handling for menus that should return int values
 * @param opts The options for the menu
 * @param perLine The number of options to display per line
 * @return An int value indicating the selected option
 */
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
