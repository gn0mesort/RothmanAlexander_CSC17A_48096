/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Stat.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Defines Statistic objects for various types of game statistics
 * Created on October 11, 2016
 */

#ifndef STAT_H
#define STAT_H

#include <string>

namespace Flow{

    //Stat
    //Defines a base Statistic object. This class contains the common elements of IStat and BStat.
    class Stat{
    private:
        std::string _flName; //The full name of the statistic
        std::string _name; //The short name of the statistic
    public:
        void setFlName(const std::string&);
        void setName(const std::string&);
        std::string flName() const;
        std::string name() const;
    };

    //BStat
    //Defines a Byte Statistic. Inherits from Stat. Byte Statistics are game stats that should wrap around for values
    //greater than 255 (hence the game's title)
    class BStat : public Stat{
    private:
        unsigned char _value; //The value of the BStat as an unsigned char this will wrap around for values greater 
        //than 255. This is the main feature of the game
    public:
        BStat();
        BStat(const std::string&, const std::string&, unsigned char);
        BStat(const BStat&);
        void setValue(unsigned char);
        unsigned char value() const;
    };

    //IStat
    //Defines an Integer Statistic. Inherits from Stat. Integer Statistics are game stats that are not intended to have
    //a wrapping behavior do to overflows
    class IStat : public Stat{
    private:
        int _absMax; //The absolute maximum value of this stat. Can't be changed
        int _absMin; //The absolute minimum value of this stat. Can't be changed
        int _max; //The current maximum value of this stat
        int _min; //The current minimum value of this stat
        int _value; //The current value of this stat
    public:
        IStat();
        IStat(const IStat&);
        IStat(const std::string &name, const std::string &flName, int value, int max = 100, int min = 0, 
            int absMax = 9999, int absMin = 0);
        void setMax(int);
        void setMin(int);
        void setValue(int);
        int absMax() const;
        int absMin() const;
        int max() const;
        int min() const;
        int value() const;
    };

}

#endif /* STAT_H */

