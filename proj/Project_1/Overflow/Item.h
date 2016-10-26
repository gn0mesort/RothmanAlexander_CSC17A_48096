/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Item.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define game items and item types
 * Created on October 14, 2016
 */

#ifndef ITEM_H
#define ITEM_H

#include "Flags.h"
#include "BinArray.h"

namespace Flow{
    
    //The number of valid ItmTypes
    const unsigned char ITM_CNT = 3;
    
    //ItmType
    //Item type enumeration. Defines the different kinds of items found in the game
    enum class ItmType {
        None = 0,
        Potion = 1,
        Armor = 2,
        Weapon = 3
    };
    
    //Item
    //Defines an item object. Used for all types of item in the game
    class Item{
    private:
        bool _ident;
        unsigned char _elem;
        unsigned char _value;
        ItmType _type;
        std::string _desc;
        std::string _name;
        std::string _uiName;
    public:
        //Static functions
        static std::string mkDesc(unsigned char, ItmType, unsigned char);
        static std::string mkName(unsigned char, ItmType);
        
        Item();
        Item(const Item&);
        Item(std::string, std::string = "Unknown Item", std::string = "An Item", 
        unsigned char = DmgElem::NONE, ItmType = ItmType::Potion, unsigned char = 0, bool = false);
        void identify();
        void mkDesc();
        void obfscte();
        void setDesc(std::string);
        void setElem(unsigned char);
        void setName(std::string);
        void setType(ItmType);
        void setUiName(std::string);
        void setValue(unsigned char);
        void toItem(BinArray&);
        bool isIdent() const;
        unsigned char element() const;
        unsigned char value() const;
        ItmType type() const;
        std::string desc() const;
        std::string name() const;
        std::string uiName() const;
        BinArray toBin();
    };
    
}

#endif /* ITEM_H */

