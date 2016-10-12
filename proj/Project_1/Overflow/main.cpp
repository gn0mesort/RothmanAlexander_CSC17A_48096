/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 11, 2016
 */

#include <iostream>
#include <fstream>

#include "Game.h"
#include "Stat.h"
#include "Byte.h"
#include "Enums.h"
using namespace std;

int main(int argc, char** argv){
    Flow::RoomType r = Flow::RoomType::Encounter;
    
    cout << Flow::EnumUtils::toByte(r).toString() << endl;
    
    return 0;
}

