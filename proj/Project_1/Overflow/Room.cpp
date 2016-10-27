/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Room.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for Room.h
 * Created on October 22, 2016
 */


//User Libraries
#include "Room.h" //Room, Floor, and Point objects
#include "Game.h" //Main game objects and loose functions

//Room
//Default constructor

Flow::Room::Room(){
    _exit = Direct::NONE;
    _event = RmEvent::None;
    _start = false;
    _end = false;
}

//Room
//Copy constructor

Flow::Room::Room(const Room &other){
    if(this != &other){
        _exit = other.exit();
        _event = other.event();
        _start = other.isStart();
        _end = other.isEnd();
    }
}

//Room
//Parameterized constructor

Flow::Room::Room(unsigned char exit, RmEvent event, bool start, bool end){
    _exit = exit;
    _event = event;
    _start = start;
    _end = end;
}

//event
//Returns this Room's event
//Output:
//The currently set event for this Room

Flow::RmEvent Flow::Room::event() const{
    return _event;
}

//exit
//Returns the exits to this Room
//Output:
//An unsigned char representing the locations of exits to this Room

unsigned char Flow::Room::exit() const{
    return _exit;
}

//setEvent
//Sets the RmEvent for this Room
//Input:
//event
//An RmEvent value to set the event to

void Flow::Room::setEvent(RmEvent event){
    _event = event;
}

//setExit
//Sets the Exits to this Room
//Input:
//exit
//An unsigned char containing exit flags

void Flow::Room::setExit(unsigned char exit){
    _exit = exit;
}

//isStart
//Returns whether or not this Room is the start Room for the Floor
//Output:
//True if it is the start Room false otherwise

bool Flow::Room::isStart() const{
    return _start;
}

//isEnd
//Returns whether or not this Room is the end Room for the Floor
//Output:
//True if it is the end Room false otherwise

bool Flow::Room::isEnd() const{
    return _end;
}

//addExit
//Adds an exit to a Room
//Input:
//exit
//The exit to add to the Room

void Flow::Room::addExit(unsigned char exit){
    _exit |= exit;
}

//trigger
//Triggers the event for the Room. Most game processing happens here

void Flow::Room::trigger(){
    bool moved = false; //If the player has moved
    std::stringstream convert; //String stream for conversion
    convert << "GameData/desc" << (static_cast<int>(_event) * 3) + ((Game::gmRand.rand() % 3) + 1) << ".txt"; //Get description path
    rdTxt(convert.str()); //Display Room description
    std::cout << std::endl;

    if(_event != RmEvent::None){ //If the RmEvent is not none
        if(_event == RmEvent::Encounter){ //If encounter
            Actor enem = Game::gmRand.rActor(); //Create enemy
            std::cout << "A " << enem.name() << " attacks!" << std::endl;
            Game::over = !Flow::encounter(enem); //Process encounter
        }
        else if(_event == RmEvent::Treasure){ //If treasure
            unsigned char tCount = (Game::gmRand.rand() % 3) + 1; //Generate between 1 and 3 treasures

            for(int i = 0; i < tCount; ++i){ //For each treasure
                Item treas = Game::gmRand.rItem(); //Generate a treasure
                std::cout << treas.uiName() << " acquired!" << std::endl;
                Game::player.addItem(treas); //Add treasure to the player's inventory
            }
        }
        else if(_event == RmEvent::Spring){ //If spring
            Game::player.setHp(Game::player.hp().max()); //Heal player
            Game::player.setMp(Game::player.mp().max()); //Heal player
            std::cout << Game::player.name() << " is fully restored!" << std::endl;
            for(int i = 0; i < Game::player.invSize(); ++i){ //Identify Items
                Game::player.identify(i); //Identify
            }
            std::cout << "Items identified!" << std::endl;
        }
        _event = RmEvent::None; //Clear room event
    }
    else{ //If the event is None
        std::cout << "There are exits to the ( " << Direct::toStr(_exit) << ")" << std::endl; //Display Exits
        if(_end){ //If this is the end Room
            std::cout << "You can see a flight of stairs in the far corner!" << std::endl; //Display End message
        }
        std::vector<std::string> tmpMenu(Game::gMenu); //Add exits to game menu
        if(FlgUtil::hasFlag(_exit, Direct::NORTH)){
            tmpMenu.push_back("North");
        }
        if(FlgUtil::hasFlag(_exit, Direct::EAST)){
            tmpMenu.push_back("East");
        }
        if(FlgUtil::hasFlag(_exit, Direct::SOUTH)){
            tmpMenu.push_back("South");
        }
        if(FlgUtil::hasFlag(_exit, Direct::WEST)){
            tmpMenu.push_back("West");
        }
        if(_end){
            tmpMenu.push_back("Down");
        }
        do{ //While the player hasn't moved Rooms
            Game::input = menu(tmpMenu, 4); //Display the game menu
            switch(Game::input){
                case 'P': //Player Status
                {
                    Game::player.stat();
                    break;
                }
                case 'I': //Inventory
                {
                    Game::player.selectItm();
                    break;
                }
                case 'O': //Options
                {
                    Flow::gMOpts();
                    if(Game::over){ //If quitting
                        moved = true;
                    }
                    break;
                }
                case 'M': //Map
                {
                    Game::floor.draw(); //Draw map
                    break;
                }
                default: //For anything else
                {
                    if(Game::input == 'N' && FlgUtil::hasFlag(_exit, Direct::NORTH)){ //If moving North
                        Game::floor.move(Game::pos, Direct::NORTH);
                        moved = true;
                    }
                    else if(Game::input == 'E' && FlgUtil::hasFlag(_exit, Direct::EAST)){ //If moving East
                        Game::floor.move(Game::pos, Direct::EAST);
                        moved = true;
                    }
                    else if(Game::input == 'S' && FlgUtil::hasFlag(_exit, Direct::SOUTH)){ //If moving South
                        Game::floor.move(Game::pos, Direct::SOUTH);
                        moved = true;
                    }
                    else if(Game::input == 'W' && FlgUtil::hasFlag(_exit, Direct::WEST)){ //If moving West
                        Game::floor.move(Game::pos, Direct::WEST);
                        moved = true;
                    }
                    else if(Game::input == 'D' && _end){ //If exiting the Floor
                        Game::over = true; //Quit game
                        if(Game::conf.ascArt){ //If ASCII art is on
                            rdTxt("GameData/win.txt"); //Win message
                        }
                        else{ //Otherwise
                            std::cout << "YOU WIN!" << std::endl;
                        }
                        save(); //Save the game
                        moved = true;
                    }
                }
            }
        } while(!moved);
    }
}

//Floor
//Default constructor

Flow::Floor::Floor(){
    _sizeX = 8;
    _sizeY = 8;
    _rooms = new Room*[_sizeY]; //Allocate Y dimension of array
    for(int i = 0; i < _sizeY; ++i){
        _rooms[i] = new Room[_sizeX]; //Allocate X dimension of array
    }
}

//Floor
//Copy constructor

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

//Floor
//Parameterized constructor

Flow::Floor::Floor(unsigned char sizeX, unsigned char sizeY){
    _sizeX = sizeX;
    _sizeY = sizeY;
    _rooms = new Room*[_sizeY]; //Allocate Y dimension of array
    for(int i = 0; i < _sizeY; ++i){
        _rooms[i] = new Room[_sizeX]; //Allocate X dimension of array
    }
}

//~Floor
//Destructor

Flow::Floor::~Floor(){
    clear(); //Clear dynamic memory
}

//[]
//Index operator for Floor objects
//Input:
//index
//The index to get
//Output:
//A pointer to one of the underlying Room arrays

Flow::Room* Flow::Floor::operator[](unsigned int index){
    return _rooms[index];
}

//=
//Copy assignment operator
//Input:
//other
//The other Floor to copy from
//Output:
//A reference to this Floor

Flow::Floor& Flow::Floor::operator=(const Floor &other){
    if(this != &other){ //Don't assign to yourself
        _sizeX = other.sizeX();
        _sizeY = other.sizeY();
        clear(); //Clear old memory
        _rooms = new Room*[_sizeY]; //Allocate new Y dimension
        for(int i = 0; i < _sizeY; ++i){
            _rooms[i] = new Room[_sizeX]; //Allocate new X dimension
        }
        for(int i = 0; i < _sizeY; ++i){
            for(int j = 0; j < _sizeX; ++j){
                _rooms[i][j] = Room(other.get(j, i)); //Copy Rooms from other to this Floor
            }
        }
    }

    return *this;
}

//sizeX
//Returns the X size for this Floor
//Output:
//The current X axis size

unsigned char Flow::Floor::sizeX() const{
    return _sizeX;
}

//sizeY
//Return the Y size for this Floor
//Output:
//The current Y axis size

unsigned char Flow::Floor::sizeY() const{
    return _sizeY;
}

//get
//Return the Room at the given (x, y) position
//Input:
//x
//The X axis position of the Room
//y
//The Y axis position of the Room
//Output:
//The Room at the given (x, y) position

Flow::Room Flow::Floor::get(unsigned char x, unsigned char y) const{
    return _rooms[y][x];
}

//isOverflowX
//Returns whether or not a position is beyond the bounds of the X axis of the Floor
//Input:
//x
//The position to check
//Output:
//True if the value is out of bounds false otherwise

bool Flow::Floor::isOverflowX(unsigned char x) const{
    if(x >= _sizeX || x < 0){ ///If greater than sizeX or less than 0
        return true;
    }
    return false;
}

//isOverflowY
//Returns whether or not a position is beyond the bounds of the Y axis of the Floor
//Input:
//y
//The position to check
//Output:
//True if the value is out of bounds false otherwise

bool Flow::Floor::isOverflowY(unsigned char y) const{
    if(y >= _sizeY || y < 0){ //If greater than sizeY or less than 0
        return true;
    }
    return false;
}

//isOverflow
//Returns whether or not a position is beyond the bounds of the X  or Y axis of the Floor
//Input:
//x
//The X position to check
//y
//The Y position to check
//Output:
//True if the value is out of bounds false otherwise

bool Flow::Floor::isOverflow(unsigned char x, unsigned char y) const{
    if(isOverflowX(x) || isOverflowY(y)){ //If overflow on X or Y
        return true;
    }
    return false;
}

//move
//Alters the position of a Point so that it has been moved one space in the correct direction
//Input:
//pos
//A point to alter
//direct
//The direction to move in
//Output:
//True if the move was possible otherwise false
//The altered pos object

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

//draw
//Draws the Floor as a map for gameplay

void Flow::Floor::draw() const{
    for(int i = 0; i < _sizeY; ++i){ //For every row
        for(int j = 0; j < _sizeX; ++j){ //For every column
            std::cout << "[";
            if(Game::pos.x == j && Game::pos.y == i){ //Output @ for the player position (similar to NetHack)
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

//drawDbg
//Draws a debug map

void Flow::Floor::drawDbg() const{
    for(int i = 0; i < _sizeY; ++i){ //For every row
        for(int j = 0; j < _sizeX; ++j){ //For every column
            //Output Debug data
            std::cout << "[" << std::setw(5) << Direct::toStr(_rooms[i][j].exit(), true);
            std::cout << _rooms[i][j].isStart() << _rooms[i][j].isEnd();
            std::cout << static_cast<int>(_rooms[i][j].event()) << "]";
        }
        std::cout << std::endl;
    }
}

//start
//Searches for and finds the start Room for a Floor
//Output:
//A point containing the position of the starting Room

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

//clear
//Clears allocated memory from the Floor object

void Flow::Floor::clear(){
    for(int i = 0; i < _sizeY; ++i){ //Delete arrays in reverse order
        delete [] _rooms[i];
        _rooms[i] = 0;
    }
    delete [] _rooms; //Then delete the outer array
    _rooms = 0;
}