/*
 * File:   main.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Further modification of program 9-19 to use a descending sort
 * Created on September 27, 2016
 */

//System Libraries
#include <iostream> //I/O
using namespace std;

// Function prototypes
void arrSelectSort(int *[], int);
void showArray(const int [], int);
void showArrPtr(int *[], int);

//Begin Execution

int main(){
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
    cout << "The donations, sorted in descending order are: \n";
    showArrPtr(arrPtr, numDnts);

    // Display the donations in their original order.
    cout << "The donations, in their original order are: \n";
    showArray(donations, numDnts);

    //Delete donation array
    delete [] donations;

    //Exit
    return 0;
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
            if(*(arr[index]) > *minElem){
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

