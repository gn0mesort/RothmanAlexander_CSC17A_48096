/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate the RetailItem class
 * Created on November 15, 2016
 */

//System Libraries
#include <iostream>
#include <iomanip>

//User Libraries
#include "retailitem.h"
using namespace std;

//Begin Execution

int main(int argc, char** argv){
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

    //Exit
    return 0;
}

