/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   actor.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define an Actor (a character who can take actions)
 * Created on December 2, 2016
 */

#ifndef ACTOR_H
#define ACTOR_H

//System Libraries
#include <memory> //Smart pointers

//User Libraries
#include "enums.h" //Enumeration types
#include "stat.h" //Stat objects
#include "structs.h" //Game structs
#include "collections.h" //LinkedLists and Dictionarys
#include "flags.h" //Game bit flags
#include "functions.h" //Loose game functions
#include "item.h" //Item objects
#include "random.h" //GmRand

namespace Flow{

    /**
     * Defines an Actor (a game character). Actors represent both the player and enemies in the game
     */
    class Actor{
    private:
        /**
         * The game's difficulty, only meaningful in the player object
         */
        unsigned char _diff;

        /**
         * The Actor's job (class), only meaningful in the player object
         */
        Job _job;

        /**
         * The Actor's name
         */
        std::string _name;

        /**
         * A single byte Stat representing the Actor's attack power
         */
        BStat _atk;

        /**
         * A single byte Stat representing the Actor's defense power
         */
        BStat _def;

        /**
         * An int Stat representing the Actor's hit points
         */
        IStat _hp;

        /**
         * An int Stat representing the Actor's magic points
         */
        IStat _mp;

        /**
         * The Actor's current Weapon
         */
        Weapon _weap;

        /**
         * The Actor's current Armor
         */
        Armor _armor;

        /**
         * The Actor's current Inventory
         */
        Collections::LinkedList<std::shared_ptr<Item>> _inv;
    public:
        Actor();
        void addItem(const Potion&);
        void addItem(const Weapon&);
        void addItem(const Armor&);
        void addItem(const std::shared_ptr<Item>&);
        void addItems(const Actor&);
        void attack(unsigned char);
        void attack(const BStat&);
        void defense(unsigned char);
        void defense(const BStat&);
        void difficulty(unsigned char);
        void equip(const Weapon&, bool = true);
        void equip(const Armor&, bool = true);
        void hit(Actor&);
        void hp(int);
        void hp(const IStat&);
        void identify(unsigned int, bool = false);
        void job(Job);
        void mp(int);
        void mp(const IStat&);
        void name(const std::string&);
        void obfuscate();
        void removeItem(unsigned int);
        void use(unsigned int, bool = true);
        unsigned char difficulty() const;
        unsigned int invSize();
        int selectItem();
        std::string name() const;
        Job job() const;
        BStat attack() const;
        BStat defense() const;
        IStat hp() const;
        IStat mp() const;
        Armor armor() const;
        Weapon weapon() const;
        Collections::LinkedList<std::string> inventoryMenu();
    };

    std::string toString(Job);
}

#endif /* ACTOR_H */

