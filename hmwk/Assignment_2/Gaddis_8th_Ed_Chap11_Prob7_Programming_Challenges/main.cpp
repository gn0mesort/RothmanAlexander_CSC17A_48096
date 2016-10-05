

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

#include "CstAcct.h"
using namespace std;

void getLn(string&);
void crAcct(vector<CstAcct>&);
void rmAcct(vector<CstAcct>&);
void dsAcct(const vector<CstAcct>&);
void edAcct(vector<CstAcct>&);

int main(int argc, char** argv){
    vector<CstAcct> data;
    unsigned short input = 0;

    cout << "Welcome!" << endl;
    do{
        cout << "MENU" << endl;
        cout << "(1) Display Accounts" << endl;
        cout << "(2) Create Account" << endl;
        cout << "(3) Remove Account" << endl;
        cout << "(4) Edit Account" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input;

        switch(input){
            case 1:
            {
                cout << "DISPLAY ACCOUNTS" << endl;
                dsAcct(data);
                break;
            }
            case 2:
            {
                cout << "CREATE NEW ACCOUNT" << endl;
                crAcct(data);
                break;
            }
            case 3:
            {
                cout << "REMOVE ACCOUNT" << endl;
                rmAcct(data);
                break;
            }
            case 4:
            {
                cout << "EDIT ACCOUNT" << endl;
                edAcct(data);
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

void crAcct(vector<CstAcct> &data){
    CstAcct acct;
    time_t rawtime;
    cout << "Enter the name of the account holder: ";
    cin.ignore();
    getLn(acct.name);
    cout << "Enter the street address of the account holder: ";
    getLn(acct.address);
    cout << "Enter the City, State, and Zip Code of the account holder: ";
    getLn(acct.ctStZp);
    cout << "Enter the telephone number of the account holder: ";
    getLn(acct.tel);
    do{
        cout << "Enter the starting balance of the account: ";
        cin >> acct.balance;
    } while(acct.balance < 0);
    time(&rawtime);
    acct.lastPay = asctime(localtime(&rawtime));

    data.push_back(acct);
}

void rmAcct(vector<CstAcct> &data){
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

void dsAcct(const vector<CstAcct> &data){
    for(int i = 0; i < data.size(); ++i){
        cout << "NAME: " << data.at(i).name << endl;
        cout << "STREET ADDRESS: " << data.at(i).address << endl;
        cout << "CITY, STATE, ZIP: " << data.at(i).ctStZp << endl;
        cout << "TELEPHONE NUMBER: " << data.at(i).tel << endl;
        cout << "BALANCE: " << data.at(i).balance << endl;
        cout << "LAST PAID: " << data.at(i).lastPay << endl;
        if(i + 1 < data.size()){
            cout << endl;
        }
    }
}

void edAcct(vector<CstAcct> &data){
    unsigned short acct = 0,
            input = 0;

    for(int i = 0; i < data.size(); ++i){
        cout << "(" << i + 1 << ") " << data.at(i).name << endl;
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> acct;
    if(acct > 0){
        --acct;
        cout << "(1) NAME" << endl;
        cout << "(2) STREET ADDRESS" << endl;
        cout << "(3) CITY, STATE, ZIP" << endl;
        cout << "(4) TELEPHONE NUMBER" << endl;
        cout << "(5) BALANCE" << endl;
        cout << "(6) DATE OF LAST PAYMENT" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input;
        switch(input){
            case 1:
            {
                cout << "CURRENT NAME: " << data.at(acct).name << endl;
                cout << "UPDATED NAME: ";
                cin.ignore();
                getLn(data.at(acct).name);
                break;
            }
            case 2:
            {
                cout << "CURRENT ADDRESS: " << data.at(acct).address << endl;
                cout << "UPDATED ADDRESS: ";
                cin.ignore();
                getLn(data.at(acct).address);
                break;
            }
            case 3:
            {
                cout << "CURRENT CITY, STATE, ZIP: " << data.at(acct).ctStZp << endl;
                cout << "UPDATED CITY, STATE, ZIP: ";
                cin.ignore();
                getLn(data.at(acct).ctStZp);
                break;
            }
            case 4:
            {
                cout << "CURRENT TELEPHONE NUMBER: " << data.at(acct).tel << endl;
                cout << "UPDATED TELEPHONE NUMBER: ";
                cin.ignore();
                getLn(data.at(acct).tel);
                break;
            }
            case 5:
            {
                cout << "CURRENT BALANCE: " << data.at(acct).balance << endl;
                cout << "UPDATED BALANCE: ";
                cin >> data.at(acct).balance;
                break;
            }
            case 6:
            {
                cout << "CURRENT DATE OF LAST PAYMENT: " << data.at(acct).lastPay << endl;
                cout << "UPDATED DATE OF LAST PAYMENT: ";
                cin.ignore();
                getLn(data.at(acct).lastPay);
                break;
            }
        }
    }
}