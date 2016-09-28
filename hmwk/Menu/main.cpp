/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Create a template menu program for displaying homework solutions
 * Created on September 21, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
using namespace std;

//Global Constants

//Function Prototypes

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int choice = 0;

    do{ //While not exiting
        do{ //While choice is not negative
            //Output Choices
            cout << setw(5) << "(1) " << "SOLUTION 1" << endl;
            cout << setw(5) << "(0) " << "EXIT" << endl;
            //Display Prompt and Read Input
            cout << "> ";
            cin >> choice;
        }while(choice < 0);
        switch(choice){ //Select function based on choice
            case 1:
            {
                cout << "SOLUTION 1" << endl;
                cout << endl;
                break;
            }
        }
    } while(choice);


    //Exit
    return 0;
}
