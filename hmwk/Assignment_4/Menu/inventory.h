/*
 * File:   inventory.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Specifies an Inventory item class for storing data about items in a store inventory.
 * This class doesn't recalculate the total value unless the quantity or cost has changed.
 * Created on November 15, 2016
 */

#ifndef INVENTORY_H
#define INVENTORY_H

//Inventory
//A class for defining inventory items for a store.

class Inventory{
private:
    int _num; //The ID number for the item
    int _qty; //The quantity of the item. If this changes the total cost should be recalculated
    unsigned int _cost; //The cost for one unit of the item in cents. If this changes the total cost should be recalculated
    unsigned int _total; //The total cost of the item in cents
    bool _recalc; //Whether or not the total cost needs to be recalculated
public:

    //Inventory
    //Default Inventory Constructor
    //Output:
    //A new Inventory object with all fields defaulted to 0 except _recalc which defaults to true

    Inventory(){
        _num = 0;
        _qty = 0;
        _cost = 0;
        _total = 0;
        _recalc = true;
    }

    //Inventory
    //Parameterized Inventory Constructor
    //Input:
    //cost
    //The cost in cents of the item
    //qty
    //The quantity of the item
    //Output:
    //A new Inventory object with the given cost and qty values set. All other values defaulted

    Inventory(unsigned int cost, unsigned int qty){
        _num = 0;
        _cost = cost;
        _qty = qty;
        _total = 0;
        _recalc = true;
    }

    //number
    //Return the Inventory ID number
    //Output:
    //An ID number for this Inventory object

    int number() const{
        return _num;
    }

    //number
    //Set the ID number of an Inventory object
    //Input:
    //num
    //The number to set the ID to

    void number(int num){
        _num = num;
    }

    //quantity
    //Return the Inventory quantity
    //Output:
    //The number of units this Inventory item represents

    int quantity() const{
        return _qty;
    }

    //quantity
    //Set the quantity of an Inventory object
    //Input:
    //qty
    //The quantity to set for the object

    void quantity(int qty){
        _qty = qty;
        _recalc = true;
    }

    //cost
    //Return the Inventory cost in cents
    //Output:
    //The cost for 1 unit of this item in cents

    unsigned int cost() const{
        return _cost;
    }

    //cost
    //Set the cost of one unit of an Inventory item
    //Input:
    //nCost
    //The cost to set for the item in cents

    void cost(unsigned int nCost){
        _cost = nCost;
        _recalc = true;
    }

    unsigned int total();

    //totalDec
    //Return the total cost of the Inventory object as a dollar value
    //Output:
    //The value of total() / 100

    float totalDec(){
        return static_cast<float>(total()) / 100.0f;
    }

    //costDec
    //Return the cost of the Inventory object as a dollar value
    //Output:
    //The value of cost() / 100

    float costDec() const{
        return static_cast<float>(_cost) / 100.0f;
    }
};

#endif /* INVENTORY_H */

