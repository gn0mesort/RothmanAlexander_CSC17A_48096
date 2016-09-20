/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 1, 2015, 5:27 PM
 * Purpose:   Determine Statistics of The Game of Craps
 * Homework:  Use Gliffy to Flowchart
 */

//System Libraries
#include <iostream> //Input/Output stream Library
#include <cstdlib>  //Random Library
#include <ctime>    //Time Library
#include <iomanip>  //Format Library
using namespace std;//Utilize standard name-space directly

//User Libraries

//Global Constants
const int COL=2;//Static Array Column Size

//Function Prototypes - Roll the Dice and Output relevant statistics
unsigned short rollDie(const unsigned char &,const unsigned char& = 6);
void outStat(const int [][COL],const int &,const int &);

/******************************************************************************/
/*************************** Craps Simulation **********************************
********************************************************************************
00000000011111111112222222222333333333344444444445555555555666666666677777777778
12345678901234567890123456789012345678901234567890123456789012345678901234567890
 * Input
 *      nGames -> Number of Games [0, 10^9] at max takes about 2 minutes
 * Output
 *      All Statistics
 *          Overall wins/losses and individual sum win/loss percentages
*******************************************************************************/
int main(int argc, char** argv) {
    //Set random number seed with respect to time.
    srand(static_cast<unsigned int>(time(0)));
    //Declare variables
    unsigned int nGames=50000000,nDie=2;//Number of Games and Dice
    int nThrows=0,mxThrow=0; //Counters for number of Throws and max Throws
    const int ROW=13;        //Static Size of Frequency Array Counter
    int winLoss[ROW][COL]={};//Initialize 2-D Static Array to 0
    //Play the game
    for(unsigned int game=1;game<=nGames;game++){
        //Throw the dice
        int sum1=rollDie(nDie),gThrow=0;
        nThrows++;gThrow++;
        //Win-Loss or keep rolling
        switch(sum1){
            case 7:case 11:         winLoss[sum1][0]++;break;//Win
            case 2:case  3:case 12: winLoss[sum1][1]++;break;//Loss
            default:{
                //Keep rolling until original or 7 are thrown.
                bool stop=false;//Boolean to end the Game
                do{//Roll the die again till stopping condition reached
                    int sumN=rollDie(nDie);//Obtain a new sum to compare
                    nThrows++;gThrow++;//Increment the throws per game
                    //Check for win or loss
                    if(sumN==7){//Rolling a 7 before the original is a Loss
                        winLoss[sum1][1]++;//Increment the Loss
                        stop=true;//End the game
                    }else if(sumN==sum1){//Roll the original before 7 is a win
                        winLoss[sum1][0]++;//Increment the Win
                        stop=true;//End the game
                    }
                }while(!stop);//Exit the game loop
            }
        }
        if(gThrow>mxThrow)mxThrow=gThrow;//Keep track of max Throws in a Game
    }
    //Output all the relevant statistics for a Craps game
    cout<<"Games played = "<<nGames<<endl;
    cout<<"Averaqe Throws/Game = "<<1.0f*nThrows/nGames<<endl;//Casting
    cout<<"During one of the games a set of dice was thrown "
        <<mxThrow<<"(times)"<<endl;
    outStat(winLoss,nGames,ROW);
    //Exit stage right
    return 0;
}

/******************************************************************************/
/*************************** Output Statistics *********************************
********************************************************************************
00000000011111111112222222222333333333344444444445555555555666666666677777777778
12345678901234567890123456789012345678901234567890123456789012345678901234567890
 * Inputs 
 *      winLoss -> Static 2 Dim Array contains statistics of Wins and Losses
 *      nGames  -> Number of Games 1 to 5x10^8, not to exceed -> 1 minute
 *      SIZE    -> Index of winLoss rows 0 to 12 covers values 2 to 12
*******************************************************************************/
void outStat(const int winLoss[][COL],const int &nGames,const int &SIZE){
    //Declare Variables
    int totWin=0,totLoss=0,totGame;//Self Explanatory
    for(int i=0;i<SIZE;i++){//Loop and add all wins and losses
        totWin+=winLoss[i][0];//Wins in column 1 index 0
        totLoss+=winLoss[i][1];//Loss in column 2 index 1
    }
    totGame=totWin+totLoss;//Should equal the number of games played
    //Output the total Stats
    cout<<"Total Games Played "<<totGame<<" = "<<nGames<<endl;
    cout<<"Total Wins   = "<<totWin<<endl;
    cout<<"Total Lost   = "<<totLoss<<endl;
    cout<<"Percent Win  = "<<100.0f*totWin/totGame<<"%"<<endl; //Casting
    cout<<"Percent Loss = "<<100.0f*totLoss/totGame<<"%"<<endl;//Casting
    //Output the individual Stats compared to total
    cout<<"Wins and Losses compared to total"<<endl;
    cout<<"Die   Win%   Loss%"<<endl;
    cout<<fixed<<setprecision(2)<<showpoint;
    for(int i=2;i<SIZE;i++){//Loop and output percentages to total
        cout<<setw(2)<<i
            <<setw(8)<<100.0f*winLoss[i][0]/totGame
            <<setw(8)<<100.0f*winLoss[i][1]/totGame<<endl;
    }
    cout<<"Wins and Losses compared to Die thrown"<<endl;
    cout<<"Die   Win%   Loss%"<<endl;
    cout<<fixed<<setprecision(2)<<showpoint;
    for(int i=2;i<SIZE;i++){//Loop and output percentages to sum
        cout<<setw(2)<<i
            <<setw(8)<<100.0f*winLoss[i][0]/(winLoss[i][0]+winLoss[i][1])
            <<setw(8)<<100.0f*winLoss[i][1]/(winLoss[i][0]+winLoss[i][1])<<endl;
    }
}

/******************************************************************************/
/*************************** Roll All the Die **********************************
********************************************************************************
00000000011111111112222222222333333333344444444445555555555666666666677777777778
12345678901234567890123456789012345678901234567890123456789012345678901234567890
 * Inputs 
 *      nDice  -> Number of Die to Roll [1,255]
 *      sides  -> Number of sides for each Die [2,255]
 * Output
 *      sum    -> Value of all die thrown [2,65,535]
*******************************************************************************/
unsigned short rollDie(const unsigned char &nDice,const unsigned char &sides){
    //Validate Inputs
    if(nDice==0||sides<2)return false;//If invalid return 0
    //Declare variables
    unsigned short sum=0;//Keep track of die rolled and their sum
    unsigned char roll=0;//Roll each die, one at a time
    //Sum the value of all the die rolled
    while(++roll<=nDice){     //Keep rolling until roll>nDice
        sum+=(rand()%sides+1);//Randomly throw a 
    }
    return sum;
}