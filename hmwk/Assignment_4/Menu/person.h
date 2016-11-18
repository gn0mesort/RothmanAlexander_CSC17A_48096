/*
 * File:   person.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a Person class which holds data about an individual person
 * Created on November 15, 2016
 */

#ifndef PERSON_H
#define PERSON_H

//System Libraries
#include <string> //Strings

//Person
//Holds data on a person including name, address, phone number, and age

class Person{
private:
    std::string _name; //The person's name
    std::string _addr; //The person's address
    std::string _tel; //The person's phone number
    unsigned char _age; //The person's age (assumes people probably won't be older than 255 years old)
public:

    //Person
    //Default Person constructor
    //Output:
    //A new person containing empty string fields and an age of 0

    Person(){
        _name = "";
        _addr = "";
        _tel = "";
        _age = 0;
    }

    //Person
    //Parameterized Person constructor. Requires at least a name
    //Input:
    //name
    //The person's name
    //addr
    //The person's address
    //tel
    //The person's phone number
    //age
    //The person's age
    //Output:
    //A Person object with the given values. Values not input will be defaulted

    Person(std::string name, std::string addr = "", std::string tel = "", unsigned char age = 0){
        _name = name;
        _addr = addr;
        _tel = tel;
        _age = age;
    }

    //name
    //Return the current value of _name
    //Output:
    //The value of _name

    std::string name() const{
        return _name;
    }

    //name
    //Set the value of _name
    //Input:
    //nName
    //The string to set _name to

    void name(std::string nName){
        _name = nName;
    }

    //address
    //Return the current value of _addr
    //Output:
    //The value of _addr

    std::string address() const{
        return _addr;
    }

    //address
    //Set the value of _addr
    //Input:
    //addr
    //The string to set _addr to

    void address(std::string addr){
        _addr = addr;
    }

    //telephone
    //Return the current value of _tel
    //Output:
    //The value of _tel

    std::string telephone() const{
        return _tel;
    }

    //telephone
    //Set the value of _tel
    //Input:
    //tel
    //The string to set _tel to

    void telephone(std::string tel){
        _tel = tel;
    }

    //age
    //Return the current value of _age
    //Output:
    //The value of _age

    unsigned char age() const{
        return _age;
    }

    //age
    //Set the value of _age
    //Input:
    //nAge
    //The value to set _age to

    void age(unsigned char nAge){
        _age = nAge;
    }
};


#endif /* PERSON_H */

