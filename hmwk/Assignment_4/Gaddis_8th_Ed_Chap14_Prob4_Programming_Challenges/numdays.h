/*
 * File:   numdays.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a class for measuring days worked by 8 hour work days
 * Created on November 16, 2016
 */

#ifndef NUMDAYS_H
#define NUMDAYS_H

//NumDays
//Class describing a number of days worked by an employee

class NumDays{
private:
    unsigned int _hours; //The number of hours worked
public:

    //NumDays
    //Default constructor
    //Output:
    //A NumDays object with a value of 0

    NumDays(){
        _hours = 0;
    }

    //NumDays
    //Parameterized constructor
    //Input:
    //hours
    //The number of hours worked
    //Output:
    //A new NumDays object with the given value

    NumDays(unsigned int hours){
        _hours = hours;
    }

    //hours
    //Return the number of hours in this object
    //Output:
    //The current number of hours worked

    unsigned int hours() const{
        return _hours;
    }

    //hours
    //Set the number of hours in this object
    //Input:
    //nHours
    //The number of hours to set this object to

    void hours(unsigned int nHours){
        _hours = nHours;
    }

    //days
    //Return the number of days worked
    //Output:
    //The number of hours / 8

    float days(){
        return _hours / 8.0f;
    }

    //days
    //Set the number of hours worked based on a input number of days
    //Input:
    //nDays
    //The number of days worked

    void days(float nDays){
        _hours = nDays * 8.0f;
    }

    //+ (binary)
    //Add two NumDays objects
    //Input:
    //rhs
    //The NumDays to add to this one
    //Output:
    //A new NumDays object with its hours set the sum of the input hours

    NumDays operator+(const NumDays &rhs){
        return NumDays(_hours + rhs.hours());
    }

    //- (binary)
    //Subtract two NumDays objects
    //Input:
    //rhs
    //The NumDays to subtract from this one
    //Output:
    //A new NumDays object with its hours set to the difference of the input hours

    NumDays operator-(const NumDays &rhs){
        return NumDays(_hours - rhs.hours());
    }

    //++ (prefix)
    //Increment this object and return it
    //Output:
    //This object with the hours incremented

    NumDays& operator++(){
        ++_hours;
        return *this;
    }

    //-- (prefix)
    //Decrement this object and return it
    //Output:
    //This object with the hours decremented

    NumDays& operator--(){
        --_hours;
        return *this;
    }

    //++ (postfix)
    //Increment this object and return a copy from before it was incremented
    //Input:
    //x
    //A dummy value
    //Output:
    //A copy of the object before incrementing

    NumDays operator++(int x){
        NumDays r = *this;
        ++_hours;
        return r;
    }

    //-- (postfix)
    //Decrement this object and return a copy from before it was Decremented
    //Input:
    //x
    //A dummy value
    //Output:
    //A copy of the object before Decrementing

    NumDays operator--(int x){
        NumDays r = *this;
        --_hours;
        return r;
    }


};

#endif /* NUMDAYS_H */

