/*
 * File:   absolutevalue.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a templated absolute value function
 * Created on November 28, 2016
 */

#ifndef ABSOLUTEVALUE_H
#define ABSOLUTEVALUE_H

/**
 * Calculate the absolute value of a number
 * @param value The value to calculate the absolute value of
 * @return The absolute value of the input number
 */
template<typename T>
T abs(T value){
    if(value < 0){ //If the value if less than 0
        return -value; //Flip the sign (or just take the two's complement of it)
    }
    return value; //Otherwise return the number as is
}


#endif /* ABSOLUTEVALUE_H */

