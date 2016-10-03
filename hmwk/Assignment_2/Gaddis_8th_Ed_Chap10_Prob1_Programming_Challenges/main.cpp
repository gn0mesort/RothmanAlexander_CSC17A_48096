/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Display data on two movies. Information taken from imdb.com
 * Created on October 3, 2016
 */

#include <iostream>

#include "MovData.h"
using namespace std;

void prntMov(MovData);

int main(int argc, char** argv){
    MovData a,
            b;
    a.title = "Blade Runner";
    a.dirctr = "Ridley Scott";
    a.yearRel = 1982;
    a.runTime = 117;
    b.title = "Ghost in the Shell";
    b.dirctr = "Mamoru Oshii";
    b.yearRel = 1995;
    b.runTime = 83;

    prntMov(a);
    cout << endl;
    prntMov(b);

    return 0;
}

void prntMov(MovData data){
    cout << "TITLE: " << data.title << endl;
    cout << "DIRECTOR: " << data.dirctr << endl;
    cout << "YEAR RELEASED: " << data.yearRel << endl;
    cout << "RUN TIME: " << data.runTime << " MINUTES" << endl;
}
