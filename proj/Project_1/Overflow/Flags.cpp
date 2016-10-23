/*
 * File:   Flags.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 15, 2016
 */

#include <sstream>

#include "Flags.h"

std::string Flow::Direct::toStr(unsigned char direct){
    std::stringstream r;

    if(direct == Flow::Direct::NONE){
        r << "No exits ";
    }
    else{
        if(Flow::FlgUtil::hasFlag(direct, Flow::Direct::NORTH)){
            r << "North ";
        }
        if(Flow::FlgUtil::hasFlag(direct, Flow::Direct::EAST)){
            r << "East ";
        }
        if(Flow::FlgUtil::hasFlag(direct, Flow::Direct::SOUTH)){
            r << "South ";
        }
        if(Flow::FlgUtil::hasFlag(direct, Flow::Direct::WEST)){
            r << "West ";
        }
    }

    return r.str();
}

std::string Flow::Direct::toStr(unsigned char direct, bool abbrv){
    std::stringstream r;

    if(abbrv){
        if(Flow::FlgUtil::hasFlag(direct, Flow::Direct::NORTH)){
            r << "N";
        }
        if(Flow::FlgUtil::hasFlag(direct, Flow::Direct::EAST)){
            r << "E";
        }
        if(Flow::FlgUtil::hasFlag(direct, Flow::Direct::SOUTH)){
            r << "S";
        }
        if(Flow::FlgUtil::hasFlag(direct, Flow::Direct::WEST)){
            r << "W";
        }
    }
    else{
        r << toStr(direct);
    }

    return r.str();
}

unsigned char Flow::Direct::reverse(unsigned char direct){
    if(direct == Flow::Direct::NORTH){
        return Flow::Direct::SOUTH;
    }
    else if(direct == Flow::Direct::SOUTH){
        return Flow::Direct::NORTH;
    }
    else if(direct == Flow::Direct::EAST){
        return Flow::Direct::WEST;
    }
    else if(direct == Flow::Direct::WEST){
        return Flow::Direct::EAST;
    }
    return Flow::Direct::NONE;
}

std::string Flow::DmgElem::toStr(unsigned char elem){
    std::stringstream r;

    if(elem == Flow::DmgElem::ABSOLUT){
        r << "Absolute ";
    }
    else{
        if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::HEALING)){
            r << "Healing ";
        }
        if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::FIRE)){
            r << "Fire ";
        }
        if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::ICE)){
            r << "Ice ";
        }
        if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::LIGHTNG)){
            r << "Lightning ";
        }
        if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::WIND)){
            r << "Wind ";
        }
        if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::HOLY)){
            r << "Holy ";
        }
        if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::SHADOW)){
            r << "Shadow ";
        }
        if(Flow::FlgUtil::hasFlag(elem, Flow::DmgElem::NGHTMRE)){
            r << "Nightmare ";
        }
    }

    return r.str();
}

bool Flow::FlgUtil::hasFlag(unsigned long data, unsigned long value){
    return (data & value) == value;
}