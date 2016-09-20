/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Lottery Winners
 * Created on September 18, 2016
 */

//System Libraries
#include <iostream> //I/O
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    const unsigned int SIZE = 10; //The size of the lucky number array
    unsigned int nums[SIZE] = {13579, 26791, 26792, 33445, 55555, 62483, 77777,
                               79422, 85647, 93121}; //Initialized lucky number array
    unsigned int winner = 0; //The winning number to be read in
    bool match = false; //Whether or not the winning number is found

    //Read Input
    do{ //While input isn't valid
        cout << "ENTER THIS WEEK'S WINNING NUMBER: ";
        cin >> winner; //Read in winner
    } while(winner > 99999 || winner < 10000);

    //Calculate Output
    for(int i = 0; i < SIZE; ++i){ //Iterate across nums
        if(nums[i] == winner){ //If the winning number is found
            match = true;
        }
    }

    //Output Data
    cout << "YOU " << (match ? "WON!" : "LOST.") << endl;

    //Exit
    return 0;
}