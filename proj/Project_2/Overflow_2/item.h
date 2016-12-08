/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   item.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 2, 2016
 */

#ifndef ITEM_H
#define ITEM_H

#include "structs.h"
#include "macros.h"
#include "flags.h"
#include "enums.h"
#include "collections.h"
#include "random.h"

namespace Flow{

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

        virtual ItemType type() const;
    };

    class Weapon : public Item{
    private:
    protected:
        std::string createName() override;
        std::string createName(const Collections::LinkedList<std::string>&);
        std::string createDescription() override;
    public:
        Weapon();
        Weapon(const Weapon&);
        Weapon(unsigned char, unsigned char);
        Weapon(const std::string&, const std::string& = "Unknown Item", const std::string& = "An Item",
               unsigned char = DmgElem::NONE, unsigned char = 0, bool = false,
               const Collections::LinkedList<std::string>* = 0);
        unsigned char element() const override;
        void element(unsigned char) override;
        void element(unsigned char, const Collections::LinkedList<std::string>&);
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
        ItemType type() const override;
    };
}

#endif /* ITEM_H */

