/*
 * File:   Actor.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 15, 2016
 */

#include "Actor.h"

Flow::Job Flow::Actor::job(){
    return _job;
}

void Flow::Actor::setJob(Job job){
    _job = job;
}