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
#include "BinArray.h"

using namespace std;
using namespace Flow;

int main(int argc, char** argv){
    bool quit = false;
    init();

    do{
        if(Game::conf.ascArt){
            rdTxt("GameData/title.txt");
        }
        else{
            cout << "OVERFLOW" << endl;
            cout << endl;
        }
        Game::input = menu(Game::mMenu, 5);
        switch(Game::input){
            case 'N':
            {
                rdTxt("GameData/crawl.txt");
                Game::player = createChar();
                ofstream out;
                out.open("test.bin");
                Game::player.toBin().write(out);
                out.close();
                play();
                break;
            }
            case 'L':
            {
                break;
            }
            case 'O':
            {
                mMOpts();
                break;
            }
            case 'H':
            {
                rdTxt("README.txt");
                break;
            }
            case 'E':
            {
                quit = true;
            }
        }
        cout << endl;
    } while(!quit);

    wConf(); //Output configuration file
    cleanUp(); //Clean up game memory
    return 0;
}

