/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Create a template menu program for displaying homework solutions
 * Created on September 21, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <cstdlib> //C Standard Library
#include <ctime> //Date and Time
#include <string> //String type and functions
#include <vector> //Vector collections

//User Libraries
#include "Array.h" //Array object from https://github.com/ml1150258/LehrMark_CSC17a_48096/blob/master/Class/MarkSort_Structure/Array.h
#include "CstAcct.h" //Customer Accounts object
#include "MovData.h" //Movie Data object
#include "Player.h" //Player object
#include "SaleDat.h" //Sales Data object
#include "Speaker.h" //Speaker object
#include "Weather.h" //Weather object and Month enumeration
using namespace std;

//Global Constants

//Function Prototypes
void solve1();
void solve2();
void solve3();
void solve4();
void solve5();
void solve6();
void solve7();
void solve8();
void solve9();
void solve10();
void solve11();
//Helper Functions
void prntMov(const MovData&);
void prntMovB(const MovData&);
void init(SaleDat&);
void total(SaleDat&);
void mean(SaleDat&);
void prntDat(const SaleDat&);
string month(unsigned char);
string mStr(Month);
void getLn(string&);
void crAcct(vector<CstAcct>&);
void rmAcct(vector<CstAcct>&);
void dsAcct(const vector<CstAcct>&);
void edAcct(vector<CstAcct>&);
void fdAcct(const vector<CstAcct>&);
string toupper(const string&);
void crSpkr(vector<Speaker>&);
void rmSpkr(vector<Speaker>&);
void dsSpkr(const vector<Speaker>&);
void edSpkr(vector<Speaker>&);
void fdSpkr(const vector<Speaker>&);
void fillArr(Array&, unsigned char);
void prntArr(const Array&, int);
void sort(Array&);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int choice = 0;

    do{ //While not exiting
        do{ //While choice is not negative
            //Output Choices
            cout << setw(5) << "(1) " << "Chapter 11 Problem 1" << endl;
            cout << setw(5) << "(2) " << "Chapter 11 Problem 2" << endl;
            cout << setw(5) << "(3) " << "Chapter 11 Problem 3" << endl;
            cout << setw(5) << "(4) " << "Chapter 11 Problem 4" << endl;
            cout << setw(5) << "(5) " << "Chapter 11 Problem 5" << endl;
            cout << setw(5) << "(6) " << "Chapter 11 Problem 6" << endl;
            cout << setw(5) << "(7) " << "Chapter 11 Problem 7" << endl;
            cout << setw(5) << "(8) " << "Chapter 11 Problem 8" << endl;
            cout << setw(5) << "(9) " << "Chapter 11 Problem 9" << endl;
            cout << setw(5) << "(10) " << "Chapter 11 Problem 10" << endl;
            cout << setw(5) << "(11) " << "Mark Sort with Structures and Pointer Notation" << endl;
            cout << setw(5) << "(0) " << "EXIT" << endl;
            //Display Prompt and Read Input
            cout << "> ";
            cin >> choice;
        } while(choice < 0);
        cin.ignore();
        switch(choice){ //Select function based on choice
            case 1:
            {
                cout << "CHAPTER 11 PROBLEM 1" << endl;
                solve1();
                cout << endl;
                break;
            }
            case 2:
            {
                cout << "CHAPTER 11 PROBLEM 2" << endl;
                solve2();
                cout << endl;
                break;
            }
            case 3:
            {
                cout << "CHAPTER 11 PROBLEM 3" << endl;
                solve3();
                cout << endl;
                break;
            }
            case 4:
            {
                cout << "CHAPTER 11 PROBLEM 4" << endl;
                solve4();
                cout << endl;
                break;
            }
            case 5:
            {
                cout << "CHAPTER 11 PROBLEM 5" << endl;
                solve5();
                cout << endl;
                break;
            }
            case 6:
            {
                cout << "CHAPTER 11 PROBLEM 6" << endl;
                solve6();
                cout << endl;
                break;
            }
            case 7:
            {
                cout << "CHAPTER 11 PROBLEM 7" << endl;
                solve7();
                cout << endl;
                break;
            }
            case 8:
            {
                cout << "CHAPTER 11 PROBLEM 8" << endl;
                solve8();
                cout << endl;
                break;
            }
            case 9:
            {
                cout << "CHAPTER 11 PROBLEM 9" << endl;
                solve9();
                cout << endl;
                break;
            }
            case 10:
            {
                cout << "CHAPTER 11 PROBLEM 10" << endl;
                solve10();
                cout << endl;
                break;
            }
            case 11:
            {
                cout << "MARK SORT WITH STRUCTURES AND POINTER NOTATION" << endl;
                solve11();
                cout << endl;
                break;
            }
        }
    } while(choice);


    //Exit
    return 0;
}

void solve1(){
    //Declaration and Initialization
    MovData a, //The first Movie Data object
            b; //The second Movie Data object
    //Initialize Movie Data
    a.title = "Blade Runner";
    a.dirctr = "Ridley Scott";
    a.yearRel = 1982;
    a.runTime = 117;
    b.title = "Ghost in the Shell";
    b.dirctr = "Mamoru Oshii";
    b.yearRel = 1995;
    b.runTime = 83;

    //Output
    prntMov(a); //Output the first Movie Data object
    cout << endl;
    prntMov(b); //Output the second Movie Data object
}

void solve2(){
    //Declaration and Initialization
    MovData a, //The first Movie Data object
            b; //The second Movie Data object
    //Initialize Movie Data
    a.title = "Blade Runner";
    a.dirctr = "Ridley Scott";
    a.yearRel = 1982;
    a.runTime = 117;
    a.cost = 28000000;
    a.revenue = 27580111;
    b.title = "Ghost in the Shell";
    b.dirctr = "Mamoru Oshii";
    b.yearRel = 1995;
    b.runTime = 83;
    b.cost = 5712639; //Estimated value of 600,000,000 JPY in 1996 when the movie was released in the USA
    b.revenue = 1099298; //Worldwide gross from 1995 + US gross from 1996

    //Output
    prntMovB(a); //Output the first Movie Data object
    cout << endl;
    prntMovB(b); //Output the second Movie Data object
}

void solve3(){
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
}

void solve4(){
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
}

void solve5(){
    //Declaration and Initialization
    const unsigned char SIZE = 12; //The number of months to collect data on
    Month yrHigh = JANUARY, //The month with the highest temperature
            yrLow = JANUARY; //The month with the lowest temperature
    Weather data[SIZE]; //The Weather objects to store data for every month
    Weather output; //A Weather object to store output data

    //Needed for random generation of data
    //    srand(static_cast<int>(time(0))); //Seed PRNG

    //Input Data Manually
    for(Month i = JANUARY; i < SIZE; i = static_cast<Month>(i + 1)){ //For every element of the data array
        cout << mStr(i) << ": " << endl; //Output the month
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
    //   for(Month i = JANUARY; i < SIZE; i = static_cast<Month>(i + 1)){ //For every element of the data array
    //        data[i].tRain = rand() % 6; //Generate random total rainfall
    //        data[i].hTemp = (rand() % 140) - 100; //Generate random high temp
    //        data[i].lTemp = (rand() % static_cast<int>(data[i].hTemp)) - 100; //Generate random low temp
    //        data[i].avTemp = (rand() % 140) - 100; //Generate random average temp
    //        cout << mStr(i) << ":" << endl; //Output month
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


    for(Month i = JANUARY; i < SIZE; i = static_cast<Month>(i + 1)){
        output.tRain += data[i].tRain; //Total the rainfall for the year
        output.avTemp += data[i].avTemp; //Total the average temperature
        if(data[i].hTemp >= output.hTemp || i == JANUARY){ //If the high temp for the current month is greater than the last month
            output.hTemp = data[i].hTemp; //Set the overall high temperature
            yrHigh = i; //Set the month
        }
        if(data[i].lTemp <= output.lTemp || i == JANUARY){ //If the low temp for the current month is less than the last month
            output.lTemp = data[i].lTemp; //Set the overall low temperature
            yrLow = i; //Set the month
        }
    }
    output.tRain /= SIZE; //Calculate average total rainfall
    output.avTemp /= SIZE; //Calculate average average temperature

    //Output
    cout << fixed << setprecision(2); //Format Output
    cout << "YEARLY AVERAGE RAINFALL: " << output.tRain << endl; //Output average rainfall
    cout << "YEARLY HIGH TEMPERATURE: " << output.hTemp << ", " << mStr(yrHigh) << endl; //Output overall high temp
    cout << "YEARLY LOW TEMPERATURE: " << output.lTemp << ", " << mStr(yrLow) << endl; //Output overall low temp
    cout << "YEARLY AVERAGE TEMPERATURE: " << output.avTemp << endl; //Output overall average temp
}

void solve6(){
    //Declaration and Initialization
    const unsigned char SIZE = 12; //The number of players
    unsigned char mvp = 0; //The position of the MVP in the team array
    unsigned short total = 0; //The total score of the team
    Player team[SIZE]; //The array of Players to store data in

    //Input
    for(int i = 0; i < SIZE; ++i){ //For every Player on the team
        short input = 0; //Store input
        cout << "ENTER PLAYER #" << i + 1 << "'S NAME: ";
        if(i > 0){ //If this isn't the first Player
            cin.ignore(); //Clear input before getline
        }
        getline(cin, team[i].name); //Read in the Player's name
        do{ //While the input value is negative
            cout << "ENTER " << team[i].name << "'S NUMBER: ";
            cin >> input; //Read input
        } while(input < 0);
        team[i].number = input; //Set the Player's number to input
        do{ //While the input value is negative
            cout << "ENTER " << team[i].name << "'S SCORE: ";
            cin >> input; //Read input
        } while(input < 0);
        team[i].score = input; //Set the Player's score to input
    }
    cout << endl;

    //Output Table
    cout << setw(10) << "NAME" << setw(10) << "NUMBER" << setw(10) << "SCORE" << endl; //Output header
    for(int i = 0; i < SIZE; ++i){ //For every Player on the team
        cout << setw(10) << team[i].name << setw(10) << team[i].number << setw(10) << team[i].score << endl; //Output row
        total += team[i].score; //Total the score
        if(team[i].score >= team[mvp].score){ //If the current Player's score is greater than the MVP's score
            mvp = i; //The current player is the MVP
        }
    }
    cout << "TOTAL SCORE: " << total << endl; //Output total score
    cout << "MVP: " << "#" << team[mvp].number << " " << team[mvp].name << " WITH " << team[mvp].score << " POINTS" << endl; //Output MVP
}

void solve7(){
    //Declaration and Initialization
    vector<CstAcct> data; //The vector containing customer account data
    unsigned short input = 0; //Input value

    cout << "Welcome!" << endl;
    do{ //While not quitting
        //Output Menu
        cout << "MENU" << endl;
        cout << "(1) Display Accounts" << endl;
        cout << "(2) Create Account" << endl;
        cout << "(3) Remove Account" << endl;
        cout << "(4) Edit Account" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input; //Read input

        switch(input){ //Select option based on input
            case 1:
            {
                cout << "DISPLAY ACCOUNTS" << endl;
                dsAcct(data); //Account display processing
                break;
            }
            case 2:
            {
                cout << "CREATE NEW ACCOUNT" << endl;
                crAcct(data); //Account creation processing
                break;
            }
            case 3:
            {
                cout << "REMOVE ACCOUNT" << endl;
                rmAcct(data); //Account removal processing
                break;
            }
            case 4:
            {
                cout << "EDIT ACCOUNT" << endl;
                edAcct(data); //Account editing processing
                break;
            }
        }
        cout << endl;
    } while(input > 0);
}

void solve8(){
    //Declaration and Initialization
    vector<CstAcct> data; //The vector containing customer account data
    unsigned short input = 0; //Input value

    cout << "Welcome!" << endl;
    do{ //While not quitting
        //Output Menu
        cout << "MENU" << endl;
        cout << "(1) Display Accounts" << endl;
        cout << "(2) Create Account" << endl;
        cout << "(3) Remove Account" << endl;
        cout << "(4) Edit Account" << endl;
        cout << "(5) Find Account" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input; //Read input

        switch(input){ //Select option based on input
            case 1:
            {
                cout << "DISPLAY ACCOUNTS" << endl;
                dsAcct(data); //Account display processing
                break;
            }
            case 2:
            {
                cout << "CREATE NEW ACCOUNT" << endl;
                crAcct(data); //Account creation processing
                break;
            }
            case 3:
            {
                cout << "REMOVE ACCOUNT" << endl;
                rmAcct(data); //Account removal processing
                break;
            }
            case 4:
            {
                cout << "EDIT ACCOUNT" << endl;
                edAcct(data); //Account editing processing
                break;
            }
            case 5:
            {
                cout << "FIND ACCOUNT" << endl;
                fdAcct(data); //Account search processing
                break;
            }
        }
        cout << endl;
    } while(input > 0);
}

void solve9(){
    //Declaration and Initialization
    vector<Speaker> data; //The vector containing speaker data
    unsigned short input = 0; //Input value

    cout << "Welcome!" << endl;
    do{ //While not quitting
        //Output Menu
        cout << "MENU" << endl;
        cout << "(1) Display Speakers" << endl;
        cout << "(2) Create Speaker" << endl;
        cout << "(3) Remove Speaker" << endl;
        cout << "(4) Edit Speaker" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input; //Read input

        switch(input){ //Select option based on input
            case 1:
            {
                cout << "DISPLAY SPEAKERS" << endl;
                dsSpkr(data); //Speaker display processing
                break;
            }
            case 2:
            {
                cout << "CREATE NEW SPEAKER" << endl;
                crSpkr(data); //Speaker creation processing
                break;
            }
            case 3:
            {
                cout << "REMOVE SPEAKER" << endl;
                rmSpkr(data); //Speaker removal processing
                break;
            }
            case 4:
            {
                cout << "EDIT SPEAKER" << endl;
                edSpkr(data); //Speaker editing processing
                break;
            }
        }
        cout << endl;
    } while(input > 0);
}

void solve10(){
    //Declaration and Initialization
    vector<Speaker> data; //The vector containing speaker data
    unsigned short input = 0; //Input value

    cout << "Welcome!" << endl;
    do{ //While not quitting
        //Output Menu
        cout << "MENU" << endl;
        cout << "(1) Display Speakers" << endl;
        cout << "(2) Create Speaker" << endl;
        cout << "(3) Remove Speaker" << endl;
        cout << "(4) Edit Speaker" << endl;
        cout << "(5) Find Speaker" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input; //Read input

        switch(input){ //Select option based on input
            case 1:
            {
                cout << "DISPLAY SPEAKERS" << endl;
                dsSpkr(data); //Speaker display processing
                break;
            }
            case 2:
            {
                cout << "CREATE NEW SPEAKER" << endl;
                crSpkr(data); //Speaker creation processing
                break;
            }
            case 3:
            {
                cout << "REMOVE SPEAKER" << endl;
                rmSpkr(data); //Speaker removal processing
                break;
            }
            case 4:
            {
                cout << "EDIT SPEAKER" << endl;
                edSpkr(data); //Speaker editing processing
                break;
            }
            case 5:
            {
                cout << "FIND ACCOUNT" << endl;
                fdSpkr(data); //Speaker search processing
                break;
            }
        }
        cout << endl;
    } while(input > 0);
}

void solve11(){
    //Declaration and Initialization
    const unsigned char SIZE = 100; //Size of the array
    unsigned char perLine = 10; //Number of values to print per line
    Array arr; //The array object to sort

    srand(static_cast<unsigned int>(time(0))); //Seed PRNG
    fillArr(arr, SIZE); //Allocate the array and fill it with random values

    //Output
    cout << "INITIAL ARRAY:" << endl;
    prntArr(arr, perLine); //Print the initial array
    cout << endl;
    sort(arr); //Sort the array
    cout << "SORTED ARRAY:" << endl;
    prntArr(arr, perLine); //Print the sorted array

    //Delete the array
    delete [] arr.data;
}

//Print Movie
//Print a Movie Data object
//Input:
//data
//The Movie Data object to print

void prntMov(const MovData &data){
    cout << "TITLE: " << data.title << endl; //Output Title
    cout << "DIRECTOR: " << data.dirctr << endl; //Output Director
    cout << "YEAR RELEASED: " << data.yearRel << endl; //Output the Year of Release
    cout << "RUN TIME: " << data.runTime << " MINUTES" << endl; //Output the Run Time in minutes
}

//Print Movie
//Print a Movie Data object
//Renamed here to avoid a naming conflict
//Input:
//data
//The Movie Data object to print

void prntMovB(const MovData &data){
    cout << "TITLE: " << data.title << endl; //Output Title
    cout << "DIRECTOR: " << data.dirctr << endl; //Output Director
    cout << "YEAR RELEASED: " << data.yearRel << endl; //Output the Year of Release
    cout << "RUN TIME: " << data.runTime << " MINUTES" << endl; //Output the Run Time in minutes
    cout << "NET PROFIT: " << static_cast<int>(data.revenue) - static_cast<int>(data.cost) << " USD" << endl; //Output Net Profits
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

//Month String
//Return a string representing the input Month
//Input:
//m
//A Month to convert to a string
//Output:
//A string representing the correct Month

string mStr(Month m){
    string r = ""; //The return string

    switch(m){ //Set r based on Month input
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
        default: //Handle errors
        {
            r = "INVALID MONTH";
        }
    }

    return r;
}

//Get Line
//Get a line of text from standard input. Shortens the normal getline function
//Input:
//str
//The string to load data into
//Output:
//The input string loaded with data

void getLn(string &str){
    getline(cin, str, '\n');
}

//Create Account
//Create a Customer Account and add it to the data vector
//Input:
//data
//The data vector for Customer Accounts
//Output:
//The updated data vector

void crAcct(vector<CstAcct> &data){
    CstAcct acct; //The new user account
    time_t rawtime; //The current time

    cout << "Enter the name of the account holder: ";
    cin.ignore(); //Clear input
    getLn(acct.name); //Read in the account name
    cout << "Enter the street address of the account holder: ";
    getLn(acct.address); //Read in the address
    cout << "Enter the City, State, and Zip Code of the account holder: ";
    getLn(acct.ctStZp); //Read in the city, state, and zip code
    cout << "Enter the telephone number of the account holder: ";
    getLn(acct.tel); //Read in the telephone number
    do{ //While the account balance is negative
        cout << "Enter the starting balance of the account: ";
        cin >> acct.balance; //Read in the account balance
    } while(acct.balance < 0);
    time(&rawtime); //Fill rawtime with the current time
    acct.lastPay = asctime(localtime(&rawtime)); //Convert the current time to a string

    data.push_back(acct); //Add the new account to the data vector
}

//Remove Account
//Remove a Customer Account from the data vector
//Input:
//data
//The data vector for Customer Accounts
//Output:
//The updated data vector

void rmAcct(vector<CstAcct> &data){
    unsigned short input = 0; //The input value

    //Display Remove Account menu
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "(" << i + 1 << ") " << data.at(i).name << endl; //Output the account name
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> input; //Read input
    if(input > 0){ //If not exiting
        data.erase(data.begin() + (input - 1)); //Erase the selected element
    }
}

//Display Accounts
//Display Customer Accounts found in the data vector
//Input:
//The data vector for Customer Accounts

void dsAcct(const vector<CstAcct> &data){
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "NAME: " << data.at(i).name << endl; //Output the account name
        cout << "STREET ADDRESS: " << data.at(i).address << endl; //Output the account address
        cout << "CITY, STATE, ZIP: " << data.at(i).ctStZp << endl; //Output the account city state and zip code
        cout << "TELEPHONE NUMBER: " << data.at(i).tel << endl; //Output the account telephone number
        cout << "BALANCE: " << data.at(i).balance << endl; //Output the account balance
        cout << "LAST PAID: " << data.at(i).lastPay << endl; //Output the date of last payment
        if(i + 1 < data.size()){ //Formatting
            cout << endl;
        }
    }
}

//Edit Account
//Edit a user account
//Input:
//data
//The data vector for Customer accounts
//Output:
//The updated data vector

void edAcct(vector<CstAcct> &data){
    unsigned short acct = 0, //The account to edit
            input = 0; //The input value for the account editing menu

    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "(" << i + 1 << ") " << data.at(i).name << endl; //Create a menu of Customer Accounts to choose from
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> acct; //Read in the selected account
    if(acct > 0){ //If not exiting
        --acct; //Set account correctly for a 0 based vector
        //Display Editing Menu
        cout << "(1) NAME" << endl;
        cout << "(2) STREET ADDRESS" << endl;
        cout << "(3) CITY, STATE, ZIP" << endl;
        cout << "(4) TELEPHONE NUMBER" << endl;
        cout << "(5) BALANCE" << endl;
        cout << "(6) DATE OF LAST PAYMENT" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input; //Read in input
        switch(input){ //Handle input from editing menu
            case 1: //Edit Name
            {
                cout << "CURRENT NAME: " << data.at(acct).name << endl;
                cout << "UPDATED NAME: ";
                cin.ignore();
                getLn(data.at(acct).name);
                break;
            }
            case 2: //Edit Address
            {
                cout << "CURRENT ADDRESS: " << data.at(acct).address << endl;
                cout << "UPDATED ADDRESS: ";
                cin.ignore();
                getLn(data.at(acct).address);
                break;
            }
            case 3: //Edit City, State, Zip Code
            {
                cout << "CURRENT CITY, STATE, ZIP: " << data.at(acct).ctStZp << endl;
                cout << "UPDATED CITY, STATE, ZIP: ";
                cin.ignore();
                getLn(data.at(acct).ctStZp);
                break;
            }
            case 4: //Edit Telephone Number
            {
                cout << "CURRENT TELEPHONE NUMBER: " << data.at(acct).tel << endl;
                cout << "UPDATED TELEPHONE NUMBER: ";
                cin.ignore();
                getLn(data.at(acct).tel);
                break;
            }
            case 5: //Edit Account Balance
            {
                cout << "CURRENT BALANCE: " << data.at(acct).balance << endl;
                cout << "UPDATED BALANCE: ";
                cin >> data.at(acct).balance;
                break;
            }
            case 6: //Edit Date of Last Payment
            {
                cout << "CURRENT DATE OF LAST PAYMENT: " << data.at(acct).lastPay << endl;
                cout << "UPDATED DATE OF LAST PAYMENT: ";
                cin.ignore();
                getLn(data.at(acct).lastPay);
                break;
            }
        }
    }
}

//Find Account
//Find a Customer Account in the data vector
//Input:
//The data vector for Customer Accounts

void fdAcct(const vector<CstAcct> &data){
    bool results = false; //Whether or not the value was found
    string key = ""; //The value to search for

    cout << "SEARCH TERM: ";
    cin.ignore(); //Clear input
    getLn(key); //Read in the key
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        if(toupper(data.at(i).name).find(toupper(key)) != string::npos){ //If the key is found
            results = true; //Set found
            cout << "(" << i + 1 << ") " << data.at(i).name << endl; //Display the account name and position
        }
    }
    if(!results){ //If not found
        cout << "NOT FOUND!" << endl;
    }
}

//To Upper
//Change a string to all upper case letters.
//Input:
//str
//The string to change to upper case
//Output:
//The string all uppercased

string toupper(const string &str){
    string r = ""; //The return string

    for(int i = 0; i < str.size(); ++i){ //For the entire input string
        r += toupper(str.at(i)); //Concatinate the uppercase character at i in str to r
    }

    return r;
}

//Create Speaker
//Create a Speaker and add it to the data vector
//Input:
//data
//The data vector for Speakers
//Output:
//The updated data vector

void crSpkr(vector<Speaker> &data){
    Speaker speak; //The new Speaker

    cout << "Enter the name of the speaker: ";
    cin.ignore(); //Clear input
    getLn(speak.name); //Read in the Speaker's name
    cout << "Enter speaker's telephone number: ";
    getLn(speak.tel); //Read in the Speaker's telephone number
    cout << "Enter speaker's topic: ";
    getLn(speak.topic); //Read in the Speaker's topic
    do{ //While the Speaker's fee is not negative
        cout << "Enter the speaker's fee: ";
        cin >> speak.fee; //Read in the fee
    } while(speak.fee < 0);

    data.push_back(speak); //Add the new Speaker to the data vector
}

//Remove Speaker
//Remove a Speaker from the data vector
//Input:
//data
//The data vector for Speakers
//Output:
//The updated data vector

void rmSpkr(vector<Speaker> &data){
    unsigned short input = 0; //The input value

    //Display Remove Speaker menu
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "(" << i + 1 << ") " << data.at(i).name << endl; //Output the Speaker's name
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> input; //Read input
    if(input > 0){ //If not exiting
        data.erase(data.begin() + (input - 1)); //Erase the selected element
    }
}

//Display Speakers
//Display Speakers found in the data vector
//Input:
//The data vector for Speakers

void dsSpkr(const vector<Speaker> &data){
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "NAME: " << data.at(i).name << endl; //Output the Speaker's name
        cout << "TELEPHONE NUMBER: " << data.at(i).tel << endl; //Output the Speaker's telephone number
        cout << "TOPIC: " << data.at(i).topic << endl; //Output the Speaker's topic
        cout << "FEE: " << data.at(i).fee << endl; //Output the Speaker's fee
    }
}

//Edit Speaker
//Edit a Speaker
//Input:
//data
//The data vector for Speakers
//Output:
//The updated data vector

void edSpkr(vector<Speaker> &data){
    unsigned short speak = 0, //The Speaker to edit
            input = 0; //The input value for the Speaker editing menu

    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        cout << "(" << i + 1 << ") " << data.at(i).name << endl; //Create a menu of Speakers to choose from
    }
    cout << "(0) Exit" << endl;
    cout << "> ";
    cin >> speak; //Read in the selected Speaker
    if(speak > 0){ //If not exiting
        --speak; //Set speaker correctly for a 0 based vector
        //Display Editing Menu
        cout << "(1) NAME" << endl;
        cout << "(2) TELEPHONE NUMBER" << endl;
        cout << "(3) TOPIC" << endl;
        cout << "(4) FEE" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> input; //Read in input
        switch(input){ //Handle input from editing menu
            case 1: //Edit Name
            {
                cout << "CURRENT NAME: " << data.at(speak).name << endl;
                cout << "UPDATED NAME: ";
                cin.ignore();
                getLn(data.at(speak).name);
                break;
            }
            case 2: //Edit Telephone Number
            {
                cout << "CURRENT TELEPHONE NUMBER: " << data.at(speak).tel << endl;
                cout << "UPDATED TELEPHONE NUMBER: ";
                cin.ignore();
                getLn(data.at(speak).tel);
                break;
            }
            case 3: //Edit Topic
            {
                cout << "CURRENT TOPIC: " << data.at(speak).topic << endl;
                cout << "UPDATED TOPIC: ";
                cin.ignore();
                getLn(data.at(speak).topic);
                break;
            }
            case 4: //Edit Fee
            {
                cout << "CURRENT FEE: " << data.at(speak).fee << endl;
                cout << "UPDATED FEE: ";
                cin >> data.at(speak).fee;
                break;
            }
        }
    }
}

//Find Speaker
//Find a Speaker in the data vector
//Input:
//The data vector for Speakers

void fdSpkr(const vector<Speaker> &data){
    bool results = false; //Whether or not the value was found
    string key = ""; //The value to search for

    cout << "SEARCH TERM: ";
    cin.ignore(); //Clear input
    getLn(key); //Read in the key
    for(int i = 0; i < data.size(); ++i){ //For the entire data vector
        if(toupper(data.at(i).topic).find(toupper(key)) != string::npos){ //If the key is found
            results = true;
            cout << "(" << i + 1 << ") " << data.at(i).name << " : " << data.at(i).topic << endl; //Display the speaker name and position
        }
    }
    if(!results){ //If not found
        cout << "NOT FOUND!" << endl;
    }
}

//Print Array
//Print an Array object with the given number of values per line
//Input:
//arr
//The Array to print values from
//perLine
//The number of values to print per line

void prntArr(const Array &arr, int perLine){
    for(int i = 0; i < arr.size; ++i){ //For every element of the array
        cout << *(arr.data + i) << " "; //Output the array value at i
        if(!((i + 1) % perLine)){ //If the next line is over the perLine value
            cout << endl;
        }
    }
}

//Fill Array
//Allocate and fill an Array object
//arr
//The Array to allocate and fill
//size
//The size of the array that should be allocated
//Output:
//The input Array object allocated and filled

void fillArr(Array &arr, unsigned char size){
    arr.data = new int[size]; //Allocate the underlying array
    arr.size = size; //Set the array size
    for(int i = 0; i < arr.size; ++i){ //For every value in the array
        *(arr.data + i) = (rand() % 90) + 10; //Set the value at i to a random number between 10 and 99
    }
}

//Sort
//Sort an Array object using the MarkSort algorithm
//Input:
//arr
//The Array to sort
//Output:
//The sorted Array

void sort(Array &arr){
    for(int i = 0; i < arr.size - 1; ++i){ //For every element of the array
        for(int j = i + 1; j < arr.size; ++j){ //For every element of the array starting at i + 1
            if(*(arr.data + i) > *(arr.data + j)){ //If the value at i is greater than the value at j
                //Swap
                *(arr.data + i) = *(arr.data + i) ^ *(arr.data + j);
                *(arr.data + j) = *(arr.data + i) ^ *(arr.data + j);
                *(arr.data + i) = *(arr.data + i) ^ *(arr.data + j);
            }
        }
    }
}