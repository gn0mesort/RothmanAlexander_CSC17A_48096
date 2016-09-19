/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Days in a month
 * Created on September 17, 2016
 */

//System Libraries
#include <cstdlib> //C Standard Library
#include <iostream> //I/O
using namespace std;

//Function Prototypes
unsigned char getDays(unsigned char, short);

//Begin Execution
int main(int argc, char** argv){
    //Declaration and Initialization
    unsigned short month = 0, //Number of the month to get days for
            year = 0; //The year to find the month in
    
    //Read and Validate input
    //Read in month
    do{
        cout << "ENTER A MONTH (1-12): ";
        cin >> month;
    } while(month < 1 || month > 12); //Must be 1 to 12
    //Read in year
    do{
        cout << "ENTER A YEAR: ";
        cin >> year;
    } while(year < 1); //Must not be 0 or negative
    
    //Calculate and Output Data
    cout << static_cast<int>(getDays(month, year)) << " days" << endl;

    //Exit
    return 0;
}


///Get Days
//Get the number of days in the month for the given month of the given year.
//Handles leap years.
//Input:
//month
//The month to get the number of days for.
//year
//The year to get the days of the given month for.
//Output:
//The number of days in the given month of the given year.
unsigned char getDays(unsigned char month, short year){
    unsigned char r = 0; //Return value

    //Assign correct number of days to r
    switch(month){
        case 1: //January
        {
            r = 31;
            break;
        }
        case 2: //February
        {
            //Handle Leap years
            if(year % 100 == 0 && year % 400 == 0){ //If year is divisible by 100 and 400
                r = 29;
            }
            else if(year % 4 == 0){ //If year is divisible by 4
                r = 29;
            }
            else{ //Otherwise
                r = 28;
            }
            break;
        }
        case 3: //March
        {
            r = 31;
            break;
        }
        case 4: //April
        {
            r = 30;
            break;
        }
        case 5: //May
        {
            r = 31;
            break;
        }
        case 6: //June
        {
            r = 30;
            break;
        }
        case 7: //July
        {
            r = 31;
            break;
        }
        case 8: //August
        {
            r = 31;
            break;
        }
        case 9: //September
        {
            r = 30;
            break;
        }
        case 10: //October
        {
            r = 31;
            break;
        }
        case 11: //November
        {
            r = 30;
            break;
        }
        case 12: //December
        {
            r = 31;
            break;
        }
        default: //Default Case
        {
            r = 0;
        }
    }

    return r;
}

