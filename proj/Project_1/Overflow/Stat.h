/* 
 * File:   Stat.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on October 11, 2016
 */

#ifndef STAT_H
#define STAT_H

#include <string>

namespace Flow{

    class Stat{
    public:
        std::string name() const;
        std::string flName() const ;
        void setName(const std::string&);
        void setFlName(const std::string&);
    private:
        std::string _name;
        std::string _flName;
        //Stat();
    };

    class BStat : public Stat{
    public:
        BStat();
        BStat(const std::string&, const std::string&, unsigned char);
        BStat(const BStat&);
        //~BStat();
        unsigned char value() const;
        void setValue(unsigned char);
        std::string toString() const;
    private:
        unsigned char _value;
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

