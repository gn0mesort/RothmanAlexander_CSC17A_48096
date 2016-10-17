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

namespace Flow{

    class GmRand{
    public:
        GmRand();
        int rand();
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
    };
    
    //Game
    //Stores static game data. Allows accessing of game data without global variables.
    struct Game{
        static const unsigned int HEADER = 0x776f6c66; //Header value for game files
        static std::vector<std::string> *nWeaps;
        static Actor player;
        static GmRand gmRand; 
        static Config conf;
    };
    
    int toInt(unsigned char);
    std::vector<std::string>* rNWeaps();
    void rdTxt(const std::string&);
    void rdTxt(std::vector<std::string>&, const std::string&); 
    bool ckFile(const std::string&);
    void init();
    void cleanUp();
    unsigned int binPow(unsigned int);

}

#endif /* GAME_H */

