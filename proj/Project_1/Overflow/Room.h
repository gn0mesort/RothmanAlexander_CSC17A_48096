/* 
 * File:   Room.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 22, 2016
 */

#ifndef ROOM_H
#define ROOM_H

namespace Flow{
    
    struct Point{
        int x;
        int y;
    };
    
    enum class RmEvent{
        None = 0,
        Encounter = 1,
        Treasure = 2,
        Spring = 3,
    };

    class Room{
    private:
        bool _start;
        bool _end;
        unsigned char _exit;
        RmEvent _event;

    public:
        Room();
        Room(const Room&);
        Room(unsigned char, RmEvent, bool = false, bool = false);
        unsigned char exit() const;
        void setExit(unsigned char);
        RmEvent event() const;
        void setEvent(RmEvent);
        bool isStart() const;
        bool isEnd() const;
        void addExit(unsigned char);
    };

    class Floor{
    private:
        Room **_rooms;
        unsigned char _sizeX;
        unsigned char _sizeY;
    public:
        Floor();
        Floor(const Floor&);
        Floor(unsigned char, unsigned char);
        ~Floor();
        unsigned char sizeX() const;
        unsigned char sizeY() const;
        Room get(unsigned char, unsigned char) const;
        Room* operator[](unsigned int);
        Floor& operator=(const Floor&);
        bool isOverflow(unsigned char, unsigned char) const;
        bool isOverflowX(unsigned char) const;
        bool isOverflowY(unsigned char) const;
        bool move(Point&, unsigned char);
        void draw() const;
        void drawDbg() const;
        Point start() const;
    };
    
}

#endif /* ROOM_H */

