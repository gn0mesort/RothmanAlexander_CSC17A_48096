/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Find the rectangle with the greater area
 * Created on September 17, 2016
 */

//System Libraries
#include <iostream> //I/O
using namespace std;

//Begin Execution
int main(int argc, char** argv){
    //Declaration and Initialization
    short length1 = 0, //Length of the first rectangle
            length2 = 0, //Length of the second rectangle
            width1 = 0, //Width of the first rectangle
            width2 = 0, //Width of the second rectangle
            area1 = 0, //Area of the first rectangle
            area2 = 0; //Area of the second rectangle

    //Read input
    //Read in length1
    cout << "ENTER THE LENGTH OF THE FIRST RECTANGLE: ";
    cin >> length1;
    //Read in width1
    cout << "ENTER THE WIDTH OF THE FIRST RECTANGLE: ";
    cin >> width1;
    //Read in length2
    cout << "ENTER THE LENGTH OF THE SECOND RECTANGLE: ";
    cin >> length2;
    //Read in width2
    cout << "ENTER THE WIDTH OF THE SECOND RECTANGLE: ";
    cin >> width2;
    
    //Calculate Areas
    area1 = length1 * width1; //Calculate area1
    area2 = length2 * width2; //Calculate area2

    //Calculate and Output the larger rectangle
    if(area1 > area2){ //Rectangle 1 is bigger
        cout << "THE FIRST RECTANGLE HAS A LARGER AREA!" << endl;
    }
    else if(area2 > area1){ //Rectangle 2 is bigger
        cout << "THE SECOND RECTANGLE HAS A LARGER AREA!" << endl;
    }
    else{ //Rectangle 1 is equal to Rectangle 2
        cout << "THE RECTANGLES ARE EQUAL!" << endl;
    }

    //Exit
    return 0;
}

