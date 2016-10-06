/* 
 * File:   MovData.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Store data about a film
 * Created on October 3, 2016
 */

#ifndef MOVDATA_H
#define MOVDATA_H

#include <string>

struct MovData{
    std::string title;
    std::string dirctr;
    unsigned short yearRel;
    unsigned short runTime;
    unsigned int cost;
    unsigned int revenue;
};

#endif /* MOVDATA_H */

