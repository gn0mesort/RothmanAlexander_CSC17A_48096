/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   enums.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define enumeration types for Overflow
 * Created on December 5, 2016
 */

#ifndef ENUMS_H
#define ENUMS_H

namespace Flow{

    /**
     * Defines various types of Items that may exist in the game
     */
    enum class ItemType{
        /**
         * No type. Default for Item objects
         */
        None = 0,

        /**
         * Type returned by Potion Items
         */
        Potion = 1,

        /**
         * Type returned by Weapon Items
         */
        Weapon = 2,

        /**
         * Type returned by Armor Items
         */
        Armor = 3
    };

    /**
     * Defines the various Jobs an Actor might have. Most RPGs call this a Class but for the sake of my own sanity
     * I've called it Job
     */
    enum class Job{
        /**
         * No Job
         */
        None = 0,

        /**
         * A Knight. Uses swords
         */
        Knight = 1,

        /**
         * A Cleric. Uses maces
         */
        Cleric = 2,

        /**
         * A Mage. Uses staves and magic relics
         */
        Mage = 3,

        /**
         * A Lancer. Uses spears
         */
        Lancer = 4
    };

    /**
     * Defines the various events that may occur in a Room
     */
    enum class RmEvent{
        /**
         * No event
         */
        None = 0,

        /**
         * Encounter an enemy
         */
        Encounter = 1,

        /**
         * Discover treasure
         */
        Treasure = 2,

        /**
         * Discover a healing spring
         */
        Spring = 3
    };
}


#endif /* ENUMS_H */

