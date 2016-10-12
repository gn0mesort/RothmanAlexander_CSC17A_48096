/* 
 * File:   Stat.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on October 11, 2016
 */

#ifndef STAT_H
#define STAT_H

#include "Byte.h"


namespace Flow{

class Stat{
public:
    std::string name;
    std::string flName;
private:
    //Stat();
};

class BStat : public Stat{
public:
    Byte::Byte<unsigned char> value;
    
    BStat();
    BStat(const std::string&, const std::string&, unsigned char);
    BStat(const BStat&);
    //~BStat();
   
    std::string toString() const;
private:
};

class IStat : public Stat{
public:
    IStat();
    IStat(const IStat&);
    IStat(const std::string&, const std::string&, int, int = 100, int = 0, int = 9999, int = 0);
    //~IStat();
    
    int value() const;
    int max() const;
    int min() const;
    int absMax() const;
    int absMin() const;
    void setVal(int);
    void setMax(int);
    void setMin(int);
    std::string toString() const;
private:
    int _max,
            _min,
            _value,
            _absMax,
            _absMin;
};

}

#endif /* STAT_H */

