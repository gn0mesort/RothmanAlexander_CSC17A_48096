/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Use Weather objects to calculate information about a year of weather data
 * Created on October 3, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <string> //String type and functions
//Needed for random generation of data
//#include <cstdlib> //C Standard Library
//#include <ctime> //Date and Time

//User Libraries
#include "Weather.h" //Weather objects
using namespace std;

//Function Prototypes
string month(unsigned char);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    const unsigned char SIZE = 12; //The number of months to collect data on
    unsigned char yrHigh = 0, //The month with the highest temperature
            yrLow = 0; //The month with the lowest temperature
    Weather data[SIZE]; //The Weather objects to store data for every month
    Weather output; //A Weather object to store output data

    //Needed for random generation of data
    //    srand(static_cast<int>(time(0))); //Seed PRNG

    //Input Data Manually
    for(int i = 0; i < SIZE; ++i){ //For every element of the data array
        cout << month(i + 1) << ": " << endl; //Output the month
        do{ //While the total rainfall is negative
            cout << "ENTER THE TOTAL RAINFALL IN INCHES: ";
            cin >> data[i].tRain; //Read in total rainfall
        } while(data[i].tRain < 0.0f);
        do{ //While the high temperature is less than -100.0 F or greater than 140.0 F
            cout << "ENTER THE HIGH TEMPERATURE IN DEGREES FAHRENHEIT (-100 to 140): ";
            cin >> data[i].hTemp; //Read in high temperature
        } while(data[i].hTemp > 140.0f || data[i].hTemp < -100.0f);
        do{ //While the low temperature is less than -100.0 F or greater than 140.0 F
            cout << "ENTER THE LOW TEMPERATURE IN DEGREES FAHRENHEIT (-100 to 140): ";
            cin >> data[i].lTemp; //Read in low temperature
        } while(data[i].lTemp > 140.0f || data[i].lTemp < -100.0f);
        do{ //While the average temperature is less than -100.0 F or greater than 140.0 F
            cout << "ENTER THE AVERAGE TEMPERATURE IN DEGREES FAHRENHEIT (-100 to 140): ";
            cin >> data[i].avTemp; //Read in average temperature
        } while(data[i].avTemp > 140.0f || data[i].avTemp < -100.0f);
    }

    //Generate Random Data
    //Data is not meant to be reasonable for Earth. It's just used to test calculations
    //    for(int i = 0; i < SIZE; ++i){ //For every element of the data array
    //        data[i].tRain = rand() % 6; //Generate random total rainfall
    //        data[i].hTemp = (rand() % 140) - 100; //Generate random high temp
    //        data[i].lTemp = (rand() % static_cast<int>(data[i].hTemp)) - 100; //Generate random low temp
    //        data[i].avTemp = (rand() % 140) - 100; //Generate random average temp
    //        cout << month(i + 1) << ":" << endl; //Output month
    //        cout << "     TOTAL RAINFALL: " << data[i].tRain << endl; //Output total rainfall
    //        cout << "     HIGH TEMPERATURE: " << data[i].hTemp << endl; //Output high temp
    //        cout << "     LOW TEMPERATURE: " << data[i].lTemp << endl; //Output low temp
    //        cout << "     AVERAGE TEMPERATURE: " << data[i].avTemp << endl;
    //    }
    //    cout << endl;

    //Initialize Output object
    output.tRain = 0.0f;
    output.avTemp = 0.0f;
    output.hTemp = 0.0f;
    output.lTemp = 0.0f;

    //Calculate Output
    for(int i = 0; i < SIZE; ++i){ //For every element of the data array
        output.tRain += data[i].tRain; //Total the rainfall for the year
        output.avTemp += data[i].avTemp; //Total the average temperature
        if(data[i].hTemp >= output.hTemp || i == 0){ //If the high temp for the current month is greater than the last month
            output.hTemp = data[i].hTemp; //Set the overall high temperature
            yrHigh = i + 1; //Set the month
        }
        if(data[i].lTemp <= output.lTemp || i == 0){ //If the low temp for the current month is less than the last month
            output.lTemp = data[i].lTemp; //Set the overall low temperature
            yrLow = i + 1; //Set the month
        }
    }
    output.tRain /= SIZE; //Calculate average total rainfall
    output.avTemp /= SIZE; //Calculate average average temperature

    //Output
    cout << fixed << setprecision(2); //Format Output
    cout << "YEARLY AVERAGE RAINFALL: " << output.tRain << endl; //Output average rainfall
    cout << "YEARLY HIGH TEMPERATURE: " << output.hTemp << ", " << month(yrHigh) << endl; //Output overall high temp
    cout << "YEARLY LOW TEMPERATURE: " << output.lTemp << ", " << month(yrLow) << endl; //Output overall low temp
    cout << "YEARLY AVERAGE TEMPERATURE: " << output.avTemp << endl; //Output overall average temp

    //Exit
    return 0;
}

//Month
//Return a string containing the name of a month based on an integer input
//Input:
//num
//The number of the month to output 1-12
//Output:
//A string representing the correct month

string month(unsigned char num){
    string r = ""; //The return string

    switch(num){ //Set r based on the number input
        case 1: //January
        {
            r = "JANUARY";
            break;
        }
        case 2: //February
        {
            r = "FEBRUARY";
            break;
        }
        case 3: //March
        {
            r = "MARCH";
            break;
        }
        case 4: //April
        {
            r = "APRIL";
            break;
        }
        case 5: //May
        {
            r = "MAY";
            break;
        }
        case 6: //June
        {
            r = "JUNE";
            break;
        }
        case 7: //July
        {
            r = "JULY";
            break;
        }
        case 8: //August
        {
            r = "AUGUST";
            break;
        }
        case 9: //September
        {
            r = "SEPTEMBER";
            break;
        }
        case 10: //October
        {
            r = "OCTOBER";
            break;
        }
        case 11: //November
        {
            r = "NOVEMBER";
            break;
        }
        case 12: //December
        {
            r = "DECEMBER";
            break;
        }
        default: //In case of errors
        {
            r = "INVALID MONTH";
        }
    }

    return r;
}



