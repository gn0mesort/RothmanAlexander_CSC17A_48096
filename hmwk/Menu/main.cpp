/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Create a template menu program for displaying homework solutions
 * Created on September 21, 2016
 */

//System Libraries
#include <iostream>
using namespace std;

//Global Constants

//Function Prototypes
int dspMenu();

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int choice = 0;

    do{ //While not exiting
        choice = dspMenu(); //Display menu and read the user input
        switch(choice){ //Select function based on choice
            case 1:
            {
                cout << "SOLUTION 1" << endl;
                cout << endl;
            }
        }
    } while(choice);


    //Exit
    return 0;
}


//Display Menu
//Function to display the actual menu text and read user input for menu
//processing.
//Output:
//An integer representing the user's choice of menu item

int dspMenu(){
    int choice = 0; //The user's choice of function or 0 to exit

    do{ //While choice is invalid
        cout << "Solutions:" << endl;
        cout << "(1) Solution 1" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> choice; //Read in choice
    } while(choice < 0 && choice > 2);

    return choice;
}
