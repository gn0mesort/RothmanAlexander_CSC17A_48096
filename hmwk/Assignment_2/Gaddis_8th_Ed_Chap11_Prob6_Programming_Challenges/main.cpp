/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Display a table based on data for a team of soccer players
 * Created on October 4, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <string> //String type and functions

//User Libraries
#include "Player.h" //Player object
using namespace std;

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    const unsigned char SIZE = 12; //The number of players
    unsigned char mvp = 0; //The position of the MVP in the team array
    unsigned short total = 0; //The total score of the team
    Player team[SIZE]; //The array of Players to store data in

    //Input
    for(int i = 0; i < SIZE; ++i){ //For every Player on the team
        short input = 0; //Store input
        cout << "ENTER PLAYER #" << i + 1 << "'S NAME: ";
        if(i > 0){ //If this isn't the first Player
            cin.ignore(); //Clear input before getline
        }
        getline(cin, team[i].name); //Read in the Player's name
        do{ //While the input value is negative
            cout << "ENTER " << team[i].name << "'S NUMBER: ";
            cin >> input; //Read input
        } while(input < 0);
        team[i].number = input; //Set the Player's number to input
        do{ //While the input value is naegative
            cout << "ENTER " << team[i].name << "'S SCORE: ";
            cin >> input; //Read input
        } while(input < 0);
        team[i].score = input; //Set the Player's score to input
    }
    cout << endl;

    //Output Table
    cout << setw(10) << "NAME" << setw(10) << "NUMBER" << setw(10) << "SCORE" << endl; //Output header
    for(int i = 0; i < SIZE; ++i){ //For every Player on the team
        cout << setw(10) << team[i].name << setw(10) << team[i].number << setw(10) << team[i].score << endl; //Output row
        total += team[i].score; //Total the score
        if(team[i].score >= team[mvp].score){ //If the current Player's score is greater than the MVP's score
            mvp = i; //The current player is the MVP
        }
    }
    cout << "TOTAL SCORE: " << total << endl; //Output total score
    cout << "MVP: " << "#" << team[mvp].number << " " << team[mvp].name << " WITH " << team[mvp].score << " POINTS" << endl; //Output MVP

    //Exit
    return 0;
}