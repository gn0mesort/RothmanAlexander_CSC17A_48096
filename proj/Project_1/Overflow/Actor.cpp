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
                unsigned int select = 0; //The selection index
                select = iMenu(invMenu(), 1); //Menu processing
                if(select > 0){ //If the selection is greater than 0
                    identify(select - 1, true); //Identify the item and output text
                }
                else{
                    addItem(target); //Otherwise add the potion back and don't use it
                }
            }
            else{ //Otherwise if you have no other items
                std::cout << "Nothing happens." << std::endl;
                addItem(target); //Add the the potion back
            }
        }
        else if(target.element() == DmgElem::ABSOLUT){ //If the potion is an absolute type potion
            std::cout << _name << " was fully restored!" << std::endl;
            _hp.setVal(_hp.max()); //Restore hp
            _mp.setVal(_mp.max()); //Restore mp
        }
        else{ //Otherwise do potion processing by element
            if(FlgUtil::hasFlag(target.element(), DmgElem::HEALING)){ //If the potion has a healing flag
                std::cout << _name << " recovered " << toInt(target.value()) << " HP!" << std::endl;
                _hp.setVal(_hp.value() + target.value()); //heal the Actor
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::FIRE)){ //If the potion has a fire flag
                std::cout << _name << "'s attack power increased by " << toInt(target.value()) << std::endl;
                _atk.setValue(_atk.value() + target.value()); //Increase the Actor's attack
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::ICE)){ //If the potion has an ice flag
                std::cout << _name << "'s defense increased by " << toInt(target.value()) << std::endl;
                _def.setValue(_def.value() + target.value()); //Increase the Actor's defense
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::LIGHTNG)){ //If the potion has a lightning flag
                std::cout << _name << "'s defense decreased by " << toInt(target.value()) << std::endl;
                _def.setValue(_def.value() - target.value()); //Decrease the Actor's defense
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::WIND)){ //If the potion has a wind flag
                std::cout << _name << "'s attack power decreased by " << toInt(target.value()) << std::endl;
                _atk.setValue(_atk.value() - target.value()); //Decrease the Actor's attack
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::HOLY)){ //If the potion has a holy flag
                std::cout << _name << "'s maximum HP has increased by " << toInt(target.value()) << std::endl;
                _hp.setMax(_hp.max() + target.value()); //Increase the Actor's max HP
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::SHADOW)){ //If the potion has a shadow flag
                std::cout << _name << "'s maximum MP has increased by " << toInt(target.value()) << std::endl;
                _mp.setMax(_mp.max() + target.value()); //Increase the Actor's max MP
            }
            if(FlgUtil::hasFlag(target.element(), DmgElem::NGHTMRE)){ //If the potion has a nightmare flag
                std::cout << _name << " had a terrible nightmare!" << std::endl;
                for(int i = 0; i < _inv.size(); ++i){ //Deidentify all items
                    _inv[i].obfscte();
                }
            }
        }

    }
}

//invMenu
//Generate a menu vector from the current inventory
//Output:
//A menu vector containing the appropriate names of all the items in the Actor's inventory

std::vector<std::string> Flow::Actor::invMenu() const{
    std::vector<std::string> r; //The return vector
    for(int i = 0; i < _inv.size(); ++i){ //For the entire inventory
        std::string opt; //The current menu option
        if(_inv[i].isIdent()){ //If the item is identified
            opt += _inv[i].name() + "\n"; //Add the name
            opt += "\t" + _inv[i].desc(); //Add the description
        }
        else{ //Otherwise
            opt += _inv[i].uiName(); //Add the unidentified name
        }
        r.push_back(opt); //Push opt to the return vector
    }
    r.push_back("Back"); //Push the Back option

    return r;
}

//identify
//Identify an Item in the Actor's inventory
//Input:
//index
//The index of the item to identify
//output
//whether or not to output text

void Flow::Actor::identify(unsigned int index, bool output){
    if(!_inv[index].isIdent()){ //If not identified
        if(output){ //If output should be displayed
            std::cout << _inv[index].uiName() << " is " << _inv[index].name() << std::endl;
        }
        _inv[index].identify(); //Identify the item
    }
    else if(output){ //Otherwise if output should be displayed
        std::cout << "Nothing happens." << std::endl;
    }
}

//selectItm
//Select an item from the Actor's inventory
//Output:
//The index of the selected item

int Flow::Actor::selectItm(){
    int r = iMenu(invMenu(), 1); //Get the return value from menu processing
    if(r > 0){ //If not back
        Game::input = menu({"Use", "Drop"}, 2); //Menu processing
        switch(Game::input){
            case 'U': //Use
            {
                use(r - 1); //Use the item
                break;
            }
            case 'D': //Drop
            {
                std::cout << _name << " dropped ";
                if(_inv[r - 1].isIdent()){ //If it's identified
                    std::cout << _inv[r - 1].name() << std::endl; //Show the identified name
                }
                else{ //Otherwise
                    std::cout << _inv[r - 1].uiName() << std::endl; //Show the unidentified name
                }
                rmItem(r - 1); //Remove the item
            }
        }
    }
    return r;
}

//setHp
//Set the Actor's current hp value to the input value
//Input:
//value
//The value to set the Actor's hp to

void Flow::Actor::setHp(int value){
    _hp.setVal(value);
}

//setMp
//Set the Actor's current mp value to the input value
//Input:
//value
//The value to set the Actor's mp to

void Flow::Actor::setMp(int value){
    _mp.setVal(value);
}

//attack
//Process an attack on another Actor, calculate damage, special effects, healing, etc
//Input:
//target
//The Actor who is the target of the attack

void Flow::Actor::attack(Actor &target){
    int damage = 0; //The total damage to be dealt
    bool healing = FlgUtil::hasFlag(_weap.element(), DmgElem::HEALING) //Whether or not this attack will heal
            && _weap.element() != DmgElem::ABSOLUT;
    bool absorb = false; //Whether or not this attack will be absorbed
    if(_weap.element() == DmgElem::ABSOLUT && target.armr().element() != DmgElem::ABSOLUT){ //If the attack element is Absolute and the defense element is not Absolute
        damage = _weap.value() + _atk.value(); //Calculate the damage based solely on attack and weapon damage
    }
    else if(target.armr().element() == DmgElem::ABSOLUT){ //Else if both elements are Absolute
        damage = (_weap.value() + _atk.value()) / ((Game::gmRand.rand() % 3) + 1); //Calculate damage as normal
        damage -= (target.armr().value() + target.def().value()) / ((Game::gmRand.rand() % 3) + 1);
    }
    else if(_weap.element() != DmgElem::ABSOLUT && target.armr().element() == DmgElem::ABSOLUT){ //If the defense element is Absolute but the attack element isn't
        absorb = true; //The damage is absorbed
    }
    else if(_weap.element() == target.armr().element() && _weap.element() != DmgElem::NONE){ //If both elements match and are not None
        absorb = true; //The damage is absorbed
    }
    else{ //Otherwise
        damage = (_weap.value() + _atk.value()) / ((Game::gmRand.rand() % 3) + 1); //Calculate damage as normal
        damage -= (target.armr().value() + target.def().value()) / ((Game::gmRand.rand() % 3) + 1);
    }
    if(damage < 0){ //If the damage is negative
        damage = 0; //No damage
    }
    if(!healing && !absorb){ //If the attack isn't a heal or absorbed
        damage += (Game::gmRand.rand() % 5); //Add between 0 and 5 damage
        if(_weap.element() != DmgElem::ABSOLUT && FlgUtil::hasFlag(_weap.element(), DmgElem::NGHTMRE) && _mp.value() > 0){ //If Nightmare damage
            std::cout << _name << "'s weapon is burning with witchfire!" << std::endl;
            int bonus = 0; //The mana bonus is 0
            bonus = Game::gmRand.rand() % _mp.value(); //Calculate the mana bonus between 0 and the current amount of MP
            _mp.setVal(_mp.value() - bonus); //Subtract the consumed MP
            damage += bonus; //Add the bonus to the damage
        }
        if(damage > 0){ //If the damage is greater than 0
            std::cout << _name << " deals " << damage << " damage to " << target.name() << std::endl;
            target.setHp(target.hp().value() - damage); //Damage the target
        }
        else{ //Otherwise
            std::cout << _name << " missed!" << std::endl; //Missed!
        }
    }
    else if(healing && !absorb){ //If healing
        std::cout << _name << " heals " << damage << " points to " << target.name() << std::endl;
        target.setHp(target.hp().value() + damage); //Heal the target
    }
    else if(absorb){ //If absorbed
        std::cout << target.name() << " absorbed the damage!" << std::endl; //No damage
    }

}

//stat
//Display the Actor's current stats by writing them to stdout

void Flow::Actor::stat() const{
    std::cout << _name << std::endl; //Output name
    std::cout << "Job: ";
    //Translate the Job to a string and output. Strings are the same as enum value names
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
    std::cout << _hp.flName() << ": " << _hp.value() << "/" << _hp.max() << std::endl; //Output HP
    std::cout << _mp.flName() << ": " << _mp.value() << "/" << _mp.max() << std::endl; //Output MP
    std::cout << _atk.flName() << ": " << toInt(_atk.value()) << std::endl; //Output ATK
    std::cout << _def.flName() << ": " << toInt(_def.value()) << std::endl; //Output DEF
    std::cout << "Weapon: " << _weap.name() << std::endl; //Output weapon
    std::cout << "\t" << _weap.desc() << std::endl;
    std::cout << "Armor: " << _armr.name() << std::endl; //Output armor
    std::cout << "\t" << _armr.desc() << std::endl;
}

//toBin
//Return a BinArray filled with the binary data for this Actor
//Output:
//A filled BinArray object containing the Actor's data as binary

Flow::BinArray Flow::Actor::toBin(){
    int hpMax = _hp.max(), //The hp value to write
            mpMax = _mp.max(); //The mp value to write
    unsigned char atk = _atk.value(), //The atk value to write
            def = _def.value(); //The def value to write
    BinArray name = Flow::toBin(_name), //A BinArray with the Actor's name in it
            weap = _weap.toBin(), //A BinArray with the Actor's equipped weapon in it
            armr = _armr.toBin(), //A BinArray with the Actor's equipped armor in it
            r(name.size() + sizeof (_job) + sizeof (hpMax) + sizeof (mpMax) + sizeof (atk) + sizeof (def)
              + weap.size() + armr.size()); //The return BinArray

    r << name; //Insert name
    r << BinArray(reinterpret_cast<char*>(&_job), sizeof (_job)); //Insert job
    r << BinArray(reinterpret_cast<char*>(&hpMax), sizeof (hpMax)); //Insert hp
    r << BinArray(reinterpret_cast<char*>(&mpMax), sizeof (mpMax)); //Insert mp
    r << BinArray(reinterpret_cast<char*>(&atk), sizeof (atk)); //Insert atk
    r << BinArray(reinterpret_cast<char*>(&def), sizeof (def)); //Insert def
    r << weap; //Insert weapon
    r << armr; //Insert armor

    return r;
}

//toActor
//Fill an actor object with the data stored in a BinArray
//Input:
//data
//A BinArray object containing Actor data

void Flow::Actor::toActor(BinArray &data){
    BinArray strSize(sizeof (unsigned int)), //The size of a string
            str, //A string
            job(sizeof (Job)), //The Actor's job
            hpMax(sizeof (int)), //The Actor's hp
            mpMax(sizeof (int)), //The Actor's mp
            atk(sizeof (unsigned char)), //The Actor's atk
            def(sizeof (unsigned char)); //The Actor's def

    data >> strSize; //Extract string size
    str = BinArray(sizeof (unsigned int) +toInt(strSize)); //Allocate string size
    data.seekg(data.tellg() - sizeof (unsigned int)); //Seek back to the beginning of the string data
    data >> str; //Extract string size
    _name = toStr(str); //Set the Actor's name

    data >> job; //Extract the job
    _job = static_cast<Job>(toInt(job)); //Set the Actor's job

    data >> hpMax; //Extract the Actor's hp
    _hp.setMax(toInt(hpMax)); //Set the Actor's max hp
    _hp.setVal(_hp.max()); //Set the Actor's current hp

    data >> mpMax; //Extract the Actor's mp
    _mp.setMax(toInt(mpMax)); //Set the Actor's max mp
    _mp.setVal(_mp.max()); //Set the Actor's current mp

    data >> atk; //Extract the Actor's atk
    _atk.setValue(atk[0]); //Set the Actor's atk

    data >> def; //Extract the Actor's def
    _def.setValue(def[0]); //Set the Actor's def

    _weap.toItem(data); //Set the Actor's weapon
    _armr.toItem(data); //Set the Actor's armor
}