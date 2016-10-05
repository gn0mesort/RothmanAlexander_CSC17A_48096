/* 
 * File:   CstAcct.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Store data for a single customer account
 * Created on October 4, 2016
 */

#ifndef CSTACCT_H
#define CSTACCT_H

//Customer Account
//Stores data on a single customer account
struct CstAcct{
    std::string name; //The customer's name
    std::string address; //The customer's address
    std::string ctStZp; //The customer's city, state, and zip code
    std::string tel; //The customer's telephone number
    int balance; //The customer's current account balance
    std::string lastPay; //The date of last payment
};

#endif /* CSTACCT_H */

