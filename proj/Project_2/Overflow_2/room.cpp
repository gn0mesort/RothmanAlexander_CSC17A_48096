/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   room.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for room.h
 * Created on December 3, 2016
 */

#include "room.h"

/**
 * Default Room constructor
 */
Flow::Room::Room(){
    _exit = Direct::NONE;
    _event = RmEvent::None;
    _start = false;
    _end = false;
}

/**
 * Room copy constructor
 * @param other The Room to copy
 */
Flow::Room::Room(const Room &other){
    _exit = other.exit();
    _event = other.event();
    _start = other.isStart();
    _end = other.isEnd();
}

/**
 * Parameterized Room constructor
 * @param exit The exits to the Room
 * @param event The Room's event
 * @param start Whether or not the Room is the start of the Floor
 * @param end Whether or not the Room is end of the Floor
 */
Flow::Room::Room(unsigned char exit, RmEvent event, bool start, bool end){
    _exit = exit;
    _event = event;
    _start = start;
    _end = end;
}

/**
 * Add an exit to the Room
 * @param exit The exit to add
 */
void Flow::Room::addExit(unsigned char exit){
    _exit |= exit;
}

/**
 * Get the event for the Room
 * @return The event for this Room
 */
Flow::RmEvent Flow::Room::event() const{
    return _event;
}

/**
 * Set the event for this Room
 * @param nEvent An RmEvent indicating the event of this Room
 */
void Flow::Room::event(RmEvent nEvent){
    _event = nEvent;
}

/**
 * Get the exits to the Room
 * @return The current exits to the Room
 */
unsigned char Flow::Room::exit() const{
    return _exit;
}

/**
 * Set the exits to the Room
 * @param nExit The exits to set
 */
void Flow::Room::exit(unsigned char nExit){
    _exit = nExit;
}

/**
 * Get whether or not this is the starting Room for the Floor
 * @return true if the Room is a Floor start. Otherwise false
 */
bool Flow::Room::isStart() const{
    return _start;
}

/**
 * Get whether or not this is the ending Room for the Floor
 * @return true if the Room is a Floor end. Otherwise false
 */
bool Flow::Room::isEnd() const{
    return _end;
}

/**
 * Default Floor constructor
 */
Flow::Floor::Floor(){
    _sizeX = 8;
    _sizeY = 8;

    //Allocate Rooms
    _rooms = new Room*[_sizeY];
    for(int i = 0; i < _sizeY; ++i){
        _rooms[i] = new Room[_sizeX];
    }
}

/**
 * Floor copy constructor
 * @param other The Floor to copy from
 */
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

/**
 * Parameterized Floor constructor
 * @param sizeX The X-axis size of the Floor
 * @param sizeY The Y-axis size of the Floor
 */
Flow::Floor::Floor(unsigned char sizeX, unsigned char sizeY){
    _sizeX = sizeX;
    _sizeY = sizeY;
    _rooms = new Room*[_sizeY]; //Allocate Y dimension of array
    for(int i = 0; i < _sizeY; ++i){
        _rooms[i] = new Room[_sizeX]; //Allocate X dimension of array
    }
}

/**
 * Floor destructor
 */
Flow::Floor::~Floor(){
    for(int i = 0; i < _sizeY; ++i){ //Delete arrays in reverse order
        delete [] _rooms[i];
        _rooms[i] = 0;
    }
    delete [] _rooms; //Then delete the outer array
    _rooms = 0;
}

/**
 * Move a point within the bounds of a Floor
 * @param pos The point to move
 * @param direct The direction to move in
 * @return Whether or not the move succeeded
 */
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

/**
 * Draw a map of the Floor
 * @param pos The position of the Game's player
 */
void Flow::Floor::draw(const Point &pos) const{
    for(int i = 0; i < _sizeY; ++i){ //For every row
        for(int j = 0; j < _sizeX; ++j){ //For every column
            std::cout << "[";
            if(pos.x == j && pos.y == i){ //Output @ for the player position (similar to NetHack)
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

/**
 * Draw Debug map of the Floor
 */
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

/**
 * Check whether an (X, Y) position is outside the bounds of the Floor
 * @param x The X position
 * @param y The Y position
 * @return true if the point is outside the bounds of the Floor. Otherwise false
 */
bool Flow::Floor::isOverflow(unsigned char x, unsigned char y) const{
    if(isOverflowX(x) || isOverflowY(y)){ //If overflow on X or Y
        return true;
    }
    return false;
}

/**
 * Check whether an X position is outside the bounds of the Floor
 * @param x The X position to check
 * @return true if the position is outside the bounds of the Floor. Otherwise false
 */
bool Flow::Floor::isOverflowX(unsigned char x) const{
    if(x >= _sizeX || x < 0){ ///If greater than sizeX or less than 0
        return true;
    }
    return false;
}

/**
 * Check whether an Y position is outside the bounds of the Floor
 * @param y The Y position to check
 * @return true if the position is outside the bounds of the Floor. Otherwise false
 */
bool Flow::Floor::isOverflowY(unsigned char y) const{
    if(y >= _sizeY || y < 0){ //If greater than sizeY or less than 0
        return true;
    }
    return false;
}

/**
 * Get the X-axis size of the Floor
 * @return The X-axis size of the Floor
 */
unsigned char Flow::Floor::sizeX() const{
    return _sizeX;
}

/**
 * Get the Y-axis size of the Floor
 * @return The Y-axis size of the Floor
 */
unsigned char Flow::Floor::sizeY() const{
    return _sizeY;
}

/**
 * Get the starting position for the Floor
 * @return A Point containing the starting position
 */
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

/**
 * Get a Room from the Floor
 * @param x The X position of the Room
 * @param y The Y position of the Room
 * @return The Room at the given position
 */
Flow::Room Flow::Floor::get(unsigned char x, unsigned char y) const{
    return _rooms[y][x];
}

/**
 * Get an array of Rooms from the Floor
 * @param index The index of the array to get
 * @return An array of Rooms as a pointer
 */
Flow::Room* Flow::Floor::operator[](unsigned int index){
    return _rooms[index];
}

/**
 * Floor assignment operator
 * @param rhs The right hand side of the operator
 * @return A reference to this Floor after assignment
 */
Flow::Floor& Flow::Floor::operator=(const Floor &rhs){
    Floor cpy(rhs); //Create a copy of the input
    swap(*this, cpy); //Swap this with the copy

    return *this;
}

/**
 * Swap 2 Floors
 * @param a The first Floor
 * @param b The second Floor
 */
void Flow::Floor::swap(Floor &a, Floor &b){
    std::swap(a._rooms, b._rooms);
    std::swap(a._sizeX, b._sizeX);
    std::swap(a._sizeY, b._sizeY);
}

