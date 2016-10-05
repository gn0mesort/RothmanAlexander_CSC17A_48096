/* 
 * File:   CstAcct.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on October 4, 2016
 */

#ifndef CSTACCT_H
#define CSTACCT_H

struct CstAcct{
    std::string name;
    std::string address;
    std::string ctStZp;
    std::string tel;
    int balance;
    std::string lastPay;
};

#endif /* CSTACCT_H */

