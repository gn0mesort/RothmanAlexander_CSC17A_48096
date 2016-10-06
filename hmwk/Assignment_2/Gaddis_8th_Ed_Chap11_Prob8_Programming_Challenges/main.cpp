/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Expand problem 7 with a search function
 * Created on October 4, 2016
 */

//System Libraries
#include <cstdlib> //C Standard Library
#include <string> //String type and functions
#include <vector> //Vector collections
#include <iostream> //I/O

//User Libraries
#include "CstAcct.h" //Customer Accounts
using namespace std;

//Function Prototypes
void getLn(string&);
void crAcct(vector<CstAcct>&);
void rmAcct(vector<CstAcct>&);
void dsAcct(const vector<CstAcct>&);
void edAcct(vector<CstAcct>&);
void fdAcct(const vector<CstAcct>&);
string toupper(const string&);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    vector<CstAcct> data; //The vector containing customer account data
    unsigned short input = 0; //Input value

    cout << "Welcome!" << endl;
    do{ //While not quitting
        //Output Menu
        cout << "MENU" << endl;
        cout << "(1) Display Accounts" << endl;
        cout << "(2) Create Account" << endl;
        cout << "(3) Remove Account" << endl;
        cout << "(4) Edit Account" << endl;
        cout << "(5) Find Account" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input; //Read input

        switch(input){ //Select option based on input
            case 1:
            {
                cout << "DISPLAY ACCOUNTS" << endl;
                dsAcct(data); //Account display processing
                break;
            }
            case 2:
            {
                cout << "CREATE NEW ACCOUNT" << endl;
                crAcct(data); //Account creation processing
                break;
            }
            case 3:
            {
                cout << "REMOVE ACCOUNT" << endl;
                rmAcct(data); //Account removal processing
                break;
            }
            case 4:
            {
                cout << "EDIT ACCOUNT" << endl;
                edAcct(data); //Account editing processing
                break;
            }
            case 5:
            {
                cout << "FIND ACCOUNT" << endl;
                fdAcct(data); //Account search processing
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

//Create Account
//Create a Customer Account and add it to the data vector
//Input:
//data
//The data vector for Customer Accounts
//Output:
//The updated data vector

void crAcct(vector<CstAcct> &data){
    CstAcct acct; //The new user account
    time_t rawtime; //The current time

    cout << "Enter the name of the account holder: ";
    cin.ignore(); //Clear input
    getLn(acct.name); //Read in the account name
    cout << "Enter the street address of the account holder: ";
    getLn(acct.address); //Read in the address
    cout << "Enter the City, State, and Zip Code of the account holder: ";
    getLn(acct.ctStZp); //Read in the city, state, and zip code
    cout << "Enter the telephone number of the account holder: ";
    getLn(acct.tel); //Read in the telephone number
    do{ //While the account balance is negative
        cout << "Enter the starting balance of the account: ";
        cin >> acct.balance; //Read in the account balance
    } while(acct.balance < 0);
    time(&rawtime); //Fill rawtime with the current time
    acct.lastPay = asctime(localtime(&rawtime)); //Convert the current time to a string

    data.push_back(acct); //Add the new account to the data vector
}

//Remove Account
//Remove a Customer Account from the data vector
//Input:
//data
//The data vector for Customer Accounts
//Output:
//The updated data vector

void rmAcct(vector<CstAcct> &data){
    unsigned short input = 0; //The input value

    //Display Remove Account menu
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "(" << i + 1 << ") " << data.at(i).name << endl; //Output the account name
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> input; //Read input
    if(input > 0){ //If not exiting
        data.erase(data.begin() + (input - 1)); //Erase the selected element
    }
}

//Display Accounts
//Display Customer Accounts found in the data vector
//Input:
//The data vector for Customer Accounts

void dsAcct(const vector<CstAcct> &data){
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "NAME: " << data.at(i).name << endl; //Output the account name
        cout << "STREET ADDRESS: " << data.at(i).address << endl; //Output the account address
        cout << "CITY, STATE, ZIP: " << data.at(i).ctStZp << endl; //Output the account city state and zip code
        cout << "TELEPHONE NUMBER: " << data.at(i).tel << endl; //Output the account telephone number
        cout << "BALANCE: " << data.at(i).balance << endl; //Output the account balance
        cout << "LAST PAID: " << data.at(i).lastPay << endl; //Output the date of last payment
        if(i + 1 < data.size()){ //Formatting
            cout << endl;
        }
    }
}

//Edit Account
//Edit a user account
//Input:
//data
//The data vector for Customer accounts
//Output:
//The updated data vector

void edAcct(vector<CstAcct> &data){
    unsigned short acct = 0, //The account to edit
            input = 0; //The input value for the account editing menu

    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "(" << i + 1 << ") " << data.at(i).name << endl; //Create a menu of Customer Accounts to choose from
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> acct; //Read in the selected account
    if(acct > 0){ //If not exiting
        --acct; //Set account correctly for a 0 based vector
        //Display Editing Menu
        cout << "(1) NAME" << endl;
        cout << "(2) STREET ADDRESS" << endl;
        cout << "(3) CITY, STATE, ZIP" << endl;
        cout << "(4) TELEPHONE NUMBER" << endl;
        cout << "(5) BALANCE" << endl;
        cout << "(6) DATE OF LAST PAYMENT" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input; //Read in input
        switch(input){ //Handle input from editing menu
            case 1: //Edit Name
            {
                cout << "CURRENT NAME: " << data.at(acct).name << endl;
                cout << "UPDATED NAME: ";
                cin.ignore();
                getLn(data.at(acct).name);
                break;
            }
            case 2: //Edit Address
            {
                cout << "CURRENT ADDRESS: " << data.at(acct).address << endl;
                cout << "UPDATED ADDRESS: ";
                cin.ignore();
                getLn(data.at(acct).address);
                break;
            }
            case 3: //Edit City, State, Zip Code
            {
                cout << "CURRENT CITY, STATE, ZIP: " << data.at(acct).ctStZp << endl;
                cout << "UPDATED CITY, STATE, ZIP: ";
                cin.ignore();
                getLn(data.at(acct).ctStZp);
                break;
            }
            case 4: //Edit Telephone Number
            {
                cout << "CURRENT TELEPHONE NUMBER: " << data.at(acct).tel << endl;
                cout << "UPDATED TELEPHONE NUMBER: ";
                cin.ignore();
                getLn(data.at(acct).tel);
                break;
            }
            case 5: //Edit Account Balance
            {
                cout << "CURRENT BALANCE: " << data.at(acct).balance << endl;
                cout << "UPDATED BALANCE: ";
                cin >> data.at(acct).balance;
                break;
            }
            case 6: //Edit Date of Last Payment
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

//Find Account
//Find a Customer Account in the data vector
//Input:
//The data vector for Customer Accounts

void fdAcct(const vector<CstAcct> &data){
    bool results = false; //Whether or not the value was found
    string key = ""; //The value to search for

    cout << "SEARCH TERM: ";
    cin.ignore(); //Clear input
    getLn(key); //Read in the key
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        if(toupper(data.at(i).name).find(toupper(key)) != string::npos){ //If the key is found
            results = true; //Set found
            cout << "(" << i + 1 << ") " << data.at(i).name << endl; //Display the account name and position
        }
    }
    if(!results){ //If not found
        cout << "NOT FOUND!" << endl;
    }
}

//To Upper
//Change a string to all upper case letters.
//Input:
//str
//The string to change to upper case
//Output:
//The string all uppercased

string toupper(const string &str){
    string r = ""; //The return string

    for(int i = 0; i < str.size(); ++i){ //For the entire input string
        r += toupper(str.at(i)); //Concatinate the uppercase character at i in str to r
    }

    return r;
}

