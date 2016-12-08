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
    _weap.identify();
    _armor.identify();
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
    bool consumed = false;
    std::shared_ptr<Item> itm = _inv[index];
    removeItem(index);
    switch(itm->type()){
        case ItemType::Potion:
        {
            if(output){
                std::cout << _name << " used " << itm->name() << "." << std::endl; //Display usage message
            }
            if(itm->element() == DmgElem::NONE){ //If the item is an Identifying Potion
                if(invSize() > 0){ //If you have more than one Item in your inventory
                    int select = intMenu(inventoryMenu(), 1);
                    if(select > 0){ //If the selection is greater than 0
                        identify(select - 1, true); //Identify the item and output text
                        consumed = true;
                    }
                }
                else if(output){ //Otherwise if you have no other items
                    std::cout << "Nothing happens." << std::endl;
                }
            }
            else if(itm->element() == DmgElem::ABSOLUT){ //If the potion is an absolute type potion
                if(output){
                    std::cout << _name << " was fully restored!" << std::endl;
                }
                _hp = _hp.max(); //Restore hp
                _mp = _mp.max(); //Restore mp
                consumed = true;
            }
            else{ //Otherwise do potion processing by element
                if(FlagUtil::hasFlag(itm->element(), DmgElem::HEALING)){ //If the potion has a healing flag
                    if(output){
                        std::cout << _name << " recovered " << to_int(itm->value()) << " HP!" << std::endl;
                    }
                    _hp.value(_hp.value() + itm->value()); //heal the Actor
                }
                if(FlagUtil::hasFlag(itm->element(), DmgElem::FIRE)){ //If the potion has a fire flag
                    if(output){
                        std::cout << _name << "'s attack power increased by " << to_int(itm->value()) << std::endl;
                    }
                    _atk.value(_atk.value() + itm->value()); //Increase the Actor's attack
                }
                if(FlagUtil::hasFlag(itm->element(), DmgElem::ICE)){ //If the potion has an ice flag
                    if(output){
                        std::cout << _name << "'s defense increased by " << to_int(itm->value()) << std::endl;
                    }
                    _def.value(_def.value() + itm->value()); //Increase the Actor's defense
                }
                if(FlagUtil::hasFlag(itm->element(), DmgElem::LIGHTNG)){ //If the potion has a lightning flag
                    if(output){
                        std::cout << _name << "'s defense decreased by " << to_int(itm->value()) << std::endl;
                    }
                    _def.value(_def.value() - itm->value()); //Decrease the Actor's defense
                }
                if(FlagUtil::hasFlag(itm->element(), DmgElem::WIND)){ //If the potion has a wind flag
                    if(output){
                        std::cout << _name << "'s attack power decreased by " << to_int(itm->value()) << std::endl;
                    }
                    _atk.value(_atk.value() - itm->value()); //Decrease the Actor's attack
                }
                if(FlagUtil::hasFlag(itm->element(), DmgElem::HOLY)){ //If the potion has a holy flag
                    if(output){
                        std::cout << _name << "'s maximum HP has increased by " << to_int(itm->value()) << std::endl;
                    }
                    _hp.max(_hp.max() + itm->value()); //Increase the Actor's max HP
                }
                if(FlagUtil::hasFlag(itm->element(), DmgElem::SHADOW)){ //If the potion has a shadow flag
                    if(output){
                        std::cout << _name << "'s maximum MP has increased by " << to_int(itm->value()) << std::endl;
                    }
                    _mp.max(_mp.max() + itm->value()); //Increase the Actor's max MP
                }
                if(FlagUtil::hasFlag(itm->element(), DmgElem::NGHTMRE)){ //If the potion has a nightmare flag
                    if(output){
                        std::cout << _name << " had a terrible nightmare!" << std::endl;
                    }
                    obfuscate();
                }
                consumed = true;
            }
            break;
        }

        case ItemType::Weapon:
        {
            std::shared_ptr<Weapon> weap = std::static_pointer_cast<Weapon>(itm);
            weap->identify();
            equip(*weap, output);
            consumed = true;
            break;
        }

        case ItemType::Armor:
        {
            std::shared_ptr<Armor> armor = std::static_pointer_cast<Armor>(itm);
            armor->identify();
            equip(*armor, output);
            consumed = true;
            break;
        }
    }
    if(!consumed){
        addItem(itm);
    }
}

void Flow::Actor::addItem(const std::shared_ptr<Item> &itm){
    _inv.addBack(itm);
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