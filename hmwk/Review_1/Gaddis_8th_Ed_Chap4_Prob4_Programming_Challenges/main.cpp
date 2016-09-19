/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Find the rectangle with the greater area
 * Created on September 17, 2016
 */

#include <iostream>
using namespace std;

int main(int argc, char** argv){
    short length1 = 0,
            length2 = 0,
            width1 = 0,
            width2 = 0,
            area1 = 0,
            area2 = 0;

    cout << "ENTER THE LENGTH OF THE FIRST RECTANGLE: ";
    cin >> length1;
    cout << "ENTER THE WIDTH OF THE FIRST RECTANGLE: ";
    cin >> width1;
    cout << "ENTER THE LENGTH OF THE SECOND RECTANGLE: ";
    cin >> length2;
    cout << "ENTER THE WIDTH OF THE SECOND RECTANGLE: ";
    cin >> width2;
    area1 = length1 * width1;
    area2 = length2 * width2;

    if(area1 > area2){
        cout << "THE FIRST RECTANGLE HAS A LARGER AREA!" << endl;
    }
    else if(area2 > area1){
        cout << "THE SECOND RECTANGLE HAS A LARGER AREA!" << endl;
    }
    else{
        cout << "THE RECTANGLES ARE EQUAL!" << endl;
    }


    return 0;
}

