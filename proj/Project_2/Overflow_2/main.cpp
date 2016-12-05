/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on November 26, 2016
 */


//System Libraries
#include <iostream>
#include <fstream>
#include <exception>

//User Libraries
#include "except.h"
#include "macros.h"
#include "collections.h"
#include "stat.h"
#include "item.h"
#include "actor.h"
#include "game.h"
#include "random.h"

//Namespaces
using namespace std;
using namespace Error;
using namespace Flow;

int main(int argc, char** argv){
    try{
        init();
        loadConfig();
        Collections::LinkedList<string> mMenu = {"New Game", "Load", "Options", "Help", "Exit"};

        bool quit = false; //Whether or not to quit the game

        shared_ptr<Config> conf = Game::get<Config>("game_config");
        shared_ptr<Actor> player = Game::get<Actor>("player");

        do{ //While not quitting
            if(conf->asciiArt){ //If ASCII art is enabled
                rdTxt("GameData/title.txt"); //Display ASCII title
            }
            else{ //Otherwise
                cout << "OVERFLOW" << endl; //Output title
                cout << endl;
            }
            char input = menu(mMenu, 5); //Do main menu processing
            switch(input){
                case 'N': //New Game
                {
                    rdTxt("GameData/crawl.txt"); //Display title crawl
                    *player = createCharacter(); //Create player character
                    play(); //Play the game
                    break;
                }
                case 'L': //Load
                {
                    *player = Actor(); //Reinitialize the player
                    if(loadMenu()){ //If the game is loaded
                        rdTxt("GameData/crawl.txt"); //Display title crawl
                        play(); //Play the game
                    }
                    break;
                }
                case 'O': //Options
                {
                    mainMenuOptions(); //Display game options menu
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

        saveConfig();
        cleanup();
    }
    catch(Exception e){
        cerr << e.toString() << endl;
        return e.errorCode();
    }
    catch(std::exception e){
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}

