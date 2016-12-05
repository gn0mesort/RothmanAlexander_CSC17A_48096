/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Main Program for Overflow. Handles initialization, main menu, config file writing, and clean up.
 * Created on October 11, 2016
 */

//System Libraries
#include <iostream> //I/O

//User Libraries
#include "Game.h" //Main Game functions and objects

using namespace std;
using namespace Flow; //Using the game namespace as well as std

//Begin Execution

int main(int argc, char** argv){
    bool quit = false; //Whether or not to quit the game
    init(); //Initialize the game

    do{ //While not quitting
        if(Game::conf.ascArt){ //If ASCII art is enabled
            rdTxt("GameData/title.txt"); //Display ASCII title
        }
        else{ //Otherwise
            cout << "OVERFLOW" << endl; //Output title
            cout << endl;
        }
        Game::input = menu(Game::mMenu, 5); //Do main menu processing
        switch(Game::input){
            case 'N': //New Game
            {
                rdTxt("GameData/crawl.txt"); //Display title crawl
                Game::player = createChar(); //Create player character
                play(); //Play the game
                break;
            }
            case 'L': //Load
            {
                Game::player = Actor(); //Reinitialize the player
                if(load()){ //If the game is loaded
                    rdTxt("GameData/crawl.txt"); //Display title crawl
                    play(); //Play the game
                }
                break;
            }
            case 'O': //Options
            {
                mMOpts(); //Display game options menu
                break;
            }
            case 'H': //Help
            {
                rdTxt("README.txt"); //Display README.txt data
                break;
            }
            case 'E': //Exit
            {
                quit = true; //Quit the game
            }
        }
        cout << endl;
    } while(!quit);

    wConf(); //Output configuration file
    cleanUp(); //Clean up game memory

    //Exit
    return 0;
}

