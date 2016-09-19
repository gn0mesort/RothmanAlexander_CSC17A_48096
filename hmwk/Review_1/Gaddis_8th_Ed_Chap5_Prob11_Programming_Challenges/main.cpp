/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Population Size over time
 * Created on September 17, 2016
 */

//System Libraries
#include <iostream> //I/O
using namespace std;

//Begin Execution
int main(int argc, char** argv){
    //Declaration and Initialization
    unsigned short initPop = 0, //The initial population size
            days = 0; //The number of days to multiply over
    short pIncr = 0; //The percentage to increase by
    float total = 0.0f; //The total population

    //Read and validate input
    do{ //While the initial population is less than 2
        cout << "ENTER THE INITIAL POPULATION: ";
        cin >> initPop; //Read in initPop
    } while(initPop < 2);
    do{ //While the number of days is less than 1
        cout << "HOW MANY DAYS WILL THEY MULTIPLY FOR: ";
        cin >> days; //Read in days
    } while(days < 1);
    do{ //While the percentage increase is less than 0
        cout << "WHAT IS THE AVERAGE INCREASE PER DAY (AS A PERCENTAGE): ";
        cin >> pIncr; //Read in pIncr
    } while(pIncr < 0);

    //Calculate and output data
    total = initPop; //Set total to the initial size
    for(int i = 0; i < days; ++i){ //For every day in days
        total += (total * pIncr / 100.0f); //Add the total multiplied by the percentage increase to the total
        cout << "POPULATION ON DAY " << (i + 1) << ": "; //Output the day's population
        cout << static_cast<int>(total) << endl; //Drop fractional creatures
    }

    //Exit
    return 0;
}

