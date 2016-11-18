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
#include <string> //Strings

//User Libraries
#include "date.h" //Date objects
#include "floatarr.h" //FloatArr objects
#include "person.h" //Person objects
#include "retailitem.h" //RetailItem objects
#include "inventory.h" //Inventory objects
#include "numbers.h" //Numbers objects
#include "dayofyear.h" //DayOfYear objects
#include "numdays.h" //NumDays objects
#include "month.h" //Month objects
using namespace std;

//Global Constants

//Function Prototypes
void solve1();
void solve2();
void solve3();
void solve4();
void solve5();
void solve6();
void solve7();
void solve8();
void solve9();
void solve10();
int toInt(unsigned char);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int choice = 0;

    do{ //While not exiting
        do{ //While choice is not negative
            //Output Choices
            cout << setw(5) << "(1) " << "CHAPTER 13 PROBLEM 1" << endl;
            cout << setw(5) << "(2) " << "CHAPTER 13 PROBLEM 4" << endl;
            cout << setw(5) << "(3) " << "CHAPTER 13 PROBLEM 5" << endl;
            cout << setw(5) << "(4) " << "CHAPTER 13 PROBLEM 6" << endl;
            cout << setw(5) << "(5) " << "CHAPTER 13 PROBLEM 10" << endl;
            cout << setw(5) << "(6) " << "CHAPTER 14 PROBLEM 1" << endl;
            cout << setw(5) << "(7) " << "CHAPTER 14 PROBLEM 2" << endl;
            cout << setw(5) << "(8) " << "CHAPTER 14 PROBLEM 3" << endl;
            cout << setw(5) << "(9) " << "CHAPTER 14 PROBLEM 4" << endl;
            cout << setw(5) << "(10) " << "CHAPTER 14 PROBLEM 7" << endl;
            cout << setw(5) << "(0) " << "EXIT" << endl;
            //Display Prompt and Read Input
            cout << "> ";
            cin >> choice;
        } while(choice < 0);
        switch(choice){ //Select function based on choice
            case 1:
            {
                cout << "CHAPTER 13 PROBLEM 1" << endl;
                solve1();
                cout << endl;
                break;
            }
            case 2:
            {
                cout << "CHAPTER 13 PROBLEM 4" << endl;
                solve2();
                cout << endl;
                break;
            }
            case 3:
            {
                cout << "CHAPTER 13 PROBLEM 5" << endl;
                solve3();
                cout << endl;
                break;
            }
            case 4:
            {
                cout << "CHAPTER 13 PROBLEM 6" << endl;
                solve4();
                cout << endl;
                break;
            }
            case 5:
            {
                cout << "CHAPTER 13 PROBLEM 10" << endl;
                solve5();
                cout << endl;
                break;
            }
            case 6:
            {
                cout << "CHAPTER 14 PROBLEM 1" << endl;
                solve6();
                cout << endl;
                break;
            }
            case 7:
            {
                cout << "CHAPTER 14 PROBLEM 2" << endl;
                solve7();
                cout << endl;
                break;
            }
            case 8:
            {
                cout << "CHAPTER 14 PROBLEM 3" << endl;
                solve8();
                cout << endl;
                break;
            }
            case 9:
            {
                cout << "CHAPTER 14 PROBLEM 4" << endl;
                solve9();
                cout << endl;
                break;
            }
            case 10:
            {
                cout << "CHAPTER 14 PROBLEM 7" << endl;
                solve10();
                cout << endl;
                break;
            }
        }
        cout << setfill(' ');
    } while(choice);


    //Exit
    return 0;
}

void solve1(){
    //Declaration and Initialization
    unsigned short day = 0, //The value of the day
            month = 0, //The value of the month
            year = 0; //The value of the year

    //Input
    do{ //While the day input isn't valid
        cout << "INPUT THE DAY OF THE MONTH: ";
        cin >> day; //Read in the day
    } while(day > 31 || day < 1);
    do{ //While the month isn't valid
        cout << "INPUT THE NUMBER OF THE MONTH: ";
        cin >> month; //Read in the month
    } while(month < 1 || month > 12);
    cout << "INPUT THE YEAR: ";
    cin >> year; //Read in the year
    //It's assumed that the year will be at least 4 characters long but there's no restriction on it.
    //If you input a number like 8 you'll get 0008 and if you input something like 12345 you'll get 12345.
    cout << endl;

    //Output
    Date d(day, month, year); //Create the Date object with the input values

    cout << d.toString() << endl; //Output regular date string (MM/DD/YYYY)
    cout << d.toLongString() << endl; //Output long date string (DD Month YYYY)
    cout << d.toLongString(true) << endl; //Output alternate long date string (Month DD, YYYY)
}

void solve2(){
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
}

void solve3(){
    const unsigned char SIZE = 3, //Number of items to create
            COLUMN = 25; //Formatting size
    RetailItem items[SIZE]; //RetailItem array

    //Set Items as per the problem in the book
    items[0] = RetailItem("Jacket", 12, 5995);
    items[1] = RetailItem("Designer Jeans", 40, 3495);
    items[2] = RetailItem("Shirt", 20, 2495);

    //Output Data in a table
    cout << fixed << setprecision(2); //Format floats
    cout << setw(COLUMN + 7) << "Description" << setw(COLUMN + 5) << "Units On Hand" << setw(COLUMN) //Header
            << "Price" << endl;
    for(int i = 0; i < SIZE; ++i){ //For each RetailItem
        cout << "ITEM #" << i + 1 << setw(COLUMN) << items[i].description() << setw(COLUMN) << items[i].units() //Output each RetailItem
                << setw(COLUMN) << "$" << items[i].priceDec() << endl;
    }
}

void solve4(){
    //Declaration and Initialization
    int input = 0, //An input integer
            size = 0; //The number of items to create
    float inputf = 0.0f; //An input float
    Inventory *inv = 0; //An array of Inventory objects


    //Input Data
    cout << "HOW MANY ITEMS SHOULD BE GENERATED: ";
    cin >> size; //Read in size

    if(size > 0){ //If size is positive
        inv = new Inventory[size]; //Allocate array
        cout << fixed << setprecision(2) << setfill('0') << endl; //Set up formatting
        for(int i = 0; i < size; ++i){ //For each Inventory item
            do{ //While not valid
                cout << "ENTER AN ITEM NUMBER: ";
                cin >> input; //Read in ID number
                inv[i].number(input); //Set number
            } while(inv[i].number() < 0);
            do{ //While not valid
                cout << "ENTER THE QUANTITY OF THE ITEM: ";
                cin >> input; //Read in quantity
                inv[i].quantity(input); //Set quantity
            } while(inv[i].quantity() < 0);
            do{ //While not valid
                cout << "ENTER THE COST OF THE ITEM : $";
                cin >> inputf; //Read in cost in dollars
            } while(inputf < 0);
            inv[i].cost(static_cast<unsigned int>(inputf * 100.0f)); //Set cost in cents
            cout << "#" << setw(10) << inv[i].number() << " : $" << inv[i].totalDec() << " for " << inv[i].quantity()
                    << " units at $" << inv[i].costDec() << " per unit." << endl; //Output current Inventory item
            cout << endl;
        }
        cout << endl;

        //Output Data
        cout << "INVENTORY: " << endl;
        for(int i = 0; i < size; ++i){ //For each Inventory item
            cout << "#" << setw(10) << inv[i].number() << " : $" << inv[i].totalDec() << " for " << inv[i].quantity()
                    << " units at $" << inv[i].costDec() << " per unit." << endl; //Output item
        }
    }

    //Clean up
    delete [] inv;
    inv = 0;
}

void solve5(){
    //Declaration and Initialization
    const unsigned char SIZE = 10; //Size of the array to create
    FloatArr arr(SIZE); //Create a new FloatArr of SIZE elements

    srand(static_cast<int>(time(0))); //Seed PRNG

    //Fill and Display arr
    for(int i = 0; i < arr.size(); ++i){ //For every element of arr
        arr.set(i, (rand() % 1000) / 10.0f); //Set the value at i to a random number
        cout << "arr[" << i << "] = " << arr.get(i) << endl; //Output arr[i]
    }
    //Output calculated values
    cout << "HIGH:    " << arr.high() << endl; //Find and output the highest value
    cout << "LOW:     " << arr.low() << endl; //Find and output the lowest value
    cout << "AVERAGE: " << arr.avg() << endl; //Calculate and output the average
}

void solve6(){
    Numbers n; //A numbers object
    int input = 0; //An input value

    do{ //While the input is invalid
        cout << "ENTER A NUMBER BETWEEN 0 AND 9999: ";
        cin >> input; //Read in input
    } while(input > 9999 || input < 0);

    n.value(input); //Set the value of n
    n.print(); //Print n
}

void solve7(){
    DayOfYear date; //A DayOfYear object

    for(int i = 0; i < 365; ++i){ //For every day of the year
        string month = date.toString().substr(0, date.toString().find(' ')); //Get the name of the current month

        cout << setw(month.size()) << date.toString() << " "; //Output the current date
        date.day(date.day() + 1); //Increment the date
        if(date.toString().substr(0, date.toString().find(' ')) != month){ //Print a line break at the end of each month
            cout << endl << endl;
        }
        else if((i + 1) % 7 == 0){ //Print a line break at the end of each week
            cout << endl;
        }
    }
}

void solve8(){
    DayOfYear date("December", 31); //A DayOfYear object

    for(int i = 0; i < 365; ++i){
        string month = date.toString().substr(0, date.toString().find(' ')); //Get the name of the current month

        cout << setw(month.size()) << (date--).toString() << " "; //Output the current date and decrement afterward
        if(date.toString().substr(0, date.toString().find(' ')) != month){ //Print a line break at the end of each month
            cout << endl << endl;
        }
        else if((i + 1) % 7 == 0){ //Print a line break at the end of each week
            cout << endl;
        }
    }
}

void solve9(){
    //Declaration and Initialization
    NumDays nd1(12), nd2(8), nd3, nd4; //Initialize some NumDays objects

    //Test constructors and functions
    cout << "1st NumDays = " << nd1.hours() << " hours or " << nd1.days() << " days." << endl;
    cout << "2nd NumDays = " << nd2.hours() << " hours or " << nd2.days() << " days." << endl;
    //Test addition
    nd3 = nd1 + nd2;
    cout << "1st + 2nd = " << nd3.hours() << " hours or " << nd3.days() << " days." << endl;
    //Test subtraction
    nd4 = nd1 - nd2;
    cout << "1st - 2nd = " << nd4.hours() << " hours or " << nd4.days() << " days." << endl;
    //Test increment and decrement
    ++nd1;
    --nd2;
    cout << "1st incremented = " << nd1.hours() << " hours or " << nd1.days() << " days." << endl;
    cout << "2nd decremented = " << nd2.hours() << " hours or " << nd2.days() << " days." << endl;
}

void solve10(){
    //Declaration and Initialization
    Month m; //A month to play around with

    //Count months forward
    cout << "ALL MONTHS FORWARD:" << endl;
    for(int i = 1; i < 13; ++i){
        cout << m++ << endl;
    }
    cout << endl;

    //Count months backward
    cout << "ALL MONTHS BACKWARD:" << endl;
    for(int i = 1; i < 13; ++i){
        cout << --m << endl;
    }
    cout << endl;

    //Parse month from string input
    do{ //While the input was valid
        cout << "INPUT A MONTH NAME: ";
        cin >> m; //Test inserting by reading in a month
    } while(m.value() == 13);
    cout << "INPUT MONTH WAS: " << m << " OR MONTH #" << static_cast<int>(m.value() ? m.value() : 12) << endl; //Output month
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