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

#include <cstdlib>
#include <ctime>
#include <memory>

#include "collections.h"
#include "macros.h"
#include "game.h"
#include "item.h"
#include "structs.h"
#include "room.h"

namespace Flow{
    class Actor;
    class Game;
    class Item;
    class Armor;
    class Weapon;
    class Potion;
    class Floor;
    class Room;

    class GmRand{
    private:
        RNGPoint _point;
    public:
        GmRand();
        void seek(unsigned int);
        void seek(const RNGPoint&);
        void srand();
        void srand(unsigned int);
        unsigned int seed();
        unsigned int pos();
        int rand();
        Actor rActor();
        void rItem(Actor&, ItemType = ItemType::None);
        unsigned char rElem();
        Floor rFloor(unsigned char = 32);
        Room rRoom(bool = false, bool = false);
        unsigned char rDirect();
    };
}

#endif /* RANDOM_H */

