/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on September 17, 2016
 */

#include <iostream>
#include <string>
using namespace std;

char getClr();
char getChar();
bool fndMix(char, char);

int main(int argc, char** argv){
    char color1 = 0,
            color2 = 0;
    do{
        color1 = getClr();
        color2 = getClr();
    } while(!fndMix(color1, color2));
    return 0;
}

bool fndMix(char color1, char color2){
    bool r = false;
    if(color1 == color2){
        cout << "BOTH COLORS ARE THE SAME. NO MIX!" << endl;
        r = false;
    }
    else if((color1 == 'R' && color2 == 'Y') ||
            (color1 == 'Y' && color2 == 'R')){
        cout << "MIX RESULT: ORANGE!" << endl;
        r = true;
    }
    else if((color1 == 'R' && color2 == 'B') ||
            (color1 == 'B' && color2 == 'R')){
        cout << "MIX RESULT: PURPLE!" << endl;
        r = true;
    }
    else if((color1 == 'B' && color2 == 'Y') ||
            (color1 == 'Y' && color2 == 'B')){
        cout << "MIX RESULT: GREEN!" << endl;
        r = true;
    }
    else{
        cout << "INVALID INPUTS" << endl;
        r = false;
    }
    return r;
}

char getClr(){
    char color = 0;
    do{
        cout << "ENTER A PRIMARY COLOR (RED, YELLOW, BLUE): ";
        color = getChar();
    } while(!(color == 'R' || color == 'Y' || color == 'B'));
}

char getChar(){
    string input;
    cin >> input;
    return toupper(input.at(0));
}

