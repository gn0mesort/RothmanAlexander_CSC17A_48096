/*
 * File:   Actor.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 15, 2016
 */

#include <iostream>
#include <sstream>

#include "Actor.h"
#include "Room.h"
#include "Game.h"

Flow::Actor::Actor(){
    _job = Job::Knight;
    _hp = Flow::IStat(std::string("HP"), std::string("Hit Points"), 100);
    _mp = Flow::IStat(std::string("MP"), std::string("Magic Points"), 100);
    _atk = Flow::BStat(std::string("ATK"), std::string("Attack"), 10);
    _def = Flow::BStat(std::string("DEF"), std::string("Defense"), 10);
    _name = "Player";
    _weap = Flow::Item("Fists", "", "Your fists", Flow::DmgElem::NONE, Flow::ItmType::Weapon, 1, true);
    _armr = Flow::Item("Clothes", "", "Your Clothes", Flow::DmgElem::NONE, Flow::ItmType::Armor, 1, true);
}

Flow::Actor::Actor(const Actor &other){
    _job = other.job();
    _hp = Flow::IStat(other.hp());
    _mp = Flow::IStat(other.mp());
    _atk = Flow::BStat(other.atk());
    _def = Flow::BStat(other.def());
    _name = other.name();
    _weap = other.weap();
    _armr = other.armr();
    for(int i = 0; i < other.invSize(); ++i){
        _inv.push_back(other.getItem(i));
    }
}

Flow::Actor::Actor(const std::string &name, Job job){
    _job = job;
    _name = name;
    _hp = Flow::IStat(std::string("HP"), std::string("Hit Points"), 100);
    _mp = Flow::IStat(std::string("MP"), std::string("Magic Points"), 100);
    _atk = Flow::BStat(std::string("ATK"), std::string("Attack"), 10);
    _def = Flow::BStat(std::string("DEF"), std::string("Defense"), 10);
    _weap = Flow::Item("Fists", "", "Your fists", Flow::DmgElem::NONE, Flow::ItmType::Weapon, 1, true);
    _armr = Flow::Item("Clothes", "", "Your Clothes", Flow::DmgElem::NONE, Flow::ItmType::Armor, 1, true);
}

Flow::Job Flow::Actor::job() const{
    return _job;
}

void Flow::Actor::setJob(Job job){
    _job = job;
}

Flow::IStat Flow::Actor::hp() const{
    return _hp;
}

void Flow::Actor::setHp(const IStat &hp){
    _hp = Flow::IStat(hp);
}

Flow::IStat Flow::Actor::mp() const{
    return _mp;
}

void Flow::Actor::setMp(const IStat &mp){
    _mp = Flow::IStat(mp);
}

Flow::BStat Flow::Actor::atk() const{
    return _atk;
}

void Flow::Actor::setAtk(const BStat &atk){
    _atk = Flow::BStat(atk);
}

void Flow::Actor::setAtk(unsigned char atk){
    _atk.setValue(atk);
}

Flow::BStat Flow::Actor::def() const{
    return _def;
}

void Flow::Actor::setDef(const BStat &def){
    _def = Flow::BStat(def);
}

void Flow::Actor::setDef(unsigned char def){
    _def.setValue(def);
}

std::string Flow::Actor::name() const{
    return _name;
}

void Flow::Actor::setName(const std::string &name){
    _name = name;
}

unsigned int Flow::Actor::invSize() const{
    return _inv.size();
}

void Flow::Actor::addItem(const Flow::Item &itm){
    _inv.push_back(itm);
}

void Flow::Actor::rmItem(unsigned int index){
    _inv.erase(_inv.begin() + index);
}

Flow::Item Flow::Actor::getItem(unsigned int index) const{
    return _inv[index];
}

Flow::Item Flow::Actor::weap() const{
    return _weap;
}

Flow::Item Flow::Actor::armr() const{
    return _armr;
}

void Flow::Actor::equip(unsigned int index, bool output){
    if(_inv[index].type() == Flow::ItmType::Weapon){
        addItem(_weap);
        _weap = _inv[index];
        if(output){
            std::cout << _name << " equipped " << _weap.name() << std::endl;
        }
        rmItem(index);
    }
    else if(_inv[index].type() == Flow::ItmType::Armor){
        addItem(_armr);
        _armr = _inv[index];
        if(output){
            std::cout << _name << " equipped " << _armr.name() << std::endl;
        }
        rmItem(index);
    }
}

void Flow::Actor::equip(const Item &itm, bool output){
    if(itm.type() == Flow::ItmType::Weapon){
        _weap = itm;
        if(output){
            std::cout << _name << " equipped " << _weap.name() << std::endl;
        }
    }
    else if(itm.type() == Flow::ItmType::Armor){
        _armr = itm;
        if(output){
            std::cout << _name << " equipped " << _armr.name() << std::endl;
        }
    }
}

void Flow::Actor::use(unsigned int index){
    _inv[index].identify();
    if(_inv[index].type() == Flow::ItmType::Weapon || _inv[index].type() == Flow::ItmType::Armor){
        equip(index);
    }
    else if(_inv[index].type() == Flow::ItmType::Potion){
        Flow::Item target = Item(_inv[index]);
        std::cout << _name << " used " << target.name() << "." << std::endl;
        rmItem(index);
        if(target.element() == Flow::DmgElem::NONE){
            if(_inv.size() > 0){
                unsigned int select = 0;
                std::stringstream convert;
                std::string input = "";

                invMenu();
                do{
                    std::cout << "> ";
                    getline(std::cin, input);
                    convert << input;
                    convert >> select;
                } while(_inv[select].isIdent());
                _inv[select].identify();
                std::cout << _inv[select].uiName() << " is " << _inv[select].name() << std::endl;
            }
            else{
                std::cout << "Nothing happens." << std::endl;
            }
        }
        else if(target.element() == Flow::DmgElem::ABSOLUT){
            std::cout << _name << " was fully restored!" << std::endl;
            _hp.setVal(_hp.max());
            _mp.setVal(_mp.max());
        }
        else{
            if(Flow::FlgUtil::hasFlag(target.element(), Flow::DmgElem::HEALING)){
                std::cout << _name << " recovered " << toInt(target.value()) << " HP!" << std::endl;
                _hp.setVal(_hp.value() + target.value());
            }
            if(Flow::FlgUtil::hasFlag(target.element(), Flow::DmgElem::FIRE)){
                std::cout << _name << "'s attack power increased by " << toInt(target.value()) << std::endl;
                _atk.setValue(_atk.value() + target.value());
            }
            if(Flow::FlgUtil::hasFlag(target.element(), Flow::DmgElem::ICE)){
                std::cout << _name << "'s defense increased by " << toInt(target.value()) << std::endl;
                _def.setValue(_def.value() + target.value());
            }
            if(Flow::FlgUtil::hasFlag(target.element(), Flow::DmgElem::LIGHTNG)){
                std::cout << _name << "'s defense decreased by " << toInt(target.value()) << std::endl;
                _def.setValue(_def.value() - target.value());
            }
            if(Flow::FlgUtil::hasFlag(target.element(), Flow::DmgElem::WIND)){
                std::cout << _name << "'s attack power decreased by " << toInt(target.value()) << std::endl;
                _atk.setValue(_atk.value() - target.value());
            }
            if(Flow::FlgUtil::hasFlag(target.element(), Flow::DmgElem::HOLY)){
                std::cout << _name << "'s maximum HP has increased by " << toInt(target.value()) << std::endl;
                _hp.setMax(_hp.max() + target.value());
            }
            if(Flow::FlgUtil::hasFlag(target.element(), Flow::DmgElem::SHADOW)){
                std::cout << _name << "'s maximum MP has increased by " << toInt(target.value()) << std::endl;
                _mp.setMax(_mp.max() + target.value());
            }
            if(Flow::FlgUtil::hasFlag(target.element(), Flow::DmgElem::NGHTMRE)){
                std::cout << _name << " had a terrible nightmare!" << std::endl;
                for(int i = 0; i < _inv.size(); ++i){
                    _inv[i].obfscte();
                }
            }
        }

    }
}

void Flow::Actor::invMenu() const{
    for(int i = 0; i < _inv.size(); ++i){
        std::cout << frmtOpt(i + 1) << " ";
        if(_inv[i].isIdent()){
            std::cout << _inv[i].name() << std::endl;
            std::cout << "\t" << _inv[i].desc() << std::endl;
        }
        else{
            std::cout << _inv[i].uiName() << std::endl;
        }
    }
    if(_inv.size() > 0){
        std::cout << "(0) Back" << std::endl;
    }
}

void Flow::Actor::identify(unsigned int index){
    _inv[index].identify();
}

int Flow::Actor::selectItm(){
    int r = -1;
    if(_inv.size() > 0){
        std::string input = "";
        std::stringstream convert;

        do{
            std::cout << "> ";
            getline(std::cin, input);
            convert << input;
            convert >> r;
        } while(r < 0 || r >= _inv.size() + 1);
        if(r > 0){
            Game::input = menu({"Use", "Drop"}, 2);
            switch(Game::input){
                case 'U':
                {
                    use(r - 1);
                    break;
                }
                case 'D':
                {
                    std::cout << _name << " dropped ";
                    if(_inv[r - 1].isIdent()){
                        std::cout << _inv[r - 1].name() << std::endl;
                    }
                    else{
                        std::cout << _inv[r - 1].uiName() << std::endl;
                    }
                    rmItem(r - 1);
                }
            }
        }
    }

    return r;
}

void Flow::Actor::setHp(int value){
    _hp.setVal(value);
}

void Flow::Actor::setMp(int value){
    _mp.setVal(value);
}

void Flow::Actor::attack(Actor &target){
    int damage = 0;
    bool healing = Flow::FlgUtil::hasFlag(_weap.element(), Flow::DmgElem::HEALING)
            && _weap.element() != Flow::DmgElem::ABSOLUT;
    bool absorb = false;
    if(_weap.element() == Flow::DmgElem::ABSOLUT && target.armr().element() != Flow::DmgElem::ABSOLUT){
        damage = _weap.value() + _atk.value();
    }
    else if(target.armr().element() == Flow::DmgElem::ABSOLUT){
        damage = (_weap.value() + _atk.value()) / ((Game::gmRand.rand() % 3) + 1);
        damage -= (target.armr().value() + target.def().value()) / ((Game::gmRand.rand() % 3) + 1);
    }
    else if(_weap.element() != Flow::DmgElem::ABSOLUT && target.armr().element() == Flow::DmgElem::ABSOLUT){
        absorb = true;
    }
    else if(_weap.element() == target.armr().element() && _weap.element() != Flow::DmgElem::NONE){
        absorb = true;
    }
    else{
        damage = (_weap.value() + _atk.value()) / ((Game::gmRand.rand() % 3) + 1);
        damage -= (target.armr().value() + target.def().value()) / ((Game::gmRand.rand() % 3) + 1);
    }
    if(damage < 0){
        damage = 0;
    }
    if(!healing && !absorb){
        damage += (Game::gmRand.rand() % 5);
        if(damage > 0){
            std::cout << _name << " deals " << damage << " damage to " << target.name() << std::endl;
            target.setHp(target.hp().value() - damage);
        }
        else{
            std::cout << _name << " missed!" << std::endl;
        }
    }
    else if(healing && !absorb){
        std::cout << _name << " heals " << damage << " points to " << target.name() << std::endl;
        target.setHp(target.hp().value() + damage);
    }
    else if(absorb){
        std::cout << target.name() << " absorbed the damage!" << std::endl;
    }

}

void Flow::Actor::stat() const{
    std::cout << _name << std::endl;
    std::cout << "Job: ";
    if(_job == Flow::Job::Knight){
        std::cout << "Knight" << std::endl;
    }
    else if(_job == Flow::Job::Cleric){
        std::cout << "Cleric" << std::endl;
    }
    else if(_job == Flow::Job::Lancer){
        std::cout << "Lancer" << std::endl;
    }
    else if(_job == Flow::Job::Mage){
        std::cout << "Mage" << std::endl;
    }
    std::cout << _hp.flName() << ": " << _hp.value() << "/" << _hp.max() << std::endl;
    std::cout << _mp.flName() << ": " << _mp.value() << "/" << _mp.max() << std::endl;
    std::cout << _atk.flName() << ": " << toInt(_atk.value()) << std::endl;
    std::cout << _def.flName() << ": " << toInt(_def.value()) << std::endl;
    std::cout << "Weapon: " << _weap.name() << std::endl;
    std::cout << "\t" << _weap.desc() << std::endl;
    std::cout << "Armor: " << _armr.name() << std::endl;
    std::cout << "\t" << _armr.desc() << std::endl;
}