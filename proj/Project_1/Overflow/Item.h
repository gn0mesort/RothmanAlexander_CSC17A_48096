/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Item.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 14, 2016
 */

#ifndef ITEM_H
#define ITEM_H

#include "Flags.h"
#include "BinArray.h"


namespace Flow{
    const unsigned char ITM_CNT = 3;
    
    enum class ItmType {
        None = 0,
        Potion = 1,
        Armor = 2,
        Weapon = 3
    };
    
    class Item{
    public:
        Item();
        Item(const Item&);
        Item(std::string, std::string = "Unknown Item", std::string = "An Item", 
        unsigned char = DmgElem::NONE, ItmType = ItmType::Potion, unsigned char = 0, bool = false);
        //~Item();
        bool isIdent() const;
        void identify();
        void obfscte();
        unsigned char element() const;
        void setElem(unsigned char);
        unsigned char value() const;
        void setValue(unsigned char);
        std::string name() const;
        void setName(std::string);
        std::string uiName() const;
        void setUiName(std::string);
        std::string desc() const;
        void setDesc(std::string);
        ItmType type() const;
        void setType(ItmType);
        static std::string mkDesc(unsigned char, ItmType, unsigned char);
        void mkDesc();
        static std::string mkName(unsigned char, ItmType);
        BinArray toBin();
    private:
        bool _ident;
        unsigned char _elem;
        unsigned char _value;
        std::string _name;
        std::string _uiName;
        std::string _desc;
        ItmType _type;
    };
}

#endif /* ITEM_H */

