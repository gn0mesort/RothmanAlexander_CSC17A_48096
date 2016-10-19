/*
 * File:   main.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 11, 2016
 */

#include <iostream>
#include <fstream>
#include <vector>

#include "Game.h"
#include "Stat.h"
#include "Flags.h"
#include "Byte.h"
#include "Item.h"

using namespace std;
using namespace Flow;

int main(int argc, char** argv){
    init();

    if(Game::conf.ascArt){
        rdTxt("GameData/title.txt");
    }
    else{
        cout << "OVERFLOW" << endl;
        cout << endl;
    }
    cout << "v" << toInt(Game::conf.mjVer) << "." << toInt(Game::conf.miVer) << endl;
    
    Game::player();
    cout << Game::player.atk().value() << endl;

    cleanUp(); //Clean up game memory
    return 0;
}

