/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Actor.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define Actor objects which represent both game players and enemies
 * Created on October 15, 2016
 */

#ifndef ACTOR_H
#define ACTOR_H

//System Libraries
#include <string> //String type and functions
#include <vector> //Vector collections
#include <iostream> //I/O

//User Libraries
#include "Item.h" //Item objects
#include "Stat.h" //Statistic objects
#include "BinArray.h" //BinArray objects

namespace Flow{
    const unsigned char JOB_CNT = 4; //The number of valid Jobs

    //Job
    //An enumeration type defining game Jobs (classes)
    enum class Job {
        None = 0,
        Knight = 1,
        Cleric = 2,
        Mage = 3,
        Lancer = 4 
    };

    //Actor
    //Describes any character in the game who is capable of acting. This is used both for the player and their enemies.
    //Also defines functions for creating binary data from Actor objects
    class Actor{
    private:
        Job _job; //The Actor's job
        std::string _name; //The Actor's name
        BStat _atk; //The Actor's Attack Statistic
        BStat _def; //The Actor's Defense Statistic
        IStat _hp; //The Actor's Hit Points Statistic
        IStat _mp; //The Actor's Magic Points Statistic
        Item _weap; //The Actor's equipped Weapon
        Item _armr; //The Actor's equipped Armor
        std::vector<Item> _inv; //The Actor's Inventory
    public:
        Actor();
        Actor(const Actor&);
        Actor(const std::string&, Job = Job::Knight);
        void addItem(const Item&);
        void attack(Actor&);
        void equip(unsigned int, bool = true);
        void equip(const Item&, bool = true);
        void identify(unsigned int, bool = false);
        void rmItem(unsigned int);
        void setAtk(unsigned char);
        void setAtk(const BStat&);
        void setDef(unsigned char);
        void setDef(const BStat&);
        void setHp(int);
        void setHp(const IStat&);
        void setJob(Job);
        void setMp(int);
        void setMp(const IStat&);
        void setName(const std::string&);
        void stat() const;
        void toActor(BinArray&);
        void use(unsigned int);
        unsigned int invSize() const;
        int selectItm();
        Job job() const;
        std::string name() const;
        BStat atk() const;
        BStat def() const;
        IStat hp() const;
        IStat mp() const;
        Item armr() const;
        Item getItem(unsigned int) const;
        Item weap() const;
        std::vector<std::string> invMenu() const;
        BinArray toBin();
    };

}

#endif /* ACTOR_H */

