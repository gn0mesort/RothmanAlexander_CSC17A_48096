/* 
 * File:   SaleDat.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Store sales data for a single company division
 * Created on October 3, 2016
 */

#ifndef SALEDAT_H
#define SALEDAT_H

#include <string>

struct SaleDat{
    static const unsigned char SIZE = 4;
    
    std::string divName;
    unsigned int sales[SIZE];
    unsigned int tSales;
    float avSales;
};


#endif /* SALEDAT_H */

