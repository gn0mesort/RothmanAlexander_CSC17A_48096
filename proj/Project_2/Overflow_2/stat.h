/*
 * File:   stat.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on November 27, 2016
 */

#ifndef STAT_H
#define STAT_H

#include "except.h"

namespace Flow{

    template<typename T>
    class Stat{
    private:
    protected:
        std::string _name;
        std::string _flName;
        T _value;
    public:
        Stat();
        std::string name() const;
        void name(const std::string&);
        std::string fullName() const;
        void fullName(const std::string&);

        //Virtual Functions
        //Ensure that a Stat always has a get and set value function
        //Ensure that a Stat always has a get max and get min function
        virtual T value() const = 0;
        virtual void value(T nValue) = 0;
        virtual T max() const = 0;
        virtual T min() const = 0;
    };

    template<typename T>
    Stat<T>::Stat(){
        unsigned char sanity = _value; //Make sure you didn't do something horrible!!!
        //This will cause a compiler error if you do something crazy like create a Stat with a std::vector
        //as its value

        _name = "";
        _flName = "";
    }

    template<typename T>
    std::string Stat<T>::name() const{
        return _name;
    }

    template<typename T>
    std::string Stat<T>::fullName() const{
        return _flName;
    }

    template<typename T>
    void Stat<T>::name(const std::string &nName){
        _name = nName;
    }

    template<typename T>
    void Stat<T>::fullName(const std::string &flName){
        _flName = flName;
    }

    /******************************************************************************************************************/
    /******************************************************************************************************************/
    /******************************************************************************************************************/

    /**
     *
     */
    class BStat : public Stat<unsigned char>{
    private:
    public:
        BStat();
        BStat(unsigned char, const std::string& = "", const std::string& = "");
        unsigned char value() const override;
        void value(unsigned char) override;
        unsigned char max() const override;
        unsigned char min() const override;
    };

    class IStat : public Stat<int>{
    private:
        int _absMax;
        int _absMin;
        int _max;
        int _min;
    public:
        IStat();
        IStat(int, const std::string& = "", const std::string& = "", int = 100, int = 0, int = 0x7FFFFFFF,
              int = 0x80000000);
        int absoluteMax() const;
        int absoluteMin() const;
        int value() const override;
        void value(int nValue) override;
        int max() const override;
        void max(int nMax);
        int min() const override;
        void min(int nMin);
    };
}

#endif /* STAT_H */

