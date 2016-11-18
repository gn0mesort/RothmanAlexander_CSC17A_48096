/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate the Person class
 * Created on November 15, 2016
 */

//System Libraries
#include <iostream> //I/O

//User Libraries
#include "person.h" //Person objects
using namespace std;

//Function Prototypes
int toInt(unsigned char);

//Begin Execution

int main(int argc, char** argv){
    const unsigned char SIZE = 3; //The number of people to create
    Person people[SIZE]; //Array of Person objects

    //Set Person objects
    people[0] = Person("Alexander Rothman", "123 Somewhere Pl.", "123-456-7890", 24);
    people[1] = Person("Jeff Jefferson", "456 Elsewhere Ct.", "456-789-0123", 57);
    people[2] = Person("Geoff Jefferson", "789 Yetanother Rd.", "789-012-3456", 57);

    //Output Data
    cout << "PEOPLE:" << endl;
    for(int i = 0; i < SIZE; ++i){ //For every Person object
        cout << "NAME: " << people[i].name() << endl; //Output name
        cout << "ADDRESS: " << people[i].address() << endl; //Output address
        cout << "TELEPHONE: " << people[i].telephone() << endl; //Output phone number
        cout << "AGE: " << toInt(people[i].age()) << endl; //Output age
        cout << endl;
    }

    //Exit
    return 0;
}

//toInt
//Convert a character to an integer
//Input:
//c
//A character to convert
//Output:
//A int value equal to c

int toInt(unsigned char c){
    return static_cast<int>(c);
}