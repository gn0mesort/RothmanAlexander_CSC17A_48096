/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   actor.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 2, 2016
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <iostream>
#include <memory>

#include "item.h"
#include "stat.h"
#include "random.h"
#include "collections.h"
#include "macros.h"

namespace Flow{

    enum class Job{
        None = 0,
        Knight = 1,
        Cleric = 2,
        Mage = 3,
        Lancer = 4
    };

    class Actor{
    private:
        unsigned char _diff;
        Job _job;
        std::string _name;
        BStat _atk;
        BStat _def;
        IStat _hp;
        IStat _mp;
        Weapon _weap;
        Armor _armor;
        Collections::LinkedList<std::shared_ptr<Item>> _inv;
    public:
        Actor();
        void addItem(const Potion&);
        void addItem(const Weapon&);
        void addItem(const Armor&);
        void hit(Actor&);
        void equip(const Weapon&, bool = true);
        void equip(const Armor&, bool = true);
        void use(unsigned int);
        void identify(unsigned int, bool = false);
        void removeItem(unsigned int);
        BStat attack() const;
        void attack(unsigned char);
        void attack(const BStat&);
        BStat defense() const;
        void defense(unsigned char);
        void defense(const BStat&);
        IStat hp() const;
        void hp(int);
        void hp(const IStat&);
        Job job() const;
        void job(Job);
        IStat mp() const;
        void mp(int);
        void mp(const IStat&);
        std::string name() const;
        void name(const std::string&);
        Weapon weapon() const;
        Armor armor() const;
        unsigned int invSize();
        int selectItem();
        void addItems(const Actor&);
        unsigned char difficulty() const;
        void difficulty(unsigned char);
    };

    std::string toString(Job);
}

#endif /* ACTOR_H */

