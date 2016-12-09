/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Flags.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for flags.h
 * Created on October 15, 2016
 */

#include "flags.h"

/**
 * Convert a direction to a string
 * @param direct The direction to convert
 * @return A string containing the directions in direct
 */
std::string Flow::Direct::toString(unsigned char direct){
    std::string r; //The return string

    if(direct == Direct::NONE){ //If no exits
        r += "No exits ";
    }
    else{ //Otherwise
        if(FlagUtil::hasFlag(direct, Direct::NORTH)){ //If there's a north exit
            r += "North ";
        }
        if(FlagUtil::hasFlag(direct, Direct::EAST)){ //If there's an east exit
            r += "East ";
        }
        if(FlagUtil::hasFlag(direct, Direct::SOUTH)){ //If there's a south exit
            r += "South ";
        }
        if(FlagUtil::hasFlag(direct, Direct::WEST)){ //If there's a west exit
            r += "West ";
        }
    }

    return r;
}

/**
 * Convert a direction to an abbreviated string or to its normal string representation
 * @param direct The direction to convert
 * @param abbrv Whether or not to abbreviate
 * @return  A string representing the input direction
 */
std::string Flow::Direct::toString(unsigned char direct, bool abbrv){
    std::string r; //The return string

    if(abbrv){ //If abbreviated
        if(FlagUtil::hasFlag(direct, Direct::NORTH)){ //If north
            r += "N";
        }
        if(FlagUtil::hasFlag(direct, Direct::EAST)){ //If east
            r += "E";
        }
        if(FlagUtil::hasFlag(direct, Direct::SOUTH)){ //If south
            r += "S";
        }
        if(FlagUtil::hasFlag(direct, Direct::WEST)){ //If west
            r += "W";
        }
    }
    else{ //Otherwise
        r += toString(direct); //Get the long string
    }

    return r;
}

/**
 * Reverse a direction
 * @param direct A direction to reverse. Must be a cardinal direction
 * @return The opposite direction or Direct::NONE for noncardinal inputs
 */
unsigned char Flow::Direct::reverse(unsigned char direct){
    if(direct == Direct::NORTH){ //If north
        return Direct::SOUTH;
    }
    else if(direct == Direct::SOUTH){ //Else if south
        return Direct::NORTH;
    }
    else if(direct == Direct::EAST){ //Else if east
        return Direct::WEST;
    }
    else if(direct == Direct::WEST){ //Else if west
        return Direct::EAST;
    }
    return Direct::NONE; //In case of noncardinal directions
}

/**
 * Convert an element to a string
 * @param elem The element to convert
 * @return A string representation of the input element
 */
std::string Flow::DmgElem::toString(unsigned char elem){
    std::string r;

    if(elem == Flow::DmgElem::ABSOLUT){
        r += "Absolute ";
    }
    else{
        if(FlagUtil::hasFlag(elem, DmgElem::HEALING)){ //If the element contains healing
            r += "Healing ";
        }
        if(FlagUtil::hasFlag(elem, DmgElem::FIRE)){ //If the element contains fire
            r += "Fire ";
        }
        if(FlagUtil::hasFlag(elem, DmgElem::ICE)){ //If the element contains ice
            r += "Ice ";
        }
        if(FlagUtil::hasFlag(elem, DmgElem::LIGHTNG)){ //If the element contains lightning
            r += "Lightning ";
        }
        if(FlagUtil::hasFlag(elem, DmgElem::WIND)){ //If the element contains wind
            r += "Wind ";
        }
        if(FlagUtil::hasFlag(elem, DmgElem::HOLY)){ //If the element contains holy
            r += "Holy ";
        }
        if(FlagUtil::hasFlag(elem, DmgElem::SHADOW)){ //If the element contains shadow
            r += "Shadow ";
        }
        if(FlagUtil::hasFlag(elem, DmgElem::NGHTMRE)){ //If the element contains nightmare
            r += "Nightmare ";
        }
    }

    return r;
}

/**
 * Return whether or not the input data has the given flag values.
 * @param data The data to compare to
 * @param value The values to compare to data
 * @return true in the values are found in the data. Otherwise false
 */
bool Flow::FlagUtil::hasFlag(unsigned long data, unsigned long value){
    return (data & value) == value;
}