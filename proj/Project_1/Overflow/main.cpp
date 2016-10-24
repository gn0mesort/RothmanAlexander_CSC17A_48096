/*
 * File:   main.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 11, 2016
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "Game.h"
#include "Stat.h"
#include "Flags.h"
#include "Byte.h"
#include "Item.h"
#include "Room.h"

using namespace std;
using namespace Flow;

int main(int argc, char** argv){
    bool quit = false;
    init();

    if(Game::conf.ascArt){
        rdTxt("GameData/title.txt");
    }
    else{
        cout << "OVERFLOW" << endl;
        cout << endl;
    }
    Game::conf.diff = (Diff::HARD);
    Game::floor = Game::gmRand.rFloor(Game::conf.diff);
    Game::pos = Game::floor.start();
    do{
        Game::input = menu(Game::mMenu, 5);
        switch(Game::input){
            case 'N':
            {
                Game::player = createChar();
                play();
                break;
            }
            case 'L':
            {
                break;
            }
            case 'O':
            {
                break;
            }
            case 'H':
            {
                break;
            }
            case 'E':
            {
                quit = true;
            }
        }
    } while(!quit);

    cleanUp(); //Clean up game memory
    return 0;
}

