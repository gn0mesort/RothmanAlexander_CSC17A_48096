/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Flags.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Define bit flags and helper functions as well as namespace them
 * Created on October 14, 2016
 */

#ifndef FLAGS_H
#define FLAGS_H

//System Libraries
#include <string> //String type and functions

namespace Flow{

    /**
     * Container namespace for Exit constants and functions
     */
    namespace Direct{
        /**
         * No direction
0         */
        const unsigned char NONE = 0,
                /**
                 * North on a compass
                 */
                NORTH = 1,

                /**
                 * East on a compass
                 */
                EAST = 2,

                /**
                 * South on a compass
                 */
                SOUTH = 4,

                /**
                 * West on a compass
                 */
                WEST = 8;

        unsigned char reverse(unsigned char);
        std::string toString(unsigned char);
        std::string toString(unsigned char, bool);
    }

    /**
     * A container namespace for damage elements
     */
    namespace DmgElem{
        /**
         * No element
         */
        const unsigned char NONE = 0,
                /**
                 * Nightmare element. Represents magic damage and obfuscation
                 */
                NGHTMRE = 1,

                /**
                 * Fire element. Represents fire damage and Attack increases
                 */
                FIRE = 2,

                /**
                 * Ice element. Represents ice damage and Defense increases
                 */
                ICE = 4,

                /**
                 * Lightning element. Represents lightning damage and Defense decreases
                 */
                LIGHTNG = 8,

                /**
                 * Wind element. Represents wind damage and Attack decreases
                 */
                WIND = 16,

                /**
                 * Holy element. Represents holy damage and HP increases
                 */
                HOLY = 32,

                /**
                 * Shadow element. Represents shadow damage and MP increases
                 */
                SHADOW = 64,

                /**
                 * Healing element. Represents healing attacks and HP regeneration
                 */
                HEALING = 128,

                /**
                 * Absolute element. Represents legendary attacks and full restoration
                 */
                ABSOLUT = 255;

        std::string toString(unsigned char);
    }

    /**
     * Container namepsace for difficulty constants
     */
    namespace Diff{
        /**
         * No difficulty
         */
        const unsigned char NONE = 0,
                /**
                 * Easy games
                 */
                EASY = 8,

                /**
                 * Medium games
                 */
                MEDIUM = 16,

                /**
                 * Hard games
                 */
                HARD = 32;
    }

    /**
     * Defines a class that contains flag handling functions
     */
    class FlagUtil{
    private:
    public:
        static bool hasFlag(unsigned long data, unsigned long value);
    };

}


#endif /* FLAGS_H */

