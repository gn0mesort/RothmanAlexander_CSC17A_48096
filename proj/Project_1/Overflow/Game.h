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
        static Actor player;
        static Point pos;
        static GmRand gmRand; 
        static Config conf;
        static Floor floor;
        static char input;
    };
    
    int toInt(unsigned char);
    std::vector<std::string>* rNWeaps();
    void rdTxt(const std::string&);
    void rdTxt(std::vector<std::string>&, const std::string&); 
    bool ckFile(const std::string&);
    void init();
    void cleanUp();
    unsigned int binPow(unsigned int);
    char menu(const std::vector<std::string>&, unsigned int);
    std::string frmtOpt(const std::string&);
    bool isValid(const std::vector<std::string>&, char);

}

#endif /* GAME_H */

