/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   enums.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 5, 2016
 */

#ifndef ENUMS_H
#define ENUMS_H

namespace Flow{

    enum class ItemType{
        None = 0,
        Potion = 1,
        Weapon = 2,
        Armor = 3
    };

    enum class Job{
        None = 0,
        Knight = 1,
        Cleric = 2,
        Mage = 3,
        Lancer = 4
    };

    enum class RmEvent{
        None = 0,
        Encounter = 1,
        Treasure = 2,
        Spring = 3
    };
}


#endif /* ENUMS_H */

