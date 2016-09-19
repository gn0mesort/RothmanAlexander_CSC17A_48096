/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Mixing primary colors
 * Created on September 17, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <string> //String type and functions
using namespace std;

//Function Prototypes
char getClr();
char getChar();
bool fndMix(char, char);

//Begin Execution
int main(int argc, char** argv){
    //Declaration and Initialization
    char color1 = 0, //The first color to mix
            color2 = 0; //The second color to mix
    
    do{
        color1 = getClr(); //Read in color1
        color2 = getClr(); //Read in color2
    } while(!fndMix(color1, color2)); //If the mix isn't valid loop
    
    //Exit
    return 0;
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

