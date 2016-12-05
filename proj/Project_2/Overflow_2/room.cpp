/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   room.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 3, 2016
 */

#include "room.h"

Flow::Room::Room(){
    _exit = Direct::NONE;
    _event = RmEvent::None;
    _start = false;
    _end = false;
}

Flow::Room::Room(const Room &other){
    _exit = other.exit();
    _event = other.event();
    _start = other.isStart();
    _end = other.isEnd();
}

Flow::Room::Room(unsigned char exit, RmEvent event, bool start, bool end){
    _exit = exit;
    _event = event;
    _start = start;
    _end = end;
}

void Flow::Room::addExit(unsigned char exit){
    _exit |= exit;
}

Flow::RmEvent Flow::Room::event() const{
    return _event;
}

void Flow::Room::event(RmEvent nEvent){
    _event = nEvent;
}

unsigned char Flow::Room::exit() const{
    return _exit;
}

void Flow::Room::exit(unsigned char nExit){
    _exit = nExit;
}

void Flow::Room::trigger(){
    std::shared_ptr<GmRand> gmRand = Game::get<GmRand>("rand");
    std::shared_ptr<Actor> player = Game::get<Actor>("player");
    std::shared_ptr<bool> over = Game::get<bool>("game_over");
    std::shared_ptr<Floor> floor = Game::get<Floor>("floor");
    std::shared_ptr<Config> conf = Game::get<Config>("game_config");
    std::shared_ptr<Point> pos = Game::get<Point>("player_pos");

    bool moved = false; //If the player has moved
    std::stringstream convert; //String stream for conversion
    convert << "GameData/desc" << (to_int(_event) * 3) + ((gmRand->rand() % 3) + 1) << ".txt"; //Get description path
    rdTxt(convert.str()); //Display Room description
    std::cout << std::endl;

    if(_event != RmEvent::None){ //If the RmEvent is not none
        if(_event == RmEvent::Encounter){ //If encounter
            Actor enem = gmRand->rActor(); //Create enemy
            std::cout << "A " << enem.name() << " attacks!" << std::endl;
            *over = !encounter(enem); //Process encounter
        }
        else if(_event == RmEvent::Treasure){ //If treasure
            unsigned char tCount = (gmRand->rand() % 3) + 1; //Generate between 1 and 3 treasures

            for(int i = 0; i < tCount; ++i){ //For each treasure
                gmRand->rItem(*player); //Generate a treasure
            }
        }
        else if(_event == RmEvent::Spring){ //If spring
            player->hp(player->hp().max()); //Heal player
            player->mp(player->mp().max()); //Heal player
            std::cout << player->name() << " is fully restored!" << std::endl;
            for(int i = 0; i < player->invSize(); ++i){ //Identify Items
                player->identify(i); //Identify
            }
            std::cout << "Items identified!" << std::endl;
        }
        _event = RmEvent::None; //Clear room event
    }
    else{ //If the event is None
        std::cout << "There are exits to the ( " << Direct::toString(_exit) << ")" << std::endl; //Display Exits
        if(_end){ //If this is the end Room
            std::cout << "You can see a flight of stairs in the far corner!" << std::endl; //Display End message
        }
        Collections::LinkedList<std::string> tmpMenu = {"Player Status", "Inventory", "Options", "Map"}; //Add exits to game menu
        if(FlagUtil::hasFlag(_exit, Direct::NORTH)){
            tmpMenu.addBack("North");
        }
        if(FlagUtil::hasFlag(_exit, Direct::EAST)){
            tmpMenu.addBack("East");
        }
        if(FlagUtil::hasFlag(_exit, Direct::SOUTH)){
            tmpMenu.addBack("South");
        }
        if(FlagUtil::hasFlag(_exit, Direct::WEST)){
            tmpMenu.addBack("West");
        }
        if(_end){
            tmpMenu.addBack("Down");
        }
        do{ //While the player hasn't moved Rooms
            char input = menu(tmpMenu, 4); //Display the game menu
            switch(input){
                case 'P': //Player Status
                {
                    std::cout << player->name() << std::endl;
                    std::cout << "Job: " << toString(player->job()) << std::endl;
                    std::cout << player->hp().fullName() << ": " << player->hp().value() << "/" << player->hp().max()
                            << std::endl;
                    std::cout << player->mp().fullName() << ": " << player->mp().value() << "/" << player->mp().max()
                            << std::endl;
                    std::cout << player->attack().fullName() << ": " << to_int(player->attack().value()) << std::endl;
                    std::cout << player->defense().fullName() << ": " << to_int(player->defense().value()) << std::endl;
                    std::cout << "Weapon: " << player->weapon().name() << std::endl;
                    std::cout << "\t" << player->weapon().description() << std::endl;
                    std::cout << "Armor: " << player->armor().name() << std::endl;
                    std::cout << "\t" << player->armor().description() << std::endl;
                    break;
                }
                case 'I': //Inventory
                {
                    player->selectItem();
                    break;
                }
                case 'O': //Options
                {
                    getOptionsMenu();
                    if(*over){ //If quitting
                        moved = true;
                    }
                    break;
                }
                case 'M': //Map
                {
                    floor->draw(); //Draw map
                    break;
                }
                default: //For anything else
                {
                    if(input == 'N' && FlagUtil::hasFlag(_exit, Direct::NORTH)){ //If moving North
                        floor->move(*pos, Direct::NORTH);
                        moved = true;
                    }
                    else if(input == 'E' && FlagUtil::hasFlag(_exit, Direct::EAST)){ //If moving East
                        floor->move(*pos, Direct::EAST);
                        moved = true;
                    }
                    else if(input == 'S' && FlagUtil::hasFlag(_exit, Direct::SOUTH)){ //If moving South
                        floor->move(*pos, Direct::SOUTH);
                        moved = true;
                    }
                    else if(input == 'W' && FlagUtil::hasFlag(_exit, Direct::WEST)){ //If moving West
                        floor->move(*pos, Direct::WEST);
                        moved = true;
                    }
                    else if(input == 'D' && _end){ //If exiting the Floor
                        *over = true; //Quit game
                        if(conf->asciiArt){ //If ASCII art is on
                            rdTxt("GameData/win.txt"); //Win message
                        }
                        else{ //Otherwise
                            std::cout << "YOU WIN!" << std::endl;
                        }
                        //save(); //Save the game
                        moved = true;
                    }
                }
            }
        } while(!moved);
    }
}

bool Flow::Room::isStart() const{
    return _start;
}

bool Flow::Room::isEnd() const{
    return _end;
}

Flow::Floor::Floor(){
    _sizeX = 8;
    _sizeY = 8;
    _rooms = new Room*[_sizeY];
    for(int i = 0; i < _sizeY; ++i){
        _rooms[i] = new Room[_sizeX];
    }
}

Flow::Floor::Floor(const Floor &other){
    _sizeX = other.sizeX();
    _sizeY = other.sizeY();
    _rooms = new Room*[_sizeY]; //Allocate Y dimension of array
    for(int i = 0; i < _sizeY; ++i){
        _rooms[i] = new Room[_sizeX]; //Allocate X dimension of array
    }
    for(int i = 0; i < _sizeY; ++i){
        for(int j = 0; j < _sizeX; ++j){
            _rooms[i][j] = Room(other.get(j, i)); //Copy Rooms from other to this Floor
        }
    }
}

Flow::Floor::Floor(unsigned char sizeX, unsigned char sizeY){
    _sizeX = sizeX;
    _sizeY = sizeY;
    _rooms = new Room*[_sizeY]; //Allocate Y dimension of array
    for(int i = 0; i < _sizeY; ++i){
        _rooms[i] = new Room[_sizeX]; //Allocate X dimension of array
    }
}

Flow::Floor::~Floor(){
    for(int i = 0; i < _sizeY; ++i){ //Delete arrays in reverse order
        delete [] _rooms[i];
        _rooms[i] = 0;
    }
    delete [] _rooms; //Then delete the outer array
    _rooms = 0;
}

bool Flow::Floor::move(Point &pos, unsigned char direct){
    if(direct == Direct::NORTH && !isOverflowY(pos.y - 1)){ //If moving North and not overflowing the Floor
        --pos.y; // Move
        return true;
    }
    else if(direct == Direct::EAST && !isOverflowX(pos.x + 1)){ //If moving East and not overflowing the Floor
        ++pos.x; //Move
        return true;
    }
    else if(direct == Direct::SOUTH && !isOverflowY(pos.y + 1)){ //If moving South and not overflowing the Floor
        ++pos.y; //Move
        return true;
    }
    else if(direct == Direct::WEST && !isOverflowX(pos.x - 1)){ //If moving West and not overflowing the Floor
        --pos.x; //Move
        return true;
    }
    return false;
}

void Flow::Floor::draw() const{
    std::shared_ptr<Point> pos = Game::get<Point>("player_pos");
    for(int i = 0; i < _sizeY; ++i){ //For every row
        for(int j = 0; j < _sizeX; ++j){ //For every column
            std::cout << "[";
            if(pos->x == j && pos->y == i){ //Output @ for the player position (similar to NetHack)
                std::cout << "@";
            }
            else if(_rooms[i][j].isStart()){ //Output S for the start position
                std::cout << "S";
            }
            else if(_rooms[i][j].exit() == 0){ //Output X for locked Rooms
                std::cout << "X";
            }
            else{ //Otherwise output a space
                std::cout << " ";
            }
            std::cout << "]";
        }
        std::cout << std::endl;
    }
}

void Flow::Floor::drawDbg() const{
    for(int i = 0; i < _sizeY; ++i){ //For every row
        for(int j = 0; j < _sizeX; ++j){ //For every column
            //Output Debug data
            std::cout << "[" << std::setw(5) << Direct::toString(_rooms[i][j].exit(), true);
            std::cout << _rooms[i][j].isStart() << _rooms[i][j].isEnd();
            std::cout << to_int(_rooms[i][j].event()) << "]";
        }
        std::cout << std::endl;
    }
}

bool Flow::Floor::isOverflow(unsigned char x, unsigned char y) const{
    if(isOverflowX(x) || isOverflowY(y)){ //If overflow on X or Y
        return true;
    }
    return false;
}

bool Flow::Floor::isOverflowX(unsigned char x) const{
    if(x >= _sizeX || x < 0){ ///If greater than sizeX or less than 0
        return true;
    }
    return false;
}

bool Flow::Floor::isOverflowY(unsigned char y) const{
    if(y >= _sizeY || y < 0){ //If greater than sizeY or less than 0
        return true;
    }
    return false;
}

unsigned char Flow::Floor::sizeX() const{
    return _sizeX;
}

unsigned char Flow::Floor::sizeY() const{
    return _sizeY;
}

Flow::Point Flow::Floor::start() const{
    Point start; //The return point

    for(int i = 0; i < _sizeY; ++i){ //For every row
        for(int j = 0; j < _sizeX; ++j){ //For every column
            if(_rooms[i][j].isStart()){ //If the Room is the start
                start.x = j; //Set the position
                start.y = i;
            }
        }
    }

    return start;
}

Flow::Room Flow::Floor::get(unsigned char x, unsigned char y) const{
    return _rooms[y][x];
}

Flow::Room* Flow::Floor::operator[](unsigned int index){
    return _rooms[index];
}

Flow::Floor& Flow::Floor::operator=(const Floor &rhs){
    Floor cpy(rhs);
    swap(*this, cpy);

    return *this;
}

void Flow::Floor::swap(Floor &a, Floor &b){
    std::swap(a._rooms, b._rooms);
    std::swap(a._sizeX, b._sizeX);
    std::swap(a._sizeY, b._sizeY);
}

