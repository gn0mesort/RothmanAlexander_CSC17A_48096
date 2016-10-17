/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Flags.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 14, 2016
 */

#ifndef FLAGS_H
#define FLAGS_H

#include <cmath>

#include "Byte.h"


namespace Flow{

    //Exit
    //Container namespace for Exit constants. Provides scoped enum like syntax to constants
    namespace Exit{
        const unsigned char NONE = 0, NORTH = 1, EAST = 2, SOUTH = 4, WEST = 8;
        std::string toStr(unsigned char);
    }
    
    //Damage Element
    //Container namespace for DamageElement constants. Provides scoped enum like syntax to constants
    namespace DmgElem{
        const unsigned char NONE = 0, HEALING = 1, FIRE = 2, ICE = 4, LIGHTNG = 8, WIND = 16, HOLY = 32, SHADOW = 64,
                NGHTMRE = 128, ABSOLUT = 255;
        std::string toStr(unsigned char);
    }
    
    class FlgUtil{
    public:
        static bool hasFlag(unsigned long data, unsigned long value);
    private:
    };

}


#endif /* FLAGS_H */

