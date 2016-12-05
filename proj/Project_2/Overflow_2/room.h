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

#include <memory>
#include <iostream>
#include <utility>

#include "flags.h"
#include "game.h"
#include "item.h"
#include "actor.h"
#include "macros.h"
#include "random.h"

namespace Flow{

    struct Point{
        int x;
        int y;
    };

    enum class RmEvent{
        None = 0,
        Encounter = 1,
        Treasure = 2,
        Spring = 3
    };

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
        void trigger();
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
        void draw() const;
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

