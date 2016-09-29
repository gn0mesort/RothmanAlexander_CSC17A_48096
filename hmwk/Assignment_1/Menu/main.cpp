/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Solve chapter 9 homework problems. I couldn't find the specific problems so I just solved them all plus
 * the mean, median, and mode problem
 * Created on September 21, 2016
 */

//System Libraries
#include <iostream> //I/O
#include <iomanip> //I/O Formatting
#include <cstdlib> //C standard library
#include <ctime> //Date and Time
#include <string> //String type and functions
using namespace std;

//Global Constants

//Function Prototypes
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
void solve11();
void solve12();
void solve13();
void solve14();
//Helper Functions
int* genArr(int);
int* reverse(int[], unsigned int);
void prntArr(const int[], unsigned int);
int* expand(int*, unsigned int);
int* shift(int[], unsigned int&);
float mean(const int[], int);
float median(const int[], int);
void sort(int[], int);
int* mode(const int[], int);
int modeCnt(const int[], int, int);
int getFreq(const int[], int);
int* getMdes(const int[], int, int, int);
void sort(short[], short);
void prntArr(const short[], short);
float mean(const short[], short);
float meanDLw(const short[], short);
void sortIdx(unsigned char[], short[], short);
void prntArr(const unsigned char[], const string[], const short[], short);
unsigned char* mkIndex(short);
int compute(int*, int*);
void arrSelectSort(int *[], int);
void showArray(const int [], int);
void showArrPtr(int *[], int);
void arrSelectSortDes(int *[], int);
void sortPt(int*, int);
int* gArrPt(int);
int modePt(const int*, int);
void pArrPt(const int*, int);
int gFreqPt(const int*, int);
int* gArrFl(int);

//Begin Execution

int main(int argc, char** argv){
    //Declaration and Initialization
    int choice = 0;

    do{ //While not exiting
        do{ //While choice is not negative
            //Output Choices
            cout << setw(5) << "(1) " << "CHAPTER 9 PROB 1" << endl;
            cout << setw(5) << "(2) " << "CHAPTER 9 PROB 2" << endl;
            cout << setw(5) << "(3) " << "CHAPTER 9 PROB 3" << endl;
            cout << setw(5) << "(4) " << "CHAPTER 9 PROB 4" << endl;
            cout << setw(5) << "(5) " << "CHAPTER 9 PROB 5" << endl;
            cout << setw(5) << "(6) " << "CHAPTER 9 PROB 6" << endl;
            cout << setw(5) << "(7) " << "CHAPTER 9 PROB 7" << endl;
            cout << setw(5) << "(8) " << "CHAPTER 9 PROB 8" << endl;
            cout << setw(5) << "(9) " << "CHAPTER 9 PROB 9" << endl;
            cout << setw(5) << "(10) " << "CHAPTER 9 PROB 10" << endl;
            cout << setw(5) << "(11) " << "CHAPTER 9 PROB 11" << endl;
            cout << setw(5) << "(12) " << "CHAPTER 9 PROB 12" << endl;
            cout << setw(5) << "(13) " << "CHAPTER 9 PROB 13" << endl;
            cout << setw(5) << "(14) " << "MEAN, MEDIAN, AND MODE" << endl;
            cout << setw(5) << "(0) " << "EXIT" << endl;
            //Display Prompt and Read Input
            cout << "> ";
            cin >> choice;
        } while(choice < 0);
        switch(choice){ //Select function based on choice
            case 1:
            {
                cout << "CHAPTER 9 PROB 1" << endl;
                solve1();
                cout << endl;
                break;
            }
            case 2:
            {
                cout << "CHAPTER 9 PROB 2" << endl;
                solve2();
                cout << endl;
                break;
            }
            case 3:
            {
                cout << "CHAPTER 9 PROB 3" << endl;
                solve3();
                cout << endl;
                break;
            }
            case 4:
            {
                cout << "CHAPTER 9 PROB 4" << endl;
                solve4();
                cout << endl;
                break;
            }
            case 5:
            {
                cout << "CHAPTER 9 PROB 5" << endl;
                solve5();
                cout << endl;
                break;
            }
            case 6:
            {
                cout << "CHAPTER 9 PROB 6" << endl;
                solve6();
                cout << endl;
                break;
            }
            case 7:
            {
                cout << "CHAPTER 9 PROB 7" << endl;
                solve7();
                cout << endl;
                break;
            }
            case 8:
            {
                cout << "CHAPTER 9 PROB 8" << endl;
                solve8();
                cout << endl;
                break;
            }
            case 9:
            {
                cout << "CHAPTER 9 PROB 9" << endl;
                solve9();
                cout << endl;
                break;
            }
            case 10:
            {
                cout << "CHAPTER 9 PROB 10" << endl;
                solve10();
                cout << endl;
                break;
            }
            case 11:
            {
                cout << "CHAPTER 9 PROB 11" << endl;
                solve11();
                cout << endl;
                break;
            }
            case 12:
            {
                cout << "CHAPTER 9 PROB 12" << endl;
                solve12();
                cout << endl;
                break;
            }
            case 13:
            {
                cout << "CHAPTER 9 PROB 13" << endl;
                solve13();
                cout << endl;
                break;
            }
            case 14:
            {
                cout << "MEAN, MEDIAN, AND MODE" << endl;
                solve14();
                cout << endl;
                break;
            }
        }
    } while(choice);


    //Exit
    return 0;
}

void solve1(){
    //Declaration and initialization
    int length = 0; //The length of the generated array
    int *array = NULL; //The dynamic array

    //Read Input
    do{ //While length is less than 1
        cout << "How many elements should be allocated: ";
        cin >> length; //Read in length
    } while(length < 1);

    array = genArr(length); //Generate the array

    //Output
    cout << "ARRAY POINTER: " << array << endl; //Output the location of the array
    cout << "ARRAY CONTENTS:" << endl; //Output the contents of the array
    for(int i = 0; i < length; ++i){ //For every element in array
        cout << array[i]; //Output the value at i
        if(length > 10){ //Formatting
            if((i + 1) % 10 == 0){
                cout << endl;
            }
            else{
                cout << ", ";
            }
        }
        else{
            if((i + 1) < length){
                cout << ", ";
            }
        }
    }

    //Delete the array
    delete [] array;
}

void solve2(){
    //Declaration and Initialization
    short input = 0, //The input value
            length = 0; //The length of the score array
    short *scores = NULL; //The score array

    //Input
    do{ //While the input is less than 0
        cout << "ENTER THE NUMBER OF TESTS: ";
        cin >> input; //Read in input
    } while(input < 0);
    length = input; //Set the length of the array
    if(input > 0){ //If the input wasn't 0
        scores = new short[length]; //Allocate the score array
        for(int i = 0; i < length; ++i){ //For every element of the score array
            do{ //While the input is less than 0
                cout << "ENTER THE SCORE FOR TEST #" << i + 1 << ": ";
                cin >> input; //Read in input
            } while(input < 0);
            scores[i] = input; //Set the current score to input
        }

        //Calculate and Output data
        cout << "SORTED SCORES:";
        if(length > 10){ //Formatting
            cout << endl;
        }
        sort(scores, length); //Sort the scores
        prntArr(scores, length); //Output the sorted scores
        cout << fixed << setprecision(2); //Formatting
        cout << "AVERAGE SCORE: " << mean(scores, length) << endl; //Output the average score

        //Delete the score array
        delete [] scores;
    }
}

void solve3(){
    //Declaration and Initialization
    short input = 0, //The input value
            length = 0; //The length of the score array
    short *scores = NULL; //The score array

    //Input
    do{ //While the input is less than 0
        cout << "ENTER THE NUMBER OF TESTS: ";
        cin >> input; //Read in input
    } while(input < 0);
    length = input; //Set the length of the array
    if(input > 0){ //If the input wasn't 0
        scores = new short[length]; //Allocate the score array
        for(int i = 0; i < length; ++i){ //For every element of the score array
            do{ //While the input is less than 0
                cout << "ENTER THE SCORE FOR TEST #" << i + 1 << ": ";
                cin >> input; //Read in input
            } while(input < 0);
            scores[i] = input; //Set the current score to input
        }

        //Calculate and Output data
        cout << "SORTED SCORES:";
        if(length > 10){ //Formatting
            cout << endl;
        }
        sort(scores, length); //Sort the scores
        prntArr(scores, length); //Output the sorted scores
        cout << fixed << setprecision(2); //Formatting
        cout << "AVERAGE SCORE: " << meanDLw(scores, length) << endl; //Output the average score

        //Delete the score array
        delete [] scores;
    }
}

void solve4(){
    //Declaration and Initialization
    short input = 0, //The input value
            length = 0; //The length of the score, names, and index arrays
    short *scores = NULL; //The score array
    unsigned char *index = NULL; //The index array
    string *names = NULL; //The names array

    //Input
    do{ //While the input is less than 0
        cout << "ENTER THE NUMBER OF TESTS: ";
        cin >> input; //Read in input
    } while(input < 0);
    length = input; //Set the length of the array
    if(input > 0){ //If the input wasn't 0
        scores = new short[length]; //Allocate the score array
        names = new string[length]; //Allocate the names array
        index = mkIndex(length); //Allocate and fill the index array
        for(int i = 0; i < length; ++i){ //For every element of the score array
            do{ //While the input is less than 0
                cout << "ENTER THE NAME FOR TEST #" << i + 1 << ": ";
                cin.ignore(); //Clear standard input
                getline(cin, names[i]); //Read in the next name
                cout << "ENTER THE SCORE FOR TEST #" << i + 1 << ": ";
                cin >> input; //Read in the next score
            } while(input < 0);
            scores[i] = input; //Set the current score to input
        }

        //Calculate and Output data
        cout << "SORTED SCORES:" << endl;
        sortIdx(index, scores, length); //Sort index by score
        prntArr(index, names, scores, length); //Display score and name data
        cout << fixed << setprecision(2); //Formatting
        cout << "AVERAGE SCORE: " << mean(scores, length) << endl; //Output average score

        //Delete arrays
        delete [] scores;
        delete [] names;
        delete [] index;
    }
}

void solve5(){
    int xVal = 0, //Value of X
            yVal = 0; //Value of Y
    int *x = &xVal, //Pointer to X
            *y = &yVal; //Pointer to Y


    //Input Data
    cout << "ENTER A VALUE FOR X: ";
    cin >> xVal; //Read in xVal
    cout << "ENTER A VALUE FOR Y: ";
    cin >> yVal; //Read in yVal

    //Calculate and Output
    cout << "X: " << *x << endl; //Output value of X
    cout << "Y: " << *y << endl; //Output value of Y
    cout << "compute(X, Y): " << compute(x, y) << endl; //Output computation of X and Y
    cout << "X: " << *x << endl; //Output value of X
    cout << "Y: " << *y << endl; //Output value of Y
}

void solve6(){
    //Declaration and Initialization
    int numDnts = 0; // Number of donations

    do{ //While the number of donations is invalid
        cout << "How many donations were there: ";
        cin >> numDnts;
    } while(numDnts <= 0);

    // An array containing the donation amounts.
    int *donations = new int[numDnts]; //Allocate dynamic array

    for(int i = 0; i < numDnts; ++i){ //For the number of donations
        do{ //While the current donation is invalid
            cout << "Enter the amount donated for donation #" << i + 1 << ": ";
            cin >> donations[i]; //Read in donation amount
        } while(donations[i] < 0);
    }

    // An array of pointers to int.
    int *arrPtr[numDnts] = {};

    // Each element of arrPtr is a pointer to int. Make each
    // element point to an element in the donations array.
    for(int count = 0; count < numDnts; count++)
        arrPtr[count] = &donations[count];

    // Sort the elements of the array of pointers.
    arrSelectSort(arrPtr, numDnts);

    // Display the donations using the array of pointers. This
    // will display them in sorted order.
    cout << "The donations, sorted in ascending order are: \n";
    showArrPtr(arrPtr, numDnts);

    // Display the donations in their original order.
    cout << "The donations, in their original order are: \n";
    showArray(donations, numDnts);

    //Delete donation array
    delete [] donations;
}

void solve7(){
    //Declaration and Initialization
    int numDnts = 0; // Number of donations

    do{ //While the number of donations is invalid
        cout << "How many donations were there: ";
        cin >> numDnts;
    } while(numDnts <= 0);


    // An array containing the donation amounts.
    int *donations = new int[numDnts]; //Allocate dynamic array

    for(int i = 0; i < numDnts; ++i){ //For the number of donations
        do{ //While the current donation is invalid
            cout << "Enter the amount donated for donation #" << i + 1 << ": ";
            cin >> donations[i]; //Read in donation amount
        } while(donations[i] < 0);
    }

    // An array of pointers to int.
    int *arrPtr[numDnts] = {};

    // Each element of arrPtr is a pointer to int. Make each
    // element point to an element in the donations array.
    for(int count = 0; count < numDnts; count++)
        arrPtr[count] = &donations[count];

    // Sort the elements of the array of pointers.
    arrSelectSortDes(arrPtr, numDnts);

    // Display the donations using the array of pointers. This
    // will display them in sorted order.
    cout << "The donations, sorted in descending order are: \n";
    showArrPtr(arrPtr, numDnts);

    // Display the donations in their original order.
    cout << "The donations, in their original order are: \n";
    showArray(donations, numDnts);

    //Delete donation array
    delete [] donations;
}

void solve8(){
    //Declaration and Initialization
    const int SIZE = 10; //The size of the array to find the mode of
    int *array = NULL; //The array to find the mode of
    int modeVal = 0; //The mode that was found

    srand(static_cast<int>(time(0))); //Seed PRNG
    array = gArrPt(SIZE); //Generate the array

    //Calculate and Output
    sortPt(array, SIZE); //Sort the array
    modeVal = modePt(array, SIZE); //Find the mode
    cout << "ARRAY: " << endl;
    pArrPt(array, SIZE); //Output the array
    if(modeVal > -1){ //If the mode was found
        cout << "THE MODE IS " << modeVal << endl; //Output the mode
    }
    else{ //Otherwise
        cout << "NO MODE!" << endl; //Output error
    }

    //Delete the array
    delete [] array;
}

void solve9(){
    //Declaration and Initialization
    int size = 0; //The size of the array
    int *array = NULL; //The array to find the median of

    srand(static_cast<int>(time(0))); //Seed PRNG
    size = rand() % 100; //Generate a random size between 0 and 99
    array = new int[size]; //Allocate array
    for(int i = 0; i < size; ++i){ //For each array elements
        array[i] = (rand() % 9) + 1; //Set the current element to a random number between 1 and 9
    }

    //Calculate and Output
    cout << "ARRAY SIZE: " << size << endl;
    cout << "INITIAL ARRAY:" << endl;
    prntArr(array, size); //Output array
    sort(array, size); //Sort array
    cout << "SORTED ARRAY:" << endl;
    prntArr(array, size); //Output sorted array
    cout << "MEDIAN: " << median(array, size) << endl; //Output median

    //Delete array
    delete [] array;
}

void solve10(){
    //Declaration and Initialization
    int *array = NULL; //The array to reverse
    unsigned int length = 0; //The length of that array

    srand(static_cast<int>(time(0))); //Seed PRNG

    length = (rand() % 100) + 1; //Generate random length between 1 and 100
    array = new int[length]; //Allocate the array
    for(int i = 0; i < length; ++i){ //For every element of the array
        array[i] = (rand() % 9) + 1; //Set the value at i to a random number 1 to 9
    }

    //Output
    cout << "ARRAY LENGTH: " << length << endl; //Output the length of the array
    cout << "INITIAL ARRAY: ";
    if(length > 10){ //Formatting
        cout << endl;
    }
    prntArr(array, length); //Output the array in its initial order
    array = reverse(array, length); //Reverse the array
    cout << endl;
    cout << "REVERSED ARRAY: ";
    if(length > 10){ //Formatting
        cout << endl;
    }
    prntArr(array, length); //Output the reversed array

    //Delete the array
    delete [] array;
}

void solve11(){
    //Declaration and Initialization
    int *array = NULL; //The array to expand
    unsigned int length; //The length of the array

    srand(static_cast<int>(time(0))); //Seed PRNG

    //Input
    do{ //While length is less than 1
        cout << "ENTER THE SIZE OF THE INITIAL ARRAY: ";
        cin >> length; //Read in length
    } while(length < 1);
    array = new int[length]; //Allocate array
    cout << "FILLING ARRAY...";
    for(int i = 0; i < length; ++i){ //For every element in the array
        array[i] = (rand() % 9) + 1; //Set the value at i to a random number 1 to 9
    }
    cout << "DONE!" << endl;
    cout << "INITIAL ARRAY: ";
    if(length > 10){
        cout << endl;
    }
    prntArr(array, length); //Output the initial array
    cout << "EXPANDING ARRAY...";
    array = expand(array, length); //Expand the array
    cout << "DONE!" << endl;
    cout << "EXPANDED ARRAY: ";
    if(length * 2 > 10){
        cout << endl;
    }
    prntArr(array, length * 2); //Print the expanded array

    //Delete the array
    delete [] array;
}

void solve12(){
    //Declaration and Initialization
    int *array = NULL; //The array to shift
    unsigned int length = 0; //The size of the initial array

    srand(static_cast<int>(time(0))); //Seed PRNG

    length = (rand() % 100) + 1; //Generate a random length between 1 and 100
    array = new int[length]; //Allocate array
    for(int i = 0; i < length; ++i){ //Fill the array with random numbers 1 to 9
        array[i] = (rand() % 9) + 1;
    }

    //Output
    cout << "ARRAY LENGTH: " << length << endl; //Output the length
    cout << "INITIAL ARRAY: ";
    if(length > 10){
        cout << endl;
    }
    prntArr(array, length); //Print the initial array
    cout << endl;
    array = shift(array, length); //Shift the array
    cout << "ARRAY LENGTH: " << length << endl; //Output the new length
    cout << "SHIFTED ARRAY: ";
    if(length > 10){
        cout << endl;
    }
    prntArr(array, length); //Print the shifted array

    //Delete the array
    delete [] array;
}

void solve13(){
    //Declaration and Initialization
    int size = 0; //The number of students who were surveyed
    int *data = NULL, //The actual survey data
            *modes = NULL; //The array containing the mode data

    //Input
    do{ //While size is less than 0
        cout << "ENTER THE NUMBER OF STUDENTS SURVEYED: ";
        cin >> size;
    } while(size < 0);

    if(size > 0){ //If data was collected
        data = new int[size]; //Allocate data array

        for(int i = 0; i < size; ++i){ //For every element of the data array
            do{ //While the input data is less than 0
                cout << "ENTER THE NUMBER OF MOVIES THAT STUDENT " << i + 1 << " WATCHED: ";
                cin >> data[i];
            } while(data[i] < 0);
        }

        //Calculate and Output Data
        cout << "DATA:" << endl;
        prntArr(data, size); //Print the original data
        sort(data, size); //Sort the data
        cout << "MEAN: " << mean(data, size) << endl; //Output the mean
        cout << "MEDIAN: " << median(data, size) << endl; //Output the median
        modes = mode(data, size); //Generate the mode data
        if(modes[1] > 1){ //If modes exist
            cout << "NUMBER OF MODES: " << modes[0] << endl; //Output the number of modes
            cout << "MODE FREQUENCY: " << modes[1] << endl; //Output the frequency of the modes
            cout << "MODES: ";
            for(int i = 2; i < modes[0] + 2; ++i){ //For all the modes found in the mode data array
                cout << modes[i]; //Output the mode
                if(i + 1 < modes[0] + 2){ //Formatting
                    cout << ", ";
                }
                else{
                    cout << endl;
                }
            }
        }
        else{ //Otherwise
            cout << "NO MODE!" << endl;
        }

        //Delete arrays
        delete [] modes;
        delete [] data;
    }
}

void solve14(){
    //Declaration and Initialization
    const int SIZE = 10; //The size of the array to generate
    int *array = NULL, //The array from which to calculate output
            *modeDat = NULL; //The array for mode data

    srand(static_cast<int>(time(0))); //Seed PRNG
    array = gArrFl(SIZE); //Generate and fill array

    //Calculate and Output
    cout << "INITIAL ARRAY:" << endl;
    prntArr(array, SIZE); //Print initial array
    cout << "SORTED ARRAY:" << endl;
    sort(array, SIZE); //Sort array
    prntArr(array, SIZE); //Print sorted array
    cout << "MEAN: " << mean(array, SIZE) << endl; //Output mean
    cout << "MEDIAN: " << median(array, SIZE) << endl; //Output median
    modeDat = mode(array, SIZE); //Calculate mode array
    if(modeDat[1] != 1){ //If modes were found
        cout << "NUMBER OF MODES: " << modeDat[0] << endl; //Output number of modes
        cout << "MODE FREQUENCY: " << modeDat[1] << endl; //Output mode frequency
        cout << "MODES: ";
        for(int i = 2; i < modeDat[0] + 2; ++i){ //For each mode
            cout << modeDat[i]; //Output mode
            if(i + 1 < modeDat[0] + 2){ //Formatting
                cout << ", ";
            }
            else{
                cout << endl;
            }
        }
    }
    else{ //Otherwise
        cout << "NO MODE!" << endl; //Output no mode found
    }

    //Delete arrays
    delete [] array;
    delete [] modeDat;
}

//Generate Array
//Generate an int array of the given size and initialize it to 0. Array initializer works in C++11 or later otherwise
//uncomment the looping routine to fill the array
//Input:
//length
//The length of the array to generate
//Output:
//A pointer to the generated array

int* genArr(int length){
    return new int[length]{ //Return a new array pointer with the given length
    };
    //If not using C++11 or later
    //    int *r = new int[length];
    //    for(int i = 0; i < length; ++i){
    //        r[i] = 0;
    //    }
    //    return r;
}

//Reverse
//Reverse an array and return a pointer to the new reversed array. Deletes the input array.
//Input:
//array
//The array to reverse
//length
//The length of the array
//Output:
//A pointer to a new array in reverse order of the input array

int* reverse(int array[], unsigned int length){
    int *r = new int[length]; //Allocate a new array with length elements

    for(int i = 0; i < length; ++i){ //For every element in the new array
        r[i] = array[(length - 1) - i]; //The current element of the new array is equal to the reverse element in the input array
    }

    //Delete the input array
    delete [] array;

    return r;
}

//Print Array
//Print an array to standard output
//Input:
//array
//The array to display
//size
//The size of that array

void prntArr(const int array[], unsigned int size){
    for(int i = 0; i < size; ++i){ //For every element in the array
        cout << array[i]; //Output the array element
        if(size > 10){ //If the size is greater than 10
            if((i + 1) % 10 == 0){ //Add some formatting
                cout << endl;
            }
            else if(i != size - 1){
                cout << ", ";
            }
        }
        else{ //Otherwise
            if(i != size - 1){ //Add some other formatting
                cout << ", ";
            }
        }
    }
    cout << endl;
}

//Expand
//Double the size of the input array and return a pointer to the expanded array. Deletes the input array.
//Input:
//array
//The array to expand
//length
//The size of the input array
//Output:
//A pointer to the new expanded array

int* expand(int *array, unsigned int length){
    int* r = NULL; //The return array pointer
    unsigned int nLength = length * 2; //The length of the new array

    r = new int[nLength]; //Allocate the return array
    for(int i = 0; i < nLength; ++i){ //For the entire expanded array
        if(i < length){ //When i is less than the original length
            r[i] = array[i]; //set the return array value to the original array value at i
        }
        else{ //Otherwise
            r[i] = 0; //set the return array value at i to 0
        }
    }

    //Delete the input array
    delete [] array;

    return r;
}

//Mode
//Calculate the modes (if any exist) of a given integer array
//Input:
//array
//The array to calculate the modes of
//size
//The size of the input array
//Output:
//A pointer to an array containing the following data
//1. The number of modes found (array[0])
//2. The frequency at which they occurred (array[1])
//3. The values of those modes (array[2 - (n - 1)])

int* mode(const int array[], int size){
    int *r = NULL, //The return array
            *modes = NULL; //The modes found by this function
    int freq = getFreq(array, size), //The frequency of the modes
            numMode = 0; //The number of modes found

    if(freq > 1){ //If modes exist
        numMode = modeCnt(array, size, freq); //Calculate the number of modes
    }
    modes = getMdes(array, size, numMode, freq); //Get the modes
    r = new int[numMode + 2]; //Allocate the return array
    r[0] = numMode; //Set the number of modes
    r[1] = freq; //Set the frequency

    for(int i = 2; i < numMode + 2; ++i){ //For each mode
        r[i] = modes[i - 2]; //Set the element of the return array at i to the mode at i - 2
    }

    //Delete modes array
    delete [] modes;

    return r;
}

//Get Modes
//Get the modes for a given array.
//Input:
//array
//The array to find modes from
//size
//The size of the array
//numMode
//The number of modes found in the array
//freq
//The frequency of the modes in the array
//Output:
//A pointer to an array containing the modes of the input array

int* getMdes(const int array[], int size, int numMode, int freq){
    int *r = new int[numMode]; //Allocate return array
    int count = 0, //The count of the current search value
            pos = 0; //The position in the return array

    for(int i = 0; i < size; ++i){ //For each value in the input array
        if(i > 0 && array[i] != array[i - 1]){ //If the current value has changed from the last value
            if(count == freq){ //If the current count is the same as the frequency
                r[pos++] = array[i - 1]; //place the previous value in the return array and increment the position
            }
            count = 1; //Reset the count
        }
        else{ //Otherwise
            ++count; //Increment the count
        }
        if(i + 1 >= size && count == freq){ //If the last value in the array is a mode
            r[pos] = array[i]; //place it in the current position of the return array
        }
    }

    return r;
}

//Get Frequency
//Get the frequency of the mode of an array
//Input:
//array
//The array to find the mode frequency of
//size
//The size of the array
//Output:
//The frequency of the mode of the array

int getFreq(const int array[], int size){
    int r = 0, //The frequency to return
            start = 0; //The position of the start of the most recent value in the array

    for(int current = 0; current < size; ++current){ //For each element in the array
        if(array[start] != array[current]){ //If the current value is not the same as the starting value
            int diff = current - start; //Hold the difference in a temporary value
            if(diff > r){ //If the difference is greater than the current return frequency
                r = diff; //Set the return frequency to the difference
            }
            start = current; //Reset the start position
        }
        else if(current + 1 >= size){ //If this is the last element in the array
            int diff = size - start; //Hold the difference in a temporary value
            if(diff > r){ //If the difference is greater than the current return frequency
                r = diff; //Set the return frequency to the difference
            }
        }
    }
    return r;
}

//Mode Count
//Count the number of modes in an array
//Input:
//array
//The array to count the modes of
//size
//The size of that array
//freq
//The frequency of the mode
//Output:
//The number of modes found in the array

int modeCnt(const int array[], int size, int freq){
    int r = 0, //The return mode count
            count = 0; //The number of times the current value has appeared

    for(int i = 0; i < size; ++i){ //For each value in the input array
        if(i > 0 && array[i] != array[i - 1]){ //If the current value has changed from the last value
            if(count == freq){ //If the current count is the same as the frequency
                ++r; //Increment the mode count
            }
            count = 1; //Reset the count
        }
        else{ //Otherwise
            ++count; //Increment the count
        }
        if(i + 1 >= size && count == freq){ //If the last value in the array is a mode
            ++r; //Increment the mode count
        }
    }

    return r;
}

//Median
//Calculate the median of a sorted array
//Input:
//array
//The array to calculate the median of
//size
//The size of the array
//Output:
//The median of the array as a float

float median(const int array[], int size){
    if(size & 1){ //If size is odd
        return array[(size - 1) / 2];
    }
    else{ //If size is even
        int offset = (size - 2) / 2; //Calculate median offset
        return (array[0 + offset] + array[(size - 1) - offset]) / 2.0f;
    }
}

//Mean
//Calculate the mean of an array
//Input:
//array
//The input array
//size
//The size of the array
//Output:
//The mean value of the array as a float

float mean(const int array[], int size){
    int total = 0; //The sum of the array elements
    for(int i = 0; i < size; ++i){ //For each array element
        total += array[i]; //Sum the elements
    }
    return total / (size * 1.0f); //Calculate and return the mean
}

//Sort
//Sorts an array based using the gnome sort algorithm
//Input:
//array
//The array to sort
//size
//The size of both arrays
//Output:
//The sorted array

void sort(int array[], int size){
    int pos = 0; //The initial position
    while(pos < size){ //While unsorted
        if(pos == 0 || array[pos] >= array[pos - 1]){ //If the position is 0 or the current value is greater than the last value
            ++pos; //Move up one position
        }
        else{ //Otherwise
            //Swap the current position and the last position
            array[pos] = array[pos] ^ array[pos - 1];
            array[pos - 1] = array[pos] ^ array[pos - 1];
            array[pos] = array[pos] ^ array[pos - 1];
            //Move back one position
            --pos;
        }
    }
}

//Sort
//Sorts an array based using the gnome sort algorithm
//Input:
//array
//The array to sort
//size
//The size of both arrays
//Output:
//The sorted array

void sort(short array[], short size){
    short pos = 0; //The initial position
    while(pos < size){ //While unsorted
        if(pos == 0 || array[pos] >= array[pos - 1]){ //If the position is 0 or the current value is greater than the last value
            ++pos; //Move up one position
        }
        else{ //Otherwise
            //Swap the current position and the last position
            array[pos] = array[pos] ^ array[pos - 1];
            array[pos - 1] = array[pos] ^ array[pos - 1];
            array[pos] = array[pos] ^ array[pos - 1];
            //Move back one position
            --pos;
        }
    }
}

//Print Array
//Print an array to standard output
//Input:
//array
//The array to display
//size
//The size of that array

void prntArr(const short array[], short size){
    for(int i = 0; i < size; ++i){ //For every element in the array
        cout << array[i]; //Output the array element
        if(size > 10){ //If the size is greater than 10
            if((i + 1) % 10 == 0){ //Add some formatting
                cout << endl;
            }
            else if(i != size - 1){
                cout << ", ";
            }
        }
        else{ //Otherwise
            if(i != size - 1){ //Add some other formatting
                cout << ", ";
            }
        }
    }
    cout << endl;
}

//Mean
//Calculate the average of a given array
//Input:
//array
//The array to calculate the average of
//length
//The size of that array
//Output:
//The average of the array as a float

float mean(const short array[], short length){
    float r = 0.0f; //The average to be returned

    for(int i = 0; i < length; ++i){ //For each element of the array
        r += array[i]; //Sum the elements
    }

    return r / (length * 1.0f); //Return the average
}

//Mean Drop Lowest
//Calculate the average of a given array. Drops the lowest score from the average
//Input:
//array
//The array to calculate the average of
//length
//The size of that array
//Output:
//The average of the array as a float

float meanDLw(const short array[], short length){
    float r = 0.0f; //The average to be returned

    for(int i = 1; i < length; ++i){ //For each element of the array except the first element
        r += array[i]; //Sum the elements
    }

    return r / ((length - 1) * 1.0f); //Return the average
}

//Make Index
//Generate an indexing array of a given size and return a pointer to it
//Input:
//size
//The size of the indexing array
//Output:
//A pointer to the indexing array

unsigned char* mkIndex(short size){
    unsigned char *r = new unsigned char[size]; //Allocate return array
    for(int i = 0; i < size; ++i){ //For all the elements of the array
        r[i] = i; //Fill array
    }
    return r;
}

//Sort Index
//Sort the indexing array using values found in the input array
//Input:
//index
//The indexing array to sort
//array
//The array of values to use in sorting
//size
//The size of the input arrays

void sortIdx(unsigned char index[], short array[], short size){
    short pos = 0; //The initial position
    while(pos < size){ //While unsorted
        if(pos == 0 || array[index[pos]] >= array[index[pos - 1]]){ //If the position is 0 or the current value is greater than the last value
            ++pos; //Move up one position
        }
        else{ //Otherwise
            //Swap the current position and the last position
            index[pos] = index[pos] ^ index[pos - 1];
            index[pos - 1] = index[pos] ^ index[pos - 1];
            index[pos] = index[pos] ^ index[pos - 1];
            //Move back one position
            --pos;
        }
    }
}

//Print Array
//Print score and name array together
//Input:
//index
//The indexing array
//names
//The array of names to be printed
//scores
//The score array to be printed
//size
//The size of the arrays

void prntArr(const unsigned char index[], const string names[], const short scores[], short size){
    for(int i = 0; i < size; ++i){ //For every array element
        cout << setw(10) << names[index[i]] << " : " << setw(4) << scores[index[i]] << endl; //Output name/score pair
    }
}

//Compute
//Preform an arbitrary computation using pointers. Should return (10 * X) + (10 * Y) and swap the values of X and Y
//Input:
//x
//A pointer to a value to use in computation
//y
//A pointer to a value to use in computation
//Output:
//A computed value

int compute(int *x, int *y){
    int temp = *x; //A temporary value
    *x = *y * 10;
    *y = temp * 10;
    return *x + *y;
}

//****************************************************************
// Definition of function arrSelectSort.                         *
// This function performs an ascending order selection sort on   *
// arr, which is an array of pointers. Each element of array     *
// points to an element of a second array. After the sort,       *
// arr will point to the elements of the second array in         *
// ascending order.                                              *
//****************************************************************

void arrSelectSort(int *arr[], int size){
    int startScan, minIndex;
    int *minElem;

    for(startScan = 0; startScan < (size - 1); startScan++){
        minIndex = startScan;
        minElem = arr[startScan];
        for(int index = startScan + 1; index < size; index++){
            if(*(arr[index]) < *minElem){
                minElem = arr[index];
                minIndex = index;
            }
        }
        arr[minIndex] = arr[startScan];
        arr[startScan] = minElem;
    }
}

//*************************************************************
// Definition of function showArray.                          *
// This function displays the contents of arr. size is the    *
// number of elements.                                        *
//*************************************************************

void showArray(const int arr[], int size){
    for(int count = 0; count < size; count++)
        cout << arr[count] << " ";
    cout << endl;
}

//**************************************************************
// Definition of function showArrPtr.                          *
// This function displays the contents of the array pointed to *
// by arr. size is the number of elements.                     *
//**************************************************************

void showArrPtr(int *arr[], int size){
    for(int count = 0; count < size; count++)
        cout << *(arr[count]) << " ";
    cout << endl;
}

//****************************************************************
// Definition of function arrSelectSortDes.                         *
// This function performs an descending order selection sort on   *
// arr, which is an array of pointers. Each element of array     *
// points to an element of a second array. After the sort,       *
// arr will point to the elements of the second array in         *
// descending order.                                              *
//****************************************************************

void arrSelectSortDes(int *arr[], int size){
    int startScan, minIndex;
    int *minElem;

    for(startScan = 0; startScan < (size - 1); startScan++){
        minIndex = startScan;
        minElem = arr[startScan];
        for(int index = startScan + 1; index < size; index++){
            if(*(arr[index]) > *minElem){
                minElem = arr[index];
                minIndex = index;
            }
        }
        arr[minIndex] = arr[startScan];
        arr[startScan] = minElem;
    }
}

//Sort Pointer Notation
//Sorts an array using the gnome sort algorithm
//Input:
//array
//The array to sort
//size
//The size of both arrays
//Output:
//The sorted array

void sortPt(int *array, int size){
    int pos = 0; //The initial position
    while(pos < size){ //While unsorted
        if(pos == 0 || *(array + pos) >= *(array + (pos - 1))){ //If the position is 0 or the current value is greater than the last value
            ++pos; //Move up one position
        }
        else{ //Otherwise
            //Swap the current position and the last position
            *(array + pos) = *(array + pos) ^ *(array + (pos - 1));
            *(array + (pos - 1)) = *(array + pos) ^ *(array + (pos - 1));
            *(array + pos) = *(array + pos) ^ *(array + (pos - 1));
            //Move back one position
            --pos;
        }
    }
}


//Generate Array Pointer Notation
//Generates an array of the given size
//Input:
//size
//The size of the array to generate
//Output:
//The pointer to the generated array

int* gArrPt(int size){
    int *r = new int[size]; //Allocate the return array

    for(int i = 0; i < size; ++i){ //Generate array values
        *(r + i) = rand() % 10; //Values between 0 and 9
    }

    return r;
}

//Print Array Pointer Notation
//Print an array to standard output
//Input:
//array
//The array to display
//size
//The size of that array

void pArrPt(const int *array, int size){
    for(int i = 0; i < size; ++i){ //For every element in the array
        cout << *(array + i); //Output the array element
        if(size > 10){ //If the size is greater than 10
            if((i + 1) % 10 == 0){ //Add some formatting
                cout << endl;
            }
            else if(i != size - 1){
                cout << ", ";
            }
        }
        else{ //Otherwise
            if(i != size - 1){ //Add some other formatting
                cout << ", ";
            }
        }
    }
    cout << endl;
}

//Mode Pointer Notation
//Get the mode of a given array
//Returns the highest valued mode rather than all modes in the case of multiple
//Input:
//array
//The array to find the mode of
//size
//The size of the array
//Output:
//The highest mode found or -1 if none exist

int modePt(const int *array, int size){
    int r = -1, //The return mode
            freq = gFreqPt(array, size), //The frequency of the mode
            count = 0, //The number of times the current number occurs
            pos = 0; //The current position
    if(freq > 1){ //If the frequency is greater than 1
        for(int i = 0; i < size; ++i){ //For every element in the array
            if(i > 0 && *(array + i) != *(array + (i - 1))){ //If the current value has changed from the last value
                if(count == freq){ //If the current count is the same as the frequency
                    r = *(array + (i - 1)); //Set the return value to the last array element
                }
                count = 1; //Reset count
            }
            else{ //Otherwise
                ++count; //Increment the count
            }
            if(i + 1 >= size && count == freq){ //If the last value in the array is a mode
                r = *(array + i); //Set the return value to the current array element
            }
        }
    }

    return r;
}

//Get Frequency Pointer Notation
//Get the frequency of the mode of an array
//Input:
//array
//The array to find the mode frequency of
//size
//The size of the array
//Output:
//The frequency of the mode of the array

int gFreqPt(const int *array, int size){
    int r = 0, //The frequency to return
            start = 0; //The position of the start of the most recent value in the array

    for(int current = 0; current < size; ++current){ //For each element in the array
        if(*(array + start) != *(array + current)){ //If the current value is not the same as the starting value
            int diff = current - start; //Hold the difference in a temporary value
            if(diff > r){ //If the difference is greater than the current return frequency
                r = diff; //Set the return frequency to the difference
            }
            start = current; //Reset the start position
        }
        else if(current + 1 >= size){ //If this is the last element in the array
            int diff = size - start; //Hold the difference in a temporary value
            if(diff > r){ //If the difference is greater than the current return frequency
                r = diff; //Set the return frequency to the difference
            }
        }
    }
    return r;
}

//Shift
//Shift an array one element to the right
//Input:
//array
//The array to shift
//length
//The length of the array to shift
//Output:
//A pointer to the shifted array
//The new augmented length of the array

int* shift(int array[], unsigned int& length){
    int *r = new int[length + 1];

    r[0] = 0;
    for(int i = 0; i < length; ++i){
        r[i + 1] = array[i];
    }
    ++length;

    delete [] array;

    return r;
}

//Generate Array Filled
//Generate an array of the given size
//Input:
//size
//The size of the array to generate
//Output:
//A pointer to the generated array

int* gArrFl(int size){
    int *r = new int[size]; //Allocate the return array

    for(int i = 0; i < size; ++i){ //For each element of the array
        r[i] = rand() % 10; //Set the element at i to a number 0 to 9
    }

    return r;
}