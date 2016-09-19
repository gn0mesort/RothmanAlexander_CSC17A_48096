/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Days in a month
 * Created on September 17, 2016
 */

#include <cstdlib>
#include <iostream>
using namespace std;

unsigned char getDays(unsigned char, short);

int main(int argc, char** argv){
    unsigned short month = 0,
            year = 0;
    do{
        cout << "ENTER A MONTH (1-12): ";
        cin >> month;
    } while(month < 1 || month > 12);
    do{
        cout << "ENTER A YEAR: ";
        cin >> year;
    } while(year < 1);
    cout << static_cast<int>(getDays(month, year)) << " days" << endl;

    return 0;
}

unsigned char getDays(unsigned char month, short year){
    unsigned char r = 0;

    switch(month){
        case 1:
        {
            r = 31;
            break;
        }
        case 2:
        {
            if(year % 100 == 0 && year % 400 == 0){
                r = 29;
            }
            else if(year % 4 == 0){
                r = 29;
            }
            else{
                r = 28;
            }
            break;
        }
        case 3:
        {
            r = 31;
            break;
        }
        case 4:
        {
            r = 30;
            break;
        }
        case 5:
        {
            r = 31;
            break;
        }
        case 6:
        {
            r = 30;
            break;
        }
        case 7:
        {
            r = 31;
            break;
        }
        case 8:
        {
            r = 31;
            break;
        }
        case 9:
        {
            r = 30;
            break;
        }
        case 10:
        {
            r = 31;
            break;
        }
        case 11:
        {
            r = 30;
            break;
        }
        case 12:
        {
            r = 31;
            break;
        }
        default:
        {
            r = 0;
        }
    }

    return r;
}

