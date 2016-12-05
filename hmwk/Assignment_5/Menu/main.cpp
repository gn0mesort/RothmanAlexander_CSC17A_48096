/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Create a template menu program for displaying homework solutions
 * Created on September 21, 2016
 */


//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <cstdlib> //C Standard Library
#include <ctime> //Time

//User Libraries
#include "employee.h" //Employee and ProductionWorker objects
#include "date.h" //Date objects
#include "sortablevector.h" //SortableVector objects
#include "absolutevalue.h" //abs() function
using namespace std;

//Global Constants

//Function Prototypes
void solve1();
void solve2();
void solve3();
void solve4();
void solve5();

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int choice = 0;

    do{ //While not exiting
        do{ //While choice is not negative
            //Output Choices
            cout << setw(5) << "(1) " << "CHAPTER 15 PROBLEM 1" << endl;
            cout << setw(5) << "(2) " << "CHAPTER 16 PROBLEM 1" << endl;
            cout << setw(5) << "(3) " << "CHAPTER 16 PROBLEM 10" << endl;
            cout << setw(5) << "(4) " << "CHAPTER 16 PROBLEM 16" << endl;
            cout << setw(5) << "(5) " << "CHAPTER 16 PROBLEM 4" << endl;
            cout << setw(5) << "(0) " << "EXIT" << endl;
            //Display Prompt and Read Input
            cout << "> ";
            cin >> choice;
        } while(choice < 0);
        switch(choice){ //Select function based on choice
            case 1:
            {
                cout << "CHAPTER 15 PROBLEM 1" << endl;
                solve1();
                cout << endl;
                break;
            }
            case 2:
            {
                cout << "CHAPTER 16 PROBLEM 1" << endl;
                solve2();
                cout << endl;
                break;
            }
            case 3:
            {
                cout << "CHAPTER 16 PROBLEM 10" << endl;
                solve3();
                cout << endl;
                break;
            }
            case 4:
            {
                cout << "CHAPTER 16 PROBLEM 16" << endl;
                solve4();
                cout << endl;
                break;
            }
            case 5:
            {
                cout << "CHAPTER 16 PROBLEM 4" << endl;
                solve5();
                cout << endl;
                break;
            }
        }
    } while(choice);


    //Exit
    return 0;
}

void solve1(){
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

    //Output worker data
    cout << fixed << setprecision(2); //Format
    cout << "EMPLOYEE INFORMATION:" << endl;
    cout << "NAME: " << worker.name() << endl; //Output name
    cout << "ID NUMBER: " << worker.number() << endl; //Output number
    cout << "HIRE DATE: " << worker.hireDate(); //Output hire date
    cout << "PAY: $" << worker.payDec() << " / hour" << endl; //Output pay rate
    cout << "SHIFT: " << worker.shiftStr() << endl; //Output shift
}

void solve2(){
    //Declaration and Initialization
    Date d(1, 1, 1990); //A new Date object set to 1/1/1990

    //Display Day errors
    for(int i = 0; i < 33; ++i){ //Loop from 1/0/1990 to 1/32/1990
        try{ //Try to set the day
            d.day(i); //Set day
            cout << d.toLongString(true) << endl; //Output Date
        }
        catch(Date::InvalidDay e){ //Catch invalid dates
            cerr << "INVALID DAY!" << endl;
        }
    }
    cout << endl;
    //Display Month errors
    for(int i = 0; i < 14; ++i){ //Loop from 0/31/1990 to 13/31/1990
        try{ //Try to set the month
            d.month(i); //Set month
            cout << d.toLongString(true) << endl; //Output Date
        }
        catch(Date::InvalidMonth e){ //Catch invalid months
            cerr << "INVALID MONTH!" << endl;
        }
    }
}

void solve3(){
    //Declaration and Initialization
    SortableVector<int> srtVec(100); //Create a sized data vector

    srand(static_cast<int>(time(0))); //Seed PRNG

    for(int i = 0; i < srtVec.size(); ++i){ //Generate random data between 10 and 99
        srtVec[i] = rand() % 89 + 10;
    }

    cout << "UNSORTED DATA:" << endl;
    for(int i = 0; i < srtVec.size(); ++i){ //Print vector
        cout << srtVec[i] << " ";
        if((i + 1) % 10 == 0){
            cout << endl;
        }
    }
    cout << endl;
    srtVec.sort(); //Sort data
    cout << "SORTED DATA:" << endl;
    for(int i = 0; i < srtVec.size(); ++i){ //Print vector
        cout << srtVec[i] << " ";
        if((i + 1) % 10 == 0){
            cout << endl;
        }
    }
    cout << endl;
    SortableVector<int> copy(srtVec); //Copy data
    cout << "COPIED DATA:" << endl;
    for(int i = 0; i < copy.size(); ++i){ //Print copied vector
        cout << copy[i] << " ";
        if((i + 1) % 10 == 0){
            cout << endl;
        }
    }
    cout << endl;
}

void solve4(){
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
}

void solve5(){
    //Test abs() with ints between -10 and 10
    for(int i = -10; i <= 10; ++i){
        cout << "|" << setw(3) << i << "| = " << abs(i) << endl;
    }
    cout << endl;
    cout << fixed << setprecision(2); //Formatting
    //Test abs() with floats between -1.25 and 1.25
    for(float f = -1.25f; f <= 1.25f; f += 0.25f){
        cout << "|" << setw(5) << f << "| = " << abs(f) << endl;
    }
}