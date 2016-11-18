/*
 * File:   retailitem.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define a RetailItem class for calculating prices
 * Created on November 15, 2016
 */

#ifndef RETAILITEM_H
#define RETAILITEM_H

//RetailItem
//Represents a single item held by a retail store. Data is held as a Description, number of Units, and Price in cents

class RetailItem{
private:
    std::string _desc; //The description of the item
    unsigned int _units; //The problem calls for an int but I don't see how you could have less than 0 units on hand
    //I guess you could have a debt of items or back orders.
    unsigned int _price; //Price in cents. Using doubles for money is silly.
public:

    //RetailItem
    //Default RetailItem Constructor
    //Output:
    //A RetailItem object with the fields defaulted to empty strings and 0

    RetailItem(){
        _desc = "";
        _units = 0;
        _price = 0;
    }

    //RetailItem
    //Parameterized RetailItem Constructor
    //Input:
    //desc
    //The item description
    //units
    //The number of units held
    //price
    //The price in cents of 1 unit
    //Output:
    //A new RetailItem object with the given values

    RetailItem(std::string desc, unsigned int units = 0, unsigned int price = 0){
        _desc = desc;
        _units = units;
        _price = price;
    }

    //description
    //Return the RetailItem's description
    //Output:
    //The current value of _desc

    std::string description(){
        return _desc;
    }

    //description
    //Set the RetailItem's description
    //Input:
    //desc
    //The value to set _desc to

    void description(std::string desc){
        _desc = desc;
    }

    //units
    //Return how many of the item are in stock
    //Output:
    //The current value of _units

    unsigned int units(){
        return _units;
    }

    //units
    //Set the number of units in stock
    //Input:
    //nUnits
    //The value to set _units to

    void units(unsigned int nUnits){
        _units = nUnits;
    }

    //price
    //Return the RetailItem's price in cents
    //Output:
    //The current value of _price

    unsigned int price(){
        return _price;
    }

    //price
    //Set the RetailItem's price
    //Input:
    //nPrice
    //The value to set _price to

    void price(unsigned int nPrice){
        _price = nPrice;
    }

    //priceDec
    //Return the RetailItem's price in dollars
    //Output:
    //The current value of _price / 100

    float priceDec(){
        return static_cast<float>(_price) / 100.0f;
    }
};

#endif /* RETAILITEM_H */

