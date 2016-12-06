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
#include "functions.h"

//Namespaces
using namespace std;
using namespace Error;
using namespace Flow;

int main(int argc, char** argv){
    try{
        Game game;
        game.config(loadConfig(game.configPath()));
        bool quit = false; //Whether or not to quit the game

        do{ //While not quitting
            if(game.config().asciiArt){ //If ASCII art is enabled
                rdTxt("GameData/title.txt"); //Display ASCII title
            }
            else{ //Otherwise
                cout << "OVERFLOW" << endl; //Output title
                cout << endl;
            }
            char input = menu({"New Game", "Load", "Options", "Help", "Exit"}, 5); //Do main menu processing
            switch(input){
                case 'N': //New Game
                {
                    rdTxt("GameData/crawl.txt"); //Display title crawl
                    createCharacter(game); //Create player character
                    game.play(); //Play the game
                    break;
                }
                case 'L': //Load
                {
                    game.player(Actor()); //Reinitialize the player
                    if(loadMenu(game)){ //If the game is loaded
                        rdTxt("GameData/crawl.txt"); //Display title crawl
                        game.play(); //Play the game
                    }
                    break;
                }
                case 'O': //Options
                {
                    mainMenuOptions(game); //Display game options menu
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

        saveConfig(game.configPath(), game.config());
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

