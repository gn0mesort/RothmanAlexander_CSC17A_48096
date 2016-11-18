/*
 * File:   month.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a month object
 * Created on November 16, 2016
 */

#ifndef MONTH_H
#define MONTH_H

//System Libraries
#include <string> //Strings
#include <iostream> //I/O

//Month
//A class to represent one month out of the year. The month will wrap around if it exceeds December/January (depending on direction)

class Month{
private:
    static const unsigned char MONTHS = 12; //The number of months
    static std::string _names[MONTHS]; //The names of the months
    unsigned char _num; //The actual underlying month number
public:

    //Month
    //Default Constructor
    //Output:
    //A new Month object set to January

    Month(){
        _num = 1;
    }

    //Month
    //Parameterized Constructor
    //Input:
    //num
    //The number of the month for this object to be set to
    //Output:
    //A Month representing the input month number

    Month(unsigned char num){
        _num = num % 12;
    }

    //Month
    //Parameterized Constructor
    //Input:
    //name
    //The name of a month to set this object to
    //Output:
    //A Month representing the input month name

    Month(std::string name){
        _num = parse(name);
    }

    //value
    //Returns the Month as an integer
    //Output:
    //The current Month value

    unsigned char value() const{
        return _num;
    }

    //value
    //Set the Month using an integer
    //Input:
    //num
    //A value between 0 and 255 representing the current month

    void value(unsigned char num){
        _num = num % 12;
    }

    //name
    //Return the current Month name
    //Output:
    //The name of the Month

    std::string name() const{
        return _names[_num];
    }

    //name
    //Set the Month by name
    //Input:
    //name
    //The name of the Month to set this object to

    void name(std::string name){
        _num = parse(name);
    }

    unsigned char parse(std::string) const;

    //++ (prefix)
    //Increment the month
    //Output:
    //this month after being incremented

    Month& operator++(){
        _num = (_num + 1) % 12;

        return *this;
    }

    Month& operator--();

    //++ (postfix)
    //Increment this Month then return a copy before it was incremented
    //Input:
    //x
    //A dummy value
    //Output:
    //A copy of this before being incremented

    Month operator++(int x){
        Month r = *this;

        ++(*this);

        return r;
    }

    //-- (postfix)
    //Decrement this Month then return a copy before it was decremented
    //Input:
    //x
    //A dummy value
    //Output:
    //A copy of this before being decremented

    Month operator--(int x){
        Month r = *this;

        --(*this);

        return r;
    }

    friend std::istream& operator>>(std::istream&, Month&);
    friend std::ostream& operator<<(std::ostream&, const Month&);
};

std::istream& operator>>(std::istream &, Month&);
std::ostream& operator<<(std::ostream&, const Month&);

#endif /* MONTH_H */

