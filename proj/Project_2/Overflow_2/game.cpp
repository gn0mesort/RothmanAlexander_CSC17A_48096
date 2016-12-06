/*
 * File:   game.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 5, 2016
 */

#include "functions.h"
#include "game.h"

/**
 * Game constructor. Serves to initialize a game
 */
Flow::Game::Game(){
    _player;
    _gmRand.srand();
    _pos;
    _config.asciiArt = true;
    _config.saveGame = "GameData/";
    _floor;
    _gameOver = false;

    _itmNames.addBack(ItemType::Potion, Collections::LinkedList<std::string>());
    _itmNames.addBack(ItemType::Armor, Collections::LinkedList<std::string>());
    _itmNames.addBack(ItemType::Weapon, Collections::LinkedList<std::string>());
    _weapNames.addBack(Job::Knight, Collections::LinkedList<std::string>());
    _weapNames.addBack(Job::Cleric, Collections::LinkedList<std::string>());
    _weapNames.addBack(Job::Lancer, Collections::LinkedList<std::string>());
    _weapNames.addBack(Job::Mage, Collections::LinkedList<std::string>());

    _indexPath = "GameData/index.sav";
    _confPath = "GameData/game.conf";

    rdTxt("GameData/monsters.txt", _monNames);
    rdTxt("GameData/uidpotionnames.txt", _itmNames[ItemType::Potion]);
    rdTxt("GameData/uidarmornames.txt", _itmNames[ItemType::Armor]);
    rdTxt("GameData/uidweaponnames.txt", _itmNames[ItemType::Weapon]);
    rdTxt("GameData/knightweapons.txt", _weapNames[Job::Knight]);
    rdTxt("GameData/clericweapons.txt", _weapNames[Job::Cleric]);
    rdTxt("GameData/lancerweapons.txt", _weapNames[Job::Lancer]);
    rdTxt("GameData/mageweapons.txt", _weapNames[Job::Mage]);
}

Flow::Config Flow::Game::config() const{
    return _config;
}

void Flow::Game::config(const Config &conf){
    _config = conf;
}

std::string Flow::Game::configPath() const{
    return _confPath;
}

Flow::Floor Flow::Game::floor() const{
    return _floor;
}

void Flow::Game::floor(const Floor &nFloor){
    _floor = nFloor;
}

Flow::GmRand Flow::Game::gmRand() const{
    return _gmRand;
}

std::string Flow::Game::indexPath() const{
    return _indexPath;
}

bool Flow::Game::isGameOver() const{
    return _gameOver;
}

Collections::Dictionary<Flow::ItemType, Collections::LinkedList<std::string>> Flow::Game::itemNames() const{
    return _itmNames;
}

Collections::LinkedList<std::string> Flow::Game::monsterNames() const{
    return _monNames;
}

Flow::Actor Flow::Game::player() const{
    return _player;
}

void Flow::Game::player(const Actor &nPlayer){
    _player = nPlayer;
}

Flow::Point Flow::Game::pos() const{
    return _pos;
}

void Flow::Game::pos(const Point &pos){
    _pos = pos;
}

void Flow::Game::setGameOver(bool gameOver){
    _gameOver = gameOver;
}

Collections::Dictionary<Flow::Job, Collections::LinkedList<std::string>> Flow::Game::weaponNames() const{
    return _weapNames;
}

void Flow::Game::play(){
    _floor = _gmRand.rFloor(_player.difficulty()); //Get a new random floor
    _pos = _floor.start(); //Move the player to the start cell
    _floor[_pos.y][_pos.x].event(Flow::RmEvent::None); //Set the start cell event to none
    do{ //While the game isn't over
        _floor[_pos.y][_pos.x].trigger(*this); //Trigger the cell event
        std::cout << std::endl;
    } while(!_gameOver);
    _gameOver = false; //Toggle the game over flag
}

bool Flow::Game::encounter(Actor &enemy){
    bool turn = false,
            r = false;

    do{
        enemy.hit(_player);
        if(_player.hp().value() > 0){
            do{
                std::cout << enemy.name() << ": " << enemy.hp().value() << "/" << enemy.hp().max() << " ";
                std::cout << enemy.hp().name() << std::endl;
                std::cout << _player.name() << ": " << _player.hp().value() << "/" << _player.hp().max() << " ";
                std::cout << _player.hp().name() << std::endl;
                turn = true;
                char input = menu({"Attack", "Inventory", "Player Status"}, 5);
                switch(input){
                    case 'A':
                    {
                        _player.hit(enemy);
                        turn = false;
                        break;
                    }
                    case 'I':
                    {
                        int index = _player.selectItem();
                        if(index > -1){
                            turn = false;
                        }
                        break;
                    }
                    case 'P':
                    {
                        stats(_player);
                        break;
                    }
                }
            } while(turn);
        }
    } while(_player.hp().value() > 0 && enemy.hp().value() > 0);
    if(_player.hp().value() > 0){
        _player.addItems(enemy);
        r = true;
    }
    else{
        if(_config.asciiArt){ //If ASCII art is on
            rdTxt("GameData/gameover.txt"); //Display game over screen
        }
        else{ //Otherwise
            std::cout << "GAME OVER!" << std::endl;
        }
        r = false;
    }

    return r;
}

