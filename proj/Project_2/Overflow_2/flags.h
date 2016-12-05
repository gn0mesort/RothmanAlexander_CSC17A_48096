/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Flags.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define bit flags and helper functions as well as namespace them
 * Created on October 14, 2016
 */

#ifndef FLAGS_H
#define FLAGS_H

//System Libraries
#include <string> //String type and functions

namespace Flow{

    //Exit
    //Container namespace for Exit constants. Provides scoped enum like syntax to constants
    namespace Direct{
        const unsigned char NONE = 0, NORTH = 1, EAST = 2, SOUTH = 4, WEST = 8;
        unsigned char reverse(unsigned char);
        std::string toString(unsigned char);
        std::string toString(unsigned char, bool);
    }

    //DmgElem
    //Container namespace for DamageElement constants. Provides scoped enum like syntax to constants
    namespace DmgElem{
        const unsigned char NONE = 0, NGHTMRE = 1, FIRE = 2, ICE = 4, LIGHTNG = 8, WIND = 16, HOLY = 32, SHADOW = 64,
                HEALING = 128, ABSOLUT = 255;
        std::string toString(unsigned char);
    }

    //Diff
    //Container namespace for Difficulty constants. Provides scoped enum like syntax to constants
    namespace Diff{
        const unsigned char NONE = 0, EASY = 8, MEDIUM = 16, HARD = 32;
    }

    //FlgUtil
    //Defines a class that contains functions for checking bit flags

    class FlagUtil{
    private:
    public:
        static bool hasFlag(unsigned long data, unsigned long value);
    };

}


#endif /* FLAGS_H */

