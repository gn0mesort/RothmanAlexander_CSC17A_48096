/*
 * File:   sortablevector.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a sortable vector
 * Created on November 28, 2016
 */

#ifndef SORTABLEVECTOR_H
#define SORTABLEVECTOR_H

//System Libraries
#include <algorithm> //Standard algorithms (for sort)
#include <vector> //Vectors

//User Libraries
#include "SimpleVector.h" //SimpleVector objects

/**
 * Defines a SimpleVector with a sort() function. The vector will hold data of the type T
 */
template<typename T>
class SortableVector : public SimpleVector<T>{
private:
public:
    SortableVector();
    SortableVector(int);
    SortableVector(const SortableVector&);
    void sort();
};

/**
 * Default constructor.
 */
template<typename T>
SortableVector<T>::SortableVector(){ }

/**
 * Parameterized constructor. Defines the size of the vector
 * @param size The size of the vector to construct
 */
template<typename T>
SortableVector<T>::SortableVector(int size) : SimpleVector<T>(size){ }

/**
 * Copy constructor.
 * @param other The other vector to copy
 */
template<typename T>
SortableVector<T>::SortableVector(const SortableVector &other) : SimpleVector<T>(other){ }

/**
 * Sorts the vector by copying it into a std::vector and sorting it. Then copies the data back out
 */
template<typename T>
void SortableVector<T>::sort(){
    std::vector<T> sorter; //A std::vector to hold sorting data

    for(int i = 0; i < SimpleVector<T>::size(); ++i){ //Copy
        sorter.push_back((*this)[i]);
    }

    std::sort(sorter.begin(), sorter.end()); //Sort the data

    for(int i = 0; i < SimpleVector<T>::size(); ++i){ //Copy data back
        (*this)[i] = sorter[i];
    }
}

#endif /* SORTABLEVECTOR_H */

