/*
 * File:   employee.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define an Employee class and a ProductionWorker that inherits from it
 * Created on November 28, 2016
 */

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

//System Libraries
#include <string> //Strings

/**
 * Defines the basic traits of an employee
 */
class Employee{
private:
protected:
    /**
     * The Employee's  name
     */
    std::string _name;
    /**
     * The Employee's ID number
     */
    unsigned int _num;
    /**
     * A string containing the date the employee was hired
     */
    std::string _hireDate;
public:

    /**
     * Parameterized Employee constructor. Contains defaults for all values
     * @param name The Employee's name
     * @param num The Employee's ID number
     * @param hireDate The date the Employee was hired as a string
     */
    Employee(const std::string &name = "", unsigned int num = 0, const std::string &hireDate = ""){
        _name = name;
        _num = num;
        _hireDate = hireDate;
    }

    /**
     * Get the Employee's name
     * @return The Employee's name
     */
    std::string name() const{
        return _name;
    }

    /**
     * Set the Employee's name
     * @param nName The new name to set
     */
    void name(const std::string &nName){
        _name = nName;
    }

    /**
     * Get the Employee's ID number
     * @return The Employee's ID number
     */
    unsigned int number() const{
        return _num;
    }

    /**
     * Set the Employee's ID number
     * @param num The new number to set
     */
    void number(unsigned int num){
        _num = num;
    }

    /**
     * Get the Employee's hire date as a string
     * @return The date the Employee was hired as a string
     */
    std::string hireDate() const{
        return _hireDate;
    }

    /**
     * Set the Employee's hire date
     * @param nHire The new date string to set
     */
    void hireDate(const std::string &nHire){
        _hireDate = nHire;
    }
};

/**
 * Defines a ProductionWorker class that inherits from Employee
 */
class ProductionWorker : public Employee{
private:
    /**
     * The shift that this ProductionWorker works. Either 1 for Day or 2 for Night (This could be a bool but the book
     * specifically wants it done this way)
     */
    unsigned char _shift;
    /**
     * The pay rate for this ProductionWorker in cents per hour
     */
    unsigned int _pay;
public:
    ProductionWorker(const std::string& = "", unsigned int = 0, const std::string& = "", unsigned char = 1,
                     unsigned int = 0);

    /**
     * Get the shift for this ProductionWorker
     * @return The current shift as an unsigned char
     */
    unsigned char shift() const{
        return _shift;
    }

    /**
     * Set the shift for this ProductionWorker
     * @param nShift The new shift to set. 1 for Day, 2 for Night
     */
    void shift(unsigned char nShift){
        _shift = nShift;
    }

    /**
     * Get the current shift as a string
     * @return A string representing the current shift. Either "Day" or "Night"
     */
    std::string shiftStr() const{
        return _shift == 1 ? "Day" : "Night";
    }

    /**
     * Get the pay rate for this ProductionWorker
     * @return The pay rate in cents per hour
     */
    unsigned int pay() const{
        return _pay;
    }

    /**
     * Set the pay rate for this ProductionWorker
     * @param nPay The new pay rate to set. Must be in cents per hour
     */
    void pay(unsigned int nPay){
        _pay = nPay;
    }

    /**
     * Get the pay rate for this ProductionWorker in dollars per hour
     * @return The pay rate in dollars per hour
     */
    float payDec() const{
        return static_cast<float>(_pay) / 100.0f;
    }

    /**
     * Set the pay rate for this ProductionWorker using dollars per hour
     * @param nPay The new rate to set in dollars per hour
     */
    void payDec(float nPay){
        _pay = static_cast<int>(nPay * 100.0f);
    }
};

#endif /* EMPLOYEE_H */

