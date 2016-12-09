/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   item.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for item.h
 * Created on December 2, 2016
 */

#include "item.h"

/**
 * Default Item constructor
 */
Flow::Item::Item(){
    _ident = false;
    _elem = DmgElem::NONE;
    _value = 0;
    _name = "Item";
    _uiName = "Unknown Item";
    _desc = "An Item";
    _genPoint.pos = 0;
    _genPoint.seed = 0;
}

/**
 * Item copy constructor
 * @param other The Item to copy
 */
Flow::Item::Item(const Item &other){
    _ident = other.isIdenitfied();
    _elem = other.element();
    _value = other.value();
    _name = other.name();
    _uiName = other.unidentifiedName();
    _desc = other.description();
    _genPoint = other.generationPoint();
}

/**
 * Parameterized Item constructor
 * @param elem The element of the Item
 * @param value The value of the Item
 */
Flow::Item::Item(unsigned char elem, unsigned char value){
    _ident = false;
    _elem = elem;
    _value = value;
    _genPoint.pos = 0;
    _genPoint.seed = 0;
}

/**
 * Parameterized Item constructor
 * @param name The Item's name
 * @param uiName The Item's unidentified name
 * @param desc The Item's description
 * @param elem The Item's element
 * @param value The Item's value
 * @param ident Whether or not the Item is identified
 */
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

/**
 * Identify the Item
 */
void Flow::Item::identify(){
    _ident = true;
}

/**
 * Obfuscate the Item
 */
void Flow::Item::obfuscate(){
    _ident = false;
}

/**
 * Get the Item's description
 * @return The current Item description
 */
std::string Flow::Item::description() const{
    return _desc;
}

/**
 * Set the Item's description
 * @param desc The new description to set
 */
void Flow::Item::description(const std::string &desc){
    _desc = desc;
}

/**
 * Get the Item's element
 * @return The current element of the Item
 */
unsigned char Flow::Item::element() const{
    return _elem;
}

/**
 * Set the Item's element. Clear conflicting elements and generate new Item name/description
 * @param elem The new element to set
 */
void Flow::Item::element(unsigned char elem){
    _elem = elem; //Set the element
    if(FlagUtil::hasFlag(_elem, (DmgElem::FIRE | DmgElem::WIND)) && _elem != DmgElem::ABSOLUT){ //Clear FIRE and WIND
        _elem ^= (DmgElem::FIRE | DmgElem::WIND);
    }
    if(FlagUtil::hasFlag(_elem, (DmgElem::ICE | DmgElem::LIGHTNG)) && _elem != DmgElem::ABSOLUT){ //Clear ICE and LIGTNG
        _elem ^= (DmgElem::ICE | DmgElem::LIGHTNG);
    }
    _name = createName(); //Generate new name
    _desc = createDescription(); //Generate new description
}

/**
 * Get the Item's name
 * @return The Item's current name
 */
std::string Flow::Item::name() const{
    return _name;
}

/**
 * Set the Item's name
 * @param nName The new name to set
 */
void Flow::Item::name(const std::string &nName){
    _name = nName;
}

/**
 * Get the Item's unidentified name
 * @return The Item's unidentified name
 */
std::string Flow::Item::unidentifiedName() const{
    return _uiName;
}

/**
 * Set the Item's unidentified name
 * @param uiName The new unidentified name to set
 */
void Flow::Item::unidentifiedName(const std::string &uiName){
    _uiName = uiName;
}

/**
 * Get whether or not the Item is identified
 * @return true if it is identified. Otherwise false
 */
bool Flow::Item::isIdenitfied() const{
    return _ident;
}

/**
 * Get the Item's value
 * @return The current value for this Item
 */
unsigned char Flow::Item::value() const{
    return _value;
}

/**
 * Set the Item's value
 * @param nValue The new value to set
 */
void Flow::Item::value(unsigned char nValue){
    _value = nValue;
}

/**
 * Get the Item's type
 * @return An ItemType value representing the type of the Item
 */
Flow::ItemType Flow::Item::type() const{
    return ItemType::None;
}

/**
 * Get the RNGPoint that this Item was generated at
 * @return The seed and position of the RNG when this value was generated
 */
Flow::RNGPoint Flow::Item::generationPoint() const{
    return _genPoint;
}

/**
 * Set the RNGPoint for this Item
 * @param genPoint The RNGPoint at which this Item was generated
 */
void Flow::Item::generationPoint(const RNGPoint &genPoint){
    _genPoint = genPoint;
}

/**
 * @see Item
 */
Flow::Weapon::Weapon() : Flow::Item(){ }

/**
 * @see Item
 */
Flow::Weapon::Weapon(const Weapon &other) : Flow::Item(other){ }

/**
 * Parameterized Weapon constructor. Sets the element using Weapon::element(unsigned char) rather than
 * Item::element(unsigned char)
 * @param elem The element of the Item
 * @param value The value of the Item
 */
Flow::Weapon::Weapon(unsigned char elem, unsigned char value) : Flow::Item(0, value){
    element(elem);
}

/**
 * Parameterized Weapon constructor
 * @param name The Weapon's name
 * @param uiName The Weapon's unidentified name
 * @param desc The Weapon's description
 * @param elem The Weapon's element
 * @param value The Weapon's value
 * @param ident Whether or not the Weapon is identified
 * @param weapNames A pointer to a LinkedList of weapon names to use in creating the Weapon
 */
Flow::Weapon::Weapon(const std::string &name, const std::string &uiName, const std::string &desc, unsigned char elem,
                     unsigned char value, bool ident, const Collections::LinkedList<std::string> *weapNames) :
Flow::Item(name, uiName, desc, 0, value, ident){
    if(weapNames != 0){ //If uiNames is set
        element(elem, *weapNames);
    }
    else{ //Otherwise
        element(elem);
    }
}

/**
 * @see Item
 */
void Flow::Weapon::element(unsigned char elem){
    Item::element(elem);
}

/**
 * Set the Weapon's element. Alter the name and description based on the element
 * @param elem The element to set
 * @param weapNames A LinkedList of Weapon names
 */
void Flow::Weapon::element(unsigned char elem, const Collections::LinkedList<std::string> &weapNames){
    _elem = elem; //Set the element
    if(FlagUtil::hasFlag(_elem, (DmgElem::FIRE | DmgElem::WIND)) && _elem != DmgElem::ABSOLUT){ //Clear FIRE and WIND
        _elem ^= (DmgElem::FIRE | DmgElem::WIND);
    }
    if(FlagUtil::hasFlag(_elem, (DmgElem::ICE | DmgElem::LIGHTNG)) && _elem != DmgElem::ABSOLUT){ //Clear ICE and LIGTNG
        _elem ^= (DmgElem::ICE | DmgElem::LIGHTNG);
    }
    _name = createName(weapNames); //Generate new name
    _desc = createDescription(); //Generate new description
}

/**
 * Get the Weapon's element
 * @return The current element of the Weapon
 */
unsigned char Flow::Weapon::element() const{
    return _elem;
}

/**
 * Create a name without a list of Weapon names
 * @return Always returns "Fists"
 */
std::string Flow::Weapon::createName(){
    return "Fists";
}

/**
 * Create a name with a list of Weapon names
 * @param weapNames The list of weapon names to use
 * @return A string representing the Weapon based on its element
 */
std::string Flow::Weapon::createName(const Collections::LinkedList<std::string> &weapNames){
    std::stringstream r;

    if(_elem == Flow::DmgElem::ABSOLUT){ //If ABSOLUT
        r << "Legendary ";
    }
    else{ //Otherwise (the same as armor and potions)
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
    r << weapNames[GmRand().rand() % weapNames.size()];

    return r.str();
}

/**
 * Create a description for the Weapon
 * @return A descriptive string for the Weapon
 */
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

/**
 * Get the type of this Weapon
 * @return ItemType::Weapon
 */
Flow::ItemType Flow::Weapon::type() const{
    return ItemType::Weapon;
}

/**
 * @see Item
 */
Flow::Armor::Armor() : Flow::Item(){ }

/**
 * @see Item
 */
Flow::Armor::Armor(const Armor &other) : Flow::Item(other){ }

/**
 * @see Item
 */
Flow::Armor::Armor(unsigned char elem, unsigned char value) : Flow::Item(0, value){
    element(elem);
}

/**
 * @see Item
 */
Flow::Armor::Armor(const std::string &name, const std::string &uiName, const std::string &desc, unsigned char elem,
                   unsigned char value, bool ident) : Flow::Item(name, uiName, desc, 0, value, ident){
    element(elem);
}

/**
 * Create a name for the Armor
 * @return A name string based on the Armor's element
 */
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

/**
 * Create a description for the Armor
 * @return A descriptive string for this Armor
 */
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

/**
 * Get the type of the Armor
 * @return ItemType::Armor
 */
Flow::ItemType Flow::Armor::type() const{
    return ItemType::Armor;
}

/**
 * @see Item
 */
Flow::Potion::Potion() : Flow::Item(){ }

/**
 * @see Item
 */
Flow::Potion::Potion(const Potion &other) : Flow::Item(other){ }

/**
 * @see Item
 */
Flow::Potion::Potion(unsigned char elem, unsigned char value) : Flow::Item(0, value){
    element(elem);
}

/**
 * @see Item
 */
Flow::Potion::Potion(const std::string &name, const std::string &uiName, const std::string &desc, unsigned char elem,
                     unsigned char value, bool ident) : Flow::Item(name, uiName, desc, 0, value, ident){
    element(elem);
}

/**
 * Create a name for the Potion based on its element
 * @return A name representing this Potion
 */
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

/**
 * Create a description for the Potion
 * @return A descriptive string for the Potion
 */
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

/**
 * Get the type of Potion items
 * @return ItemType::Potion
 */
Flow::ItemType Flow::Potion::type() const{
    return ItemType::Potion;
}