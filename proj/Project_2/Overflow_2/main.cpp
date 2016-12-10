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
 * Purpose: Control the main flow of the Overflow game program
 * Created on November 26, 2016
 */


//System Libraries
#include <iostream> //I/O
#include <exception> //std::exceptions
#include <ctime> //Time
#include <string> //Strings
#include <iomanip> //I/O Formatting
#include <cstdlib> //C Standard Library
#include <cstdio> //C Standard I/O

//User Libraries
#include "except.h" //Error::Exceptions
#include "game.h" //Main game classes and data
#include "functions.h" //Loose game functions

//Namespaces
using namespace std; //Standard namespace
using namespace Error; //Namespace for Error::Exceptions
using namespace Flow; //Game namespace

int main(int argc, char** argv){
    try{ //Try to run the game
        Game game; //Initialize a new Game
        bool quit = false; //Whether or not to quit the game

        game.config(loadConfig(game.configPath())); //Load the game config
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
                    game.createCharacter(); //Create player character
                    game.play(); //Play the game
                    break;
                }
                case 'L': //Load
                {
                    game.player(Actor()); //Reinitialize the player
                    if(game.loadMenu()){ //If the game is loaded
                        rdTxt("GameData/crawl.txt"); //Display title crawl
                        game.play(); //Play the game
                    }
                    break;
                }
                case 'O': //Options
                {
                    game.mainMenuOptions(); //Display game options menu
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
        saveConfig(game.configPath(), game.config()); //Save the game configuration
    }
    catch(Exception e){ //Catch any Error::Exceptions thrown by the game
        cerr << e.toString() << endl; //Output the error
        return e.errorCode(); //Return 1
    }
    catch(std::exception e){ //Catch std::exceptions thrown by the game
        cerr << e.what() << endl; //Output the error
        return 1; //Return 1
    }

    return 0; //Exit
}

