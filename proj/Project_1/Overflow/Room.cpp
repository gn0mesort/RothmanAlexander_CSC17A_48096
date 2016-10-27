/*
 * File:   Room.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 22, 2016
 */

#include <iostream>
#include <iomanip>
#include <sstream>

#include "Room.h"
#include "Flags.h"
#include "Game.h"

Flow::Room::Room(){
    _exit = Flow::Direct::NONE;
    _event = Flow::RmEvent::None;
    _start = false;
    _end = false;
}

Flow::Room::Room(const Room &other){
    if(this != &other){
        _exit = other.exit();
        _event = other.event();
        _start = other.isStart();
        _end = other.isEnd();
    }
}

Flow::Room::Room(unsigned char exit, RmEvent event, bool start, bool end){
    _exit = exit;
    _event = event;
    _start = start;
    _end = end;
}

Flow::RmEvent Flow::Room::event() const{
    return _event;
}

unsigned char Flow::Room::exit() const{
    return _exit;
}

void Flow::Room::setEvent(RmEvent event){
    _event = event;
}

void Flow::Room::setExit(unsigned char exit){
    _exit = exit;
}

bool Flow::Room::isStart() const{
    return _start;
}

bool Flow::Room::isEnd() const{
    return _end;
}

void Flow::Room::addExit(unsigned char exit){
    _exit |= exit;
}

void Flow::Room::trigger(){
    bool moved = false;
    std::stringstream convert;
    convert << "GameData/desc" << (static_cast<int>(_event) * 3) + ((Game::gmRand.rand() % 3) + 1) << ".txt";
    Flow::rdTxt(convert.str());
    std::cout << std::endl;

    if(_event != Flow::RmEvent::None){
        if(_event == Flow::RmEvent::Encounter){
            Flow::Actor enem = Game::gmRand.rActor();
            std::cout << "A " << enem.name() << " attacks!" << std::endl;
            Game::over = !Flow::encounter(enem);
        }
        else if(_event == Flow::RmEvent::Treasure){
            unsigned char tCount = (Game::gmRand.rand() % 3) + 1;

            for(int i = 0; i < tCount; ++i){
                Flow::Item treas = Game::gmRand.rItem();
                std::cout << treas.uiName() << " acquired!" << std::endl;
                Game::player.addItem(treas);
            }
        }
        else if(_event == Flow::RmEvent::Spring){
            Game::player.setHp(Game::player.hp().max());
            Game::player.setMp(Game::player.mp().max());
            std::cout << Game::player.name() << " is fully restored!" << std::endl;
            for(int i = 0; i < Game::player.invSize(); ++i){
                Game::player.identify(i);
            }
            std::cout << "Items identified!" << std::endl;
        }
        _event = Flow::RmEvent::None;
    }
    else{
        std::cout << "There are exits to the ( " << Flow::Direct::toStr(_exit) << ")" << std::endl;
        if(_end){
            std::cout << "You can see a flight of stairs in the far corner!" << std::endl;
        }
        std::vector<std::string> tmpMenu(Game::gMenu);
        if(Flow::FlgUtil::hasFlag(_exit, Flow::Direct::NORTH)){
            tmpMenu.push_back("North");
        }
        if(Flow::FlgUtil::hasFlag(_exit, Flow::Direct::EAST)){
            tmpMenu.push_back("East");
        }
        if(Flow::FlgUtil::hasFlag(_exit, Flow::Direct::SOUTH)){
            tmpMenu.push_back("South");
        }
        if(Flow::FlgUtil::hasFlag(_exit, Flow::Direct::WEST)){
            tmpMenu.push_back("West");
        }
        if(_end){
            tmpMenu.push_back("Down");
        }
        do{
            Game::input = menu(tmpMenu, 4);
            switch(Game::input){
                case 'P':
                {
                    Game::player.stat();
                    break;
                }
                case 'I':
                {
                    Game::player.selectItm();
                    break;
                }
                case 'O':
                {
                    Flow::gMOpts();
                    if(Game::over){
                        moved = true;
                    }
                    break;
                }
                case 'M':
                {
                    Game::floor.draw();
                    break;
                }
                default:
                {
                    if(Game::input == 'N' && Flow::FlgUtil::hasFlag(_exit, Flow::Direct::NORTH)){
                        Game::floor.move(Game::pos, Flow::Direct::NORTH);
                        moved = true;
                    }
                    else if(Game::input == 'E' && Flow::FlgUtil::hasFlag(_exit, Flow::Direct::EAST)){
                        Game::floor.move(Game::pos, Flow::Direct::EAST);
                        moved = true;
                    }
                    else if(Game::input == 'S' && Flow::FlgUtil::hasFlag(_exit, Flow::Direct::SOUTH)){
                        Game::floor.move(Game::pos, Flow::Direct::SOUTH);
                        moved = true;
                    }
                    else if(Game::input == 'W' && Flow::FlgUtil::hasFlag(_exit, Flow::Direct::WEST)){
                        Game::floor.move(Game::pos, Flow::Direct::WEST);
                        moved = true;
                    }
                    else if(Game::input == 'D' && _end){
                        Game::over = true;
                        if(Game::conf.ascArt){
                            rdTxt("GameData/win.txt");
                        }
                        else{
                            std::cout << "YOU WIN!" << std::endl;
                        }
                        save();
                        moved = true;
                    }
                }
            }
        } while(!moved);
    }
}

Flow::Floor::Floor(){
    _sizeX = 8;
    _sizeY = 8;
    _rooms = new Flow::Room*[_sizeY];
    for(int i = 0; i < _sizeY; ++i){
        _rooms[i] = new Flow::Room[_sizeX];
    }
}

Flow::Floor::Floor(const Floor &other){
    _sizeX = other.sizeX();
    _sizeY = other.sizeY();
    _rooms = new Flow::Room*[_sizeY];
    for(int i = 0; i < _sizeY; ++i){
        _rooms[i] = new Flow::Room[_sizeX];
    }
    for(int i = 0; i < _sizeY; ++i){
        for(int j = 0; j < _sizeX; ++j){
            _rooms[i][j] = Room(other.get(j, i));
        }
    }
}

Flow::Floor::Floor(unsigned char sizeX, unsigned char sizeY){
    _sizeX = sizeX;
    _sizeY = sizeY;
    _rooms = new Flow::Room*[_sizeY];
    for(int i = 0; i < _sizeY; ++i){
        _rooms[i] = new Flow::Room[_sizeX];
    }
}

Flow::Floor::~Floor(){
    clear();
}

Flow::Room* Flow::Floor::operator[](unsigned int index){
    return _rooms[index];
}

Flow::Floor& Flow::Floor::operator=(const Floor &other){
    if(this != &other){
        _sizeX = other.sizeX();
        _sizeY = other.sizeY();
        clear();
        _rooms = new Flow::Room*[_sizeY];
        for(int i = 0; i < _sizeY; ++i){
            _rooms[i] = new Flow::Room[_sizeX];
        }
        for(int i = 0; i < _sizeY; ++i){
            for(int j = 0; j < _sizeX; ++j){
                _rooms[i][j] = Room(other.get(j, i));
            }
        }
    }

    return *this;
}

unsigned char Flow::Floor::sizeX() const{
    return _sizeX;
}

unsigned char Flow::Floor::sizeY() const{
    return _sizeY;
}

Flow::Room Flow::Floor::get(unsigned char x, unsigned char y) const{
    return _rooms[y][x];
}

bool Flow::Floor::isOverflowX(unsigned char x) const{
    if(x >= _sizeX || x < 0){
        return true;
    }
    return false;
}

bool Flow::Floor::isOverflowY(unsigned char y) const{
    if(y >= _sizeY || y < 0){
        return true;
    }
    return false;
}

bool Flow::Floor::isOverflow(unsigned char x, unsigned char y) const{
    if(isOverflowX(x) || isOverflowY(y)){
        return true;
    }
    return false;
}

bool Flow::Floor::move(Flow::Point &pos, unsigned char direct){
    if(direct == Flow::Direct::NORTH && !isOverflowY(pos.y - 1)){
        --pos.y;
        return true;
    }
    else if(direct == Flow::Direct::EAST && !isOverflowX(pos.x + 1)){
        ++pos.x;
        return true;
    }
    else if(direct == Flow::Direct::SOUTH && !isOverflowY(pos.y + 1)){
        ++pos.y;
        return true;
    }
    else if(direct == Flow::Direct::WEST && !isOverflowX(pos.x - 1)){
        --pos.x;
        return true;
    }
    return false;
}

void Flow::Floor::draw() const{
    for(int i = 0; i < _sizeY; ++i){
        for(int j = 0; j < _sizeX; ++j){
            std::cout << "[";
            if(Game::pos.x == j && Game::pos.y == i){
                std::cout << "@";
            }
            else if(_rooms[i][j].isStart()){
                std::cout << "S";
            }
            else if(_rooms[i][j].exit() == 0){
                std::cout << "X";
            }
            else{
                std::cout << " ";
            }
            std::cout << "]";
        }
        std::cout << std::endl;
    }
}

void Flow::Floor::drawDbg() const{
    for(int i = 0; i < _sizeY; ++i){
        for(int j = 0; j < _sizeX; ++j){
            std::cout << "[" << std::setw(5) << Direct::toStr(_rooms[i][j].exit(), true);
            std::cout << _rooms[i][j].isStart() << _rooms[i][j].isEnd();
            std::cout << static_cast<int>(_rooms[i][j].event()) << "]";
        }
        std::cout << std::endl;
    }
}

Flow::Point Flow::Floor::start() const{
    Point start;

    for(int i = 0; i < _sizeY; ++i){
        for(int j = 0; j < _sizeX; ++j){
            if(_rooms[i][j].isStart()){
                start.x = j;
                start.y = i;
            }
        }
    }

    return start;
}

void Flow::Floor::clear(){
    for(int i = 0; i < _sizeY; ++i){
        delete [] _rooms[i];
        _rooms[i] = 0;
    }
    delete [] _rooms;
    _rooms = 0;
}