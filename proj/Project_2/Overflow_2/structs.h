/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   structs.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define Game structs outside of other headers
 * Created on December 4, 2016
 */

#ifndef STRUCTS_H
#define STRUCTS_H

//System Libraries
#include <string> //Strings

namespace Flow{

    /**
     * Defines a Random Number Generator position
     */
    struct RNGPoint{
        /**
         * The 0 based position of the generator
         */
        unsigned int pos;

        /**
         * The seed of the generator
         */
        unsigned int seed;
    };

    /**
     * Defines a Game configuration
     */
    struct Config{
        /**
         * Whether or not to display ASCII art
         */
        bool asciiArt;

        /**
         * The current save path
         */
        std::string saveGame;
    };

    /**
     * Defines an (X, Y) position on a grid
     */
    struct Point{
        /**
         * The X position
         */
        int x;

        /**
         * The Y position
         */
        int y;
    };
}

#endif /* STRUCTS_H */

