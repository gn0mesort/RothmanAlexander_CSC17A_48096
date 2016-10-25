/* 
 * File:   Actor.h
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 15, 2016
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <vector>

#include "Item.h"
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
        void setHp(int);
        IStat mp() const;
        void setMp(const IStat&);
        void setMp(int);
        BStat atk() const;
        void setAtk(const BStat&);
        void setAtk(unsigned char);
        BStat def() const;
        void setDef(const BStat&);
        void setDef(unsigned char);
        std::string name() const;
        void setName(const std::string&);
        void addItem(const Item&);
        Item getItem(unsigned int) const;
        void rmItem(unsigned int);
        unsigned int invSize() const;
        Item weap() const;
        Item armr() const;
        void equip(unsigned int, bool = true);
        void equip(const Item&, bool = true);
        void use(unsigned int);
        void invMenu() const;
        void identify(unsigned int);
        void attack(Actor&);
        void stat() const;
        int selectItm();
        BinArray toBin();
        void toActor(BinArray&);
    private:
        Job _job;
        IStat _hp;
        IStat _mp;
        BStat _atk;
        BStat _def;
        Item _weap;
        Item _armr;
        std::string _name;
        std::vector<Item> _inv;
    };

}

#endif /* ACTOR_H */

