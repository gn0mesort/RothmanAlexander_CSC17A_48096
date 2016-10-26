/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Actor.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for Actor.h
 * Created on October 15, 2016
 */

#include <iostream>
#include <sstream>

#include "Actor.h"
#include "Room.h"
#include "Game.h"
#include "BinArray.h"

//Actor
//Default constructor for an Actor object
Flow::Actor::Actor(){
    _job = Job::Knight;
    _hp = IStat(std::string("HP"), std::string("Hit Points"), 100);
    _mp = IStat(std::string("MP"), std::string("Magic Points"), 100);
    _atk = BStat(std::string("ATK"), std::string("Attack"), 10);
    _def = BStat(std::string("DEF"), std::string("Defense"), 10);
    _name = "Player";
    _weap = Item("Fists", "Fists", "Your fists", DmgElem::NONE, ItmType::Weapon, 1, true);
    _armr = Item("Clothes", "Clothes", "Your Clothes", DmgElem::NONE, ItmType::Armor, 1, true);
}

//Actor
//Copy constructor for an Actor object
Flow::Actor::Actor(const Actor &other){
    _job = other.job();
    _hp = IStat(other.hp());
    _mp = IStat(other.mp());
    _atk = BStat(other.atk());
    _def = BStat(other.def());
    _name = other.name();
    _weap = other.weap();
    _armr = other.armr();
    for(int i = 0; i < other.invSize(); ++i){ //For the entire other inventory
        _inv.push_back(other.getItem(i)); //Copy inventory
    }
}

//Actor
//Parameterized constructor for an Actor object
Flow::Actor::Actor(const std::string &name, Job job){
    _job = job;
    _name = name;
    _hp = IStat(std::string("HP"), std::string("Hit Points"), 100);
    _mp = IStat(std::string("MP"), std::string("Magic Points"), 100);
    _atk = BStat(std::string("ATK"), std::string("Attack"), 10);
    _def = BStat(std::string("DEF"), std::string("Defense"), 10);
    _weap = Item("Fists", "Fists", "Your fists", DmgElem::NONE, ItmType::Weapon, 1, true);
    _armr = Item("Clothes", "Clothes", "Your Clothes", DmgElem::NONE, ItmType::Armor, 1, true);
}

//Job
//Returns the Actor's Job
//Output:
//The current value of _job
Flow::Job Flow::Actor::job() const{
    return _job;
}

//setJob
//Sets the Actor's Job
//Input:
//job
//The new Job value to set _job to
void Flow::Actor::setJob(Job job){
    _job = job;
}

//hp
//Returns the Actor's current hp IStat
//Output:
//An IStat object holding the Actor's current hp
Flow::IStat Flow::Actor::hp() const{
    return _hp;
}

//setHp
//Sets the Actor's current hp IStat
//Input:
//hp
//An IStat to set _hp to 
void Flow::Actor::setHp(const IStat &hp){
    _hp = Flow::IStat(hp);
}

//mp
//Returns the Actor's current mp IStat
//Output:
//An IStat holding the Actor's current hp
Flow::IStat Flow::Actor::mp() const{
    return _mp;
}

//setMp
//Sets the Actor's current mp IStat
//Input:
//mp
//An IStat to set _mp to 
void Flow::Actor::setMp(const IStat &mp){
    _mp = Flow::IStat(mp);
}

//atk
//Returns the Actor's current atk BStat
//Output:
//A BStat holding the Actor's current atk
Flow::BStat Flow::Actor::atk() const{
    return _atk;
}

//setAtk
//Sets the Actor's current atk BStat
//Input:
//atk
//A BStat to set _atk to
void Flow::Actor::setAtk(const BStat &atk){
    _atk = Flow::BStat(atk);
}

//setAtk
//Set the value of the Actor's current atk BStat
//Input:
//atk
//A byte value to set the value of _atk to
void Flow::Actor::setAtk(unsigned char atk){
    _atk.setValue(atk);
}

//def
//Returns the Actor's current def BStat
//Output:
//A BStat holding the Actor's current def
Flow::BStat Flow::Actor::def() const{
    return _def;
}

//setDef
//Sets the Actor's current def BStat
//Input:
//def
//A BStat to set _def to
void Flow::Actor::setDef(const BStat &def){
    _def = Flow::BStat(def);
}

//setAtk
//Set the value of the Actor's current def BStat
//Input:
//def
//A byte value to set the value of _def to
void Flow::Actor::setDef(unsigned char def){
    _def.setValue(def);
}

//name
//Returns the Actor's name
//Output:
//The Actor's name as a string
std::string Flow::Actor::name() const{
    return _name;
}

//setName
//Sets the actor's name
//Input:
//name
//A string to set _name to
void Flow::Actor::setName(const std::string &name){
    _name = name;
}

//invSize
//Returns the size of the Actor's inventory vector
//Output:
//The size of the inventory vector. Equivalent to _inv.size()
unsigned int Flow::Actor::invSize() const{
    return _inv.size();
}

//addItem
//Adds an Item to the Actor's inventory vector
//Input:
//itm
//The Item to add to the inventory
void Flow::Actor::addItem(const Flow::Item &itm){
    _inv.push_back(itm);
}

//rmItem
//Removes an item from the Actor's inventory
//Input:
//index
//The index of the Item to remove
void Flow::Actor::rmItem(unsigned int index){
    _inv.erase(_inv.begin() + index);
}

//getItem
//Returns an Item from the Actor's inventory at the specified index
//Input:
//index
//The index to return the Item from
//Output:
//The Item at the given index
Flow::Item Flow::Actor::getItem(unsigned int index) const{
    return _inv[index];
}

//weap
//Return the Actor's currently equipped weapon
//Output:
//The Item stored in _weap
Flow::Item Flow::Actor::weap() const{
    return _weap;
}

//armr
//Return the Actor's currently equipped armor
//Output:
//The Item stored in _armr
Flow::Item Flow::Actor::armr() const{
    return _armr;
}

//equip
//Equip an item from the Actor's inventory
//Input:
//index
//The index of the item to equip
//output
//Whether or not to output any text
void Flow::Actor::equip(unsigned int index, bool output){
    if(_inv[index].type() == ItmType::Weapon){ //If The item is a weapon
        addItem(_weap); //Add the current weapon back to the inventory
        _weap = _inv[index]; //Equip the new weapon
        if(output){ //If text should be output
            std::cout << _name << " equipped " << _weap.name() << std::endl;
        }
        rmItem(index); //Remove the newly equipped weapon from the inventory 
    }
    else if(_inv[index].type() == ItmType::Armor){ //If item is armor
        addItem(_armr); //Add the current armor back to the inventory
        _armr = _inv[index]; //Equip the new armor
        if(output){ //If text should be output
            std::cout << _name << " equipped " << _armr.name() << std::endl;
        }
        rmItem(index); //Remove the newly equipped armor from the inventory
    }
}

//equip
//Equip the given input item. This overwrites the current equipment
//Input:
//itm
//The Item object to equip
//output
//Whether or not to output any text
void Flow::Actor::equip(const Item &itm, bool output){
    if(itm.type() == ItmType::Weapon){ //If itm is a weapon
        _weap = itm; //Equip the new weapon
        if(output){ //If text should be output
            std::cout << _name << " equipped " << _weap.name() << std::endl;
        }
    }
    else if(itm.type() == ItmType::Armor){ //If itm is armor
        _armr = itm; //Equip the new armor
        if(output){ //If text should be output
            std::cout << _name << " equipped " << _armr.name() << std::endl;
        }
    }
}

//use
//Uses the Item at the given inventory slot. Behavior depends on the type of item
//Input:
//index
//The index of the Item to use in the Actor's inventory
void Flow::Actor::use(unsigned int index){
    _inv[index].identify(); //When an Item is used it is implicitly identified
    if(_inv[index].type() == ItmType::Weapon || _inv[index].type() == ItmType::Armor){ //If the Item is a weapon or armor
        equip(index); //Equip it
    }
    else if(_inv[index].type() == ItmType::Potion){ //Otherwise if it's a potion
        Item target = Item(_inv[index]); //Copy the item out of the inventory
        std::cout << _name << " used " << target.name() << "." << std::endl; //Display usage message
        rmItem(index); //Remove the item from the inventory
        if(target.element() == DmgElem::NONE){ //If the item is an Identifying Potion
            if(_inv.size() > 0){ //If you have more than one Item in your inventory
               unsigned int select = 0;
               select = iMenu(invMenu(), 1);
               if(select > 0){ 
                    identify(select - 1, true);
               }
               else{
                   addItem(target);
               }
            }
            else{
                std::cout << "Nothing happens." << std::endl;
            }
        }
        else if(target.element() == DmgElem::ABSOLUT){
            std::cout << _name << " was fully restored!" << std::endl;
            _hp.setVal(_hp.max());
            _mp.setVal(_mp.max());
        }
        else{
            if(FlgUtil::hasFlag(target.element(), DmgElem::HEALING)){
                std::cout << _name << " recovered " << toInt(target.value()) << " HP!" << std::endl;
                _hp.setVal(_hp.value() + target.value());
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::FIRE)){
                std::cout << _name << "'s attack power increased by " << toInt(target.value()) << std::endl;
                _atk.setValue(_atk.value() + target.value());
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::ICE)){
                std::cout << _name << "'s defense increased by " << toInt(target.value()) << std::endl;
                _def.setValue(_def.value() + target.value());
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::LIGHTNG)){
                std::cout << _name << "'s defense decreased by " << toInt(target.value()) << std::endl;
                _def.setValue(_def.value() - target.value());
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::WIND)){
                std::cout << _name << "'s attack power decreased by " << toInt(target.value()) << std::endl;
                _atk.setValue(_atk.value() - target.value());
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::HOLY)){
                std::cout << _name << "'s maximum HP has increased by " << toInt(target.value()) << std::endl;
                _hp.setMax(_hp.max() + target.value());
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::SHADOW)){
                std::cout << _name << "'s maximum MP has increased by " << toInt(target.value()) << std::endl;
                _mp.setMax(_mp.max() + target.value());
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::NGHTMRE)){
                std::cout << _name << " had a terrible nightmare!" << std::endl;
                for(int i = 0; i < _inv.size(); ++i){
                    _inv[i].obfscte();
                }
            }
        }

    }
}

std::vector<std::string> Flow::Actor::invMenu() const{
    std::vector<std::string> r;
    for(int i = 0; i < _inv.size(); ++i){
        std::stringstream opt;
        if(_inv[i].isIdent()){
            opt << _inv[i].name() << std::endl;
            opt << "\t" << _inv[i].desc();
        }
        else{
            opt << _inv[i].uiName();
        }
        r.push_back(opt.str());
    }
    r.push_back("Back");
    
    return r;
}

void Flow::Actor::identify(unsigned int index, bool output){
    if(!_inv[index].isIdent()){
        if(output){
            std::cout << _inv[index].uiName() << " is " << _inv[index].name() << std::endl;
        }
        _inv[index].identify();
    }
    else if(output) {
        std::cout << "Nothing happens." << std::endl;
    }
}

int Flow::Actor::selectItm(){
    int r = iMenu(invMenu(), 1);
        if(r > 0){
            Game::input = menu({"Use", "Drop"}, 2);
            switch(Game::input){
                case 'U':
                {
                    use(r - 1);
                    break;
                }
                case 'D':
                {
                    std::cout << _name << " dropped ";
                    if(_inv[r - 1].isIdent()){
                        std::cout << _inv[r - 1].name() << std::endl;
                    }
                    else{
                        std::cout << _inv[r - 1].uiName() << std::endl;
                    }
                    rmItem(r - 1);
                }
            }
        }
    

    return r;
}

void Flow::Actor::setHp(int value){
    _hp.setVal(value);
}

void Flow::Actor::setMp(int value){
    _mp.setVal(value);
}

void Flow::Actor::attack(Actor &target){
    int damage = 0;
    bool healing = FlgUtil::hasFlag(_weap.element(), DmgElem::HEALING)
            && _weap.element() != DmgElem::ABSOLUT;
    bool absorb = false;
    if(_weap.element() == DmgElem::ABSOLUT && target.armr().element() != DmgElem::ABSOLUT){
        damage = _weap.value() + _atk.value();
    }
    else if(target.armr().element() == DmgElem::ABSOLUT){
        damage = (_weap.value() + _atk.value()) / ((Game::gmRand.rand() % 3) + 1);
        damage -= (target.armr().value() + target.def().value()) / ((Game::gmRand.rand() % 3) + 1);
    }
    else if(_weap.element() != DmgElem::ABSOLUT && target.armr().element() == DmgElem::ABSOLUT){
        absorb = true;
    }
    else if(_weap.element() == target.armr().element() && _weap.element() != DmgElem::NONE){
        absorb = true;
    }
    else{
        damage = (_weap.value() + _atk.value()) / ((Game::gmRand.rand() % 3) + 1);
        damage -= (target.armr().value() + target.def().value()) / ((Game::gmRand.rand() % 3) + 1);
    }
    if(damage < 0){
        damage = 0;
    }
    if(!healing && !absorb){
        damage += (Game::gmRand.rand() % 5);
        if(damage > 0){
            std::cout << _name << " deals " << damage << " damage to " << target.name() << std::endl;
            target.setHp(target.hp().value() - damage);
        }
        else{
            std::cout << _name << " missed!" << std::endl;
        }
    }
    else if(healing && !absorb){
        std::cout << _name << " heals " << damage << " points to " << target.name() << std::endl;
        target.setHp(target.hp().value() + damage);
    }
    else if(absorb){
        std::cout << target.name() << " absorbed the damage!" << std::endl;
    }

}

void Flow::Actor::stat() const{
    std::cout << _name << std::endl;
    std::cout << "Job: ";
    if(_job == Job::Knight){
        std::cout << "Knight" << std::endl;
    }
    else if(_job == Job::Cleric){
        std::cout << "Cleric" << std::endl;
    }
    else if(_job == Job::Lancer){
        std::cout << "Lancer" << std::endl;
    }
    else if(_job == Job::Mage){
        std::cout << "Mage" << std::endl;
    }
    std::cout << _hp.flName() << ": " << _hp.value() << "/" << _hp.max() << std::endl;
    std::cout << _mp.flName() << ": " << _mp.value() << "/" << _mp.max() << std::endl;
    std::cout << _atk.flName() << ": " << toInt(_atk.value()) << std::endl;
    std::cout << _def.flName() << ": " << toInt(_def.value()) << std::endl;
    std::cout << "Weapon: " << _weap.name() << std::endl;
    std::cout << "\t" << _weap.desc() << std::endl;
    std::cout << "Armor: " << _armr.name() << std::endl;
    std::cout << "\t" << _armr.desc() << std::endl;
}

Flow::BinArray Flow::Actor::toBin(){
    int hpMax = _hp.max(),
            mpMax = _mp.max();
    unsigned char atk = _atk.value(),
            def = _def.value();
    BinArray name = Flow::toBin(_name),
            weap = _weap.toBin(),
            armr = _armr.toBin(),
            r(name.size() + sizeof (_job) + sizeof (hpMax) + sizeof (mpMax) + sizeof (atk) + sizeof (def)
              + weap.size() + armr.size());

    r << name;
    r << BinArray(reinterpret_cast<char*>(&_job), sizeof (_job));
    r << BinArray(reinterpret_cast<char*>(&hpMax), sizeof (hpMax));
    r << BinArray(reinterpret_cast<char*>(&mpMax), sizeof (mpMax));
    r << BinArray(reinterpret_cast<char*>(&atk), sizeof (atk));
    r << BinArray(reinterpret_cast<char*>(&def), sizeof (def));
    r << weap;
    r << armr;

    return r;
}

void Flow::Actor::toActor(BinArray &data){
    BinArray strSize(sizeof (unsigned int)),
            str,
            job(sizeof (Job)),
            hpMax(sizeof (int)),
            mpMax(sizeof (int)),
            atk(sizeof (unsigned char)),
            def(sizeof (unsigned char));

    data >> strSize;
    str = BinArray(sizeof (unsigned int) + toInt(strSize));
    data.seekg(data.tellg() - sizeof (unsigned int));
    data >> str;
    _name = toStr(str);

    data >> job;
    _job = static_cast<Job>(toInt(job));

    data >> hpMax;
    _hp.setMax(toInt(hpMax));
    _hp.setVal(_hp.max());

    data >> mpMax;
    _mp.setMax(toInt(mpMax));
    _mp.setVal(_mp.max());

    data >> atk;
    _atk.setValue(atk[0]);

    data >> def;
    _def.setValue(def[0]);

    _weap.toItem(data);
    _armr.toItem(data);
}