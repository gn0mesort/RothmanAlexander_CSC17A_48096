/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Create a template menu program for displaying homework solutions
 * Created on September 21, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <string> //String type and functions
#include <fstream> //File I/O
#include <vector> //Vector collections

//User Libraries
#include "SaleDat.h" //SaleDat type
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

unsigned int length(const char*);
void reverse(const char*, unsigned int);
unsigned int count(const char*, unsigned int);
unsigned int count(const string&);
float avgAlph(const char*, unsigned int, unsigned int);
float avgAlph(const string&, unsigned int);
bool isVowel(char);
unsigned int vowels(const char*, unsigned int);
unsigned int cnsnnts(const char*, unsigned int);
unsigned int strSum(const string&);
unsigned char high(const string&);
unsigned char low(const string&);
int toInt(unsigned char);
void getData(SaleDat&);
void save(const char*, SaleDat&);
void load(const char*, vector<SaleDat>&);
void clear(const char*);
void toFile(const char*, int*, int);
void toArray(const char*, int*, int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int choice = 0;

    do{ //While not exiting
        do{ //While choice is not negative
            //Output Choices
            cout << setw(5) << "(1) " << "Chapter 10 Problem 1" << endl;
            cout << setw(5) << "(2) " << "Chapter 10 Problem 2" << endl;
            cout << setw(5) << "(3) " << "Chapter 10 Problem 4" << endl;
            cout << setw(5) << "(4) " << "Chapter 10 Problem 6" << endl;
            cout << setw(5) << "(5) " << "Chapter 10 Problem 8" << endl;
            cout << setw(5) << "(6) " << "Chapter 12 Problem 1" << endl;
            cout << setw(5) << "(7) " << "Chapter 12 Problem 2" << endl;
            cout << setw(5) << "(8) " << "Chapter 12 Problem 7" << endl;
            cout << setw(5) << "(9) " << "Chapter 12 Problem 8" << endl;
            cout << setw(5) << "(10) " << "Chapter 12 Problem 11" << endl;
            cout << setw(5) << "(0) " << "EXIT" << endl;
            //Display Prompt and Read Input
            cout << "> ";
            cin >> choice;
        } while(choice < 0);
        cin.ignore();
        switch(choice){ //Select function based on choice
            case 1:
            {
                cout << "CHAPTER 10 PROBLEM 1" << endl;
                solve1();
                cout << endl;
                break;
            }
            case 2:
            {
                cout << "CHAPTER 10 PROBLEM 2" << endl;
                solve2();
                cout << endl;
                break;
            }
            case 3:
            {
                cout << "CHAPTER 10 PROBLEM 4" << endl;
                solve3();
                cout << endl;
                break;
            }
            case 4:
            {
                cout << "CHAPTER 10 PROBLEM 6" << endl;
                solve4();
                cout << endl;
                break;
            }
            case 5:
            {
                cout << "CHAPTER 10 PROBLEM 8" << endl;
                solve5();
                cout << endl;
                break;
            }
            case 6:
            {
                cout << "CHAPTER 12 PROBLEM 1" << endl;
                solve6();
                cout << endl;
                break;
            }
            case 7:
            {
                cout << "CHAPTER 12 PROBLEM 2" << endl;
                solve7();
                cout << endl;
                break;
            }
            case 8:
            {
                cout << "CHAPTER 12 PROBLEM 7" << endl;
                solve8();
                cout << endl;
                break;
            }
            case 9:
            {
                cout << "CHAPTER 12 PROBLEM 8" << endl;
                solve9();
                cout << endl;
                break;
            }
            case 10:
            {
                cout << "CHAPTER 12 PROBLEM 11" << endl;
                solve10();
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
    string input = ""; //The string to measure

    //Input
    cout << "ENTER A STRING: ";
    getline(cin, input); //Read in input

    //Output
    cout << "LENGTH: " << length(input.c_str()) << endl; //Output length
    if(length(input.c_str()) == input.size()){ //If the calculated length is the same as input.size()
        cout << "CHECK!" << endl; //Output that they match
    }
}

void solve2(){
    //Declaration and Initialization
    string str = ""; //The string to reverse

    //Input
    cout << "ENTER A STRING: ";
    getline(cin, str); //Read in str

    //Output
    cout << "REVERSED STRING: ";
    reverse(str.c_str(), str.size()); //Output reversed string

}

void solve3(){
    //Declaration and Initialization
    ifstream in; //File input stream
    string text = ""; //The current line of text
    unsigned int lines = 0; //The number of lines read


    in.open("data_10_4.txt"); //Open file for reading
    cout << fixed << setprecision(2); //Format output
    cout << "Line#" << endl; //Line number heading
    while(getline(in, text)){ //While there are more lines to read
        cout << setw(5) << lines++ << " " << text << endl; //Output line number
        //Calculate and output data
        cout << "      " << "WORD COUNT AS STRING:  " << setw(6) << count(text) << endl;
        cout << "      " << "WORD COUNT AS CSTRING: " << setw(6) << count(text.c_str(), text.size()) << endl;
        cout << "      " << "AVERAGE LETTERS AS STRING:   " << setw(6) << avgAlph(text, count(text)) << endl;
        cout << "      " << "AVERAGE LETTERS AS CSTRING:  " << setw(6);
        cout << avgAlph(text.c_str(), text.size(), count(text.c_str(), text.size())) << endl;
        cout << endl;
    }
    in.close(); //Close file
}

void solve4(){
    //Declaration and Initialization
    bool quit = false; //If quitting
    string str = ""; //The string to test

    //Input str
    cout << "ENTER THE INITIAL TEST STRING" << endl;
    cout << "> ";
    getline(cin, str); //Read in str
    do{ //While not quitting
        string input = ""; //The current user input
        unsigned char select = 0; //The input as a number

        //Output Menu
        cout << "STRING: " << str << endl;
        cout << "MENU:" << endl;
        cout << "(1) Count the number of vowels in the string" << endl;
        cout << "(2) Count the number of consonants in the string" << endl;
        cout << "(3) Count both the vowels and the consonants in the string" << endl;
        cout << "(4) Enter another string" << endl;
        cout << "(0) Exit" << endl;

        do{ //While input is invalid
            cout << "> ";
            getline(cin, input); //Read in input
            select = input[0] - 48; //Calculate selection
        } while(select > 4 && select < 0);

        switch(select){ //Preform selected choice
            case 1: //Count vowels
            {
                cout << "VOWELS: " << vowels(str.c_str(), str.size()) << endl;
                break;
            }
            case 2: //Count consonants
            {
                cout << "CONSONANTS: " << cnsnnts(str.c_str(), str.size()) << endl;
                break;
            }
            case 3: //Count both
            {
                cout << "VOWELS AND CONSONANTS: ";
                cout << vowels(str.c_str(), str.size()) + cnsnnts(str.c_str(), str.size()) << endl;
                break;
            }
            case 4: //Edit string
            {
                cout << "ENTER THE NEW STRING" << endl;
                cout << "> ";
                getline(cin, str);
                break;
            }
            case 0: //Quit
            {
                quit = true;
                break;
            }
        }
    } while(!quit);
}

void solve5(){
    //Declaration and Initialization
    string str = ""; //The string to sum

    //Input
    cout << "ENTER A STRING TO SUM: ";
    getline(cin, str); //Read in str

    //Output
    cout << "SUM: " << strSum(str) << endl; //Output sum
    cout << "HIGHEST DIGIT: " << toInt(high(str)) << endl; //Output highest digit
    cout << "LOWEST DIGIT: " << toInt(low(str)) << endl; //Output lowest digit
}

void solve6(){
    //Declaration and Initialization
    const char *END = "**END OF FILE**"; //A CString to output at the end of a short file

    int count = 0; //The number of lines read
    string path = ""; //The path to read from
    ifstream in; //The input file stream

    //Input
    cout << "ENTER A FILE NAME: ";
    getline(cin, path); //Read in path


    //Read and output file
    in.open(path.c_str()); //Open file
    if(in.is_open()){ //If the file opened properly
        string data; //The current line
        while(getline(in, data) && count < 10){ //While the stream is still good and count is less than 10
            cout << data << endl; //Output the current line
            ++count; //Increment count
        }
        if(count < 10){ //If the count is less than 10 at the end of the file
            cout << END << endl; //Output END
        }
    }
    in.close(); //Close the file
}

void solve7(){
    //Declaration and Initialization
    int count = 0; //The number of lines read
    string path = ""; //The path to read from
    ifstream in; //The input file stream

    //Input
    cout << "ENTER A FILE NAME: ";
    getline(cin, path); //Read in path

    //Read and output data
    in.open(path.c_str()); //Open file
    if(in.is_open()){ //If file opened correctly
        string data; //The current file line
        while(getline(in, data)){ //While there are more lines to read
            cout << data << endl; //Output the data
            ++count; //Increment the count
            if((count + 1) % 24 == 0){ //If the next line is the 24th line since the last break
                cout << "--MORE--"; //Output page break message
                cin.get(); //Hold terminal open for input
            }
        }
    }
    in.close(); //Close file
}

void solve8(){
    //Declaration and Initialization
    string inFile = "", //The input file path
            outFile = "", //The output file path
            data = ""; //The string to read lines into
    ifstream in; //The input file stream
    ofstream out; //The output file stream

    //Input
    cout << "ENTER THE INPUT FILE PATH: ";
    getline(cin, inFile); //Read in inFile
    cout << "ENTER THE OUTPUT FILE PATH: ";
    getline(cin, outFile); //Read in outFile

    //Filter file
    in.open(inFile.c_str()); //Open the input file
    out.open(outFile.c_str()); //Open the output file
    while(getline(in, data)){ //While there is more input to read
        bool endSent = true; //Whether or not the program is at the end of a sentence
        for(int i = 0; i < data.size(); ++i){ //For every character in the current line
            if(!endSent && (data[i - 1] == '.' || data[i - 1] == '?' || data[i - 1] == '!')){ //If this is a sentence ending
                endSent = true; //The program is at the end of a sentence
            }
            if(endSent && isalpha(data[i])){ //If we reached the end of a sentence and the next character is a letter
                data[i] = toupper(data[i]); //Uppercase the letter
                endSent = false; //The program is not at a sentence ending
            }
            else{ //Otherwise
                data[i] = tolower(data[i]); //Lowercase the data
            }
        }
        if(!data.empty()){ //If the current line isn't empty
            cout << data << endl; //Output the line to stdout
            out << data << endl; //Output the line to the output file
        }
    }
    in.close(); //Close the input file
    out.close(); //Close the output file
}

void solve9(){
    //Declaration and Initialization
    const char *OUTPATH = "out_12_8.dat"; //The output path

    int *array = NULL; //The array to read data into
    unsigned int size; //The size of the array

    //Input
    cout << "ENTER THE SIZE OF THE ARRAY TO ALLOCATE: ";
    cin >> size; //Read in size
    array = new int[size]; //Allocate an array of the input size
    for(int i = 0; i < size; ++i){ //For every element of the array
        cout << "ENTER THE VALUE FOR ARRAY[" << i << "]: ";
        cin >> array[i]; //Read in array[i]
    }
    cout << endl;

    //Write array to disk
    cout << "WRITING ARRAY TO DISK...";
    toFile(OUTPATH, array, size); //Write the array to a file
    for(int i = 0; i < size; ++i){ //Clear the array
        array[i] = 0;
    }
    cout << "DONE!" << endl;

    //Read data back from disk
    cout << "READING ARRAY FROM DISK...";
    toArray(OUTPATH, array, size); //Read the file into the array
    cout << "DONE!" << endl;
    cout << endl;
    for(int i = 0; i < size; ++i){ //Output the array again
        cout << "ARRAY[" << i << "]: " << array[i] << endl;
    }

    //Delete the array
    delete [] array;
}

void solve10(){
    //Declaration and Initialization
    const char *PATH = "salesdata.bin"; //CString containing the save path

    SaleDat north, east, south, west; //SaleDat objects
    vector<SaleDat> data; //Vector to read back data into
    //Set division names
    north.divName = "North";
    east.divName = "East";
    south.divName = "South";
    west.divName = "West";

    //Input Data
    clear(PATH); //Clear salesdata.bin
    cout << "INPUT QUARTERLY SALES DATA" << endl;
    getData(north); //Input data for north
    getData(east); //Input data for east
    getData(south); //Input data for south
    getData(west); //Input data for west
    cout << endl;

    //Write data to disk
    cout << "WRITING DATA TO " << PATH << "...";
    save(PATH, north); //Save north
    save(PATH, east); //Save east
    save(PATH, south); //Save south
    save(PATH, west); //Save west
    cout << "DONE!" << endl;

    //Read back data from disk
    cout << "READING FROM " << PATH << "...";
    load(PATH, data); //Load the written data
    cout << "DONE!" << endl;
    cout << endl;

    //Output Data vector
    for(int i = 0; i < data.size(); ++i){ //For the entire vector
        cout << "DIVISION: " << data[i].divName << endl; //Output the division name
        for(int j = 0; j < SaleDat::SIZE; ++j){ //For all the quarterly data
            cout << "SALES FOR Q" << j + 1 << ": $" << data[i].sales[j] << endl; //Output quarterly data
        }
    }
}

//Length
//Calculate the length of a CString
//Input:
//str
//A pointer to a CString
//Output:
//The length of that string

unsigned int length(const char *str){
    unsigned int r = 0; //The return value

    while(str[r] != '\0'){ //While the current character is not a null terminator
        ++r; //increment r
    }

    return r;
}

//Reverse
//Print a CString in reverse to stdout
//Input:
//str
//A pointer to a CString
//size
//The size of str in characters

void reverse(const char *str, unsigned int size){
    for(int i = size - 1; i >= 0; --i){ //Start at the last character and work backward
        cout << str[i]; //Output the character at i
    }
}

//Count
//Count the number of words in a CString
//Input:
//str
//A pointer to a CString
//size
//The size of str in characters
//Output:
//The number of words in the input CString

unsigned int count(const char *str, unsigned int size){
    unsigned int r = 0; //The word count
    bool word = false; //If the program is currently in a word

    for(int i = 0; i < size; ++i){ //For all the characters in str
        if(word && i + 1 >= size){ //If the line ends on a word
            ++r; //Increment word count
        }
        else if(isprint(str[i]) && isalpha(str[i])){ //If the current character is printable and in the alphabet
            word = true; //The program is in a word
        }
        else if(word){ //Otherwise if the program was in a word
            ++r; //Increment word count
            word = false; //The program is not in a word
        }
    }

    return r;
}

//Count
//Count the number of words in a string
//Input:
//str
//a string to count the words in
//Output:
//The number of words in the input string

unsigned int count(const string &str){
    unsigned int r = 0; //The word count
    bool word = false; //If the program is currently in a word

    for(int i = 0; i < str.size(); ++i){ //For all the characters in str
        if(word && i + 1 >= str.size()){ //If the line ends on a word
            ++r; //Increment word count
        }
        else if(isprint(str[i]) && isalpha(str[i])){ //If the current character is printable and in the alphabet
            word = true; //The program is in a word
        }
        else if(word){ //Otherwise if the program was in a word
            ++r; //Increment word count
            word = false; //The program is not in a word
        }
    }

    return r;
}

//Average Alphabetic Characters
//Calculates the average number of alphabetic characters in a CString based on a word count
//Input:
//str
//A pointer to a CString
//size
//The size of that CString
//count
//The word count of the input CString
//Output:
//A float value representing the average number of alphabetic characters

float avgAlph(const char *str, unsigned int size, unsigned int count){
    float r = 0.0f; //The average
    unsigned int total = 0; //The running total of characters

    if(count > 0){ //If the CString actually contains some words
        for(int i = 0; i < size; ++i){ //For every character
            if(isalpha(str[i])){ //If the current character is alphabetic
                ++total; //Increment the total
            }
        }
        r = total / (count * 1.0f); //Calculate the average
    }

    return r;
}

//Average Alphabetic Characters
//Calculates the average number of alphabetic characters in a string based on a word count
//Input:
//str
//A string to calculate the average characters of
//count
//The word count of the input string
//Output:
//A float value representing the average number of alphabetic characters

float avgAlph(const string &str, unsigned int count){
    float r = 0.0f; //The average
    unsigned int total = 0; //The running total of characters

    if(count > 0){ //If the string actually contains some words
        for(int i = 0; i < str.size(); ++i){ //For every character
            if(isalpha(str[i])){ //If the current character is alphabetic
                ++total; //Increment the total
            }
        }
        r = total / (count * 1.0f); //Calculate the average
    }

    return r;
}

//Is Vowel
//Return whether or not a character is a value
//Input:
//c
//The character to test
//Output:
//whether or not c is a vowel

bool isVowel(char c){
    c = toupper(c); //Set c to upper case
    return (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'); //Preform check and return
}


//Vowels
//Count the number of vowels in a CString
//Input:
//str
//A pointer to a CString
//size
//The size of str in characters
//Output:
//The number of vowels in str

unsigned int vowels(const char *str, unsigned int size){
    unsigned int r = 0; //The number of vowels

    for(int i = 0; i < size; ++i){ //For every character in str
        if(isVowel(str[i])){ //If it is a vowel
            ++r; //Increment r
        }
    }

    return r;
}


//Consonants
//Count the number of consonants in a CString
//Input:
//str
//A pointer to a CString
//size
//The size of str in characters
//Output:
//The number of consonants in str

unsigned int cnsnnts(const char *str, unsigned int size){
    unsigned int r = 0; //The number of consonants

    for(int i = 0; i < size; ++i){ //For every character in str
        if(!isVowel(str[i]) && isalpha(str[i])){ //If it isn't a vowel but is alphabetic
            ++r; //increment r
        }
    }

    return r;
}

//String Sum
//Sum all the digits in a string. Ignores characters that aren't digits
//Input:
//str
//The string to sum
//Output:
//The sum of all digits in the string

unsigned int strSum(const string &str){
    unsigned int r = 0; //The sum

    for(int i = 0; i < str.size(); ++i){ //For every character in str
        if(isdigit(str[i])){ //If the character is a digit
            r += str[i] - 48; //Calculate value and add it to the total
        }
    }

    return r;
}

//High
//Find the highest digit in a string
//Input:
//str
//The string to find the highest digit of
//Output:
//The highest digit in str

unsigned char high(const string &str){
    unsigned char r = 0; //The highest digit

    for(int i = 0; i < str.size(); ++i){ //For every character in str
        if(isdigit(str[i]) && str[i] - 48 > r){ //If the character is a digit and is higher than r
            r = str[i] - 48; //The highest digit is the numeric value of the current character
        }
    }

    return r;
}

//Low
//Find the lowest digit in a string
//Input:
//str
//The string to find the lowest digit of
//Output:
//The lowest digit in str

unsigned char low(const string &str){
    unsigned char r = 255; //The lowest digit. Set to 2^8 - 1

    for(int i = 0; i < str.size(); ++i){ //For every character in str
        if(isdigit(str[i]) && str[i] - 48 < r){ //If the character is a digit and is lower than r
            r = str[i] - 48; //The lowest digit is the numeric value of the current character
        }
    }

    return r;
}

//To Int
//Convert a unsigned char to an int without having to write out the static_cast
//Input:
//c
//The unsigned char to covert
//Output:
//The value of c static_cast to an int

int toInt(unsigned char c){
    return static_cast<int>(c);
}

//Save
//Write a record to a file
//Input:
//path
//The path to the file to save to
//data
//The SaleDat object to create a record from

void save(const char *path, SaleDat &data){
    ofstream out; //The output file stream
    int len = data.divName.size() + 1; //The length of the division name for this record + a null terminator

    out.open(path, ios::binary | ios::app); //Open the file in binary mode and append the data to the end of the file
    out.write(reinterpret_cast<char*>(&len), sizeof (len)); //Write the length of the division name
    out.write(data.divName.c_str(), len); //Write the division name
    for(int i = 0; i < SaleDat::SIZE; ++i){ //For each quarter
        out.write(reinterpret_cast<char*>(&data.sales[i]), sizeof (data.sales[i])); //Write the sales data
    }
    out.close(); //Close the file
}

//Load
//Load SaleDat objects from a given file into a vector
//Input:
//path
//The path of the file to read from
//data
//The vector to load data into
//Output:
//The data vector filled with the records found in the given file

void load(const char *path, vector<SaleDat> &data){
    int size = 0; //The size of the file
    ifstream in; //The input file stream

    in.open(path, ios::binary); //Open the file in binary mode
    in.seekg(0, ios::end); //Seek to the end of the file
    size = in.tellg(); //Set the file size
    in.seekg(0, ios::beg); //Seek back to the beginning of the file
    while(in.tellg() < size){ //While the current position is less than the file size
        SaleDat tmp; //Temporary sales data
        int len = 0; //The length of the current record's name
        in.read(reinterpret_cast<char*>(&len), sizeof (len)); //Read the length
        char *buffer = new char[len]; //Create a new CString of len
        in.read(buffer, len); //Read in the the division name
        tmp.divName = buffer; //Set the division name to the buffer storage data
        delete [] buffer; //Release the buffer
        for(int i = 0; i < SaleDat::SIZE; ++i){ //For each quarter
            in.read(reinterpret_cast<char*>(&tmp.sales[i]), sizeof (tmp.sales[i])); //Read in sales data
        }
        data.push_back(tmp); //Push tmp to the data vector
    }
    in.close(); //Close the file
}

//Get Data
//Load sales data into a SaleDat object
//Input:
//data
//The object to load data into
//Output:
//The data object filled with data

void getData(SaleDat &data){
    cout << "DIVISION: " << data.divName << endl; //Output division name
    for(int i = 0; i < SaleDat::SIZE; ++i){ //For each quarter
        int input = 0; //The input value
        do{ //While input is less than 0
            cout << "ENTER SALES FOR Q" << i + 1 << ": $";
            cin >> input; //Read in input
        } while(input < 0);
        data.sales[i] = input; //Set the current quarter's data to the input
    }
}


//Clear
//Clear a file
//Input:
//path
//The file path to clear

void clear(const char *path){
    ofstream out; //The file output stream
    out.open(path, ios::trunc); //Open file in truncate mode
    out.close(); //Close file
}

//To File
//Write an array to a file
//Input:
//path
//The path to write to
//array
//The array to get data from
//size
//The size of the array

void toFile(const char *path, int *array, int size){
    ofstream out; //The output file stream

    out.open(path, ios::binary); //Open the file in binary mode
    for(int i = 0; i < size; ++i){ //For each element of the array
        out.write(reinterpret_cast<char*>(&array[i]), sizeof (array[i])); //Write the value of the current element to the disk
    }
    out.close(); //Close the file
}


///To Array
//Read a file into an array
//Input:
//path
//The path to read from
//array
//The array to read data into
//size
//The size of the array
//Output:
//The array filled with data from the file

void toArray(const char *path, int *array, int size){
    ifstream in; //The input file stream

    in.open(path, ios::binary); //Open the file in binary mode
    for(int i = 0; i < size; ++i){ //For every element of the array
        in.read(reinterpret_cast<char*>(&array[i]), sizeof (array[i])); //Read the value into the current element
    }
    in.close(); //Close the file
}