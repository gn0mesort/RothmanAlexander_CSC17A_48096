/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   room.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 3, 2016
 */

#ifndef ROOM_H
#define ROOM_H

#include "enums.h"

namespace Flow{

    class Room{
    private:
        bool _end;
        bool _start;
        unsigned char _exit;
        RmEvent _event;
    public:
        Room();
        Room(const Room&);
        Room(unsigned char, RmEvent, bool = false, bool = false);
        void addExit(unsigned char);
        RmEvent event() const;
        void event(RmEvent);
        unsigned char exit() const;
        void exit(unsigned char);
        void trigger(Game&);
        bool isEnd() const;
        bool isStart() const;
    };

    class Floor{
    private:
        unsigned char _sizeX;
        unsigned char _sizeY;
        Room **_rooms;
    public:
        Floor();
        Floor(const Floor&);
        Floor(unsigned char, unsigned char);
        ~Floor();
        bool move(Point&, unsigned char);
        void draw(Game&) const;
        void drawDbg() const;
        bool isOverflow(unsigned char, unsigned char) const;
        bool isOverflowX(unsigned char) const;
        bool isOverflowY(unsigned char) const;
        unsigned char sizeX() const;
        unsigned char sizeY() const;
        Point start() const;
        Room get(unsigned char, unsigned char) const;
        static void swap(Floor&, Floor&);

        Room* operator[](unsigned int);
        Floor& operator=(const Floor&);
    };
}

#endif /* ROOM_H */

