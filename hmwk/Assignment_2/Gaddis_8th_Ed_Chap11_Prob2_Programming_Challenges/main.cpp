/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Display data on two movies. Information taken from imdb.com
 * Created on October 3, 2016
 */

//System Libraries
#include <iostream> //I/O

//User Libraries
#include "MovData.h" //Movie Data
using namespace std;

//Function Prototypes
void prntMov(const MovData&);

//Begin Execution

int main(int argc, char** argv){
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
    prntMov(a); //Output the first Movie Data object
    cout << endl;
    prntMov(b); //Output the second Movie Data object

    //Exit
    return 0;
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
    cout << "NET PROFIT: " << static_cast<int>(data.revenue) - static_cast<int>(data.cost) << " USD" << endl; //Output Net Profits
}
