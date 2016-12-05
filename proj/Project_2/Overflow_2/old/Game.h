/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Game.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define main game objects and loose game functions.
 * Created on October 11, 2016
 */

#ifndef GAME_H
#define GAME_H

//System Libraries
#include <vector> //Vector collections
#include <string> //String type and functions
#include <fstream> //File Streams
#include <iostream> //I/O
#include <cstdlib> //C Standard Library
#include <cstdio> //C Standard I/O (for std::remove)
#include <ctime> //C Time
#include <sstream> //String Streams

//User Libraries
#include "Actor.h" //Actor Objects
#include "Room.h" //Room, Point, and Floor objects
#include "BinArray.h" //BinArray objects
#include "Flags.h" //Bit Flags

//Flow
//This is Overflow's main namespace. Contains all game objects and data.
namespace Flow{

    //GmRand
    //The Game Random number generator object. Allows for reseeding of PRNG as well as PRNG seeking. Generates various
    //Game objects as well as numbers.
    class GmRand{
    private:
        unsigned int _seed; //PRNG seed equal to static_cast<int>(time(0)) when default constructed
        unsigned int _pos; //The current PRNG position. Equal to the number of calls to rand()
    public:
        GmRand();
        void seek(unsigned int);
        void srand();
        void srand(unsigned int);
        unsigned char rDirect();
        unsigned char rElem();
        unsigned int seed();
        unsigned int pos();
        int rand();
        Item rItem(bool = false);
        Actor rActor();
        Room rRoom(bool = false, bool = false);
        Floor rFloor(unsigned char = 32); 
    };
    
    //Config
    //Game configuration objects. Contains information about the current game configuration
    struct Config{
        static const std::string SAVPATH; //Configuration save path
        
        bool ascArt; //Setting for displaying ASCII art title 
        unsigned char diff; //The game difficulty
        std::string saveGame; //The current path to save player data to
    };
    
    //Game
    //Stores static game data. Allows accessing of game data without global variables.
    struct Game{
        static const unsigned int HEADER = 0x776f6c66; //Header value for game files
        //Should be equal to "flow" on most systems
        
        static bool over; //Game::over, whether or not the game has ended
        static char input; //The last game input character
        static Point pos; //The position of the game's player
        static Config conf; //The game's current configuration
        static GmRand gmRand;  //The game's PRNG
        static Actor player; //The Actor representing the game's player
        static std::vector<std::string> mMenu; //Main Menu vector
        static std::vector<std::string> nMons; //Monster names vector
        static std::vector<std::string> bMenu; //Battle menu vector
        static std::vector<std::string> gMenu; //Main game menu vector
        static std::vector<std::string> dMenu; //Difficulty menu vector
        static std::vector<std::string> *nItems; //Pointer to unidentified item names array/vectors
        static std::vector<std::string> *nWeaps; //Pointer to weapon names array/vectors
        static Floor floor; //The game's current board as a Floor object
    };
    
    //Function Prototypes
    void cleanUp();
    void gConf();
    void gMOpts();
    void init();
    void mMOpts();
    void play();
    void rdTxt(const std::string&);
    void rdTxt(std::vector<std::string>&, const std::string&);
    void wConf();
    void save();
    bool ckFile(const std::string&);
    bool encounter(Actor&);
    bool isValid(const std::vector<std::string>&, char);
    bool load();
    char menu(const std::vector<std::string>&, unsigned int);
    unsigned int binPow(unsigned int);
    int iMenu(const std::vector<std::string>&, unsigned int);
    int toInt(unsigned char);
    std::string frmtOpt(int);
    std::string frmtOpt(const std::string&);
    Actor createChar();
    std::vector<std::string>* gNItems();
    std::vector<std::string>* gNWeaps();
}

#endif /* GAME_H */

