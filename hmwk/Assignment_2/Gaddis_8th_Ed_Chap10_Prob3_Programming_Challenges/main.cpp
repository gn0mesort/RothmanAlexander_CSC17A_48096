/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Calculate sales data for different divisions of a company
 * Created on October 3, 2016
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include "SaleDat.h"
using namespace std;

void init(SaleDat&);
void total(SaleDat&);
void mean(SaleDat&);
void prntDat(const SaleDat&);

int main(int argc, char** argv){
    SaleDat north = {"North"},
    east = {"East"},
    south = {"South"},
    west = {"West"};

    srand(static_cast<int>(time(0)));
    init(north);
    init(east);
    init(south);
    init(west);

    total(north);
    mean(north);
    total(east);
    mean(east);
    total(south);
    mean(south);
    total(west);
    mean(west);

    prntDat(north);
    cout << endl;
    prntDat(east);
    cout << endl;
    prntDat(south);
    cout << endl;
    prntDat(west);

    return 0;
}

void init(SaleDat &data){
    //Generate Data Randomly
    //    for(int i = 0; i < SaleDat::SIZE; ++i){
    //        data.sales[i] = rand() % 1000000;
    //    }

    //Input Data Manually
    int input = 0;
    for(int i = 0; i < SaleDat::SIZE; ++i){
        do{
            cout << "ENTER THE SALES FOR " << data.divName << " IN Q" << i + 1 << ": ";
            cin >> input;
        } while(input < 0);
        data.sales[i] = input;
    }
    cout << endl;

    //Always
    data.tSales = 0;
    data.avSales = 0.0f;
}

void total(SaleDat &data){
    for(int i = 0; i < SaleDat::SIZE; ++i){
        data.tSales += data.sales[i];
    }
}

void mean(SaleDat &data){
    if(data.tSales <= 0){
        total(data);
    }
    data.avSales = data.tSales / static_cast<float>(SaleDat::SIZE);
}

void prntDat(const SaleDat &data){
    cout << "DIVISION NAME: " << data.divName << endl;
    for(int i = 0; i < SaleDat::SIZE; ++i){
        cout << "Q" << i + 1 << " SALES: $" << setw(7) << data.sales[i] << endl;
    }
    cout << "TOTAL ANNUAL SALES: $" << data.tSales << endl;
    cout << fixed << setprecision(2);
    cout << "AVERAGE QUARTERLY SALES: $" << data.avSales << endl;
}