/* 
 * File:   Player.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Store data on soccer players
 * Created on October 4, 2016
 */

#ifndef PLAYER_H
#define PLAYER_H

//System Libraries
#include <string> //String type and functions

//Player
//Stores data about a single player on the soccer team

struct Player{
    std::string name; //The player's name
    unsigned short number; //The player's number
    unsigned short score; //The player's score in the current game
};

#endif /* PLAYER_H */
