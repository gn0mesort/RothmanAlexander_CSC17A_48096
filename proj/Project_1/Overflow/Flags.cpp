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
 * Purpose: Source file for Flags.h
 * Created on October 15, 2016
 */

#include "Flags.h"

//toStr
//Convert a direction constant to a string
//Input:
//direct
//A direction to return the string of
//Output:
//A string representing the input direction

std::string Flow::Direct::toStr(unsigned char direct){
    std::string r; //The return string

    if(direct == Direct::NONE){ //If no exits
        r += "No exits ";
    }
    else{ //Otherwise
        if(FlgUtil::hasFlag(direct, Direct::NORTH)){ //If there's a north exit
            r += "North ";
        }
        if(FlgUtil::hasFlag(direct, Direct::EAST)){ //If there's an east exit
            r += "East ";
        }
        if(FlgUtil::hasFlag(direct, Direct::SOUTH)){ //If there's a south exit
            r += "South ";
        }
        if(FlgUtil::hasFlag(direct, Direct::WEST)){ //If there's a west exit
            r += "West ";
        }
    }

    return r;
}

//toStr
//Convert a direction to an abbreviated string or to its normal string representation
//Input:
//direct
//The direction to return the string of
//Output:
//A string representing the input direction

std::string Flow::Direct::toStr(unsigned char direct, bool abbrv){
    std::string r; //The return string

    if(abbrv){ //If abbreviated
        if(FlgUtil::hasFlag(direct, Direct::NORTH)){ //If north
            r += "N";
        }
        if(FlgUtil::hasFlag(direct, Direct::EAST)){ //If east
            r += "E";
        }
        if(FlgUtil::hasFlag(direct, Direct::SOUTH)){ //If south
            r += "S";
        }
        if(FlgUtil::hasFlag(direct, Direct::WEST)){ //If west
            r << "W";
        }
    }
    else{ //Otherwise
        r += toStr(direct); //Get the long string
    }

    return r;
}

//reverse
//Return the reverse of the input direction
//Input:
//direct
//The direction to return the reverse of
//Output:
//The opposite of any cardinal direction or Flow::Direct::NONE (0) otherwise

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

//toStr
//Convert an element to a string
//Input:
//elem
//The element to convert
//Output:
//The string representation of the element

std::string Flow::DmgElem::toStr(unsigned char elem){
    std::string r;

    if(elem == Flow::DmgElem::ABSOLUT){
        r += "Absolute ";
    }
    else{
        if(FlgUtil::hasFlag(elem, DmgElem::HEALING)){ //If the element contains healing
            r += "Healing ";
        }
        if(FlgUtil::hasFlag(elem, DmgElem::FIRE)){ //If the element contains fire
            r += "Fire ";
        }
        if(FlgUtil::hasFlag(elem, DmgElem::ICE)){ //If the element contains ice
            r += "Ice ";
        }
        if(FlgUtil::hasFlag(elem, DmgElem::LIGHTNG)){ //If the element contains lightning
            r += "Lightning ";
        }
        if(FlgUtil::hasFlag(elem, DmgElem::WIND)){ //If the element contains wind
            r += "Wind ";
        }
        if(FlgUtil::hasFlag(elem, DmgElem::HOLY)){ //If the element contains holy
            r += "Holy ";
        }
        if(FlgUtil::hasFlag(elem, DmgElem::SHADOW)){ //If the element contains shadow
            r += "Shadow ";
        }
        if(FlgUtil::hasFlag(elem, DmgElem::NGHTMRE)){ //If the element contains nightmare
            r += "Nightmare ";
        }
    }

    return r;
}

//hasFlag
//Return whether or not the input data has the given flag value. Works with flags of any size up to unsigned long
//Input:
//data
//The set of flags to check
//value
//The elemental flag value to check for
//Output:
//True if the flag is found otherwise false

bool Flow::FlgUtil::hasFlag(unsigned long data, unsigned long value){
    return (data & value) == value;
}