/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   random.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 2, 2016
 */

#include "random.h"

Flow::GmRand::GmRand(){
    _point.pos = 0;
    _point.seed = 0;
}

void Flow::GmRand::srand(){
    _point.pos = 0;
    _point.seed = to_int(time(0));

    std::srand(_point.seed);
}

void Flow::GmRand::srand(unsigned int seed){
    _point.pos = 0;
    _point.seed = seed;

    std::srand(_point.seed);
}

int Flow::GmRand::rand(){
    ++_point.pos;
    return std::rand();
}

void Flow::GmRand::seek(unsigned int pos){
    srand(_point.seed);

    for(unsigned int i = 0; i < pos; ++i){
        rand();
    }
}

unsigned int Flow::GmRand::pos(){
    return _point.pos;
}

unsigned int Flow::GmRand::seed(){
    return _point.seed;
}

Flow::Actor Flow::GmRand::rActor(){ }

unsigned char Flow::GmRand::rElem(){
    unsigned char val = rand() % 100; //Generate a percentage
    unsigned char r = 0;

    if(val < 75){ //75% chance of unenchanted item
        r = DmgElem::NONE;
    }
    else if(val >= 75 && val < 90){ //15% chance of single enchanted item
        r = 1 << (rand() % 8); //Generate a single element value between 2^0 and 2^7
    }
    else{ ///10% chance of possible multiple enchants
        r = rand() % 256; //Generate a totally random element
    }
}

void Flow::GmRand::rItem(Actor &target, ItemType type){
    std::shared_ptr<Collections::Dictionary<ItemType, Collections::LinkedList < std::string>>> uiNames =
            Game::get<Collections::Dictionary<ItemType, Collections::LinkedList < std::string>>>("item_names");
    RNGPoint gen = _point;
    unsigned char value = rand() % 256;
    unsigned char elem = rElem();
    int percent = rand() % 100;
    std::string uiName = "";

    if(type == ItemType::None){
        if(percent < 50){
            uiName = (*uiNames)[ItemType::Potion][rand() % uiNames->size()];
            Potion itm("", uiName, "", elem, value);
            itm.generationPoint(gen);
            target.addItem(itm);
        }
        else if(percent >= 50 && percent < 70){
            uiName = (*uiNames)[ItemType::Armor][rand() % uiNames->size()];
            Armor itm("", uiName, "", elem, value);
            itm.generationPoint(gen);
            target.addItem(itm);
        }
        else{
            uiName = (*uiNames)[ItemType::Weapon][rand() % uiNames->size()];
            Weapon itm("", uiName, "", elem, value);
            itm.generationPoint(gen);
            target.addItem(itm);
        }
    }
    else{
        switch(type){
            case ItemType::Potion:
            {
                uiName = (*uiNames)[ItemType::Potion][rand() % uiNames->size()];
                Potion itm("", uiName, "", elem, value);
                itm.generationPoint(gen);
                target.addItem(itm);
                break;
            }
            case ItemType::Weapon:
            {
                uiName = (*uiNames)[ItemType::Weapon][rand() % uiNames->size()];
                Weapon itm("", uiName, "", elem, value);
                itm.generationPoint(gen);
                target.addItem(itm);
                break;
            }
            case ItemType::Armor:
            {
                uiName = (*uiNames)[ItemType::Armor][rand() % uiNames->size()];
                Armor itm("", uiName, "", elem, value);
                itm.generationPoint(gen);
                target.addItem(itm);
                break;
            }
        }
    }

    std::cout << uiName << " acquired!" << std::endl;
}

void Flow::GmRand::seek(const RNGPoint &point){
    _point.seed = point.seed;
    seek(point.pos);
}

Flow::Floor Flow::GmRand::rFloor(unsigned char size){
    Floor r; //The return floor
    Point pos; //The current position of the generator
    Point last; //The previous position
    bool filled[r.sizeY()][r.sizeX()] = {}; //A 2D array indicating if the generator has already filled a room
    unsigned char direct = Direct::NONE; //The direction to move in

    pos.x = rand() % r.sizeX(); //Generate a random x position
    pos.y = rand() % r.sizeY(); //Generate a random y position

    for(int i = 0; i < size; i += filled[last.y][last.x]){ //Until the Floor has reached the correct size
        //Set the last position
        last.x = pos.x;
        last.y = pos.y;

        if(i == 0){ //If this is the first room
            r[pos.y][pos.x] = rRoom(true); //Generate a random room
            filled[pos.y][pos.x] = true; //Set it as filled
            do{ //While the generator hasn't stepped
                direct = rDirect(); //Generate a random direction
            } while(!r.move(pos, direct)); //Attempt to move in that direction
            r[last.y][last.x].addExit(direct); //Add an exit

        }
        else if(i == size - 1){ //If this is the last room
            if(!filled[pos.y][pos.x]){ //If the room hasn't been filled
                r[pos.y][pos.x] = rRoom(false, true); //Generate a random room
                filled[pos.y][pos.x] = true; //Fill it
            }
            else{ //Otherwise
                r[pos.y][pos.x] = Room(r[pos.y][pos.x].exit(), r[pos.y][pos.x].event(), false, true); //Add the stairs down
            }
            r[pos.y][pos.x].addExit(Direct::reverse(direct)); //Add an exit to the last room
        }
        else{ //Otherwise
            if(!filled[pos.y][pos.x]){ //If room hasn't been filled
                r[pos.y][pos.x] = rRoom(); //Generate a random room
                filled[pos.y][pos.x] = true; //Fill it
            }
            r[pos.y][pos.x].addExit(Direct::reverse(direct)); //Add an exit to the last room
            do{ //While the generator hasn't stepped
                direct = rDirect(); //Generate a random direction
            } while(!r.move(pos, direct)); //Attempt to move in that direction
            r[last.y][last.x].addExit(direct); //Add an exit
        }
    }

    return r;
}

Flow::Room Flow::GmRand::rRoom(bool start, bool end){
    unsigned char rVal = rand() % 100; //Generate a percentage
    RmEvent event = RmEvent::None; //Default the even to none

    if(rVal >= 0 && rVal < 50){ //50% chance of an Encounter
        event = RmEvent::Encounter;
    }
    else if(rVal >= 50 && rVal < 70){ //20% chance of Treasure
        event = RmEvent::Treasure;
    }
    else if(rVal >= 70 && rVal < 80){ //10% chance of healing Spring
        event = RmEvent::Spring;
    }

    return Room(Direct::NONE, event, start, end); //Return the new room
}

unsigned char Flow::GmRand::rDirect(){
    unsigned char r = Direct::NONE; //The return value

    switch(rand() % 4){ //Convert from 0-3 to 2^0, 2^1, 2^2, or 2^3
        case 0:
        {
            r = Direct::NORTH;
            break;
        }
        case 1:
        {
            r = Direct::EAST;
            break;
        }
        case 2:
        {
            r = Direct::SOUTH;
            break;
        }
        case 3:
        {
            r = Direct::WEST;
            break;
        }
    }

    return r;
}