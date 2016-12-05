/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Item.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for Item.h
 * Created on October 14, 2016
 */

//User Libraries
#include "Item.h" //Item objects
#include "Game.h" //Main game objects and loose functions

//Item
//Default Constructor

Flow::Item::Item(){
    _ident = false;
    _elem = DmgElem::NONE;
    _value = 0;
    _name = "Item";
    _uiName = "Unknown Item";
    _desc = "An Item";
    _type = ItmType::Potion;
}

//Item
//Copy constructor

Flow::Item::Item(const Item &other){
    if(this != &other){
        _ident = other.isIdent();
        setElem(other.element());
        _value = other.value();
        _name = other.name();
        _uiName = other.uiName();
        _desc = other.desc();
        _type = other.type();
    }
}

//Item
//Parameterized constructor

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

//isIdent
//Returns whether or not the Item is identified
//Output:
//True if identified otherwise false

bool Flow::Item::isIdent() const{
    return _ident;
}

//identify
//Identify the Item

void Flow::Item::identify(){
    if(!_ident){ //If not identified
        _ident = true; //Identify
    }
}

//obfscte
//Obfuscate the Item

void Flow::Item::obfscte(){
    if(_ident){ //If identified
        _ident = false; //Obfuscate
    }
}

//element
//Returns the current element flag settings
//Output:
//The current element flags in an unsigned char

unsigned char Flow::Item::element() const{
    return _elem;
}

//setElem
//Sets the value of the Item's element. Changes the Item's name and description as appropriate
//Input:
//elem
//An set of element flags in an unsigned char

void Flow::Item::setElem(unsigned char elem){
    _elem = elem; //Set the value
    if(FlgUtil::hasFlag(_elem, (DmgElem::FIRE | DmgElem::WIND))
       && _elem != DmgElem::ABSOLUT){ //If the element has FIRE and WIND but is not ABSOLUT
        _elem ^= (DmgElem::FIRE | DmgElem::WIND); //Toggle conflicting flags off
    }
    if(FlgUtil::hasFlag(_elem, (DmgElem::ICE | DmgElem::LIGHTNG)) //If the element has ICE and LIGHTNING but is not ABSOLUT
       && _elem != DmgElem::ABSOLUT){
        _elem ^= (DmgElem::ICE | DmgElem::LIGHTNG); //Toggle conflicting flags off
    }
    _name = Item::mkName(_elem, _type); //Make a new name
    _desc = Item::mkDesc(_elem, _type, _value); //Make a new description
}

//value
//Returns the current value of the Item
//Output:
//The data stored in _value

unsigned char Flow::Item::value() const{
    return _value;
}

//setValue
//Sets the current value of the Item
//Input:
//value
//The value to set the Item to

void Flow::Item::setValue(unsigned char value){
    _value = value;
}

//name
//Returns the current name of the Item
//Output:
//The data stored in _name

std::string Flow::Item::name() const{
    return _name;
}

//setName
//Sets the current name of the Item
//Input:
//name
//The name to set the Item's name to

void Flow::Item::setName(std::string name){
    _name = name;
}

//uiName
//Returns the current unidentified name of the Item
//Output:
//The data stored in _uiName

std::string Flow::Item::uiName() const{
    return _uiName;
}

//setUiName
//Sets the current unidentified name of the Item
//Input:
//uiName
//The unidentified name to set _uiName to

void Flow::Item::setUiName(std::string uiName){
    _uiName;
}

//desc
//Returns the current description of the Item
//Output:
//The data stored in _desc

std::string Flow::Item::desc() const{
    return _desc;
}

//setDesc
//Sets the description of the Item
//Input:
//desc
//The description to set for this Item

void Flow::Item::setDesc(std::string desc){
    _desc = desc;
}

//type
//Returns the current type of the Item
//Output:
//The data stored in _type

Flow::ItmType Flow::Item::type() const{
    return _type;
}

//setType
//Sets the type of the Item
//Input:
//type
//The type to set this Item to

void Flow::Item::setType(ItmType type){
    _type = type;
}

//mkDesc
//Make an Item description
//Input:
//elem
//The element of the Item to create a description for
//type
//The type of the Item to create a description for
//value
//The value of the Item to create a description for
//Output:
//A string containing a description for the Item

std::string Flow::Item::mkDesc(unsigned char elem, ItmType type, unsigned char value){
    std::stringstream r; //String stream to create a string from

    if(type == ItmType::Potion){ //If the Item is a potion
        if(elem == DmgElem::NONE){ //If the Item element is NONE
            r << "Identifies 1 item. ";
        }
        if(elem == DmgElem::ABSOLUT){ //If the Item element is ABSOLUT
            r << "Fully restores HP and MP. ";
        }
        else{ //Otherwise
            if(FlgUtil::hasFlag(elem, DmgElem::HEALING)){ //If the HEALING flag is on
                r << "Restores " << toInt(value) << " HP. ";
            }
            if(FlgUtil::hasFlag(elem, DmgElem::FIRE)){ //If the FIRE flag is on
                r << "Increases Attack by " << toInt(value) << ". ";
            }
            if(FlgUtil::hasFlag(elem, DmgElem::ICE)){ //If the ICE flag is on
                r << "Increases Defense by " << toInt(value) << ". ";
            }
            if(FlgUtil::hasFlag(elem, DmgElem::LIGHTNG)){ //If the LIGHTNG flag is on
                r << "Decreases Defense by " << toInt(value) << ". ";
            }
            if(FlgUtil::hasFlag(elem, DmgElem::WIND)){ //If the WIND flag is on
                r << "Decreases Attack by " << toInt(value) << ". ";
            }
            if(FlgUtil::hasFlag(elem, DmgElem::HOLY)){ //If the HOLY flag is on
                r << "Increases max HP by " << toInt(value) << ". ";
            }
            if(FlgUtil::hasFlag(elem, DmgElem::SHADOW)){ //If the SHADOW flag is on
                r << "Increases max MP by " << toInt(value) << ". ";
            }
            if(FlgUtil::hasFlag(elem, DmgElem::NGHTMRE)){ //If the NGHTMRE flag is on
                r << "Obfuscates all items. ";
            }
        }
    }
    else if(type == ItmType::Weapon){ //If the Item is a weapon
        if(elem == DmgElem::NONE){ //If no element
            r << "+" << toInt(value) << " Attack. ";
        }
        else{ //Otherwise
            r << "Deals ( " << DmgElem::toStr(elem) << ") damage. +" << toInt(value) << " Attack. ";
        }
    }
    else if(type == ItmType::Armor){ //Else if the Item is armor
        if(elem == DmgElem::NONE){ //If no element
            r << "+" << toInt(value) << " Defense. ";
        }
        else{
            r << "Resists ( " << DmgElem::toStr(elem) << ") damage. +" << toInt(value) << " Defense. ";
        }
    }

    return r.str(); //Convert to string and return
}

//mkName
//Make an Item name
//Input:
//elem
//The element of the Item to make a name for
//type
//The type of the Item to make a name for
//Output:
//A string containing an Item name

std::string Flow::Item::mkName(unsigned char elem, ItmType type){
    std::stringstream r; //A string string to create a string from

    switch(type){
        case ItmType::Armor: //If the Item is Armor
        {
            if(elem == DmgElem::ABSOLUT){ //If ABSOLUT
                r << "Legendary ";
            }
            else{ //Otherwise
                if(FlgUtil::hasFlag(elem, DmgElem::HEALING)){ //If the HEALING flag is on
                    r << "Curative ";
                }
                if(FlgUtil::hasFlag(elem, DmgElem::NGHTMRE)){ //If the NGHTMRE flag is on
                    r << "Weirding ";
                }
                if(FlgUtil::hasFlag(elem, (DmgElem::HOLY | DmgElem::SHADOW))){ //If the HOLY and SHADOW flags are on
                    r << "Streaked ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::HOLY)){ //If the HOLY flag is on
                    r << "Sanctified ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::SHADOW)){ //If the SHADOW flag is on
                    r << "Damned ";
                }
                if(FlgUtil::hasFlag(elem, (DmgElem::FIRE | DmgElem::ICE))){ //If the FIRE and ICE flags are on
                    r << "Cauterizing ";
                }
                else if(FlgUtil::hasFlag(elem, (DmgElem::FIRE | DmgElem::LIGHTNG))){ //If the FIRE and LIGHTNG flags are on
                    r << "Quivering ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::FIRE)){ //If the FIRE flag is on
                    r << "Flaming ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::LIGHTNG)){ //If the LIGHTNG flag is on
                    r << "Shocking ";
                }
                else if(FlgUtil::hasFlag(elem, (DmgElem::ICE | DmgElem::WIND))){ //If the ICE and WIND flags are on
                    r << "Steaming ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::ICE)){ //If the ICE flag is on
                    r << "Frosted ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::WIND)){ //If the WIND flag is on
                    r << "Storming ";
                }
            }

            r << "Armor";
            break;
        }
        case ItmType::Potion: //If the Item is a Potion
        {
            if(elem == Flow::DmgElem::NONE){ //If NONE
                r << "Identifying ";
            }
            if(elem == Flow::DmgElem::ABSOLUT){ //If ABSOLUT
                r << "Invigorating ";
            }
            else{ //Otherwise (This is the same as with weapons and armor even though the names are different)
                if(FlgUtil::hasFlag(elem, DmgElem::HEALING)){
                    r << "Frothing ";
                }
                if(FlgUtil::hasFlag(elem, DmgElem::NGHTMRE)){
                    r << "Obfuscating ";
                }
                if(FlgUtil::hasFlag(elem, (DmgElem::HOLY | DmgElem::SHADOW))){
                    r << "Swirling ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::HOLY)){
                    r << "Sanctified ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::SHADOW)){
                    r << "Damned ";
                }
                if(FlgUtil::hasFlag(elem, (DmgElem::FIRE | DmgElem::ICE))){
                    r << "Bubbling ";
                }
                else if(FlgUtil::hasFlag(elem, (DmgElem::FIRE | DmgElem::LIGHTNG))){
                    r << "Thickened ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::FIRE)){
                    r << "Searing ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::LIGHTNG)){
                    r << "Convulsing ";
                }
                else if(FlgUtil::hasFlag(elem, (DmgElem::ICE | DmgElem::WIND))){
                    r << "Misty ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::ICE)){
                    r << "Freezing ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::WIND)){
                    r << "Harrowing ";
                }
            }

            r << "Potion";
            break;
        }
        case ItmType::Weapon: //If the Item is a Weapon
        {
            if(elem == Flow::DmgElem::ABSOLUT){ //If ABSOLUT
                r << "Legendary ";
            }
            else{ //Otherwise (again the same as armor and potions)
                if(FlgUtil::hasFlag(elem, DmgElem::HEALING)){
                    r << "Curative ";
                }
                if(FlgUtil::hasFlag(elem, DmgElem::NGHTMRE)){
                    r << "Weirding ";
                }
                if(FlgUtil::hasFlag(elem, (DmgElem::HOLY | DmgElem::SHADOW))){
                    r << "Streaked ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::HOLY)){
                    r << "Sanctified ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::SHADOW)){
                    r << "Damned ";
                }
                if(FlgUtil::hasFlag(elem, (DmgElem::FIRE | DmgElem::ICE))){
                    r << "Cauterizing ";
                }
                else if(FlgUtil::hasFlag(elem, (DmgElem::FIRE | DmgElem::LIGHTNG))){
                    r << "Quivering ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::FIRE)){
                    r << "Flaming ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::LIGHTNG)){
                    r << "Shocking ";
                }
                else if(FlgUtil::hasFlag(elem, (DmgElem::ICE | DmgElem::WIND))){
                    r << "Steaming ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::ICE)){
                    r << "Frosted ";
                }
                else if(FlgUtil::hasFlag(elem, DmgElem::WIND)){
                    r << "Storming ";
                }
            }

            if(Game::player.job() != Job::None){ //If the player has a set Job
                int loc = static_cast<int>(Game::player.job()) - 1; //Calculate the index of that Job's weapon names
                r << Game::nWeaps[loc].at(Game::gmRand.rand() % Game::nWeaps[loc].size()); //Insert the weapon name
            }
            else{ //Otherwise
                r << "Fists";
            }

            break;
        }
        default: //This shouldn't be able to happen
        {
            r << "Invalid Type";
        }
    }

    return r.str(); //Convert r to a string and return
}

//toBin
//Convert the Item object to a BinArray
//Output:
//A BinArray containing the binary data for this object

Flow::BinArray Flow::Item::toBin(){
    BinArray name = Flow::toBin(_name), //The name of the Item as binary
            uiName = Flow::toBin(_uiName), //The unidentified name as binary
            desc = Flow::toBin(_desc), //The description as binary
            r(name.size() + uiName.size() + desc.size() + sizeof (_elem) + sizeof (_value) + sizeof (_type)
              + sizeof (_ident)); //Allocate the return array

    r << name; //Insert the name
    r << uiName; //Insert the unidentified name
    r << desc; //Insert the description
    r << BinArray(reinterpret_cast<char*>(&_elem), sizeof (_elem)); //Insert the element
    r << BinArray(reinterpret_cast<char*>(&_value), sizeof (_value)); //Insert the value
    r << BinArray(reinterpret_cast<char*>(&_type), sizeof (_type)); //Insert the type
    r << BinArray(reinterpret_cast<char*>(&_ident), sizeof (_ident)); //Insert whether or not the Item was identified

    return r;
}

//toItem
//Fill this item using the input binary data
//Input:
//data
//The data to create Item properties from

void Flow::Item::toItem(BinArray &data){
    BinArray strSize(sizeof (unsigned int)), //Allocate string size
            str, //A string
            elem(sizeof (_elem)), //Allocate element
            value(sizeof (_value)), //Allocate value
            iType(sizeof (_type)), //Allocate type
            ident(sizeof (_ident)); //Allocate ident

    data >> strSize; //Read string size
    str = BinArray(sizeof (unsigned int) +Flow::toInt(strSize)); //Allocate string
    data.seekg(data.tellg() - sizeof (unsigned int)); //Seek back
    data >> str; //Extract string
    _name = Flow::toStr(str); //Set name

    data >> strSize;
    str = BinArray(sizeof (unsigned int) +Flow::toInt(strSize));
    data.seekg(data.tellg() - sizeof (unsigned int));
    data >> str;
    _uiName = Flow::toStr(str); //Set unidentified name

    data >> strSize;
    str = BinArray(sizeof (unsigned int) +Flow::toInt(strSize));
    data.seekg(data.tellg() - sizeof (unsigned int));
    data >> str;
    _desc = Flow::toStr(str); //Set description

    data >> elem; //Extract element
    _elem = elem[0]; //Set element

    data >> value; //Extract value
    _value = value[0]; //Set value

    data >> iType; //Extract type as an int
    _type = static_cast<ItmType>(toInt(iType)); //Set type

    data >> ident; //Extract ident
    _ident = ident[0]; //Set ident
}