/* 
 * File:   Game.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on October 11, 2016
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Actor.h"
#include "Room.h"

namespace Flow{

    class GmRand{
    public:
        GmRand();
        int rand();
        Floor rFloor(unsigned char = 32);
        unsigned char rDirect();
        unsigned char rElem();
        Room rRoom(bool = false, bool = false);
        Item rItem(bool = false);
        Actor rActor();
        unsigned int seed();
        void srand();
        void srand(unsigned int);
        unsigned int pos();
        void seek(unsigned int);
    private:
        unsigned int _seed;
        unsigned int _pos;
    };
    
    struct Config{
        static const std::string SAVPATH; //Configuration save path
        bool ascArt; //Setting for displaying ASCII art title 
        unsigned char mjVer; //Major Version number
        unsigned char miVer; //Minor Version number
        unsigned char diff; //The game difficulty
    };
    
    //Game
    //Stores static game data. Allows accessing of game data without global variables.
    struct Game{
        static const unsigned int HEADER = 0x776f6c66; //Header value for game files
        static std::vector<std::string> *nWeaps;
        static std::vector<std::string> mMenu;
        static std::vector<std::string> *nItems;
        static std::vector<std::string> nMons;
        static std::vector<std::string> bMenu;
        static std::vector<std::string> gMenu;
        static bool over;
        static Actor player;
        static Point pos;
        static GmRand gmRand; 
        static Config conf;
        static Floor floor;
        static char input;
    };
    
    int toInt(unsigned char);
    std::vector<std::string>* gNWeaps();
    std::vector<std::string>* gNItems();
    void rdTxt(const std::string&);
    void rdTxt(std::vector<std::string>&, const std::string&); 
    bool ckFile(const std::string&);
    void init();
    void cleanUp();
    unsigned int binPow(unsigned int);
    char menu(const std::vector<std::string>&, unsigned int);
    std::string frmtOpt(const std::string&);
    std::string frmtOpt(int);
    bool isValid(const std::vector<std::string>&, char);
    bool encounter(Actor&);
    void play();
    Actor createChar();

}

#endif /* GAME_H */

