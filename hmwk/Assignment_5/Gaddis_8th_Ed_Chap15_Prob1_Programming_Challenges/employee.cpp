/*
 * File:   employee.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for employee.h
 * Created on November 28, 2016
 */

#include "employee.h"

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
    _shift = shift;
    _pay = pay;
}