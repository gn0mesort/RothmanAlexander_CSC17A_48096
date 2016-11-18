/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Demonstrate Inventory class
 * Created on November 15, 2016
 */

//System Libraries
#include <iostream>
#include <iomanip>

//User Libraries
#include "inventory.h"
using namespace std;

//Begin Execution

int main(int argc, char** argv){
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

    //Exit
    return 0;
}

