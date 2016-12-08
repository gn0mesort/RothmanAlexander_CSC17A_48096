/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   random.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 2, 2016
 */

#ifndef RANDOM_H
#define RANDOM_H

#include "structs.h"
#include "enums.h"
#include "room.h"

namespace Flow{

    class GmRand{
    private:
        static RNGPoint _point;
    public:
        //GmRand();
        void seek(unsigned int);
        void seek(const RNGPoint&);
        void srand();
        void srand(unsigned int);
        unsigned int seed();
        unsigned int pos();
        int rand();
        unsigned char rElem();
        Floor rFloor(unsigned char = 32);
        Room rRoom(bool = false, bool = false);
        unsigned char rDirect();
    };
}

#endif /* RANDOM_H */

