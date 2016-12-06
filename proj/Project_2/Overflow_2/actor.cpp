/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   actor.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 2, 2016
 */

#include "random.h"
#include "actor.h"

Flow::Actor::Actor(){
    _job = Job::Knight;
    _name = "Player";
    _atk = BStat(10, "ATK", "Attack");
    _def = BStat(10, "DEF", "Defense");
    _hp = IStat(100, "HP", "Hit Points", 100, 0, 9999, 0);
    _mp = IStat(100, "MP", "Magic Points", 100, 0, 9999, 0);
    _weap = Weapon(0, 10);
    _armor = Armor(0, 10);
}

void Flow::Actor::addItem(const Potion &item){
    _inv.addBack(std::make_shared<Potion>(item));
}

void Flow::Actor::addItem(const Weapon &item){
    _inv.addBack(std::make_shared<Weapon>(item));
}

void Flow::Actor::addItem(const Armor &item){
    _inv.addBack(std::make_shared<Armor>(item));
}

void Flow::Actor::hit(Actor &target){
    GmRand gmRand;
    int damage = 0; //The total damage to be dealt
    bool healing = FlagUtil::hasFlag(_weap.element(), DmgElem::HEALING) //Whether or not this attack will heal
            && _weap.element() != DmgElem::ABSOLUT;
    bool absorb = false; //Whether or not this attack will be absorbed
    if(_weap.element() == DmgElem::ABSOLUT && target.armor().element() != DmgElem::ABSOLUT){ //If the attack element is Absolute and the defense element is not Absolute
        damage = _weap.value() + _atk.value(); //Calculate the damage based solely on attack and weapon damage
    }
    else if(target.armor().element() == DmgElem::ABSOLUT){ //Else if both elements are Absolute
        damage = (_weap.value() + _atk.value()) / ((gmRand.rand() % 3) + 1); //Calculate damage as normal
        damage -= (target.armor().value() + target.defense().value()) / ((gmRand.rand() % 3) + 1);
    }
    else if(_weap.element() != DmgElem::ABSOLUT && target.armor().element() == DmgElem::ABSOLUT){ //If the defense element is Absolute but the attack element isn't
        absorb = true; //The damage is absorbed
    }
    else if(_weap.element() == target.armor().element() && _weap.element() != DmgElem::NONE){ //If both elements match and are not None
        absorb = true; //The damage is absorbed
    }
    else{ //Otherwise
        damage = (_weap.value() + _atk.value()) / ((gmRand.rand() % 3) + 1); //Calculate damage as normal
        damage -= (target.armor().value() + target.defense().value()) / ((gmRand.rand() % 3) + 1);
    }
    if(damage < 0){ //If the damage is negative
        damage = 0; //No damage
    }
    if(!healing && !absorb){ //If the attack isn't a heal or absorbed
        damage += (gmRand.rand() % 5); //Add between 0 and 5 damage
        if(_weap.element() != DmgElem::ABSOLUT && FlagUtil::hasFlag(_weap.element(), DmgElem::NGHTMRE) && _mp.value() > 0){ //If Nightmare damage
            std::cout << _name << "'s weapon is burning with witchfire!" << std::endl;
            int bonus = 0; //The mana bonus is 0
            bonus = gmRand.rand() % _mp.value(); //Calculate the mana bonus between 0 and the current amount of MP
            _mp.value(_mp.value() - bonus); //Subtract the consumed MP
            damage += bonus; //Add the bonus to the damage
        }
        if(damage > 0){ //If the damage is greater than 0
            std::cout << _name << " deals " << damage << " damage to " << target.name() << std::endl;
            target.hp(target.hp().value() - damage); //Damage the target
        }
        else{ //Otherwise
            std::cout << _name << " missed!" << std::endl; //Missed!
        }
    }
    else if(healing && !absorb){ //If healing
        std::cout << _name << " heals " << damage << " points to " << target.name() << std::endl;
        target.hp(target.hp().value() + damage); //Heal the target
    }
    else if(absorb){ //If absorbed
        std::cout << target.name() << " absorbed the damage!" << std::endl; //No damage
    }
}

void Flow::Actor::equip(const Weapon &weap, bool output){
    addItem(_weap);
    _weap = weap;
    if(output){
        std::cout << _name << " equipped " << _weap.name() << std::endl;
    }
}

void Flow::Actor::equip(const Armor &armor, bool output){
    addItem(_armor);
    _armor = armor;
    if(output){
        std::cout << _name << " equipped " << _armor.name() << std::endl;
    }
}

void Flow::Actor::identify(unsigned int index, bool output){
    if(!_inv[index]->isIdenitfied()){
        if(output){ //If output should be displayed
            std::cout << _inv[index]->unidentifiedName() << " is " << _inv[index]->name() << std::endl;
        }
        _inv[index]->identify();
    }
    else if(output){ //Otherwise if output should be displayed
        std::cout << "Nothing happens." << std::endl;
    }
}

void Flow::Actor::removeItem(unsigned int index){
    _inv.remove(index);
}

Flow::BStat Flow::Actor::attack() const{
    return _atk;
}

void Flow::Actor::attack(unsigned char atk){
    _atk.value(atk);
}

void Flow::Actor::attack(const BStat &atk){
    _atk = atk;
}

Flow::BStat Flow::Actor::defense() const{
    return _def;
}

void Flow::Actor::defense(unsigned char def){
    _def.value(def);
}

void Flow::Actor::defense(const BStat &def){
    _def = def;
}

Flow::IStat Flow::Actor::hp() const{
    return _hp;
}

void Flow::Actor::hp(int nHp){
    _hp.value(nHp);
}

void Flow::Actor::hp(const IStat &nHp){
    _hp = nHp;
}

Flow::Job Flow::Actor::job() const{
    return _job;
}

void Flow::Actor::job(Job nJob){
    _job = nJob;
}

Flow::IStat Flow::Actor::mp() const{
    return _mp;
}

void Flow::Actor::mp(int nMp){
    _mp.value(nMp);
}

void Flow::Actor::mp(const IStat &nMp){
    _mp = nMp;
}

std::string Flow::Actor::name() const{
    return _name;
}

void Flow::Actor::name(const std::string &nName){
    _name = nName;
}

Flow::Weapon Flow::Actor::weapon() const{
    return _weap;
}

Flow::Armor Flow::Actor::armor() const{
    return _armor;
}

int Flow::Actor::selectItem(){
    int r = intMenu(inventoryMenu(), 1); //Get the return value from menu processing
    if(r > 0){ //If not back
        char input = menu({"Use", "Drop"}, 2); //Menu processing
        switch(input){
            case 'U': //Use
            {
                use(r - 1); //Use the item
                break;
            }
            case 'D': //Drop
            {
                std::cout << _name << " dropped ";
                if(_inv[r - 1]->isIdenitfied()){ //If it's identified
                    std::cout << _inv[r - 1]->name() << std::endl; //Show the identified name
                }
                else{ //Otherwise
                    std::cout << _inv[r - 1]->unidentifiedName() << std::endl; //Show the unidentified name
                }
                removeItem(r - 1); //Remove the item
            }
        }
    }
    return r;
}

Collections::LinkedList<std::string> Flow::Actor::inventoryMenu(){
    Collections::LinkedList<std::string> r; //The return vector
    for(int i = 0; i < _inv.size(); ++i){ //For the entire inventory
        std::string opt; //The current menu option
        if(_inv[i]->isIdenitfied()){ //If the item is identified
            opt += _inv[i]->name() + "\n"; //Add the name
            opt += "\t" + _inv[i]->description(); //Add the description
        }
        else{ //Otherwise
            opt += _inv[i]->unidentifiedName(); //Add the unidentified name
        }
        r.addBack(opt); //Push opt to the return vector
    }
    r.addBack("Back"); //Push the Back option

    return r;
}

unsigned int Flow::Actor::invSize(){
    return _inv.size();
}

void Flow::Actor::addItems(const Actor &other){
    for(int i = 0; i < other._inv.size(); ++i){
        //std::cout << other._inv[i]->isIdenitfied() << std::endl;
        _inv.addBack(other._inv[i]);
        std::cout << other._inv[i]->unidentifiedName() << " acquired!" << std::endl;
    }
}

unsigned char Flow::Actor::difficulty() const{
    return _diff;
}

void Flow::Actor::difficulty(unsigned char diff){
    _diff = diff;
}

void Flow::Actor::use(unsigned int index, bool output){
    std::shared_ptr<Item> itm = _inv[index];
    removeItem(index);
    if(!itm->use(*this, output)){
        _inv.addBack(itm);
    }
}

void Flow::Actor::obfuscate(){
    for(int i = 0; i < _inv.size(); ++i){
        _inv[i]->obfuscate();
    }
}

std::string Flow::toString(Flow::Job job){
    if(job == Flow::Job::Knight){
        return "Knight";
    }
    else if(job == Flow::Job::Cleric){
        return "Cleric";
    }
    else if(job == Flow::Job::Lancer){
        return "Lancer";
    }
    else if(job == Flow::Job::Mage){
        return "Mage";
    }
    else{
        return "";
    }
}