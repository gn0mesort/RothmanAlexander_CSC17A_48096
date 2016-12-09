/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   actor.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for actor.h
 * Created on December 2, 2016
 */

#include "actor.h"

/**
 * Default Actor constructor
 */
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

/**
 * Add an Item to the Actor's inventory
 * @param item A Potion to add to the inventory
 */
void Flow::Actor::addItem(const Potion &item){
    _inv.addBack(std::make_shared<Potion>(item));
}

/**
 * Add an Item to the Actor's inventory
 * @param item A Weapon to add to the inventory
 */
void Flow::Actor::addItem(const Weapon &item){
    _inv.addBack(std::make_shared<Weapon>(item));
}

/**
 * Add an Item to the Actor's inventory
 * @param item An Armor object to add to the inventory
 */
void Flow::Actor::addItem(const Armor &item){
    _inv.addBack(std::make_shared<Armor>(item));
}

/**
 * Calculate and apply damage from a physical attack to a target Actor
 * @param target
 */
void Flow::Actor::hit(Actor &target){
    GmRand gmRand; //Get an RNG instance
    int damage = 0; //The total damage to be dealt
    bool healing = FlagUtil::hasFlag(_weap.element(), DmgElem::HEALING) //Whether or not this attack will heal
            && _weap.element() != DmgElem::ABSOLUT;
    bool absorb = false; //Whether or not this attack will be absorbed
    if(_weap.element() == DmgElem::ABSOLUT && target.armor().element() != DmgElem::ABSOLUT){ //If the attack element is
        //Absolute and the defense element is not Absolute
        damage = _weap.value() + _atk.value(); //Calculate the damage based solely on attack and weapon damage
    }
    else if(target.armor().element() == DmgElem::ABSOLUT){ //Else if both elements are Absolute
        damage = (_weap.value() + _atk.value()) / ((gmRand.rand() % 3) + 1); //Calculate damage as normal
        damage -= (target.armor().value() + target.defense().value()) / ((gmRand.rand() % 3) + 1);
    }
    else if(_weap.element() != DmgElem::ABSOLUT && target.armor().element() == DmgElem::ABSOLUT){ //If the defense
        //element is Absolute but the attack element isn't
        absorb = true; //The damage is absorbed
    }
    else if(_weap.element() == target.armor().element() && _weap.element() != DmgElem::NONE){ //If both elements match
        //and are not None
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
        if(_weap.element() != DmgElem::ABSOLUT && FlagUtil::hasFlag(_weap.element(), DmgElem::NGHTMRE)
           && _mp.value() > 0){ //If Nightmare damage
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

/**
 * Equip a Weapon
 * @param weap The Weapon to equip
 * @param output Whether or not to output text
 */
void Flow::Actor::equip(const Weapon &weap, bool output){
    addItem(_weap);
    _weap = weap;
    if(output){
        std::cout << _name << " equipped " << _weap.name() << std::endl;
    }
}

/**
 * Equip some Armor
 * @param armor The Armor to equip
 * @param output Whether or not to output text
 */
void Flow::Actor::equip(const Armor &armor, bool output){
    addItem(_armor);
    _armor = armor;
    if(output){
        std::cout << _name << " equipped " << _armor.name() << std::endl;
    }
}

/**
 * Identify an Item in the Actor's inventory
 * @param index The index in the inventory to identify
 * @param output Whether or not to output text
 */
void Flow::Actor::identify(unsigned int index, bool output){
    if(!_inv[index]->isIdenitfied()){ //If not Identified
        if(output){ //If output should be displayed
            std::cout << _inv[index]->unidentifiedName() << " is " << _inv[index]->name() << std::endl;
        }
        _inv[index]->identify();
    }
    else if(output){ //Otherwise if output should be displayed
        std::cout << "Nothing happens." << std::endl;
    }
}

/**
 * Remove an Item from the Actor's inventory
 * @param index The index of the Item to remove
 */
void Flow::Actor::removeItem(unsigned int index){
    _inv.remove(index);
}

/**
 * Return the Actor's attack Stat
 * @return A BStat containing the Actor's attack data
 */
Flow::BStat Flow::Actor::attack() const{
    return _atk;
}

/**
 * Set the Actor's attack Stat
 * @param atk A value to set the value of _atk to
 */
void Flow::Actor::attack(unsigned char atk){
    _atk.value(atk);
}

/**
 * Set the Actor's attack Stat
 * @param atk A BStat object to set _atk to
 */
void Flow::Actor::attack(const BStat &atk){
    _atk = atk;
}

/**
 * Return the Actor's defense Stat
 * @return A BStat containing the Actor's defense data
 */
Flow::BStat Flow::Actor::defense() const{
    return _def;
}

/**
 * Set the Actor's defense Stat
 * @param def A value to set the value of _def to
 */
void Flow::Actor::defense(unsigned char def){
    _def.value(def);
}

/**
 * Set the Actor's defense Stat
 * @param def A BStat object to set _def to
 */
void Flow::Actor::defense(const BStat &def){
    _def = def;
}

/**
 * Return the Actor's HP Stat
 * @return An IStat containing the Actor's HP data
 */
Flow::IStat Flow::Actor::hp() const{
    return _hp;
}

/**
 * Set the Actor's HP
 * @param nHp A value to set the value of _hp to
 */
void Flow::Actor::hp(int nHp){
    _hp.value(nHp);
}

/**
 * Set the Actor's HP
 * @param nHp An IStat to set _hp to
 */
void Flow::Actor::hp(const IStat &nHp){
    _hp = nHp;
}

/**
 * Return the Actor's current Job
 * @return The value of _job
 */
Flow::Job Flow::Actor::job() const{
    return _job;
}

/**
 * Set the Actor's current Job
 * @param nJob A Job to set the Actor to
 */
void Flow::Actor::job(Job nJob){
    _job = nJob;
}

/**
 * Returns the Actor's MP Stat
 * @return An IStat containing the Actor's MP data
 */
Flow::IStat Flow::Actor::mp() const{
    return _mp;
}

/**
 * Set the Actor's MP
 * @param nMp A value to set the value of _mp to
 */
void Flow::Actor::mp(int nMp){
    _mp.value(nMp);
}

/**
 * Set the Actor's MP
 * @param nMp An IStat to set _mp to
 */
void Flow::Actor::mp(const IStat &nMp){
    _mp = nMp;
}

/**
 * Get the Actor's name
 * @return The value of _name
 */
std::string Flow::Actor::name() const{
    return _name;
}

/**
 * Set the Actor's name
 * @param nName A new name to set _name to
 */
void Flow::Actor::name(const std::string &nName){
    _name = nName;
}

/**
 * Get the Actor's current Weapon
 * @return The currently equipped Weapon
 */
Flow::Weapon Flow::Actor::weapon() const{
    return _weap;
}

/**
 * Get the Actor's current Armor
 * @return The currently equipped Armor
 */
Flow::Armor Flow::Actor::armor() const{
    return _armor;
}

/**
 * Select an Item from the Actor's inventory
 * @return The index of the selected Item
 */
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

/**
 * Get a menu LinkedList containing the names of Items in the Actor's inventory
 * @return A LinkedList containing the names of Items in the Actor's inventory. Names are either identified names for
 * identified items or unidentified names
 */
Collections::LinkedList<std::string> Flow::Actor::inventoryMenu(){
    Collections::LinkedList<std::string> r; //The return LinkedList

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

/**
 * Get the size of the Actor's inventory
 * @return The size of the Actor's inventory in Items
 */
unsigned int Flow::Actor::invSize(){
    return _inv.size();
}

/**
 * Add Items to the Actor's inventory from another Actor's inventory
 * @param other The other Actor to take Items from
 */
void Flow::Actor::addItems(const Actor &other){
    for(int i = 0; i < other._inv.size(); ++i){ //For the inventory of other
        _inv.addBack(other._inv[i]); //Add items
        std::cout << other._inv[i]->unidentifiedName() << " acquired!" << std::endl; //Output acquired message
    }
}

/**
 * Get the difficulty of the game
 * @return The difficulty value for this Actor
 */
unsigned char Flow::Actor::difficulty() const{
    return _diff;
}

/**
 * Set the difficulty of the game
 * @param diff The difficulty to set the game to
 */
void Flow::Actor::difficulty(unsigned char diff){
    _diff = diff;
}

/**
 * Use an Item from the Actor's inventory
 * @param index The index of the Item to use
 * @param output Whether or not to output usage text
 */
void Flow::Actor::use(unsigned int index, bool output){
    bool consumed = false; //Whether or not the Item was consumed
    std::shared_ptr<Item> itm = _inv[index]; //Get the Item
    removeItem(index); //Remove the Item from the inventory
    switch(itm->type()){
        case ItemType::Potion: //If it's a Potion
        {
            if(output){
                std::cout << _name << " used " << itm->name() << "." << std::endl; //Display usage message
            }
            if(itm->element() == DmgElem::NONE){ //If the item is an Identifying Potion
                if(invSize() > 0){ //If you have more than one Item in your inventory
                    int select = intMenu(inventoryMenu(), 1);
                    if(select > 0){ //If the selection is greater than 0
                        identify(select - 1, true); //Identify the item and output text
                        consumed = true; //The Item was consumed
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
                consumed = true; //The Item was consumed
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
                    obfuscate(); //Obfuscate all Items in the inventory
                }
                consumed = true; //The Item was consumed
            }
            break;
        }
        case ItemType::Weapon: //If it's a Weapon
        {
            std::shared_ptr<Weapon> weap = std::static_pointer_cast<Weapon>(itm); //Convert the Item to a Weapon
            weap->identify(); //Identify the Weapon
            equip(*weap, output); //Equip the Weapon
            consumed = true; //The Item was consumed
            break;
        }

        case ItemType::Armor: //If it's Armor
        {
            std::shared_ptr<Armor> armor = std::static_pointer_cast<Armor>(itm); //Convert the Item to Armor
            armor->identify(); //Identify the Armor
            equip(*armor, output); //Equip the Armor
            consumed = true; //The Item was consumed
            break;
        }
    }
    if(!consumed){ //If the Item wasn't consumed
        addItem(itm); //Add it back to the Inventory
    }
}

/**
 * Add an Item to the Actor's inventory
 * @param itm A std::shared_ptr<Item> pointing to the Item to add
 */
void Flow::Actor::addItem(const std::shared_ptr<Item> &itm){
    _inv.addBack(itm);
}

/**
 * Obfuscate all Items in the Actor's inventory
 */
void Flow::Actor::obfuscate(){
    for(int i = 0; i < _inv.size(); ++i){
        _inv[i]->obfuscate();
    }
}

/**
 * Convert a Job to a string
 * @param job The Job to convert
 * @return A string representing the input Job
 */
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