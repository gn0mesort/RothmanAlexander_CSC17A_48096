/* 
 * File:   Actor.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 15, 2016
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include "Stat.h"

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
        Actor();
        Actor(const Actor&);
        Actor(const std::string&, Job = Job::Knight);
        Job job() const;
        void setJob(Job);
        IStat hp() const;
        void setHp(const IStat&);
        IStat mp() const;
        void setMp(const IStat&);
        BStat atk() const;
        void setAtk(const BStat&);
        BStat def() const;
        void setDef(const BStat&);
        std::string name() const;
        void setName(const std::string&);
    private:
        Job _job;
        IStat _hp;
        IStat _mp;
        BStat _atk;
        BStat _def;
        std::string _name;
    };

}

#endif /* ACTOR_H */

