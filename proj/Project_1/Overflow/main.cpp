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
using namespace std;

int main(int argc, char** argv){
    Byte::Byte<int> b = 0x79656f5a;
    ofstream out;

    out.open("out.bin", ios::binary);
    out.write(b.getSBytes(), b.size());
    out.close();

    return 0;
}

