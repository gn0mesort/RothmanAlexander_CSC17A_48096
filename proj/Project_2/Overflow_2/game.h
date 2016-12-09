/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   game.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define the main game object as well as functions that rely on it
 * Created on December 2, 2016
 */

#ifndef GAME_H
#define GAME_H

//User Libraries
#include "random.h" //Game RNG
#include "room.h" //Room and Floor objects
#include "collections.h" //LinkedLists and Dictionarys
#include "actor.h" //Actor objects
#include "enums.h" //Enumeration types
#include "functions.h" //Loose game functions

/**
 * A namespace containing objects for the Overflow game
 */
namespace Flow{
    /**
     * Game header value. Translates to the ASCII sequence "flow" when written to a file
     */
    const int HEADER = 0x776f6c66;

    /**
     * Game object. Contains all the Game's data as well as gameplay functions.
     */
    class Game{
    private:
        /**
         * Value indicating whether or not the game has ended
         */
        bool _gameOver;

        /**
         * The Game's player
         */
        Actor _player;

        /**
         * The position of the Game's player
         */
        Point _pos;

        /**
         * The Game's configuration
         */
        Config _config;

        /**
         * The current Game map
         */
        Floor _floor;

        /**
         * A LinkedList containing monster names. Filled during the construction of a Game from GameData/monsters.txt
         */
        Collections::LinkedList<std::string> _monNames;

        /**
         * A Dictionary containing Item names by ItemType. Filled during the construction of a Game as follows:
         * ItemType::None   : 0
         * ItemType::Potion : Data from GameData/uidpotionnames.txt
         * ItemType::Weapon : Data from GameData/uidweaponnames.txt
         * ItemType::Armor  : Data from GameData/uidarmornames.txt
         */
        Collections::Dictionary<ItemType, Collections::LinkedList<std::string>> _itmNames;

        /**
         * A Dictionary containing Weapon names by Job. Filled during the construction of of a Game as follows:
         * Job::None   : 0
         * Job::Knight : Data from GameData/knightweapons.txt
         * Job::Cleric : Data from GameData/clericweapons.txt
         * Job::Mage   : Data from GameData/mageweapons.txt
         * Job::Lancer : Data from GameData/lancerweapons.txt
         */
        Collections::Dictionary<Job, Collections::LinkedList<std::string>> _weapNames;

        /**
         * Path to the Game's index.sav file. Defaulted to GameData/index.sav
         */
        std::string _indexPath;

        /**
         * Path to the Game's configuration file. Defaulted to GameData/game.conf
         */
        std::string _confPath;
    public:
        Game();
        void createCharacter();
        void config(const Config&);
        void floor(const Floor&);
        void gameOptionsMenu();
        void mainMenuOptions();
        void play();
        void player(const Actor&);
        void pos(const Point&);
        void setGameOver(bool);
        void stats(const Actor&);
        void trigger(Room&);
        bool encounter(Actor&);
        bool isGameOver() const;
        bool loadMenu();
        std::string configPath() const;
        std::string indexPath() const;
        Config config() const;
        Point pos() const;
        Actor player() const;
        Floor floor() const;
        Collections::LinkedList<std::string> monsterNames() const;
        Collections::Dictionary<ItemType, Collections::LinkedList<std::string>> itemNames() const;
        Collections::Dictionary<Job, Collections::LinkedList<std::string>> weaponNames() const;
    };

    void load(const std::string&, Game&);
    void save(const std::string&, const Game&);
    void saveConfig(const std::string&, Config);
    void rItem(Actor&, Game&, ItemType = ItemType::None, bool = true);
    void updateSaveIndex(const std::string&, const Game&);
    Config loadConfig(const std::string&);
    Actor rActor(Game&);
}

#endif /* GAME_H */

