/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   structs.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 4, 2016
 */

#ifndef STRUCTS_H
#define STRUCTS_H
namespace Flow{

    struct RNGPoint{
        unsigned int pos;
        unsigned int seed;
    };

    struct Config{
        bool asciiArt;
        std::string saveGame;
    };

}

#endif /* STRUCTS_H */

