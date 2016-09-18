/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@studnet.rcc.edu>
 * Purpose: Rain or Shine
 * Created on September 17, 2016
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

const unsigned char SIZE_W = 30;

void newData();
void rdData(char[][SIZE_W], unsigned char);
void pData(char[][SIZE_W], unsigned char);
void getRprt(char[][SIZE_W], unsigned char);
void fllRprt(char[][SIZE_W], unsigned char);

int main(int argc, char** argv){
    const unsigned char SIZE = 3;
    char input = 0;
    char data[SIZE][SIZE_W];

    srand(static_cast<int>(time(0)));

    do{
        cout << "GENERATE NEW DATA? (Y/N) ";
        cin >> input;
    } while(!(toupper(input) == 'Y' || toupper(input) == 'N'));
    if(toupper(input) == 'Y'){
        newData();
    }
    rdData(data, SIZE);
    cout << "REPORT:" << endl;
    pData(data, SIZE);
    cout << "JUNE:" << endl;
    getRprt(data, 0);
    cout << "JULY:" << endl;
    getRprt(data, 1);
    cout << "AUGUST:" << endl;
    getRprt(data, 2);
    cout << "3 MONTH PERIOD:" << endl;
    fllRprt(data, SIZE);
    return 0;
}

void newData(){
    char days[3] = {'R', 'C', 'S'};
    ofstream output;

    output.open("RainOrShine.txt");
    for(int i = 0; i < 90; ++i){
        output << days[rand() % 3] << endl;
    }
    output.close();
}

void fllRprt(char data[][SIZE_W], unsigned char size){
    unsigned char rCount = 0,
            cCount = 0,
            sCount = 0,
            high = 0;
    unsigned char rDays[size];
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < SIZE_W; ++j){
            if(data[i][j] == 'R'){
                ++rCount;
            }
            else if(data[i][j] == 'C'){
                ++cCount;
            }
            else if(data[i][j] == 'S'){
                ++sCount;
            }
            else{
                cout << "Invalid Data at [" << i << "][" << j << "]" << endl;
            }
        }
        rDays[i] = rCount;
        rCount = 0;
    }
    rCount = 0;
    for(int i = 0; i < size; ++i){
        if(rDays[i] > rDays[high]){
            high = i;
        }
        rCount += rDays[i];
    }
    cout << setw(20) << "RAINY DAYS: " << static_cast<int>(rCount) << endl;
    cout << setw(20) << "CLOUDY DAYS: " << static_cast<int>(cCount) << endl;
    cout << setw(20) << "SUNNY DAYS: " << static_cast<int>(sCount) << endl;
    cout << setw(20) << "HIGHEST RAIN: ";
    if(high == 0){
        cout << "JUNE" << endl;
    }
    else if(high == 1){
        cout << "JULY" << endl;
    }
    else{
        cout << "AUGUST" << endl;
    }

}

void getRprt(char data[][SIZE_W], unsigned char month){
    unsigned char rCount = 0,
            cCount = 0,
            sCount = 0;
    for(int i = 0; i < SIZE_W; ++i){
        if(data[month][i] == 'R'){
            ++rCount;
        }
        else if(data[month][i] == 'C'){
            ++cCount;
        }
        else if(data[month][i] == 'S'){
            ++sCount;
        }
        else{
            cout << "Invalid Data at [" << month << "][" << i << "]" << endl;
        }
    }
    cout << setw(20) << "RAINY DAYS: " << static_cast<int>(rCount) << endl;
    cout << setw(20) << "CLOUDY DAYS: " << static_cast<int>(cCount) << endl;
    cout << setw(20) << "SUNNY DAYS: " << static_cast<int>(sCount) << endl;

}

void pData(char data[][SIZE_W], unsigned char size){
    for(int i = 0; i < size; ++i){
        if(i == 0){
            cout << setw(10) << "JUNE: ";
        }
        else if(i == 1){
            cout << setw(10) << "JULY: ";
        }
        else{
            cout << setw(10) << "AUGUST: ";
        }
        for(int j = 0; j < SIZE_W; ++j){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

void rdData(char data[][SIZE_W], unsigned char size){
    ifstream input;

    input.open("RainOrShine.txt");
    if(input.good()){
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < SIZE_W; ++j){
                input >> data[i][j];
            }
        }
    }
    input.close();
}

