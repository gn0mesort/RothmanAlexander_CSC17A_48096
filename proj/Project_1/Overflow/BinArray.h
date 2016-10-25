/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BinArray.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 24, 2016
 */

#ifndef BINARRAY_H
#define BINARRAY_H

namespace Flow{
    class BinArray{
    private:
        char *_data;
        unsigned int _size;
        unsigned int _read;
        unsigned int _write;
        void clear();
    public:
        BinArray();
        BinArray(const BinArray&);
        BinArray(const char*, unsigned int);
        BinArray(int);
        ~BinArray();
        unsigned int size() const;
        BinArray& operator=(const BinArray&);
        char get(unsigned int) const;
        void set(unsigned int, char);
        char& operator[](unsigned int);
        unsigned int tellp() const;
        unsigned int tellg() const;
        void seekp(unsigned int);
        void seekg(unsigned int);
        BinArray& operator<<(const BinArray&);
        BinArray& operator>>(BinArray&);
    };
}

#endif /* BINARRAY_H */

