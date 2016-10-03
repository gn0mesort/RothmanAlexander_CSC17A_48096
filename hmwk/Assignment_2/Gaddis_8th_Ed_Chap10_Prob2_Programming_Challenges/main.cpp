/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Display data on two movies. Information taken from imdb.com
 * Created on October 3, 2016
 */

#include <iostream>

#include "MovData.h"
using namespace std;

void prntMov(const MovData&);

int main(int argc, char** argv){
    MovData a,
            b;
    a.title = "Blade Runner";
    a.dirctr = "Ridley Scott";
    a.yearRel = 1982;
    a.runTime = 117;
    a.cost = 28000000;
    a.revenue = 27580111;
    b.title = "Ghost in the Shell";
    b.dirctr = "Mamoru Oshii";
    b.yearRel = 1995;
    b.runTime = 83;
    b.cost = 5712639; //Estimated value of 600,000,000 JPY in 1996 when the movie was released in the USA
    b.revenue = 1099298; //Worldwide gross from 1995 + US gross from 1996

    prntMov(a);
    cout << endl;
    prntMov(b);

    return 0;
}

void prntMov(const MovData &data){
    cout << "TITLE: " << data.title << endl;
    cout << "DIRECTOR: " << data.dirctr << endl;
    cout << "YEAR RELEASED: " << data.yearRel << endl;
    cout << "RUN TIME: " << data.runTime << " MINUTES" << endl;
    cout << "NET PROFIT: " << static_cast<int>(data.revenue) - static_cast<int>(data.cost) << " USD" << endl;
}
