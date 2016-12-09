/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   stat.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define Stat objects
 * Created on November 27, 2016
 */

#ifndef STAT_H
#define STAT_H

//User Libraries
#include "except.h" //ArgumentExceptions

namespace Flow{

    /**
     * Define Stat objects. Stats are abstract and take a template type. The templating type should always a value type
     */
    template<typename T>
    class Stat{
    private:
    protected:
        /**
         * The short name of the Stat
         */
        std::string _name;

        /**
         * The full name of the Stat
         */
        std::string _flName;

        /**
         * The value of the Stat
         */
        T _value;
    public:
        Stat();
        void fullName(const std::string&);
        void name(const std::string&);
        std::string fullName() const;
        std::string name() const;

        //Virtual Functions
        //Ensure that a Stat always has a get and set value function
        //Ensure that a Stat always has a get max and get min function
        virtual void value(T nValue) = 0;
        virtual T max() const = 0;
        virtual T min() const = 0;
        virtual T value() const = 0;
    };

    /**
     * Default Stat constructor
     */
    template<typename T>
    Stat<T>::Stat(){
        unsigned char sanity = _value; //Make sure you didn't do something horrible!!!
        //This will cause a compiler error if you do something crazy like create a Stat with a std::vector
        //as its value

        _name = "";
        _flName = "";
    }

    /**
     * Get the short name of the Stat
     * @return The short name of the Stat
     */
    template<typename T>
    std::string Stat<T>::name() const{
        return _name;
    }

    /**
     * Get the full name of the Stat
     * @return The full name of the Stat
     */
    template<typename T>
    std::string Stat<T>::fullName() const{
        return _flName;
    }

    /**
     * Set the short name of the Stat
     * @param nName The new short name
     */
    template<typename T>
    void Stat<T>::name(const std::string &nName){
        _name = nName;
    }

    /**
     * Set the full name of the Stat
     * @param flName The new full name
     */
    template<typename T>
    void Stat<T>::fullName(const std::string &flName){
        _flName = flName;
    }

    /******************************************************************************************************************/
    /******************************************************************************************************************/
    /******************************************************************************************************************/

    /**
     * Defines a Stat that uses a unsigned char as the templating type
     */
    class BStat : public Stat<unsigned char>{
    private:
    public:
        BStat();
        BStat(unsigned char, const std::string& = "", const std::string& = "");
        void value(unsigned char) override;
        unsigned char max() const override;
        unsigned char min() const override;
        unsigned char value() const override;
    };

    /**
     * Defines a Stat that uses an int as a templating type
     */
    class IStat : public Stat<int>{
    private:
        /**
         * The Absolute maximum value of an IStat
         */
        int _absMax;

        /**
         * The Absolute minimum value of an IStat
         */
        int _absMin;

        /**
         * The max value of an IStat
         */
        int _max;

        /**
         * The min value of an IStat
         */
        int _min;
    public:
        IStat();
        IStat(int, const std::string& = "", const std::string& = "", int = 100, int = 0, int = 0x7FFFFFFF,
              int = 0x80000000);
        void max(int nMax);
        void min(int nMin);
        void value(int nValue) override;
        int absoluteMax() const;
        int absoluteMin() const;
        int max() const override;
        int min() const override;
        int value() const override;
    };
}

#endif /* STAT_H */

