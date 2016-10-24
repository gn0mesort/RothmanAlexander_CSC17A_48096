#include <iostream>
#include "array.h"

Array::Array(int size){
    if(size > 0){
        _data = new int[size];
        _size = size;
    }
}

Array::Array(const Array &other){
    _data = new int[other.size()];
    _size = other.size();
    for(int i = 0; i < _size; ++i){
        _data[i] = other.get(i);
    }
}

int Array::get(int index) const{
    return _data[index];
}
void Array::set(int index, int value){
    _data[index] = value;
}

int Array::size() const{
    return _size;
}

void Array::fillRand(){
    for(int i = 0; i < _size; ++i){
        _data[i] = rand() % 90 + 10;
    }
}

void Array::print(int perLine) const{
    for(int i = 0; i < _size; ++i){
        std::cout << _data[i] << " ";
        if(i % perLine == perLine - 1) { std::cout << std::endl; }
    }
    std::cout << std::endl;
}

void Array::sort(){
        for(int i = 0; i < _size - 1; ++i){
        for(int j = i + 1; j < _size; ++j){
            if(_data[i] > _data[j]){
                _data[i] = _data[i] ^ _data[j];
                _data[j] = _data[i] ^ _data[j];
                _data[i] = _data[i] ^ _data[j];
            }
        }
    }
}


