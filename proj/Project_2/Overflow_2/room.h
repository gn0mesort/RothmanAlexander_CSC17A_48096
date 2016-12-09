/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   room.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define Room and Floor objects
 * Created on December 3, 2016
 */

#ifndef ROOM_H
#define ROOM_H

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting

//User Libraries
#include "enums.h" //Enumeration types
#include "structs.h" //Game structs
#include "flags.h" //Bit flags
#include "macros.h" //Preprocessor macros

namespace Flow{

    /**
     * Defines a Room in the game world
     */
    class Room{
    private:
        /**
         * Whether or not the Room is the ending of a Floor
         */
        bool _end;

        /**
         * Whether or not the Room is the beginning of a Floor
         */
        bool _start;

        /**
         * The exits to the Room
         */
        unsigned char _exit;

        /**
         * The Room's event
         */
        RmEvent _event;
    public:
        Room();
        Room(const Room&);
        Room(unsigned char, RmEvent, bool = false, bool = false);
        void addExit(unsigned char);
        void event(RmEvent);
        void exit(unsigned char);
        bool isEnd() const;
        bool isStart() const;
        unsigned char exit() const;
        RmEvent event() const;
    };

    /**
     * Defines a Floor in the game world. A Floor is a 2D array or Rooms
     */
    class Floor{
    private:
        /**
         * The X-axis size of the Floor
         */
        unsigned char _sizeX;

        /**
         * The Y-axis size of the Floor
         */
        unsigned char _sizeY;

        /**
         * The Rooms for the Floor
         */
        Room **_rooms;
    public:
        Floor();
        Floor(const Floor&);
        Floor(unsigned char, unsigned char);
        ~Floor();
        void draw(const Point&) const;
        void drawDbg() const;
        bool isOverflow(unsigned char, unsigned char) const;
        bool isOverflowX(unsigned char) const;
        bool isOverflowY(unsigned char) const;
        bool move(Point&, unsigned char);
        unsigned char sizeX() const;
        unsigned char sizeY() const;
        Point start() const;
        Room get(unsigned char, unsigned char) const;

        Room* operator[](unsigned int);
        Floor& operator=(const Floor&);

        static void swap(Floor&, Floor&);
    };
}

#endif /* ROOM_H */

