/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on October 4, 2016
 */

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

#include "Speaker.h"

using namespace std;

void getLn(string&);
void crSpkr(vector<Speaker>&);
void rmSpkr(vector<Speaker>&);
void dsSpkr(const vector<Speaker>&);
void edSpkr(vector<Speaker>&);

int main(int argc, char** argv){
    vector<Speaker> data;
    unsigned short input = 0;

    cout << "Welcome!" << endl;
    do{
        cout << "MENU" << endl;
        cout << "(1) Display Speakers" << endl;
        cout << "(2) Create Speaker" << endl;
        cout << "(3) Remove Speaker" << endl;
        cout << "(4) Edit Speaker" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input;

        switch(input){
            case 1:
            {
                cout << "DISPLAY SPEAKERS" << endl;
                dsSpkr(data);
                break;
            }
            case 2:
            {
                cout << "CREATE NEW SPEAKER" << endl;
                crSpkr(data);
                break;
            }
            case 3:
            {
                cout << "REMOVE SPEAKER" << endl;
                rmSpkr(data);
                break;
            }
            case 4:
            {
                cout << "EDIT SPEAKER" << endl;
                edSpkr(data);
                break;
            }
        }
        cout << endl;
    } while(input > 0);

    return 0;
}

void getLn(string &str){
    getline(cin, str, '\n');
}

void crSpkr(vector<Speaker> &data){
    Speaker speak;

    cout << "Enter the name of the speaker: ";
    cin.ignore();
    getLn(speak.name);
    cout << "Enter speaker's telephone number: ";
    getLn(speak.tel);
    cout << "Enter speaker's topic: ";
    getLn(speak.topic);
    do{
        cout << "Enter the speaker's fee: ";
        cin >> speak.fee;
    } while(speak.fee < 0);

    data.push_back(speak);
}

void rmSpkr(vector<Speaker> &data){
    unsigned short input = 0;
    for(int i = 0; i < data.size(); ++i){
        cout << "(" << i + 1 << ") " << data.at(i).name << endl;
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> input;
    if(input > 0){
        data.erase(data.begin() + (input - 1));
    }
}

void dsSpkr(const vector<Speaker> &data){
    for(int i = 0; i < data.size(); ++i){
        cout << "NAME: " << data.at(i).name << endl;
        cout << "TELEPHONE NUMBER: " << data.at(i).tel << endl;
        cout << "TOPIC: " << data.at(i).topic << endl;
        cout << "FEE: " << data.at(i).fee << endl;
    }
}

void edSpkr(vector<Speaker> &data){
    unsigned short speak = 0,
            input = 0;

    for(int i = 0; i < data.size(); ++i){
        cout << "(" << i + 1 << ") " << data.at(i).name << endl;
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> speak;
    if(speak > 0){
        --speak;
        cout << "(1) NAME" << endl;
        cout << "(2) TELEPHONE NUMBER" << endl;
        cout << "(3) TOPIC" << endl;
        cout << "(4) FEE" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input;
        switch(input){
            case 1:
            {
                cout << "CURRENT NAME: " << data.at(speak).name << endl;
                cout << "UPDATED NAME: ";
                cin.ignore();
                getLn(data.at(speak).name);
                break;
            }
            case 2:
            {
                cout << "CURRENT TELEPHONE NUMBER: " << data.at(speak).tel << endl;
                cout << "UPDATED TELEPHONE NUMBER: ";
                cin.ignore();
                getLn(data.at(speak).tel);
                break;
            }
            case 3:
            {
                cout << "CURRENT TOPIC: " << data.at(speak).topic << endl;
                cout << "UPDATED TOPIC: ";
                cin.ignore();
                getLn(data.at(speak).topic);
                break;
            }
            case 4:
            {
                cout << "CURRENT FEE: " << data.at(speak).fee << endl;
                cout << "UPDATED FEE: ";
                cin >> data.at(speak).fee;
                break;
            }
        }
    }
}
