/*
 * File:   employee.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for employee.h
 * Created on November 28, 2016
 */

#include "employee.h"

/**
 * Parameterized Employee constructor. Contains defaults for all values
 * @param name The Employee's name
 * @param num The Employee's ID number
 * @param hireDate The date the Employee was hired as a string
 */
Employee::Employee(const std::string &name, unsigned int num, const std::string &hireDate){
    if(num < 0 || num > 9999){ //Check number
        throw InvalidEmployeeNumber();
    }
    _name = name;
    _num = num;
    _hireDate = hireDate;
}

/**
 * Parameterized ProductionWorker constructor. Defaults all values
 * @param name The ProductionWorker's name
 * @param num The ProductionWorker's ID number
 * @param hireDate The ProductionWorker's hire date
 * @param shift The ProductionWorker's shift (Day or Night)
 * @param pay The ProductionWorker's pay rate in cents per hour
 */
ProductionWorker::ProductionWorker(const std::string &name, unsigned int num, const std::string &hireDate,
                                   unsigned char shift, unsigned int pay) : Employee(name, num, hireDate){
    if(shift > 2 || shift < 1){ //Check shift
        throw InvalidShift();
    }
    if(pay < 1){ //Check pay
        throw InvalidPayRate();
    }
    _shift = shift;
    _pay = pay;
}