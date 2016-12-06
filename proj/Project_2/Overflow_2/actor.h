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

#include <memory>

#include "enums.h"
#include "stat.h"
#include "structs.h"
#include "collections.h"
#include "flags.h"
#include "functions.h"

namespace Flow{
    class Actor;

    class Item{
    private:
    protected:
        bool _ident;
        unsigned char _elem;
        unsigned char _value;
        std::string _desc;
        std::string _name;
        std::string _uiName;
        RNGPoint _genPoint;

        virtual std::string createName() = 0;
        virtual std::string createDescription() = 0;
    public:
        Item();
        Item(const Item&);
        Item(unsigned char, unsigned char);
        Item(const std::string&, const std::string& = "Unknown Item", const std::string& = "An Item",
             unsigned char = DmgElem::NONE, unsigned char = 0, bool = false);
        void identify();
        void obfuscate();
        std::string description() const;
        void description(const std::string&);
        virtual unsigned char element() const;
        virtual void element(unsigned char);
        std::string name() const;
        void name(const std::string&);
        std::string unidentifiedName() const;
        void unidentifiedName(const std::string&);
        unsigned char value() const;
        void value(unsigned char);
        bool isIdenitfied() const;
        RNGPoint generationPoint() const;
        void generationPoint(const RNGPoint&);

        virtual bool use(Actor&, bool = true) = 0;
        virtual ItemType type() const;
    };

    class Weapon : public Item{
    private:
    protected:
        std::string createName() override;
        std::string createName(Game&);
        std::string createDescription() override;
    public:
        Weapon();
        Weapon(const Weapon&);
        Weapon(unsigned char, unsigned char, Game&);
        Weapon(unsigned char, unsigned char);
        Weapon(Game&, const std::string&, const std::string& = "Unknown Item", const std::string& = "An Item",
               unsigned char = DmgElem::NONE, unsigned char = 0, bool = false);
        unsigned char element() const override;
        void element(unsigned char) override;
        void element(unsigned char, Game&);
        bool use(Actor&, bool = true) override;
        ItemType type() const override;
    };

    class Armor : public Item{
    private:
    protected:
        std::string createName() override;
        std::string createDescription() override;
    public:
        Armor();
        Armor(const Armor&);
        Armor(unsigned char, unsigned char);
        Armor(const std::string&, const std::string& = "Unknown Item", const std::string& = "An Item",
              unsigned char = DmgElem::NONE, unsigned char = 0, bool = false);
        bool use(Actor&, bool = true) override;
        ItemType type() const override;
    };

    class Potion : public Item{
    private:
    protected:
        std::string createName() override;
        std::string createDescription() override;
    public:
        Potion();
        Potion(const Potion&);
        Potion(unsigned char, unsigned char);
        Potion(const std::string&, const std::string& = "Unknown Item", const std::string& = "An Item",
               unsigned char = DmgElem::NONE, unsigned char = 0, bool = false);
        bool use(Actor&, bool = true) override;
        ItemType type() const override;
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
        void use(unsigned int, bool = true);
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
        Collections::LinkedList<std::string> inventoryMenu();
        void obfuscate();
    };



    std::string toString(Job);
}

#endif /* ACTOR_H */

