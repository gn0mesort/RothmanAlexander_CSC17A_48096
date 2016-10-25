/*
 * File:   BinArray.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 24, 2016
 */

#include "BinArray.h"

Flow::BinArray::BinArray(){
    _data = 0;
    _size = 0;
    _read = 0;
    _write = 0;
}

Flow::BinArray::BinArray(const BinArray &other){
    _data = new char[other.size()]{
    };
    _size = other.size();
    _read = 0;
    _write = 0;

    for(int i = 0; i < _size; ++i){
        _data[i] = other.get(i);
    }
}

Flow::BinArray::BinArray(const char *data, unsigned int size){
    _data = new char[size]{
    };
    _size = size;

    for(int i = 0; i < _size; ++i){
        _data[i] = data[i];
    }
}

Flow::BinArray::BinArray(int size){
    _data = new char[size]{
    };
    _size = size;
    _read = 0;
    _write = 0;
}

Flow::BinArray::~BinArray(){
    clear();
}

unsigned int Flow::BinArray::size() const{
    return _size;
}

unsigned int Flow::BinArray::tellg() const{
    return _read;
}

unsigned int Flow::BinArray::tellp() const{
    return _write;
}

void Flow::BinArray::seekg(unsigned int pos){
    _read = pos;
}

void Flow::BinArray::seekp(unsigned int pos){
    _write = pos;
}

char& Flow::BinArray::operator[](unsigned int index){
    return _data[index];
}

Flow::BinArray& Flow::BinArray::operator=(const BinArray &rhs){
    if(this != &rhs){
        clear();

        _data = new char[rhs.size()];
        _size = rhs.size();
        _read = 0;
        _write = 0;

        for(int i = 0; i < _size; ++i){
            _data[i] = rhs.get(i);
        }
    }
}

void Flow::BinArray::clear(){
    delete [] _data;
    _data = 0;
}

char Flow::BinArray::get(unsigned int index) const{
    return _data[index];
}

void Flow::BinArray::set(unsigned int index, char value){
    _data[index] = value;
}

Flow::BinArray& Flow::BinArray::operator<<(const Flow::BinArray &rhs){
    if(_write + rhs.size() < _size){
        for(unsigned int i = 0; i < rhs.size(); ++i){
            _data[_write + i] = rhs.get(i);
        }
        _write += rhs.size();
    }
    return *this;
}

Flow::BinArray& Flow::BinArray::operator>>(BinArray &rhs){
    if(_read + rhs.size() < _size){
        for(unsigned int i = 0; i < rhs.size(); ++i){
            rhs.set(i, _data[i]);
        }
        _read += rhs.size();
    }
    return *this;
}