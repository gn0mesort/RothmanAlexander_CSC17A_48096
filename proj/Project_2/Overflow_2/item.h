/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   item.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define various Item objects based on abstract Item class
 * Created on December 2, 2016
 */

#ifndef ITEM_H
#define ITEM_H

//User Libraries
#include "structs.h" //Game structs
#include "macros.h" //Preprocessor macros
#include "flags.h" //Game bit flags
#include "enums.h" //Enumeration types
#include "collections.h" //LinkedLists
#include "random.h" //Game RNG

namespace Flow{

    class Item{
    private:
    protected:
        /**
         * Whether or not the Item is identified
         */
        bool _ident;

        /**
         * The Item's element
         */
        unsigned char _elem;

        /**
         * The Item's value
         */
        unsigned char _value;

        /**
         * The Item's description
         */
        std::string _desc;

        /**
         * The Item's name
         */
        std::string _name;

        /**
         * The Item's unidentified name
         */
        std::string _uiName;

        /**
         * The RNG position that generated this Item
         */
        RNGPoint _genPoint;

        virtual std::string createDescription() = 0;
        virtual std::string createName() = 0;
    public:
        Item();
        Item(const Item&);
        Item(unsigned char, unsigned char);
        Item(const std::string&, const std::string& = "Unknown Item", const std::string& = "An Item",
             unsigned char = DmgElem::NONE, unsigned char = 0, bool = false);
        void description(const std::string&);
        void generationPoint(const RNGPoint&);
        void identify();
        void name(const std::string&);
        void obfuscate();
        void unidentifiedName(const std::string&);
        void value(unsigned char);
        bool isIdenitfied() const;
        unsigned char value() const;
        std::string description() const;
        std::string name() const;
        std::string unidentifiedName() const;
        RNGPoint generationPoint() const;

        virtual void element(unsigned char);
        virtual unsigned char element() const;
        virtual ItemType type() const;
    };

    class Weapon : public Item{
    private:
    protected:
        std::string createDescription() override;
        std::string createName() override;
        std::string createName(const Collections::LinkedList<std::string>&);
    public:
        Weapon();
        Weapon(const Weapon&);
        Weapon(unsigned char, unsigned char);
        Weapon(const std::string&, const std::string& = "Unknown Item", const std::string& = "An Item",
               unsigned char = DmgElem::NONE, unsigned char = 0, bool = false,
               const Collections::LinkedList<std::string>* = 0);
        void element(unsigned char) override;
        void element(unsigned char, const Collections::LinkedList<std::string>&);
        unsigned char element() const override;
        ItemType type() const override;
    };

    class Armor : public Item{
    private:
    protected:
        std::string createDescription() override;
        std::string createName() override;
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
        std::string createDescription() override;
        std::string createName() override;
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

