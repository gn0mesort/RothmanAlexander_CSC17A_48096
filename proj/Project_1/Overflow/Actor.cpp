/*
 * File:   Actor.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 15, 2016
 */

#include "Actor.h"

Flow::Actor::Actor(){
    _job = Job::Knight;
    _hp("HP", "Hit Points", 100);
    _mp("MP", "Magic Points", 100);
    _atk("ATK", "Attack", 10);
    _def("DEF", "Defense", 10);
    _name = "Player";
}

Flow::Actor::Actor(const Actor &other){
    _job = other.job();
    _hp(other.hp());
    _mp(other.mp());
    _atk(other.atk());
    _def(other.def());
    _name = other.name();
}

Flow::Actor::Actor(const std::string &name, Job job){
    _job = job;
    _name = name;
    _hp("HP", "Hit Points", 100);
    _mp("MP", "Magic Points", 100);
    _atk("ATK", "Attack", 10);
    _def("DEF", "Defense", 10);
}

Flow::Job Flow::Actor::job(){
    return _job;
}

void Flow::Actor::setJob(Job job){
    _job = job;
}

Flow::IStat Flow::Actor::hp() const{
    return _hp;
}

void Flow::Actor::setHp(const IStat &hp){
    _hp(hp);
}

Flow::IStat Flow::Actor::mp() const{
    return _mp;
}

void Flow::Actor::setMp(const IStat &mp){
    _mp(mp);
}

Flow::BStat Flow::Actor::atk() const{
    return _atk;
}

void Flow::Actor::setAtk(const BStat &atk){
    _atk(atk);
}

Flow::BStat Flow::Actor::def() const{
    return _def;
}

void Flow::Actor::setDef(const BStat &def){
    _def(def);
}

std::string Flow::Actor::name() const{
    return _name;
}

void Flow::Actor::setName(const std::string &name){
    _name = name;
}