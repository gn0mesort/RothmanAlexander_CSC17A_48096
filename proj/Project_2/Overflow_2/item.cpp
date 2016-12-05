/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   item.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 2, 2016
 */

#include "item.h"
#include "stat.h"
#include "actor.h"

Flow::Item::Item(){
    _ident = false;
    _elem = DmgElem::NONE;
    _value = 0;
    _name = "Item";
    _uiName = "Unknown Item";
    _desc = "An Item";
}

Flow::Item::Item(const Item &other){
    _ident = other.isIdenitfied();
    _elem = other.element();
    _value = other.value();
    _name = other.name();
    _uiName = other.unidentifiedName();
    _desc = other.description();
    _genPoint = other.generationPoint();
}

Flow::Item::Item(unsigned char elem, unsigned char value){
    _ident = false;
    _elem = elem;
    _value = value;
    _genPoint.pos = 0;
    _genPoint.seed = 0;
}

Flow::Item::Item(const std::string &name, const std::string &uiName, const std::string &desc, unsigned char elem,
                 unsigned char value, bool ident){
    _ident = ident;
    _elem = elem;
    _value = value;
    _name = name;
    _uiName = uiName;
    _desc = desc;
    _genPoint.pos = 0;
    _genPoint.seed = 0;
}

void Flow::Item::identify(){
    _ident = true;
}

void Flow::Item::obfuscate(){
    _ident = false;
}

std::string Flow::Item::description() const{
    return _desc;
}

void Flow::Item::description(const std::string &desc){
    _desc = desc;
}

unsigned char Flow::Item::element() const{
    return _elem;
}

void Flow::Item::element(unsigned char elem){
    _elem = elem;
    if(FlagUtil::hasFlag(_elem, (DmgElem::FIRE | DmgElem::WIND)) && _elem != DmgElem::ABSOLUT){
        _elem ^= (DmgElem::FIRE | DmgElem::WIND);
    }
    if(FlagUtil::hasFlag(_elem, (DmgElem::ICE | DmgElem::LIGHTNG)) && _elem != DmgElem::ABSOLUT){
        _elem ^= (DmgElem::ICE | DmgElem::LIGHTNG);
    }
    _name = createName();
    _desc = createDescription();
}

std::string Flow::Item::name() const{
    return _name;
}

void Flow::Item::name(const std::string &nName){
    _name = nName;
}

std::string Flow::Item::unidentifiedName() const{
    return _uiName;
}

void Flow::Item::unidentifiedName(const std::string &uiName){
    _uiName = uiName;
}

bool Flow::Item::isIdenitfied() const{
    return _ident;
}

unsigned char Flow::Item::value() const{
    return _value;
}

void Flow::Item::value(unsigned char nValue){
    _value = nValue;
}

Flow::ItemType Flow::Item::type() const{
    return ItemType::None;
}

Flow::RNGPoint Flow::Item::generationPoint() const{
    return _genPoint;
}

void Flow::Item::generationPoint(const RNGPoint &genPoint){
    _genPoint = genPoint;
}

Flow::Weapon::Weapon() : Flow::Item(){ }

Flow::Weapon::Weapon(const Weapon &other) : Flow::Item(other){ }

Flow::Weapon::Weapon(unsigned char elem, unsigned char value) : Flow::Item(0, value){
    element(elem);
}

Flow::Weapon::Weapon(const std::string &name, const std::string &uiName, const std::string &desc, unsigned char elem,
                     unsigned char value, bool ident) : Flow::Item(name, uiName, desc, 0, value, ident){
    element(elem);
}

std::string Flow::Weapon::createName(){
    std::stringstream r;

    if(_elem == Flow::DmgElem::ABSOLUT){ //If ABSOLUT
        r << "Legendary ";
    }
    else{ //Otherwise (again the same as armor and potions)
        if(FlagUtil::hasFlag(_elem, DmgElem::HEALING)){
            r << "Curative ";
        }
        if(FlagUtil::hasFlag(_elem, DmgElem::NGHTMRE)){
            r << "Weirding ";
        }
        if(FlagUtil::hasFlag(_elem, (DmgElem::HOLY | DmgElem::SHADOW))){
            r << "Streaked ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::HOLY)){
            r << "Sanctified ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::SHADOW)){
            r << "Damned ";
        }
        if(FlagUtil::hasFlag(_elem, (DmgElem::FIRE | DmgElem::ICE))){
            r << "Cauterizing ";
        }
        else if(FlagUtil::hasFlag(_elem, (DmgElem::FIRE | DmgElem::LIGHTNG))){
            r << "Quivering ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::FIRE)){
            r << "Flaming ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::LIGHTNG)){
            r << "Shocking ";
        }
        else if(FlagUtil::hasFlag(_elem, (DmgElem::ICE | DmgElem::WIND))){
            r << "Steaming ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::ICE)){
            r << "Frosted ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::WIND)){
            r << "Storming ";
        }
    }

    try{
        if(Game::get<Actor>("player")->job() != Job::None){ //If the player has a set Job
            std::shared_ptr<Collections::Dictionary<Job, Collections::LinkedList < std::string>>> nWeaps =
                    Game::get<Collections::Dictionary<Job, Collections::LinkedList < std::string>>>("weapon_names");
            r << (*nWeaps)[Game::get<Actor>("player")->job()][Game::get<GmRand>("rand")->rand() %
                    (*nWeaps)[Game::get<Actor>("player")->job()].size()]; //Insert the weapon name
        }
        else{ //Otherwise
            r << "Fists";
        }
    }
    catch(Error::ArgumentException e){
        r << "Fists";
    }

    return r.str();
}

std::string Flow::Weapon::createDescription(){
    std::stringstream r;

    if(_elem == DmgElem::NONE){ //If no element
        r << "+" << to_int(_value) << " Attack. ";
    }
    else{ //Otherwise
        r << "Deals ( " << DmgElem::toString(_elem) << ") damage. +" << to_int(_value) << " Attack. ";
    }

    return r.str();
}

bool Flow::Weapon::use(Actor &target){
    identify();
    target.equip(*this);
    return true;
}

Flow::ItemType Flow::Weapon::type() const{
    return ItemType::Weapon;
}

Flow::Armor::Armor() : Flow::Item(){ }

Flow::Armor::Armor(const Armor &other) : Flow::Item(other){ }

Flow::Armor::Armor(unsigned char elem, unsigned char value) : Flow::Item(0, value){
    element(elem);
}

Flow::Armor::Armor(const std::string &name, const std::string &uiName, const std::string &desc, unsigned char elem,
                   unsigned char value, bool ident) : Flow::Item(name, uiName, desc, 0, value, ident){
    element(elem);
}

std::string Flow::Armor::createName(){
    std::stringstream r;

    if(_elem == DmgElem::ABSOLUT){ //If ABSOLUT
        r << "Legendary ";
    }
    else{ //Otherwise
        if(FlagUtil::hasFlag(_elem, DmgElem::HEALING)){ //If the HEALING flag is on
            r << "Curative ";
        }
        if(FlagUtil::hasFlag(_elem, DmgElem::NGHTMRE)){ //If the NGHTMRE flag is on
            r << "Weirding ";
        }
        if(FlagUtil::hasFlag(_elem, (DmgElem::HOLY | DmgElem::SHADOW))){ //If the HOLY and SHADOW flags are on
            r << "Streaked ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::HOLY)){ //If the HOLY flag is on
            r << "Sanctified ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::SHADOW)){ //If the SHADOW flag is on
            r << "Damned ";
        }
        if(FlagUtil::hasFlag(_elem, (DmgElem::FIRE | DmgElem::ICE))){ //If the FIRE and ICE flags are on
            r << "Cauterizing ";
        }
        else if(FlagUtil::hasFlag(_elem, (DmgElem::FIRE | DmgElem::LIGHTNG))){ //If the FIRE and LIGHTNG flags are on
            r << "Quivering ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::FIRE)){ //If the FIRE flag is on
            r << "Flaming ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::LIGHTNG)){ //If the LIGHTNG flag is on
            r << "Shocking ";
        }
        else if(FlagUtil::hasFlag(_elem, (DmgElem::ICE | DmgElem::WIND))){ //If the ICE and WIND flags are on
            r << "Steaming ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::ICE)){ //If the ICE flag is on
            r << "Frosted ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::WIND)){ //If the WIND flag is on
            r << "Storming ";
        }
    }

    r << "Armor";

    return r.str();
}

std::string Flow::Armor::createDescription(){
    std::stringstream r;

    if(_elem == DmgElem::NONE){ //If no element
        r << "+" << to_int(_value) << " Defense. ";
    }
    else{
        r << "Resists ( " << DmgElem::toString(_elem) << ") damage. +" << to_int(_value) << " Defense. ";
    }

    return r.str();
}

bool Flow::Armor::use(Actor &target){
    identify();
    target.equip(*this);
    return true;
}

Flow::ItemType Flow::Armor::type() const{
    return ItemType::Armor;
}

Flow::Potion::Potion() : Flow::Item(){ }

Flow::Potion::Potion(const Potion &other) : Flow::Item(other){ }

Flow::Potion::Potion(unsigned char elem, unsigned char value) : Flow::Item(0, value){
    element(elem);
}

Flow::Potion::Potion(const std::string &name, const std::string &uiName, const std::string &desc, unsigned char elem,
                     unsigned char value, bool ident) : Flow::Item(name, uiName, desc, 0, value, ident){
    element(elem);
}

std::string Flow::Potion::createName(){
    std::stringstream r;

    if(_elem == Flow::DmgElem::NONE){ //If NONE
        r << "Identifying ";
    }
    if(_elem == Flow::DmgElem::ABSOLUT){ //If ABSOLUT
        r << "Invigorating ";
    }
    else{ //Otherwise (This is the same as with weapons and armor even though the names are different)
        if(FlagUtil::hasFlag(_elem, DmgElem::HEALING)){
            r << "Frothing ";
        }
        if(FlagUtil::hasFlag(_elem, DmgElem::NGHTMRE)){
            r << "Obfuscating ";
        }
        if(FlagUtil::hasFlag(_elem, (DmgElem::HOLY | DmgElem::SHADOW))){
            r << "Swirling ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::HOLY)){
            r << "Sanctified ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::SHADOW)){
            r << "Damned ";
        }
        if(FlagUtil::hasFlag(_elem, (DmgElem::FIRE | DmgElem::ICE))){
            r << "Bubbling ";
        }
        else if(FlagUtil::hasFlag(_elem, (DmgElem::FIRE | DmgElem::LIGHTNG))){
            r << "Thickened ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::FIRE)){
            r << "Searing ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::LIGHTNG)){
            r << "Convulsing ";
        }
        else if(FlagUtil::hasFlag(_elem, (DmgElem::ICE | DmgElem::WIND))){
            r << "Misty ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::ICE)){
            r << "Freezing ";
        }
        else if(FlagUtil::hasFlag(_elem, DmgElem::WIND)){
            r << "Harrowing ";
        }
    }

    r << "Potion";

    return r.str();
}

std::string Flow::Potion::createDescription(){
    std::stringstream r;

    if(_elem == DmgElem::NONE){ //If the Item element is NONE
        r << "Identifies 1 item. ";
    }
    if(_elem == DmgElem::ABSOLUT){ //If the Item element is ABSOLUT
        r << "Fully restores HP and MP. ";
    }
    else{ //Otherwise
        if(FlagUtil::hasFlag(_elem, DmgElem::HEALING)){ //If the HEALING flag is on
            r << "Restores " << to_int(_value) << " HP. ";
        }
        if(FlagUtil::hasFlag(_elem, DmgElem::FIRE)){ //If the FIRE flag is on
            r << "Increases Attack by " << to_int(_value) << ". ";
        }
        if(FlagUtil::hasFlag(_elem, DmgElem::ICE)){ //If the ICE flag is on
            r << "Increases Defense by " << to_int(_value) << ". ";
        }
        if(FlagUtil::hasFlag(_elem, DmgElem::LIGHTNG)){ //If the LIGHTNG flag is on
            r << "Decreases Defense by " << to_int(_value) << ". ";
        }
        if(FlagUtil::hasFlag(_elem, DmgElem::WIND)){ //If the WIND flag is on
            r << "Decreases Attack by " << to_int(_value) << ". ";
        }
        if(FlagUtil::hasFlag(_elem, DmgElem::HOLY)){ //If the HOLY flag is on
            r << "Increases max HP by " << to_int(_value) << ". ";
        }
        if(FlagUtil::hasFlag(_elem, DmgElem::SHADOW)){ //If the SHADOW flag is on
            r << "Increases max MP by " << to_int(_value) << ". ";
        }
        if(FlagUtil::hasFlag(_elem, DmgElem::NGHTMRE)){ //If the NGHTMRE flag is on
            r << "Obfuscates all items. ";
        }
    }

    return r.str();
}

bool Flow::Potion::use(Actor &target){
    return false;
}

Flow::ItemType Flow::Potion::type() const{
    return ItemType::Potion;
}