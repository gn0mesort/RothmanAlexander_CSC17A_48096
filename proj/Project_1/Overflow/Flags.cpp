/*
 * File:   Flags.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 15, 2016
 */

#include <sstream>

#include "Flags.h"

std::string Flow::Exit::toStr(unsigned char exit){
    std::stringstream r;

    if(exit == Flow::Exit::NONE){
        r << "No exits ";
    }
    else{
        if(Flow::FlgUtil::hasFlag(exit, Flow::Exit::NORTH)){
            r << "North ";
        }
        if(Flow::FlgUtil::hasFlag(exit, Flow::Exit::EAST)){
            r << "East ";
        }
        if(Flow::FlgUtil::hasFlag(exit, Flow::Exit::SOUTH)){
            r << "South ";
        }
        if(Flow::FlgUtil::hasFlag(exit, Flow::Exit::WEST)){
            r << "West ";
        }
    }

    return r.str();
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