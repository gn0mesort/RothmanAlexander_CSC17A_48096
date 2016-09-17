/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Population Size over time
 * Created on September 17, 2016
 */

#include <iostream>
using namespace std;

int main(int argc, char** argv){
    unsigned short initPop = 0,
            days = 0;
    short pIncr = 0;
    float total = 0.0f;

    do{
        cout << "ENTER THE INITIAL POPULATION: ";
        cin >> initPop;
    } while(initPop < 2);
    do{
        cout << "HOW MANY DAYS WILL THEY MULTIPLY FOR: ";
        cin >> days;
    } while(days < 1);
    do{
        cout << "WHAT IS THE AVERAGE INCREASE PER DAY (AS A PERCENTAGE): ";
        cin >> pIncr;
    } while(pIncr < 0);

    total = initPop;
    for(int i = 0; i < days; ++i){
        total += (total * pIncr / 100.0f);
        cout << "POPULATION ON DAY " << (i + 1) << ": ";
        cout << static_cast<int>(total) << endl;
    }

    return 0;
}

