/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   random.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define the Game's RNG. Wraps the rand() and srand() functions found in cstdlib
 * Created on December 2, 2016
 */

#ifndef RANDOM_H
#define RANDOM_H

//User Libraries
#include "structs.h" //Game structs
#include "enums.h" //Enumeration types
#include "room.h" //Room and Floor objects

namespace Flow{

    /**
     * Defines an object which allows access to the rand() function and records the number of generations which have
     * occurred
     */
    class GmRand{
    private:
        /**
         * The current position of the PRNG. This data is static and so any call to GmRand.rand() will increment it
         */
        static RNGPoint _point;
    public:
        void seek(unsigned int);
        void seek(const RNGPoint&);
        void srand();
        void srand(unsigned int);
        unsigned char rDirect();
        unsigned char rElem();
        unsigned int seed();
        unsigned int pos();
        int rand();
        Room rRoom(bool = false, bool = false);
        Floor rFloor(unsigned char = 32);
    };
}

#endif /* RANDOM_H */

