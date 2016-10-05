/* 
 * File:   MovData.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Store data about a film
 * Created on October 3, 2016
 */

#ifndef MOVDATA_H
#define MOVDATA_H

//System Libraries
#include <string>

//Movie Data
//Stores data relating to a single film
struct MovData{
    std::string title; //The film's title
    std::string dirctr; //The film's director
    unsigned short yearRel; //the film's year of release
    unsigned short runTime; //the film's run time in minutes
};

#endif /* MOVDATA_H */

