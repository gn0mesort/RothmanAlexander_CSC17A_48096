/* 
 * File:   Speaker.h
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Store data on a single speaker
 * Created on October 4, 2016
 */

#ifndef SPEAKER_H
#define SPEAKER_H

//System Libraries
#include <string> //String type and functions

//Speaker
//Store data on a speaker

struct Speaker{
    std::string name; //The name of the speaker
    std::string tel; //The speaker's telephone number
    std::string topic; //The speaker's topic
    unsigned int fee; //The speaker's fee
};

#endif /* SPEAKER_H */

