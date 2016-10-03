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

string mStr(Month);

int main(int argc, char** argv){
    const unsigned char SIZE = 12;
    Month yrHigh = JANUARY,
            yrLow = JANUARY;
    Weather data[12];
    Weather output;

    srand(static_cast<int>(time(0)));

    //Input Data Manually
    for(Month i = JANUARY; i < SIZE; i = static_cast<Month>(i + 1)){
        cout << mStr(i) << ": " << endl;
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
    //    for(Month i = JANUARY; i < SIZE; i = static_cast<Month>(i + 1)){
    //        data[i].tRain = rand() % 6;
    //        data[i].hTemp = (rand() % 140) - 100;
    //        data[i].lTemp = (rand() % static_cast<int>(data[i].hTemp)) - 100;
    //        data[i].avTemp = (rand() % 140) - 100;
    //        cout << mStr(i) << ":" << endl;
    //        cout << "     TOTAL RAINFALL: " << data[i].tRain << endl;
    //        cout << "     HIGH TEMPERATURE: " << data[i].hTemp << endl;
    //        cout << "     LOW TEMPERATURE: " << data[i].lTemp << endl;
    //        cout << "     AVERAGE TEMPERATURE: " << data[i].avTemp << endl;
    //    }
    //    cout << endl;


    output.hTemp = 0.0f;
    output.lTemp = 0.0f;
    for(Month i = JANUARY; i < SIZE; i = static_cast<Month>(i + 1)){
        output.tRain += data[i].tRain;
        output.avTemp += data[i].avTemp;
        if(data[i].hTemp >= output.hTemp || i == JANUARY){
            output.hTemp = data[i].hTemp;
            yrHigh = i;
        }
        if(data[i].lTemp <= output.lTemp || i == JANUARY){
            output.lTemp = data[i].lTemp;
            yrLow = i;
        }
    }
    output.tRain /= SIZE;
    output.avTemp /= SIZE;

    cout << fixed << setprecision(2);
    cout << "YEARLY AVERAGE RAINFALL: " << output.tRain << endl;
    cout << "YEARLY HIGH TEMPERATURE: " << output.hTemp << ", " << mStr(yrHigh) << endl;
    cout << "YEARLY LOW TEMPERATURE: " << output.lTemp << ", " << mStr(yrLow) << endl;
    cout << "YEARLY AVERAGE TEMPERATURE: " << output.avTemp << endl;

    return 0;
}

string mStr(Month m){
    string r = "";

    switch(m){
        case JANUARY:
        {
            r = "JANUARY";
            break;
        }
        case FEBRUARY:
        {
            r = "FEBRUARY";
            break;
        }
        case MARCH:
        {
            r = "MARCH";
            break;
        }
        case APRIL:
        {
            r = "APRIL";
            break;
        }
        case MAY:
        {
            r = "MAY";
            break;
        }
        case JUNE:
        {
            r = "JUNE";
            break;
        }
        case JULY:
        {
            r = "JULY";
            break;
        }
        case AUGUST:
        {
            r = "AUGUST";
            break;
        }
        case SEPTEMBER:
        {
            r = "SEPTEMBER";
            break;
        }
        case OCTOBER:
        {
            r = "OCTOBER";
            break;
        }
        case NOVEMBER:
        {
            r = "NOVEMBER";
            break;
        }
        case DECEMBER:
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



