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

#include "random.h"
#include "room.h"
#include "collections.h"
#include "actor.h"
#include "enums.h"

namespace Flow{
    const int HEADER = 0x776f6c66;

    /**
     * Game context object. Doing things this way eliminates global state but also saves me from having to add
     * 10,000,000,000 parameters to everything :O
     *
     * I'm not sure why doing this didn't occur to me before but I had to read about 10 different web pages before
     * I figured this out. In retrospect this is really obvious and the right thing to do.
     */
    class Game{
    private:
        //Member fields
        Actor _player;
        GmRand _gmRand;
        Point _pos;
        Config _config;
        Floor _floor;
        bool _gameOver;

        Collections::LinkedList<std::string> _monNames;
        Collections::Dictionary<ItemType, Collections::LinkedList<std::string>> _itmNames;
        Collections::Dictionary<Job, Collections::LinkedList<std::string>> _weapNames;

        std::string _indexPath;
        std::string _confPath;
    public:
        Game();

        Actor player() const;
        void player(const Actor&);
        GmRand gmRand() const;
        Point pos() const;
        void pos(const Point&);
        Config config() const;
        void config(const Config&);
        Floor floor() const;
        void floor(const Floor&);
        bool isGameOver() const;
        void setGameOver(bool);

        Collections::LinkedList<std::string> monsterNames() const;
        Collections::Dictionary<ItemType, Collections::LinkedList<std::string>> itemNames() const;
        Collections::Dictionary<Job, Collections::LinkedList<std::string>> weaponNames() const;

        std::string indexPath() const;
        std::string configPath() const;

        //Gameplay Functions
        void play();
        bool encounter(Actor&);
        void trigger(Room&);
        void stats(const Actor&);
        bool loadMenu();
        void gameOptionsMenu();
        void mainMenuOptions();
        void createCharacter();
    };

    void save(const std::string&, const Game&);
    void load(const std::string&, Game&);
    void updateSaveIndex(const std::string&, const Game&);
    Config loadConfig(const std::string&);
    void saveConfig(const std::string&, Config);

    Actor rActor(Game&);
    void rItem(Actor&, Game&, ItemType = ItemType::None, bool = true);
}

#endif /* GAME_H */

