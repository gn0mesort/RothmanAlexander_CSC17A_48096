/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Review 1 Menu Program
 * Created on September 21, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <string> //String type and functions
#include <fstream> //File I/O
#include <cstdlib> //C Standard Library
#include <ctime> //Date and Time
using namespace std;

//Global Constants
const unsigned char SIZE_W = 30; //The width of the 2D character array in this solution 8


//Function Prototypes
int dspMenu(int);
//Solution Functions
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
//Other Functions
unsigned char getDays(unsigned char, short);
char getClr();
char getChar();
bool fndMix(char, char);
float celsius(float);
void newData();
void rdData(char[][SIZE_W], unsigned char);
void pData(char[][SIZE_W], unsigned char);
void getRprt(char[][SIZE_W], unsigned char);
void fllRprt(char[][SIZE_W], unsigned char);
string toupper(const string&);
void rdData(string[], unsigned char);
void mkIndx(unsigned char[], unsigned char);
int binSrch(const string[], const unsigned char[], unsigned char, const string&);
void sort(string[], unsigned char[], unsigned char);


//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int choice = 0;

    do{ //While not exiting
        choice = dspMenu(10); //Display menu and read the user input
        switch(choice){ //Select function based on choice
            case 1:
            {
                cout << "CELSIUS TO FAHRENHEIT CONVERSION" << endl;
                solve1();
                cout << endl;
                break;
            }
            case 2:
            {
                cout << "DOLLARS TO YEN AND EUROS" << endl;
                solve2();
                cout << endl;
                break;
            }
            case 3:
            {
                cout << "DAYS IN A MONTH BY YEAR" << endl;
                solve3();
                cout << endl;
                break;
            }
            case 4:
            {
                cout << "FIND THE RECTANGLE WITH THE GREATEST AREA" << endl;
                solve4();
                cout << endl;
                break;
            }
            case 5:
            {
                cout << "PRIMARY COLOR MIXING" << endl;
                solve5();
                cout << endl;
                break;
            }
            case 6:
            {
                cout << "POPULATION GROWTH" << endl;
                solve6();
                cout << endl;
                break;
            }
            case 7:
            {
                cout << "CELSIUS TEMPERATURE TABLE" << endl;
                solve7();
                cout << endl;
            }
            case 8:
            {
                cout << "RAIN OR SHINE WEATHER REPORT" << endl;
                solve8();
                cout << endl;
            }
            case 9:
            {
                cout << "LOTTERY WINNERS" << endl;
                solve9();
                cout << endl;
            }
            case 10:
            {
                cout << "BINARY SEARCH FOR A STRING" << endl;
                solve10();
                cout << endl;
            }

        }
    } while(choice);


    //Exit
    return 0;
}


//Display Menu
//Function to display the actual menu text and read user input for menu
//processing.
//Input:
//count
//The number of solutions
//Output:
//An integer representing the user's choice of menu item

int dspMenu(int count){
    int choice = 0; //The user's choice of function or 0 to exit

    do{ //While choice is invalid
        cout << "Solutions:" << endl;
        cout << "(1) Gaddis 8th Ed Chap3 Prob12" << endl;
        cout << "(2) Gaddis 8th Ed Chap3 Prob13" << endl;
        cout << "(3) Gaddis 8th Ed Chap4 Prob10" << endl;
        cout << "(4) Gaddis 8th Ed Chap4 Prob4" << endl;
        cout << "(5) Gaddis 8th Ed Chap4 Prob8" << endl;
        cout << "(6) Gaddis 8th Ed Chap5 Prob11" << endl;
        cout << "(7) Gaddis 8th Ed Chap6 Prob7" << endl;
        cout << "(8) Gaddis 8th Ed Chap7 Prob6" << endl;
        cout << "(9) Gaddis 8th Ed Chap8 Prob2" << endl;
        cout << "(10) Gaddis 8th Ed Chap8 Prob7" << endl;
        cout << "(0) Exit" << endl;
        cout << "> ";
        cin >> choice; //Read in choice
    } while(choice < 0 || choice > count);

    return choice;
}

void solve1(){
    //Declaration and Initialization
    const float CNV_F = 9.0f / 5.0f; //Celsius to Fahrenheit conversion factor
    float cTemp = 0.0f, //The temperature in Celsius. Input by the user
            fTemp = 0.0f; //The temperature in Fahrenheit

    //Read Input
    cout << "INPUT A TEMPERATURE IN CELSIUS: ";
    cin >> cTemp; //Read in cTemp

    //Calculate Output
    fTemp = (CNV_F * cTemp) + 32; //Calculate fTemp using cTemp and CNV_F

    //Output Data
    cout << fixed << setprecision(2); //Format output to 2 decimal places
    //Output cTemp and fTemp
    cout << setw(24) << "TEMPERATURE CELSIUS: " << cTemp << endl;
    cout << setw(24) << "TEMPERATURE FAHRENHEIT: " << fTemp << endl;
}

void solve2(){
    //Declaration and Initialization
    const float CNV_JPY = 102.28f, //Number of YEN in a DOLLAR as of 11:40AM 9/17/2016
            CNV_EUR = 0.9f; //Number of EUROs in a DOLLAR as of 11:41AM 9/17/2016
    float dollars = 0.0f; //The value to convert

    //Read Input
    cout << "INPUT A VALUE TO CONVERT: $";
    cin >> dollars;

    //Calculate and Output Data
    cout << fixed << setprecision(2); //Format output to 2 decimal places
    cout << setw(15) << dollars << " USD" << endl; //Output DOLLARS
    cout << setw(15) << dollars * CNV_JPY << " JPY" << endl; //Output YEN
    cout << setw(15) << dollars * CNV_EUR << " EUR" << endl; //Output EUROS
}

void solve3(){
    //Declaration and Initialization
    unsigned short month = 0, //Number of the month to get days for
            year = 0; //The year to find the month in

    //Read and Validate input
    //Read in month
    do{
        cout << "ENTER A MONTH (1-12): ";
        cin >> month;
    } while(month < 1 || month > 12); //Must be 1 to 12
    //Read in year
    do{
        cout << "ENTER A YEAR: ";
        cin >> year;
    } while(year < 1); //Must not be 0 or negative

    //Calculate and Output Data
    cout << static_cast<int>(getDays(month, year)) << " days" << endl;
}

void solve4(){
    //Declaration and Initialization
    short length1 = 0, //Length of the first rectangle
            length2 = 0, //Length of the second rectangle
            width1 = 0, //Width of the first rectangle
            width2 = 0, //Width of the second rectangle
            area1 = 0, //Area of the first rectangle
            area2 = 0; //Area of the second rectangle

    //Read input
    //Read in length1
    cout << "ENTER THE LENGTH OF THE FIRST RECTANGLE: ";
    cin >> length1;
    //Read in width1
    cout << "ENTER THE WIDTH OF THE FIRST RECTANGLE: ";
    cin >> width1;
    //Read in length2
    cout << "ENTER THE LENGTH OF THE SECOND RECTANGLE: ";
    cin >> length2;
    //Read in width2
    cout << "ENTER THE WIDTH OF THE SECOND RECTANGLE: ";
    cin >> width2;

    //Calculate Areas
    area1 = length1 * width1; //Calculate area1
    area2 = length2 * width2; //Calculate area2

    //Calculate and Output the larger rectangle
    if(area1 > area2){ //Rectangle 1 is bigger
        cout << "THE FIRST RECTANGLE HAS A LARGER AREA!" << endl;
    }
    else if(area2 > area1){ //Rectangle 2 is bigger
        cout << "THE SECOND RECTANGLE HAS A LARGER AREA!" << endl;
    }
    else{ //Rectangle 1 is equal to Rectangle 2
        cout << "THE RECTANGLES ARE EQUAL!" << endl;
    }
}

void solve5(){
    //Declaration and Initialization
    char color1 = 0, //The first color to mix
            color2 = 0; //The second color to mix

    do{
        color1 = getClr(); //Read in color1
        color2 = getClr(); //Read in color2
    } while(!fndMix(color1, color2)); //If the mix isn't valid loop

}

void solve6(){
    //Declaration and Initialization
    unsigned short initPop = 0, //The initial population size
            days = 0; //The number of days to multiply over
    short pIncr = 0; //The percentage to increase by
    float total = 0.0f; //The total population

    //Read and validate input
    do{ //While the initial population is less than 2
        cout << "ENTER THE INITIAL POPULATION: ";
        cin >> initPop; //Read in initPop
    } while(initPop < 2);
    do{ //While the number of days is less than 1
        cout << "HOW MANY DAYS WILL THEY MULTIPLY FOR: ";
        cin >> days; //Read in days
    } while(days < 1);
    do{ //While the percentage increase is less than 0
        cout << "WHAT IS THE AVERAGE INCREASE PER DAY (AS A PERCENTAGE): ";
        cin >> pIncr; //Read in pIncr
    } while(pIncr < 0);

    //Calculate and output data
    total = initPop; //Set total to the initial size
    for(int i = 0; i < days; ++i){ //For every day in days
        total += (total * pIncr / 100.0f); //Add the total multiplied by the percentage increase to the total
        cout << "POPULATION ON DAY " << (i + 1) << ": "; //Output the day's population
        cout << static_cast<int>(total) << endl; //Drop fractional creatures
    }

}

void solve7(){
    //Calculate and Output data
    cout << fixed << setprecision(2); //Format output to 2 decimal places
    for(int i = 0; i < 21; ++i){ //For values 0 to 20
        cout << setw(6) << i << " Fahrenheit = " << setw(6) << celsius(i); //Calculate and output temperature in Celsius
        cout << " Celsius" << endl;
    }
}

void solve8(){
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
}

void solve9(){
    //Declaration and Initialization
    const unsigned int SIZE = 10; //The size of the lucky number array
    unsigned int nums[SIZE] = {13579, 26791, 26792, 33445, 55555, 62483, 77777,
                               79422, 85647, 93121}; //Initialized lucky number array
    unsigned int winner = 0; //The winning number to be read in
    bool match = false; //Whether or not the winning number is found

    //Read Input
    do{ //While input isn't valid
        cout << "ENTER THIS WEEK'S WINNING NUMBER: ";
        cin >> winner; //Read in winner
    } while(winner > 99999 || winner < 10000);

    //Calculate Output
    for(int i = 0; i < SIZE; ++i){ //Iterate across nums
        if(nums[i] == winner){ //If the winning number is found
            match = true;
        }
    }

    //Output Data
    cout << "YOU " << (match ? "WON!" : "LOST.") << endl;
}

void solve10(){
    //Declaration and Initialization
    const unsigned char SIZE = 20; //The size of the names array
    char loc = 0; //The location at which the key was wound
    unsigned char index[SIZE]; //An indexing array for names
    string names[SIZE]; //An array containing name data read from names.txt
    string key; //The key to search for

    srand(static_cast<int>(time(0))); //Seed PRNG
    rdData(names, SIZE); //Read data into names
    mkIndx(index, SIZE); //Fill the indexing array
    key = names[rand() % SIZE]; //Pick a random name as a key

    //Calculate and Output data
    cout << "SEARCHING FOR: " << key << endl;
    cout << "SORTING...";
    sort(names, index, SIZE); //Sort the indexing array based on names
    cout << "DONE!" << endl;
    cout << "SEARCHING...";
    loc = binSrch(names, index, SIZE, key); //Get the location of the key using a binary search
    cout << "DONE!" << endl;
    if(loc > -1){ //If found
        cout << key << " FOUND AT " << static_cast<int>(loc) << endl;
        cout << "names[" << static_cast<int>(loc) << "] = ";
        cout << names[index[loc]] << endl;
    }
    else{ //If not found
        cout << key << " NOT FOUND!" << endl;
    }
    cout << endl << endl;
    for(int i = 0; i < SIZE; ++i){ //Iterate across and display names
        cout << i << ":" << names[index[i]] << endl;
    }
}

///Get Days
//Get the number of days in the month for the given month of the given year.
//Handles leap years.
//Input:
//month
//The month to get the number of days for.
//year
//The year to get the days of the given month for.
//Output:
//The number of days in the given month of the given year.

unsigned char getDays(unsigned char month, short year){
    unsigned char r = 0; //Return value

    //Assign correct number of days to r
    switch(month){
        case 1: //January
        {
            r = 31;
            break;
        }
        case 2: //February
        {
            //Handle Leap years
            if(year % 100 == 0 && year % 400 == 0){ //If year is divisible by 100 and 400
                r = 29;
            }
            else if(year % 4 == 0){ //If year is divisible by 4
                r = 29;
            }
            else{ //Otherwise
                r = 28;
            }
            break;
        }
        case 3: //March
        {
            r = 31;
            break;
        }
        case 4: //April
        {
            r = 30;
            break;
        }
        case 5: //May
        {
            r = 31;
            break;
        }
        case 6: //June
        {
            r = 30;
            break;
        }
        case 7: //July
        {
            r = 31;
            break;
        }
        case 8: //August
        {
            r = 31;
            break;
        }
        case 9: //September
        {
            r = 30;
            break;
        }
        case 10: //October
        {
            r = 31;
            break;
        }
        case 11: //November
        {
            r = 30;
            break;
        }
        case 12: //December
        {
            r = 31;
            break;
        }
        default: //Default Case
        {
            r = 0;
        }
    }

    return r;
}

//Find Mix
//Finds and outputs the mix of two colors. If the mix is valid this function
//returns true. Otherwise it returns false.
//Input:
//color1
//The first color to mix
//color2
//The second color to mix
//Output:
//Whether or not a valid mix was produced

bool fndMix(char color1, char color2){
    bool r = false; //Return value

    if(color1 == color2){ //If colors are the same no mix is possible
        cout << "BOTH COLORS ARE THE SAME. NO MIX!" << endl;
        r = false;
    }
    else if((color1 == 'R' && color2 == 'Y') || //If the mix result is orange
            (color1 == 'Y' && color2 == 'R')){
        cout << "MIX RESULT: ORANGE!" << endl;
        r = true;
    }
    else if((color1 == 'R' && color2 == 'B') || //If the mix result is purple
            (color1 == 'B' && color2 == 'R')){
        cout << "MIX RESULT: PURPLE!" << endl;
        r = true;
    }
    else if((color1 == 'B' && color2 == 'Y') || //If the mix result is green
            (color1 == 'Y' && color2 == 'B')){
        cout << "MIX RESULT: GREEN!" << endl;
        r = true;
    }
    else{ //Otherwise something went wrong
        cout << "INVALID INPUTS" << endl;
        r = false;
    }

    return r;
}

//Get Color
//Get a valid color value from standard input.
//Output:
//A valid color character ('R', 'Y' or 'B') representing a primary color

char getClr(){
    char color = 0; //Color to return

    //Read in color and validate it
    do{
        cout << "ENTER A PRIMARY COLOR (RED, YELLOW, BLUE): ";
        color = getChar(); //Read in color
    } while(!(color == 'R' || color == 'Y' || color == 'B')); //while color is not valid

    //This function worked perfectly fine without this return statement @_@;
    return color;
}

//Get Character
//Get a single character input from standard in and return it as uppercase.
//Handles and discards any extra input.
//Output:
//The first character of the input in its upper case form.

char getChar(){
    string input; //Temporary string value
    cin >> input; //Read the whole input line
    return toupper(input.at(0)); //Return the first character
}

//Celsius
//Convert a Fahrenheit temperature to a Celsius temperature
//Input:
//tempF
//The temperature in Fahrenheit to convert to Celsius
//Output:
//The input temperature converted to Celsius

float celsius(float tempF){
    return (tempF - 32) * (5.0f / 9.0f);
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

//Binary Search
//Preform a binary search on an array of strings for the given key
//Input:
//data
//The underlying data array
//index
//The indexing array for data (sorted)
//size
//The size of the data and indexing arrays
//key
//The string to search for
//Output:
//An integer representing the position of the key in the indexing array

int binSrch(const string data[], const unsigned char index[],
            unsigned char size, const string &key){
    char first = 0, //The lower bound
            last = size - 1, //The upper bound
            middle, //The midpoint of the bounds
            pos = -1; //The position of the key
    bool found = false; //If the key has been found or not

    while(!found && first <= last){ //While the key hasn't been found and first is not greater than last
        middle = (first + last) / 2; //calculate midpoint
        if(data[index[middle]].compare(key) == 0){ //If the key is found
            found = true;
            pos = middle; //the key was found at the current midpoint
        }
        else if(data[index[middle]].compare(key) > 0){ //If the current value is greater than the key
            last = middle - 1;
        }
        else{ //If the current value is less than the key
            first = middle + 1;
        }
    }

    return pos;
}

//Make Index
//Fills an indexing array for a given size
//Input:
//index
//The array to fill
//size
//The size of the array
//Output:
//The filled indexing array

void mkIndx(unsigned char index[], unsigned char size){
    for(int i = 0; i < size; ++i){ //Iterate across index
        index[i] = i; //Fill each element with i
    }
}

//Sort
//Sorts an indexing array based on string values found in a data array using the
//gnome sort algorithm
//Input:
//data
//The string data array
//index
//The indexing array for data to be sorted
//size
//The size of both arrays
//Output:
//The sorted indexing array

void sort(string data[], unsigned char index[], unsigned char size){
    unsigned char pos = 0; //The initial position

    while(pos < size){ //While unsorted
        if(pos == 0 || data[index[pos]].compare(data[index[pos - 1]]) > 0){ //If the postion is 0 or the current value is greater than the last value
            ++pos; //Move up one position
        }
        else{ //Otherwise
            //Swap the current position and the last position
            index[pos] = index[pos] ^ index[pos - 1];
            index[pos - 1] = index[pos] ^ index[pos - 1];
            index[pos] = index[pos] ^ index[pos - 1];
            pos = pos - 1; //Move back one position
        }
    }
}

//To Upper Case
//Convert a string to upper case characters
//Input:
//str
//The string to convert
//Output:
//The input string with all upper case characters

string toupper(const string &str){
    string r = ""; //The return value

    for(int i = 0; i < str.size(); ++i){ //Iterate across str
        r += toupper(str.at(i)); //add the upper case value of str at i to r
    }

    return r;
}

//Read Data
//Read name data from a file into an array
//Input:
//names
//The array to fill with data
//size
//The size of names
//Output:
//The filled array

void rdData(string names[], unsigned char size){
    ifstream input; //Input stream
    string tmp; //Temporary string storage

    input.open("names.txt"); //Open input stream
    if(input.good()){ //If the input stream is good
        for(int i = 0; i < size; ++i){ //Iterate across names
            getline(input, tmp); //Get the next line of the file
            names[i] = toupper(tmp); //uppercase and store the value in names
        }
    }
    input.close(); //Close input stream
}