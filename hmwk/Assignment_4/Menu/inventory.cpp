/*
 * File:   inventory.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for inventory.h
 * Created on November 15, 2016
 */

//User Libraries
#include "inventory.h" //Inventory objects

//total
//Returns the total price of all the units in an Inventory object
//Output:
//The cost of the Inventory item * the quantity

unsigned int Inventory::total(){
    if(_recalc){ //If the value is flagged for recalculation
        _total = _cost * _qty; //recalculate total
        _recalc = false; //Remove flag
    }

    return _total;
}