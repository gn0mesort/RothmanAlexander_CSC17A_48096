/* 
 * File:   Actor.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 15, 2016
 */

#ifndef ACTOR_H
#define ACTOR_H

namespace Flow{
    const unsigned char JOB_CNT = 4;

    enum class Job {
        None = 0,
        Knight = 1,
        Cleric = 2,
        Mage = 3,
        Lancer = 4 
    };

    class Actor{
    public:
        Job job();
        void setJob(Job);
    private:
        Job _job;
    };

}

#endif /* ACTOR_H */

