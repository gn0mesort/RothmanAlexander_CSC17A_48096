/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Lottery Winners
 * Created on September 18, 2016
 */

#include <iostream>
using namespace std;

int main(int argc, char** argv){
    const unsigned int SIZE = 10;
    unsigned int nums[SIZE] = {13579, 26791, 26792, 33445, 55555, 62483, 77777,
                               79422, 85647, 93121};
    unsigned int winner = 0;
    bool match = false;
    do{
        cout << "ENTER THIS WEEK'S WINNING NUMBER: ";
        cin >> winner;
    } while(winner > 99999 || winner < 10000);
    for(int i = 0; i < SIZE; ++i){
        if(nums[i] == winner){
            match = true;
        }
    }
    cout << "YOU " << (match ? "WON!" : "LOST.") << endl;

    return 0;
}

