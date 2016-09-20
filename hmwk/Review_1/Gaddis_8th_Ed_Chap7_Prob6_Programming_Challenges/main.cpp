/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@studnet.rcc.edu>
 * Purpose: Rain or Shine
 * Created on September 17, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <fstream> //File I/O
#include <cstdlib> //C Standard Library
#include <ctime> //Date and Time
using namespace std;

//Global Constants
const unsigned char SIZE_W = 30; //The width of the 2D character array in this program

//Function Prototypes
void newData();
void rdData(char[][SIZE_W], unsigned char);
void pData(char[][SIZE_W], unsigned char);
void getRprt(char[][SIZE_W], unsigned char);
void fllRprt(char[][SIZE_W], unsigned char);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    const unsigned char SIZE = 3; //The length of the 2D array in this program
    char input = 0; //An input value representing whether or not new data should be generated
    char data[SIZE][SIZE_W]; //2D array holding weather data

    srand(static_cast<int>(time(0))); //Seed PRNG


    do{ //While input is not valid
        cout << "GENERATE NEW DATA? (Y/N) ";
        cin >> input; //Read in input
    } while(!(toupper(input) == 'Y' || toupper(input) == 'N'));
    if(toupper(input) == 'Y'){ //If the input equals Y or y
        newData(); //generate new random weather data
    }

    //Read weather data from RainOrShine.txt
    rdData(data, SIZE);

    //Calculate and Output Data
    cout << "REPORT:" << endl;
    pData(data, SIZE); //Print data as a table
    cout << "JUNE:" << endl;
    getRprt(data, 0); //Get the report for June
    cout << "JULY:" << endl;
    getRprt(data, 1); //Get the report for July
    cout << "AUGUST:" << endl;
    getRprt(data, 2); //Get the report for August
    cout << "3 MONTH PERIOD:" << endl;
    fllRprt(data, SIZE); //Get the full report

    //Exit
    return 0;
}


//New Data
//Generates new random weather data for a 90-day period. Data is written to
//RainOrShine.txt

void newData(){
    char days[3] = {'R', 'C', 'S'}; //Possible values
    ofstream output; //Output stream

    output.open("RainOrShine.txt"); //Open output stream
    if(output.good()){ //If the stream is working
        for(int i = 0; i < 90; ++i){
            output << days[rand() % 3] << endl; //Write a random weather value
        }
    }
    output.close(); //Close the output stream
}


//Full Report
//Generate and print a weather report for a 90-day period
//Input:
//data
//A 2D array containing weather data.
//size
//The size of the first dimension of data

void fllRprt(char data[][SIZE_W], unsigned char size){
    unsigned char rCount = 0, //rainy day count
            cCount = 0, //cloudy day count
            sCount = 0, //sunny day count
            high = 0; //The month with the most rainy days
    unsigned char rDays[size]; //array containing the number of rainy days in each 30-day period

    for(int i = 0; i < size; ++i){ //Iterate across data
        for(int j = 0; j < SIZE_W; ++j){
            if(data[i][j] == 'R'){ //If the day was rainy
                ++rCount;
            }
            else if(data[i][j] == 'C'){ //If the day was cloudy
                ++cCount;
            }
            else if(data[i][j] == 'S'){ //If the day was sunny
                ++sCount;
            }
            else{ //Otherwise
                cout << "Invalid Data at [" << i << "][" << j << "]" << endl;
            }
        }
        rDays[i] = rCount; //Set the current months rainy days to the corresponding array value
        rCount = 0; //Clear the current rainy day count
    }
    rCount = 0; //Clear rCount again
    for(int i = 0; i < size; ++i){ //Iterate across rDays
        if(rDays[i] > rDays[high]){ //If the current month had more rainy days than the last month
            high = i; //Set high to the current month
        }
        rCount += rDays[i]; //Add the current month's rainy days to the total
    }

    //Output Report
    cout << setw(20) << "RAINY DAYS: " << static_cast<int>(rCount) << endl;
    cout << setw(20) << "CLOUDY DAYS: " << static_cast<int>(cCount) << endl;
    cout << setw(20) << "SUNNY DAYS: " << static_cast<int>(sCount) << endl;
    cout << setw(20) << "HIGHEST RAIN: ";
    if(high == 0){ //If June had the most rain
        cout << "JUNE" << endl;
    }
    else if(high == 1){ //If July had the most rain
        cout << "JULY" << endl;
    }
    else{ //If August had the most rain
        cout << "AUGUST" << endl;
    }

}

//Get Report
//Generate and print a report for the given month
//Input:
//A 2D array containing weather data.
//month
//The month to generate a report for. Must be a valid position in data's 1st dimension

void getRprt(char data[][SIZE_W], unsigned char month){
    unsigned char rCount = 0, //Rainy day count
            cCount = 0, //Cloudy day count
            sCount = 0; //Sunny day count

    for(int i = 0; i < SIZE_W; ++i){ //Iterate across data's second dimension only
        if(data[month][i] == 'R'){ //If the day was rainy
            ++rCount;
        }
        else if(data[month][i] == 'C'){ //If the day was cloudy
            ++cCount;
        }
        else if(data[month][i] == 'S'){ //If the day was sunny
            ++sCount;
        }
        else{ //Otherwise
            cout << "Invalid Data at [" << month << "][" << i << "]" << endl;
        }
    }

    //Output Report
    cout << setw(20) << "RAINY DAYS: " << static_cast<int>(rCount) << endl;
    cout << setw(20) << "CLOUDY DAYS: " << static_cast<int>(cCount) << endl;
    cout << setw(20) << "SUNNY DAYS: " << static_cast<int>(sCount) << endl;

}

//Print Data
//Print the program's weather data as a table
//Input:
//data
//A 2D array containing weather data.
//size
//The size of the first dimension of data

void pData(char data[][SIZE_W], unsigned char size){
    for(int i = 0; i < size; ++i){ //Iterate across data
        //Print month names
        if(i == 0){ //If the month is June
            cout << setw(10) << "JUNE: ";
        }
        else if(i == 1){ ///If the month is July
            cout << setw(10) << "JULY: ";
        }
        else{ //If the month is August
            cout << setw(10) << "AUGUST: ";
        }
        //Print weather data
        for(int j = 0; j < SIZE_W; ++j){
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

//Read Data
//Read weather data from a file called RainOrShine.txt in the current
//directory. RainOrShine.txt is expected to be unformatted or use newlines as
//delimiters
//Input:
//data
//A 2D array containing weather data.
//size
//The size of the first dimension of data
//Output:
//The filled data array

void rdData(char data[][SIZE_W], unsigned char size){
    ifstream input; //The input stream

    input.open("RainOrShine.txt"); //Open input stream
    if(input.good()){ //If the stream is good
        for(int i = 0; i < size; ++i){ //Iterate across data
            for(int j = 0; j < SIZE_W; ++j){
                input >> data[i][j]; //Read in data values
            }
        }
    }
    input.close(); //Close input stream
}

