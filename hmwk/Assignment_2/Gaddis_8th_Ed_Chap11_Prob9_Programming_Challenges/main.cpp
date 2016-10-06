/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: A menu driven application for creating, editing, and deleting Speaker objects
 * Created on October 4, 2016
 */

//System Libraries
#include <cstdlib> //C Standard Library
#include <string> //String type and functions
#include <vector> //Vector collections
#include <iostream> //I/O

//User Libraries
#include "Speaker.h" //Speaker object
using namespace std;

//Function Prototypes
void getLn(string&);
void crSpkr(vector<Speaker>&);
void rmSpkr(vector<Speaker>&);
void dsSpkr(const vector<Speaker>&);
void edSpkr(vector<Speaker>&);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    vector<Speaker> data; //The vector containing speaker data
    unsigned short input = 0; //Input value

    cout << "Welcome!" << endl;
    do{ //While not quitting
        //Output Menu
        cout << "MENU" << endl;
        cout << "(1) Display Speakers" << endl;
        cout << "(2) Create Speaker" << endl;
        cout << "(3) Remove Speaker" << endl;
        cout << "(4) Edit Speaker" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input; //Read input

        switch(input){ //Select option based on input
            case 1:
            {
                cout << "DISPLAY SPEAKERS" << endl;
                dsSpkr(data); //Speaker display processing
                break;
            }
            case 2:
            {
                cout << "CREATE NEW SPEAKER" << endl;
                crSpkr(data); //Speaker creation processing
                break;
            }
            case 3:
            {
                cout << "REMOVE SPEAKER" << endl;
                rmSpkr(data); //Speaker removal processing
                break;
            }
            case 4:
            {
                cout << "EDIT SPEAKER" << endl;
                edSpkr(data); //Speaker editing processing
                break;
            }
        }
        cout << endl;
    } while(input > 0);

    //Exit
    return 0;
}

//Get Line
//Get a line of text from standard input. Shortens the normal getline function
//Input:
//str
//The string to load data into
//Output:
//The input string loaded with data

void getLn(string &str){
    getline(cin, str, '\n');
}

//Create Speaker
//Create a Speaker and add it to the data vector
//Input:
//data
//The data vector for Speakers
//Output:
//The updated data vector

void crSpkr(vector<Speaker> &data){
    Speaker speak; //The new Speaker

    cout << "Enter the name of the speaker: ";
    cin.ignore(); //Clear input
    getLn(speak.name); //Read in the Speaker's name
    cout << "Enter speaker's telephone number: ";
    getLn(speak.tel); //Read in the Speaker's telephone number
    cout << "Enter speaker's topic: ";
    getLn(speak.topic); //Read in the Speaker's topic
    do{ //While the Speaker's fee is not negative
        cout << "Enter the speaker's fee: ";
        cin >> speak.fee; //Read in the fee
    } while(speak.fee < 0);

    data.push_back(speak); //Add the new Speaker to the data vector
}

//Remove Speaker
//Remove a Speaker from the data vector
//Input:
//data
//The data vector for Speakers
//Output:
//The updated data vector

void rmSpkr(vector<Speaker> &data){
    unsigned short input = 0; //The input value

    //Display Remove Speaker menu
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "(" << i + 1 << ") " << data.at(i).name << endl; //Output the Speaker's name
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> input; //Read input
    if(input > 0){ //If not exiting
        data.erase(data.begin() + (input - 1)); //Erase the selected element
    }
}

//Display Speakers
//Display Speakers found in the data vector
//Input:
//The data vector for Speakers

void dsSpkr(const vector<Speaker> &data){
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "NAME: " << data.at(i).name << endl; //Output the Speaker's name
        cout << "TELEPHONE NUMBER: " << data.at(i).tel << endl; //Output the Speaker's telephone number
        cout << "TOPIC: " << data.at(i).topic << endl; //Output the Speaker's topic
        cout << "FEE: " << data.at(i).fee << endl; //Output the Speaker's fee
    }
}

//Edit Speaker
//Edit a Speaker
//Input:
//data
//The data vector for Speakers
//Output:
//The updated data vector

void edSpkr(vector<Speaker> &data){
    unsigned short speak = 0, //The Speaker to edit
            input = 0; //The input value for the Speaker editing menu

    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "(" << i + 1 << ") " << data.at(i).name << endl; //Create a menu of Speakers to choose from
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> speak; //Read in the selected Speaker
    if(speak > 0){ //If not exiting
        --speak; //Set speaker correctly for a 0 based vector
        //Display Editing Menu
        cout << "(1) NAME" << endl;
        cout << "(2) TELEPHONE NUMBER" << endl;
        cout << "(3) TOPIC" << endl;
        cout << "(4) FEE" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input; //Read in input
        switch(input){ //Handle input from editing menu
            case 1: //Edit Name
            {
                cout << "CURRENT NAME: " << data.at(speak).name << endl;
                cout << "UPDATED NAME: ";
                cin.ignore();
                getLn(data.at(speak).name);
                break;
            }
            case 2: //Edit Telephone Number
            {
                cout << "CURRENT TELEPHONE NUMBER: " << data.at(speak).tel << endl;
                cout << "UPDATED TELEPHONE NUMBER: ";
                cin.ignore();
                getLn(data.at(speak).tel);
                break;
            }
            case 3: //Edit Topic
            {
                cout << "CURRENT TOPIC: " << data.at(speak).topic << endl;
                cout << "UPDATED TOPIC: ";
                cin.ignore();
                getLn(data.at(speak).topic);
                break;
            }
            case 4: //Edit Fee
            {
                cout << "CURRENT FEE: " << data.at(speak).fee << endl;
                cout << "UPDATED FEE: ";
                cin >> data.at(speak).fee;
                break;
            }
        }
    }
}
