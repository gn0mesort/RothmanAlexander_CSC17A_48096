/* 
 * File:   SaleDat.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Store sales data for a single company division
 * Created on October 3, 2016
 */

#ifndef SALEDAT_H
#define SALEDAT_H

//System Libraries
#include <string> //String type and functions

//Sales Data
//Stores sales data for a single division of a company
struct SaleDat{
    static const unsigned char SIZE = 4; //The size of the sales array in Sales Data object
    
    std::string divName; //The division name
    unsigned int sales[SIZE]; //The quarterly sales data
};


#endif /* SALEDAT_H */

