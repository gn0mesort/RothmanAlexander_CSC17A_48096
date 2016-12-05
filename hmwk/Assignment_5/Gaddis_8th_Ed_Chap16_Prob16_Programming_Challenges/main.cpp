/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate ProductionWorker
 * Created on November 28, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <cstdlib> //C Standard Library
#include <ctime> //Time

//User Libraries
#include "employee.h" //Employee and ProductionWorker objects
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    ProductionWorker worker; //Create a production worker for use

    srand(static_cast<int>(time(0))); //Seed PRNG

    //Set worker data
    worker.name("Canberra Montgomery"); //Set name
    worker.number((rand() % 8999) + 1000); //Set number between 1000 and 9999
    time_t date; //Create a date object
    time(&date); //Fill date
    worker.hireDate(asctime(localtime(&date))); //Set hire date based on date
    worker.pay((rand() % 9899) + 100); //Set pay between $1.00 and $99.99
    worker.shift((rand() % 2) + 1); //Set shift between 1 and 2

    //Deliberately generate erros
    try{ //Try setting ID number
        cout << "SETTING INVALID ID NUMBER...";
        worker.number(10000); //Set ID to 10000
    }
    catch(Employee::InvalidEmployeeNumber e){ //Catch invalid numbers
        cerr << "INVALID EMPLOYEE NUMBER!" << endl;
    }
    try{ //Try setting shift
        cout << "SETTING INVALID SHIFT...";
        worker.shift(27); //Set shift to 27
    }
    catch(ProductionWorker::InvalidShift e){ //Catch invalid shifts
        cerr << "INVALID SHIFT!" << endl;
    }
    try{ //Try setting pay
        cout << "SETTING INVALID PAY RATE...";
        worker.pay(0); //Set pay to 0
    }
    catch(ProductionWorker::InvalidPayRate e){ //Catch invalid pay rates
        cerr << "INVALID PAY RATE!" << endl;
    }
    //Output worker data
    cout << fixed << setprecision(2); //Format
    cout << "EMPLOYEE INFORMATION:" << endl;
    cout << "NAME: " << worker.name() << endl; //Output name
    cout << "ID NUMBER: " << worker.number() << endl; //Output number
    cout << "HIRE DATE: " << worker.hireDate(); //Output hire date
    cout << "PAY: $" << worker.payDec() << " / hour" << endl; //Output pay rate
    cout << "SHIFT: " << worker.shiftStr() << endl; //Output shift

    //Exit
    return 0;
}

