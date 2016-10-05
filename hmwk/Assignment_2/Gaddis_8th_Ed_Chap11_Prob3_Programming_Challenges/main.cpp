/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Calculate sales data for different divisions of a company
 * Created on October 3, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
//Needed for random generation
//#include <cstdlib> //C Standard Library
//#include <ctime> //Date and Time

//User Libraries
#include "SaleDat.h" //Sales Data
using namespace std;

//Function Prototypes
void init(SaleDat&);
void total(SaleDat&);
void mean(SaleDat&);
void prntDat(const SaleDat&);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    SaleDat north = {"North"}, //Data for the north division
    east = {"East"}, //Data for the east division
    south = {"South"}, //Data for the south division
    west = {"West"}; //Data for the west division

    //Needed for random generation
    //srand(static_cast<int>(time(0)));
    init(north); //Initialize data for the north division
    init(east); //Initialize data for the east division
    init(south); //Initialize data for the south division
    init(west); //Initialize data for the west division

    //Calculate
    //Calculate north division total and mean
    total(north);
    mean(north);
    //Calculate east division total and mean
    total(east);
    mean(east);
    //Calculate south division total and mean
    total(south);
    mean(south);
    //Calculate west division total and mean
    total(west);
    mean(west);

    //Output data
    prntDat(north); //Output data for the north division
    cout << endl;
    prntDat(east); //Output data for the east division
    cout << endl;
    prntDat(south); //Output data for the south division
    cout << endl;
    prntDat(west); //Output data for the west division

    //Exit
    return 0;
}

//Initialize
//Initialize a Sales Data object
//Input:
//data
//The data object to initialize
//Output:
//The data object after initialization

void init(SaleDat &data){
    //Generate Data Randomly
    //    for(int i = 0; i < SaleDat::SIZE; ++i){ //For every element of the sales array
    //        data.sales[i] = rand() % 1000000; //Set it to a random value
    //    }

    //Input Data Manually
    int input = 0; //The input value
    for(int i = 0; i < SaleDat::SIZE; ++i){ //For every element of the sales array
        do{ //While the input is invalid
            cout << "ENTER THE SALES FOR " << data.divName << " IN Q" << i + 1 << ": ";
            cin >> input; //Read in input
        } while(input < 0);
        data.sales[i] = input; //Set the current sales value to input
    }
    cout << endl;

    //Always
    data.tSales = 0; //Initialize total
    data.avSales = 0.0f; //Initialize average
}

//Total
//Calculate the total sales for a Sales Data object
//Input:
//data
//The object to calculate the total of
//Output:
//The input object with the total set

void total(SaleDat &data){
    for(int i = 0; i < SaleDat::SIZE; ++i){ //For every sale in the Sales Data object
        data.tSales += data.sales[i];
    }
}

//Mean
//Calculate the average sale for a Sales Data object
//Input:
//data
//The object to calculate the average of
//Output:
//The input object with the average set

void mean(SaleDat &data){
    if(data.tSales <= 0){ //If the object hasn't been totaled
        total(data); //Total the object
    }
    data.avSales = data.tSales / static_cast<float>(SaleDat::SIZE); //Calculate the average
}

//Print Data
//Output the values in a Sales Data object
//Input:
//data
//The object to display

void prntDat(const SaleDat &data){
    cout << "DIVISION NAME: " << data.divName << endl; //Output division name
    for(int i = 0; i < SaleDat::SIZE; ++i){ //For every element of the sales array
        cout << "Q" << i + 1 << " SALES: $" << setw(7) << data.sales[i] << endl; //Output quarterly sales
    }
    cout << "TOTAL ANNUAL SALES: $" << data.tSales << endl; //Output total sales
    cout << fixed << setprecision(2);
    cout << "AVERAGE QUARTERLY SALES: $" << data.avSales << endl; //Output average sales
}