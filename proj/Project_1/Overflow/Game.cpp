/*
 * File:   Game.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 15, 2016
 */

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Game.h"


const std::string Flow::Config::SAVPATH = "GameData/game.conf";

std::vector<std::string> *Flow::Game::nWeaps = NULL;
Flow::Actor Flow::Game::player;
Flow::GmRand Flow::Game::gmRand;
Flow::Config Flow::Game::conf;

std::vector<std::string>* Flow::rNWeaps(){
    std::vector<std::string> *r = new std::vector<std::string>[JOB_CNT];

    for(int i = 0; i < JOB_CNT; ++i){
        std::string path;
        if(i == 0){
            path = "GameData/knightweapons.txt";
        }
        else if(i == 1){
            path = "GameData/clericweapons.txt";
        }
        else if(i == 2){
            path = "GameData/mageweapons.txt";
        }
        else{
            path = "GameData/lancerweapons.txt";
        }
        Flow::rdTxt(r[i], path);
    }

    return r;
}

void Flow::rdTxt(const std::string &path){
    std::ifstream in;

    in.open(path);
    while(in.good() && !in.eof()){
        std::string input;
        getline(in, input);
        std::cout << input << std::endl;
    }
    in.close();
}

void Flow::rdTxt(std::vector<std::string> &data, const std::string &path){
    std::ifstream in;

    in.open(path);
    while(in.good() && !in.eof()){
        std::string input;
        getline(in, input);
        data.push_back(input);
    }
    in.close();
}

bool Flow::ckFile(const std::string &path){
    bool r = false;
    std::ifstream in;

    in.open(path);
    r = in.good();
    in.close();

    return r;
}

void Flow::init(){
    Game::nWeaps = rNWeaps();
    if(ckFile(Flow::Config::SAVPATH)){

    }
    else{
        Flow::Game::conf.ascArt = true;
        Flow::Game::conf.mjVer = 1;
        Flow::Game::conf.miVer = 0;
    }
}

void Flow::cleanUp(){
    delete [] Game::nWeaps;
}

unsigned int Flow::binPow(unsigned int pow){
    if(pow == 0){
        return 1;
    }
    else{
        return 2 * binPow(pow - 1);
    }
}

int Flow::toInt(unsigned char value){
    return static_cast<int>(value);
}

int Flow::GmRand::rand(){
    ++_pos;
    return std::rand();
}

unsigned int Flow::GmRand::seed(){
    return _seed;
}

void Flow::GmRand::srand(){
    std::srand(_seed);
    _pos = 0;
}

void Flow::GmRand::srand(unsigned int seed){
    std::srand(seed);
    _seed = seed;
    _pos = 0;
}

unsigned int Flow::GmRand::pos(){
    return _pos;
}

void Flow::GmRand::seek(unsigned int pos){
    std::srand(_seed);
    for(int i = 0; i < pos; ++i){
        std::rand();
    }
    _pos = pos;
}

Flow::GmRand::GmRand(){
    _pos = 0;
    _seed = static_cast<int>(time(0));
    srand();
}