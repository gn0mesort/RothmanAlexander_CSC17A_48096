/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   game.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 2, 2016
 */

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <iostream>
#include <fstream>

#include "collections.h"
#include "stringext.h"
//#include "actor.h"
#include "room.h"

namespace Flow{
    const int HEADER = 0x776f6c66;
    class Actor;

    /**
     * Replaces the Game structure from version 1. Game is now a class containing a static dictionary of
     * std::shared_ptr<void>. This allows the game to make a pointer to any value it likes (and potentially create a
     * huge number of such pointers) but while they are globally retrievable they are not globally accessible (you need
     * to know both the correct type and key to access the data). Values whose pointers get stored this way must be
     * explicitly unset to delete them. Otherwise they will exist for the duration of the program. Setting a pointer a
     * second time will result in the old pointer being released and the stored pointer being overwritten
     *
     * This was based on the Service Locator pattern found at: http://gameprogrammingpatterns.com/service-locator.html
     */
    class Game{
    private:
        static Collections::Dictionary<std::string, std::shared_ptr<void>> _data;
    public:
        template<typename T>
        static std::shared_ptr<T> get(const std::string&);
        static void set(const std::string&, const std::shared_ptr<void>&);
        static void unset(const std::string&);
        static unsigned int size();
        static void recover();
    };

    template<typename T>
    std::shared_ptr<T> Game::get(const std::string &key){
        return std::static_pointer_cast<T>(_data[key]);
    }

    void init();
    void cleanup();
    void rdTxt(const std::string&);
    void rdTxt(const std::string&, Collections::LinkedList<std::string>&);
    bool encounter(Actor&);
    char menu(const Collections::LinkedList<std::string>&, int = 10);
    void save(const std::string&, const Actor&);
    void getOptionsMenu();
    void loadConfig();
    void mainMenuOptions(); //mMOpts()
    void play();
    void saveConfig();
    bool checkFile(const std::string&);
    bool isValid(const Collections::LinkedList<std::string>&, char);
    bool loadMenu();
    void load(const std::string&, Actor&);
    int intMenu(const Collections::LinkedList<std::string>&, int = 10);
    std::string formatOption(int);
    std::string formatOption(const std::string&);
    Actor createCharacter();
    void getItemNames();
    void getWeaponNames();
    void stats(const Actor&);
    void updateSaveIndex(const std::string&);

}

#endif /* GAME_H */

