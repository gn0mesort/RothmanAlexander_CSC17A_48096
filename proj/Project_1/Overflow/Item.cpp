/*
 * File:   Item.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 14, 2016
 */

#include <sstream>
#include <cstring>

#include "Item.h"
#include "Game.h"

Flow::Item::Item(){
    _ident = false;
    _elem = DmgElem::NONE;
    _value = 0;
    _name = "Item";
    _uiName = "Unknown Item";
    _desc = "An Item";
    _type = ItmType::Potion;
}

Flow::Item::Item(const Item &other){
    if(this != &other){
        _ident = other.isIdent();
        _elem = other.element();
        _value = other.value();
        _name = other.name();
        _uiName = other.uiName();
        _desc = other.desc();
        _type = other.type();
    }
}

Flow::Item::Item(std::string name, std::string uiName, std::string desc, unsigned char elem, ItmType type,
                 unsigned char value, bool ident){
    _ident = ident;
    setElem(elem);
    _value = value;
    _name = name;
    _uiName = uiName;
    _desc = desc;
    _type = type;
}

bool Flow::Item::isIdent() const{
    return _ident;
}

void Flow::Item::identify(){
    if(!_ident){
        _ident = true;
    }
}

void Flow::Item::obfscte(){
    if(_ident){
        _ident = false;
    }
}

unsigned char Flow::Item::element() const{
    return _elem;
}

void Flow::Item::setElem(unsigned char elem){
    _elem = elem;
    if(Flow::FlgUtil::hasFlag(_elem, (Flow::DmgElem::FIRE | Flow::DmgElem::WIND))
       && _elem != Flow::DmgElem::ABSOLUT){
        _elem ^= (Flow::DmgElem::FIRE | Flow::DmgElem::WIND);
    }
    if(Flow::FlgUtil::hasFlag(_elem, (Flow::DmgElem::ICE | Flow::DmgElem::LIGHTNG))
       && _elem != Flow::DmgElem::ABSOLUT){
        _elem ^= (Flow::DmgElem::ICE | Flow::DmgElem::LIGHTNG);
    }
    _name = Item::mkName(_elem, _type);
    _desc = Item::mkDesc(_elem, _type, _value);
}

unsigned char Flow::Item::value() const{
    return _value;
}

void Flow::Item::setValue(unsigned char value){
    _value = value;
}

std::string Flow::Item::name() const{
    return _name;
}

void Flow::Item::setName(std::string name){
    _name = name;
}

std::string Flow::Item::uiName() const{
    return _uiName;
}

void Flow::Item::setUiName(std::string uiName){
    _uiName;
}

std::string Flow::Item::desc() const{
    return _desc;
}

void Flow::Item::setDesc(std::string desc){
    _desc = desc;
}

Flow::ItmType Flow::Item::type() const{
    return _type;
}

void Flow::Item::setType(Flow::ItmType type){
    _type = type;
}

std::string Flow::Item::mkDesc(unsigned char elem, Flow::ItmType type, unsigned char value){
    std::stringstream r;

    if(type == Flow::ItmType::Potion){
        if(elem == Flow::DmgElem::NONE){
            r << "Identifies 1 item. ";
        }
        if(elem == Flow::DmgElem::ABSOLUT){
            r << "Fully restores HP and MP. ";
        }
        else{
            if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::HEALING)){
                r << "Restores " << toInt(value) << " HP. ";
            }
            if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::FIRE)){
                r << "Increases Attack by " << toInt(value) << ". ";
            }
            if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::ICE)){
                r << "Increases Defense by " << toInt(value) << ". ";
            }
            if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::LIGHTNG)){
                r << "Decreases Defense by " << toInt(value) << ". ";
            }
            if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::WIND)){
                r << "Decreases Attack by " << toInt(value) << ". ";
            }
            if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::HOLY)){
                r << "Increases max HP by " << toInt(value) << ". ";
            }
            if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::SHADOW)){
                r << "Increases max MP by " << toInt(value) << ". ";
            }
            if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::NGHTMRE)){
                r << "Obfuscates all items. ";
            }
        }
    }
    else if(type == Flow::ItmType::Weapon){
        if(elem == Flow::DmgElem::NONE){
            r << "+" << toInt(value) << " Attack. ";
        }
        else{
            r << "Deals ( " << Flow::DmgElem::toStr(elem) << ") damage. +" << toInt(value) << " Attack. ";
        }
    }
    else if(type == Flow::ItmType::Armor){
        if(elem == Flow::DmgElem::NONE){
            r << "+" << toInt(value) << " Defense. ";
        }
        else{
            r << "Resists ( " << Flow::DmgElem::toStr(elem) << ") damage. +" << toInt(value) << " Defense. ";
        }
    }

    return r.str();
}

void Flow::Item::mkDesc(){
    _desc = mkDesc(_elem, _type, _value);
}

std::string Flow::Item::mkName(unsigned char elem, Flow::ItmType type){
    std::stringstream r;

    switch(type){
        case Flow::ItmType::Armor:
        {
            if(elem == Flow::DmgElem::ABSOLUT){
                r << "Legendary ";
            }
            else{
                if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::HEALING)){
                    r << "Curative ";
                }
                if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::NGHTMRE)){
                    r << "Weirding ";
                }
                if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::HOLY | Flow::DmgElem::SHADOW))){
                    r << "Streaked ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::HOLY)){
                    r << "Sanctified ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::SHADOW)){
                    r << "Damned ";
                }
                if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::FIRE | Flow::DmgElem::ICE))){
                    r << "Cauterizing ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::FIRE | Flow::DmgElem::LIGHTNG))){
                    r << "Quivering ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::FIRE)){
                    r << "Flaming ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::LIGHTNG)){
                    r << "Shocking ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::ICE | Flow::DmgElem::WIND))){
                    r << "Steaming ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::ICE)){
                    r << "Frosted ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::WIND)){
                    r << "Storming ";
                }
            }

            r << "Armor";
            break;
        }
        case Flow::ItmType::Potion:
        {
            if(elem == Flow::DmgElem::NONE){
                r << "Identifying ";
            }
            if(elem == Flow::DmgElem::ABSOLUT){
                r << "Invigorating ";
            }
            else{
                if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::HEALING)){
                    r << "Frothing ";
                }
                if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::NGHTMRE)){
                    r << "Obfuscating ";
                }
                if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::HOLY | Flow::DmgElem::SHADOW))){
                    r << "Swirling ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::HOLY)){
                    r << "Sanctified ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::SHADOW)){
                    r << "Damned ";
                }
                if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::FIRE | Flow::DmgElem::ICE))){
                    r << "Bubbling ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::FIRE | Flow::DmgElem::LIGHTNG))){
                    r << "Thickened ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::FIRE)){
                    r << "Searing ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::LIGHTNG)){
                    r << "Convulsing ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::ICE | Flow::DmgElem::WIND))){
                    r << "Misty ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::ICE)){
                    r << "Freezing ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::WIND)){
                    r << "Harrowing ";
                }
            }

            r << "Potion";
            break;
        }
        case Flow::ItmType::Weapon:
        {
            if(elem == Flow::DmgElem::ABSOLUT){
                r << "Legendary ";
            }
            else{
                if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::HEALING)){
                    r << "Curative ";
                }
                if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::NGHTMRE)){
                    r << "Weirding ";
                }
                if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::HOLY | Flow::DmgElem::SHADOW))){
                    r << "Streaked ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::HOLY)){
                    r << "Sanctified ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::SHADOW)){
                    r << "Damned ";
                }
                if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::FIRE | Flow::DmgElem::ICE))){
                    r << "Cauterizing ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::FIRE | Flow::DmgElem::LIGHTNG))){
                    r << "Quivering ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::FIRE)){
                    r << "Flaming ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::LIGHTNG)){
                    r << "Shocking ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, (Flow::DmgElem::ICE | Flow::DmgElem::WIND))){
                    r << "Steaming ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::ICE)){
                    r << "Frosted ";
                }
                else if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::WIND)){
                    r << "Storming ";
                }
            }

            if(Game::player.job() != Flow::Job::None){
                int loc = static_cast<int>(Game::player.job()) - 1;
                r << Game::nWeaps[loc].at(Game::gmRand.rand() % Game::nWeaps[loc].size());
            }
            else{
                r << "Fists";
            }

            break;
        }
        default:
        {
            r << "Invalid Type";
        }
    }

    return r.str();
}

Flow::BinArray Flow::Item::toBin(){
    BinArray name = Flow::toBin(_name),
            uiName = Flow::toBin(_uiName),
            desc = Flow::toBin(_desc),
            r(name.size() + uiName.size() + desc.size() + sizeof (_elem) + sizeof (_value) + sizeof (_type)
              + sizeof (_ident));

    r << name;
    r << uiName;
    r << desc;
    r << BinArray(reinterpret_cast<char*>(&_elem), sizeof (_elem));
    r << BinArray(reinterpret_cast<char*>(&_value), sizeof (_value));
    r << BinArray(reinterpret_cast<char*>(&_type), sizeof (_type));
    r << BinArray(reinterpret_cast<char*>(&_ident), sizeof (_ident));

    return r;
}

void Flow::Item::toItem(BinArray &data){
    BinArray strSize(sizeof (unsigned int)),
            str,
            elem(sizeof (_elem)),
            value(sizeof (_value)),
            iType(sizeof (_type)),
            ident(sizeof (_ident));

    data >> strSize;
    str = BinArray(sizeof (unsigned int) +Flow::toInt(strSize));
    data.seekg(data.tellg() - sizeof (unsigned int));
    data >> str;
    _name = Flow::toStr(str);

    data >> strSize;
    str = BinArray(sizeof (unsigned int) +Flow::toInt(strSize));
    data.seekg(data.tellg() - sizeof (unsigned int));
    data >> str;
    _uiName = Flow::toStr(str);

    data >> strSize;
    str = BinArray(sizeof (unsigned int) +Flow::toInt(strSize));
    data.seekg(data.tellg() - sizeof (unsigned int));
    data >> str;
    _desc = Flow::toStr(str);

    data >> elem;
    _elem = elem[0];

    data >> value;
    _value = value[0];

    data >> iType;
    _type = static_cast<ItmType>(toInt(iType));

    data >> ident;
    _ident = ident[0];
}