/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Room.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:  Defines objects for handling the game board
 * Created on October 22, 2016
 */

#ifndef ROOM_H
#define ROOM_H

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <sstream> //String streams

//User Libraries
#include "Flags.h" //Bit Flags

namespace Flow{
    
    //Point
    //Defines a single (x, y) point
    struct Point{
        int x; //The X position
        int y; //The Y position
    };
    
    //RmEvent
    //An enumeration defining the various different events that may occur in a room object
    enum class RmEvent{
        None = 0, //No event
        Encounter = 1, //Encounter a monster
        Treasure = 2, //Discover treasure
        Spring = 3, //Find a magic spring
    };

    //Room
    //Defines an object representing a single room on the game board.
    class Room{
    private:
        bool _end; //If this room has the stairs down
        bool _start; //If this room is the floor start
        unsigned char _exit; //Exit flags
        RmEvent _event; //The event for this room
    public:
        Room();
        Room(const Room&);
        Room(unsigned char, RmEvent, bool = false, bool = false);
        void addExit(unsigned char);
        void setEvent(RmEvent);
        void setExit(unsigned char);
        void trigger();
        bool isEnd() const;
        bool isStart() const;
        unsigned char exit() const;
        RmEvent event() const;
    };

    //Floor
    //Defines an object for handling a 2D collection of rooms
    class Floor{
    private:
        unsigned char _sizeX; //The X axis size of the Floor
        unsigned char _sizeY; //The Y axis size of the Floor
        Room **_rooms; //The actual 2D array of Room objects
        
        void clear();
    public:
        Floor();
        Floor(const Floor&);
        Floor(unsigned char, unsigned char);
        ~Floor();
        void draw() const;
        void drawDbg() const;
        bool isOverflow(unsigned char, unsigned char) const;
        bool isOverflowX(unsigned char) const;
        bool isOverflowY(unsigned char) const;
        bool move(Point&, unsigned char);
        unsigned char sizeX() const;
        unsigned char sizeY() const;
        Point start() const;
        Room get(unsigned char, unsigned char) const;
        
        //Operator Overloads
        Room* operator[](unsigned int);
        Floor& operator=(const Floor&);
    };
    
}

#endif /* ROOM_H */

