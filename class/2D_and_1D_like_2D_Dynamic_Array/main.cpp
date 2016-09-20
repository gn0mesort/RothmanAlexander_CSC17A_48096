/* 
 * File:   main.cpp
 * Author: Alexander Rothman
 * Created on September 12, 2016, 1:07 PM
 * Purpose: 1D and 2D dynamic arrays
 */

//System Libraries
#include <iostream> //I/O
#include <cstdlib> //C Standard Library
#include <ctime> //Time

using namespace std;

//Function Prototypes
int* fillAry(int);
int** fillAry(int, int);
void mrkSort(int[], int);
void prntAry(int*, int, int);
void prntAry(int**, int, int);

//Begin Execution
int main(int argc, char** argv) {
    //Declare Variables
    const int ROW = 15,
            COL = 10,
        SIZE = ROW * COL, //Size of the array to sort 
              LINES = 10; //Number of values to print per line
    int utilize = SIZE / 2; //The size of the array to actually fill
    int *a1D, **a2D; //The array to be sorted
    
    //Initialize rand()
    srand(static_cast<int>(time(0)));
    
    //Fill Arrays
    a1D = fillAry(SIZE); //1D
    a2D = fillAry(ROW, COL); //2D
    //Print Arrays
    cout << "1D Array" << endl;
    prntAry(a1D, SIZE, LINES); //Print 1D Array
    cout << endl << "2D Array" << endl;
    prntAry(a2D, ROW, COL);
    
    //Specific ROW and COL test
    int sRow = 7, sCol = 4;
    cout << "Output Specific Row and Column [" << sRow << " , " << sCol; 
    cout << "]" << endl;
    cout << "a1D[" << sRow << "][" << sCol << "] = "; 
    cout << a1D[sRow * COL + sCol] << endl;
    cout << "a2D[" << sRow << "][" << sCol << "] = " << a2D[sRow][sCol] << endl;
    
    //Delete Pointers
    delete [] a1D;
    for(int i = 0; i < ROW; i++){
        delete [] a2D[i];
    }
    delete [] a2D;
    
    //Exit
    return 0;
}

//Fill Array
//Fill an array with random 2 digit numbers
//INPUT:
//a[]
//An array to fill
//n
//The length of the array to fill
//OUTPUT:
//a[]
//The filled array
int* fillAry(int n){
    int *a = new int[n];
    for(int i = 0; i < n; ++i){
        a[i] = rand() % 90 + 10; //Generate random 2 digit numbers
    }
    return a;
}

int** fillAry(int r, int c){
    int **a = new int*[r];
    for(int i = 0; i < r; ++i){
        a[i] = new int[c];
    }
    for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            a[i][j] = rand() % 90 + 10;
        }
    }
    return a;
}

//Print Array
//Print an integer array to standard output
//INPUT:
//a[]
//The array to print
//n
//The length of the array
//perLine
//The number of values to print per line
void prntAry(int *a, int n, int perLine){
    for(int i = 0; i < n; ++i){
        cout << a[i] << " ";
        if(i % perLine == perLine - 1) { cout << endl; }
    }
    cout << endl;
}

void prntAry(int **a, int r, int c){
        for(int i = 0; i < r; ++i){
        for(int j = 0; j < c; ++j){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

//Mark Sort
//Sort an array of integers
//INPUT:
//a[]
//The array to sort
//n
//The length of the array
//OUTPUT:
//a[]
//The sorted array
void mrkSort(int a[], int n){
    for(int i = 0; i < n - 1; ++i){
        for(int j = i + 1; j < n; ++j){
            if(a[i] > a[j]){
                a[i] = a[i] ^ a[j];
                a[j] = a[i] ^ a[j];
                a[i] = a[i] ^ a[j];
            }
        }
    }
}

