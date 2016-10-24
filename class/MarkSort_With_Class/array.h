/* 
 * File:   array.h
 * Author: rcc
 * Purpose: Dynamically allocate and clean up array
 * Created on October 24, 2016
 */

#ifndef ARRAY_H
#define ARRAY_H

class Array{
private:
    int _size;
    int *_data;
public:
    Array(int);
    Array(const Array&);
    ~Array(){
        delete [] _data;
    }
    int get(int) const;
    void set(int, int);
    int size() const;
    void fillRand();
    void print(int = 10) const;
    void sort();
};

#endif /* ARRAY_H */

