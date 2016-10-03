/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose:
 * Created on October 3, 2016
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Weather.h"
using namespace std;

string month(unsigned char);

int main(int argc, char** argv){
    const unsigned char SIZE = 12;
    unsigned char yrHigh = 0,
            yrLow = 0;
    Weather data[12];
    Weather output;

    srand(static_cast<int>(time(0)));

    //Input Data Manually
    for(int i = 0; i < SIZE; ++i){
        cout << month(i + 1) << ": " << endl;
        do{
            cout << "ENTER THE TOTAL RAINFALL IN INCHES: ";
            cin >> data[i].tRain;
        } while(data[i].tRain < 0.0f);
        do{
            cout << "ENTER THE HIGH TEMPERATURE IN DEGREES FAHRENHEIT (-100 to 140): ";
            cin >> data[i].hTemp;
        } while(data[i].hTemp > 140.0f || data[i].hTemp < -100.0f);
        do{
            cout << "ENTER THE LOW TEMPERATURE IN DEGREES FAHRENHEIT (-100 to 140): ";
            cin >> data[i].lTemp;
        } while(data[i].lTemp > 140.0f || data[i].lTemp < -100.0f);
        do{
            cout << "ENTER THE AVERAGE TEMPERATURE IN DEGREES FAHRENHEIT (-100 to 140): ";
            cin >> data[i].avTemp;
        } while(data[i].avTemp > 140.0f || data[i].avTemp < -100.0f);
    }

    //Generate Random Data
    //Data is not meant to be reasonable for Earth. It's just used to test calculations
    //    for(int i = 0; i < SIZE; ++i){
    //        data[i].tRain = rand() % 6;
    //        data[i].hTemp = (rand() % 140) - 100;
    //        data[i].lTemp = (rand() % static_cast<int>(data[i].hTemp)) - 100;
    //        data[i].avTemp = (rand() % 140) - 100;
    //        cout << month(i + 1) << ":" << endl;
    //        cout << "     TOTAL RAINFALL: " << data[i].tRain << endl;
    //        cout << "     HIGH TEMPERATURE: " << data[i].hTemp << endl;
    //        cout << "     LOW TEMPERATURE: " << data[i].lTemp << endl;
    //        cout << "     AVERAGE TEMPERATURE: " << data[i].avTemp << endl;
    //    }
    //    cout << endl;


    output.hTemp = 0.0f;
    output.lTemp = 0.0f;
    for(int i = 0; i < SIZE; ++i){
        output.tRain += data[i].tRain;
        output.avTemp += data[i].avTemp;
        if(data[i].hTemp >= output.hTemp || i == 0){
            output.hTemp = data[i].hTemp;
            yrHigh = i + 1;
        }
        if(data[i].lTemp <= output.lTemp || i == 0){
            output.lTemp = data[i].lTemp;
            yrLow = i + 1;
        }
    }
    output.tRain /= SIZE;
    output.avTemp /= SIZE;

    cout << fixed << setprecision(2);
    cout << "YEARLY AVERAGE RAINFALL: " << output.tRain << endl;
    cout << "YEARLY HIGH TEMPERATURE: " << output.hTemp << ", " << month(yrHigh) << endl;
    cout << "YEARLY LOW TEMPERATURE: " << output.lTemp << ", " << month(yrLow) << endl;
    cout << "YEARLY AVERAGE TEMPERATURE: " << output.avTemp << endl;

    return 0;
}

string month(unsigned char num){
    string r = "";

    switch(num){
        case 1:
        {
            r = "JANUARY";
            break;
        }
        case 2:
        {
            r = "FEBRUARY";
            break;
        }
        case 3:
        {
            r = "MARCH";
            break;
        }
        case 4:
        {
            r = "APRIL";
            break;
        }
        case 5:
        {
            r = "MAY";
            break;
        }
        case 6:
        {
            r = "JUNE";
            break;
        }
        case 7:
        {
            r = "JULY";
            break;
        }
        case 8:
        {
            r = "AUGUST";
            break;
        }
        case 9:
        {
            r = "SEPTEMBER";
            break;
        }
        case 10:
        {
            r = "OCTOBER";
            break;
        }
        case 11:
        {
            r = "NOVEMBER";
            break;
        }
        case 12:
        {
            r = "DECEMBER";
            break;
        }
        default:
        {
            r = "INVALID MONTH";
        }
    }

    return r;
}



