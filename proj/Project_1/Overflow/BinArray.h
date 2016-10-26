/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   BinArray.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a class for quickly reading and writing binary data based on objects
 * Created on October 24, 2016
 */

#ifndef BINARRAY_H
#define BINARRAY_H

#include <fstream>

namespace Flow{
    //BinArray
    //A class for holding binary data. Defines the basic array, its size, as well as read and write positions.
    class BinArray{
    private:
        unsigned int _size; //The size of the Array
        unsigned int _read;
        unsigned int _write;
        char *_data;
        
        void clear();
    public:
        BinArray();
        BinArray(const BinArray&);
        BinArray(int);
        BinArray(const char*, unsigned int);
        ~BinArray();
        void read(std::fstream&);
        void seekg(unsigned int);
        void seekp(unsigned int);
        void set(unsigned int, char);
        void write(std::fstream&);
        char get(unsigned int) const;
        unsigned int size() const;
        unsigned int tellg() const;
        unsigned int tellp() const;
        
        //Operator Overloads
        char& operator[](unsigned int);
        BinArray& operator=(const BinArray&);
        BinArray& operator<<(const BinArray&);
        BinArray& operator>>(BinArray&);     
    };
    
    //Function Prototypes
    unsigned int toInt(BinArray&);
    std::string toStr(BinArray&);
    BinArray toBin(const std::string&);
   
}

#endif /* BINARRAY_H */

