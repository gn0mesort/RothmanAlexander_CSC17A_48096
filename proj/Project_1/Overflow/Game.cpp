/*
 * File:   Game.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on October 15, 2016
 */

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <sstream>

#include "Game.h"
#include "Room.h"
#include "Flags.h"


const std::string Flow::Config::SAVPATH = "GameData/game.conf";

std::vector<std::string> *Flow::Game::nWeaps = NULL;
Flow::Actor Flow::Game::player;
Flow::Point Flow::Game::pos;
Flow::GmRand Flow::Game::gmRand;
Flow::Config Flow::Game::conf;
Flow::Floor Flow::Game::floor;
std::vector<std::string> Flow::Game::mMenu;
std::vector<std::string> Flow::Game::bMenu;
std::vector<std::string> Flow::Game::gMenu;
std::vector<std::string> *Flow::Game::nItems = NULL;
std::vector<std::string> Flow::Game::nMons;
std::vector<std::string> Flow::Game::dMenu;
char Flow::Game::input = 0;
bool Flow::Game::over = false;

std::vector<std::string>* Flow::gNWeaps(){
    std::vector<std::string> *r = new std::vector<std::string>[JOB_CNT];

    for(int i = 0; i < JOB_CNT; ++i){
        std::string path;
        if(i == 0){
            path = "GameData/knightweapons.txt";
        }
        else if(i == 1){
            path = "GameData/clericweapons.txt";
        }
        else if(i == 2){
            path = "GameData/mageweapons.txt";
        }
        else{
            path = "GameData/lancerweapons.txt";
        }
        Flow::rdTxt(r[i], path);
    }

    return r;
}

std::vector<std::string>* Flow::gNItems(){
    std::vector<std::string> *r = new std::vector<std::string>[ITM_CNT];

    for(int i = 0; i < ITM_CNT; ++i){
        std::string path;
        if(i == 0){
            path = "GameData/uidpotionnames.txt";
        }
        else if(i == 1){
            path = "GameData/uidarmornames.txt";
        }
        else{
            path = "GameData/uidweaponnames.txt";
        }
        Flow::rdTxt(r[i], path);
    }

    return r;
}

void Flow::rdTxt(const std::string &path){
    std::ifstream in;

    in.open(path);
    while(in.good() && !in.eof()){
        std::string input;
        getline(in, input);
        std::cout << input << std::endl;
    }
    in.close();
}

void Flow::rdTxt(std::vector<std::string> &data, const std::string &path){
    std::ifstream in;

    in.open(path);
    while(in.good() && !in.eof()){
        std::string input;
        getline(in, input);
        if(input[input.size() - 1] == '\r'){ //This is needed to clean Windows line endings
            //Windows ends lines with \r\n rather than just \n
            input.erase(input.end() - 1);
        }
        if(!input.empty()){
            data.push_back(input);
        }
    }
    in.close();
}

bool Flow::ckFile(const std::string &path){
    bool r = false;
    int header = 0;
    std::ifstream in;

    in.open(path, in.binary);
    if(in.is_open()){
        in.read(reinterpret_cast<char*>(&header), sizeof (header));
    }
    r = in.is_open() && header == Game::HEADER;
    in.close();

    return r;
}

void Flow::init(){
    Game::nWeaps = gNWeaps();
    Game::nItems = gNItems();
    rdTxt(Game::nMons, std::string("GameData/monsters.txt"));
    Game::mMenu = {"New Game", "Load", "Options", "Help", "Exit"};
    Game::bMenu = {"Attack", "Inventory", "Status"};
    Game::gMenu = {"Player Status", "Inventory", "Options", "Map"};
    Game::dMenu = {"Stroll" /*8*/, "Mosey" /*16*/, "Journey" /*32*/, "Adventure" /*40*/, "Quest" /*48*/, "Epic" /*56*/};
    if(ckFile(Config::SAVPATH)){
        gConf();
    }
    else{
        Game::conf.ascArt = true;
        Game::conf.saveGame = "GameData/";
        Game::conf.diff = Diff::EASY;
    }
}

void Flow::cleanUp(){
    delete [] Game::nWeaps;
    Game::nWeaps = NULL;
    delete [] Game::nItems;
    Game::nItems = NULL;
}

unsigned int Flow::binPow(unsigned int pow){
    if(pow == 0){
        return 1;
    }
    else{
        return 2 * binPow(pow - 1);
    }
}

int Flow::toInt(unsigned char value){
    return static_cast<int>(value);
}

char Flow::menu(const std::vector<std::string> &opts, unsigned int perLine){
    std::string input = "";
    do{
        for(int i = 0; i < opts.size(); ++i){
            if(i % perLine != 0 && i != 0){
                std::cout << "     ";
            }
            if(i % perLine == 0){
                std::cout << std::endl;
            }
            std::cout << frmtOpt(opts[i]) << " ";
        }
        std::cout << std::endl << "> ";
        std::getline(std::cin, input);
    } while(!isValid(opts, input[0]));

    return std::toupper(input[0]);
}

int Flow::iMenu(const std::vector<std::string> &opts, unsigned int perLine){
    int r = 0;
    std::string input = "";
    std::stringstream convert;
    do{
        for(int i = 0; i < opts.size(); ++i){
            if(i % perLine != 0 && i != 0){
                std::cout << "     ";
            }
            if(i % perLine == 0){
                std::cout << std::endl;
            }
            std::cout << frmtOpt(opts[i]) << " ";
        }
        std::cout << std::endl << "> ";
        std::getline(std::cin, input);
    } while(!isValid(opts, input[0]));
    convert << input;
    convert >> r;

    return r;
}

std::string Flow::frmtOpt(const std::string &opt){
    std::string r = opt;

    r.insert(0, 1, '(');
    r.insert(2, 1, ')');

    return r;
}

std::string Flow::frmtOpt(int opt){
    std::stringstream r;

    r << '(' << opt << ')';

    return r.str();
}

bool Flow::isValid(const std::vector<std::string> &opts, char key){
    for(int i = 0; i < opts.size(); ++i){
        if(std::toupper(opts.at(i)[0]) == std::toupper(key)){
            return true;
        }
    }
    return false;
}

bool Flow::encounter(Actor &enem){
    bool turn = false;
    do{
        //Enemy Turn
        enem.attack(Game::player);

        //Player Turn
        if(Game::player.hp().value() > 0){
            do{
                std::cout << enem.name() << ": " << enem.hp().value() << "/" << enem.hp().max() << " ";
                std::cout << enem.hp().name() << std::endl;
                std::cout << Game::player.name() << ": " << Game::player.hp().value() << "/" << Game::player.hp().max();
                std::cout << " " << Game::player.hp().name() << std::endl;
                turn = true;
                Game::input = menu(Game::bMenu, 5);
                switch(Game::input){
                    case 'A':
                    {
                        Game::player.attack(enem);
                        turn = false;
                        break;
                    }
                    case 'I':
                    {
                        int index = 0;
                        Game::player.invMenu();
                        index = Game::player.selectItm();
                        if(index > -1){
                            turn = false;
                        }
                        break;
                    }
                    case 'S':
                    {
                        Game::player.stat();
                        break;
                    }
                }
            } while(turn);
        }
    } while(Game::player.hp().value() > 0 && enem.hp().value() > 0);
    if(Game::player.hp().value() > 0){
        for(int i = 0; i < enem.invSize(); ++i){
            Game::player.addItem(enem.getItem(i));
            std::cout << enem.getItem(i).uiName() << " acquired!" << std::endl;
        }
        return true;
    }
    else{
        if(Game::conf.ascArt){
            rdTxt(std::string("GameData/gameover.txt"));
        }
        else{
            std::cout << "GAME OVER!" << std::endl;
        }
        return false;
    }
}

void Flow::play(){
    Game::floor = Game::gmRand.rFloor(Game::conf.diff);
    Game::pos = Game::floor.start();
    Game::floor[Game::pos.y][Game::pos.x].setEvent(Flow::RmEvent::None);
    do{
        Game::floor[Game::pos.y][Game::pos.x].trigger();
        std::cout << std::endl;
    } while(!Game::over);
    Game::over = false;
}

Flow::Actor Flow::createChar(){
    std::vector<std::string> jMenu = {"Knight", "Cleric", "Mage", "Lancer"};
    std::string input;
    Actor r;
    std::cout << "What's your name?" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, input);
    r.setName(input);
    std::cout << "Choose your class:" << std::endl;
    Game::input = menu(jMenu, 4);
    switch(Game::input){
        case 'K':
        {
            r.setJob(Flow::Job::Knight);
            break;
        }
        case 'C':
        {
            r.setJob(Flow::Job::Cleric);
            break;
        }
        case 'M':
        {
            r.setJob(Flow::Job::Mage);
            break;
        }
        case 'L':
        {
            r.setJob(Flow::Job::Lancer);
            break;
        }
    }
    Game::player.setJob(r.job());
    r.equip(Item(Item::mkName(Flow::DmgElem::NONE, Flow::ItmType::Weapon),
                 Item::mkName(Flow::DmgElem::NONE, Flow::ItmType::Weapon),
                 Item::mkDesc(Flow::DmgElem::NONE, Flow::ItmType::Weapon, 10),
                 Flow::DmgElem::NONE, Flow::ItmType::Weapon, 10, true), false);
    r.equip(Item(Item::mkName(Flow::DmgElem::NONE, Flow::ItmType::Armor),
                 Item::mkName(Flow::DmgElem::NONE, Flow::ItmType::Armor),
                 Item::mkDesc(Flow::DmgElem::NONE, Flow::ItmType::Armor, 10),
                 Flow::DmgElem::NONE, Flow::ItmType::Armor, 10, true), false);
    std::cout << "Choose a difficulty:" << std::endl;
    Game::input = menu(Game::dMenu, 1);
    switch(Game::input){
        case 'S':
        {
            Game::conf.diff = Flow::Diff::EASY;
            break;
        }
        case 'M':
        {
            Game::conf.diff = Flow::Diff::MEDIUM;
            break;
        }
        case 'J':
        {
            Game::conf.diff = Flow::Diff::EASY | Flow::Diff::MEDIUM;
            break;
        }
        case 'A':
        {
            Game::conf.diff = Flow::Diff::HARD;
            break;
        }
        case 'Q':
        {
            Game::conf.diff = Flow::Diff::EASY | Flow::Diff::HARD;
            break;
        }
        case 'E':
        {
            Game::conf.diff = Flow::Diff::EASY | Flow::Diff::MEDIUM | Flow::Diff::HARD;
        }

    }

    return r;
}

void Flow::mMOpts(){
    bool back = false;
    Config nConf = Game::conf;
    std::vector<std::string> optMen = {"Ascii Art", "Save Path", "Back"};

    do{
        std::cout << "ASCII ART: " << (nConf.ascArt ? "ON" : "OFF") << std::endl;
        std::cout << "GAME SAVE PATH: " << nConf.saveGame << std::endl;
        Game::input = menu(optMen, 3);
        switch(Game::input){
            case 'A':
            {
                std::vector<std::string> tmp = {"1 On", "2 Off"};
                std::cout << "Toggle game ASCII art on or off" << std::endl;
                Game::input = menu(tmp, 2);
                if(Game::input == '1'){
                    nConf.ascArt = true;
                }
                else if(Game::input == '2'){
                    nConf.ascArt = false;
                }
                break;
            }
            case 'S':
            {
                std::cout << "Enter the new path to save to:" << std::endl;
                std::cout << "> ";
                std::getline(std::cin, nConf.saveGame);
                break;
            }
            case 'B':
            {
                back = true;
                break;
            }
        }
    } while(!back);
    Game::conf = nConf;

}

void Flow::gMOpts(){
    bool back = false;
    Config nConf = Game::conf;
    std::vector<std::string> optMen = {"Ascii Art", "Save Game", "Quit to menu", "Back"};

    do{
        std::cout << "ASCII ART: " << (nConf.ascArt ? "ON" : "OFF") << std::endl;
        std::cout << "GAME SAVE PATH: " << nConf.saveGame << std::endl;
        std::cout << "MAX FLOOR SIZE: " << toInt(nConf.diff) << std::endl;
        Game::input = menu(optMen, 4);
        switch(Game::input){
            case 'A':
            {
                std::vector<std::string> tmp = {"1 On", "2 Off"};
                std::cout << "Toggle game ASCII art on or off" << std::endl;
                Game::input = menu(tmp, 2);
                if(Game::input == '1'){
                    nConf.ascArt = true;
                }
                else if(Game::input == '2'){
                    nConf.ascArt = false;
                }
                break;
            }
            case 'S':
            {
                save();
                std::cout << "GAME SAVED to " << Game::conf.saveGame << Game::player.name() << ".sav" << std::endl;
                std::cout << std::endl;
                break;
            }
            case 'Q':
            {
                save();
                Game::over = true;
                back = true;
                break;
            }
            case 'B':
            {
                back = true;
                break;
            }
        }
    } while(!back);
    Game::conf = nConf;
}

void Flow::wConf(){
    unsigned int header = Game::HEADER;
    int len = Game::conf.saveGame.size() + 1;
    std::ofstream out;

    out.open(Game::conf.SAVPATH.c_str(), std::ios::binary | std::ios::trunc);
    out.write(reinterpret_cast<char*>(&header), sizeof (header));
    out.write(reinterpret_cast<char*>(&Game::conf.ascArt), sizeof (Game::conf.ascArt));
    out.write(reinterpret_cast<char*>(&len), sizeof (len));
    out.write(Game::conf.saveGame.c_str(), len);
    out.close();
}

void Flow::gConf(){
    unsigned int header = 0;
    int len = 0;
    char *buffer = NULL;
    std::ifstream in;

    in.open(Game::conf.SAVPATH.c_str(), std::ios::binary);
    in.read(reinterpret_cast<char*>(&header), sizeof (header));
    if(header == Game::HEADER){
        in.read(reinterpret_cast<char*>(&Game::conf.ascArt), sizeof (Game::conf.ascArt));
        in.read(reinterpret_cast<char*>(&len), sizeof (len));
        buffer = new char[len];
        in.read(buffer, len);
        Game::conf.saveGame = buffer;
        delete [] buffer;
    }
    in.close();
}

void Flow::save(){
    unsigned int header = Game::HEADER;
    std::string path = Game::conf.saveGame;
    if(path[path.size() - 1] != '/' && path[path.size() - 1] != '\\'){
        path += '/';
        Game::conf.saveGame += '/';
    }
    path += Game::player.name() + ".sav";
    std::fstream file;

    if(!ckFile(path)){
        std::ofstream create;
        create.open(path.c_str(), std::ios::binary);
        create.write(reinterpret_cast<char*>(&header), sizeof (header));
        create.close();
        create.open("GameData/index.sav", std::ios::app);
        create << path << std::endl;
        create.close();
    }

    file.open(path.c_str(), std::ios::binary | std::ios::in | std::ios::out);
    file.seekg(std::ios::beg + sizeof (header));
    file.write(reinterpret_cast<char*>(&Game::conf.diff), sizeof (Game::conf.diff));
    Game::player.toBin().write(file);
    file.close();
}

bool Flow::load(){
    bool r = false,
            back = false;
    int input = 0;
    std::vector<std::string> paths,
            lMenu,
            aMenu = {"Load", "Delete", "Back"};
    rdTxt(paths, "GameData/index.sav");
    for(int i = 0; i < paths.size(); ++i){
        std::stringstream convert;
        convert << i + 1;
        lMenu.push_back(convert.str() + " " + paths[i]);
    }
    lMenu.push_back("0 Back");

    do{
        input = iMenu(lMenu, 1);
        if(input > 0 && ckFile(paths[input - 1])){
            Game::input = menu(aMenu, 3);
            switch(Game::input){
                case 'L':
                {
                    std::fstream in;
                    BinArray data;

                    in.open(paths[input - 1].c_str(), std::ios::binary | std::ios::in | std::ios::ate);
                    data = BinArray(in.tellg());
                    in.seekg(std::ios::beg + sizeof (Game::HEADER));
                    in.read(reinterpret_cast<char*>(&Game::conf.diff), sizeof (Game::conf.diff));
                    data.read(in);
                    in.close();

                    Game::player.toActor(data);
                    r = true;
                    back = true;
                    break;
                }
                case 'D':
                {
                    std::remove(paths[input - 1].c_str());
                    paths.erase(paths.begin() + (input - 1));
                    std::ofstream out;

                    out.open("GameData/index.sav");
                    for(int i = 0; i < paths.size(); ++i){
                        out << paths[i];
                    }
                    out.close();
                    break;
                }
            }
        }
        else{
            back = true;
        }
    } while(!back);

    return r;
}

unsigned int Flow::strBSize(const std::string &str){
    return (sizeof (int) + (str.size() + 1));
}

int Flow::GmRand::rand(){
    ++_pos;
    return std::rand();
}

Flow::Room Flow::GmRand::rRoom(bool start, bool end){
    unsigned char rVal = rand() % 100;
    RmEvent event = RmEvent::None;

    if(rVal >= 0 && rVal < 50){
        event = RmEvent::Encounter;
    }
    else if(rVal >= 50 && rVal < 70){
        event = RmEvent::Treasure;
    }
    else if(rVal >= 70 && rVal < 80){
        event = RmEvent::Spring;
    }

    return Room(Flow::Direct::NONE, event, start, end);
}

unsigned char Flow::GmRand::rDirect(){
    unsigned char r = Flow::Direct::NONE;

    switch(rand() % 4){
        case 0:
        {
            r = Flow::Direct::NORTH;
            break;
        }
        case 1:
        {
            r = Flow::Direct::EAST;
            break;
        }
        case 2:
        {
            r = Flow::Direct::SOUTH;
            break;
        }
        case 3:
        {
            r = Flow::Direct::WEST;
            break;
        }
    }

    return r;
}

unsigned char Flow::GmRand::rElem(){
    unsigned char val = rand() % 100;
    unsigned char r = 0;

    if(val < 75){
        r = Flow::DmgElem::NONE;
    }
    else if(val >= 75 && val < 95){
        r = (rand() % 29) + 2;
    }
    else{
        r = rand() % 256;
    }

    if((rand() % 1000) != 0 && Flow::FlgUtil::hasFlag(r, Flow::DmgElem::HEALING)){
        r ^= Flow::DmgElem::HEALING;
    }

    return r;
}

Flow::Floor Flow::GmRand::rFloor(unsigned char size){
    Flow::Floor r;
    Flow::Point pos;
    Flow::Point last;
    bool filled[r.sizeY()][r.sizeX()] = {};
    unsigned char direct = Flow::Direct::NONE;

    pos.x = rand() % r.sizeX();
    pos.y = rand() % r.sizeY();

    for(int i = 0; i < size; i += filled[last.y][last.x]){
        last.x = pos.x;
        last.y = pos.y;

        if(i == 0){
            r[pos.y][pos.x] = rRoom(true);
            filled[pos.y][pos.x] = true;
            do{
                direct = rDirect();
            } while(!r.move(pos, direct));
            r[last.y][last.x].addExit(direct);

        }
        else if(i == size - 1){
            if(!filled[pos.y][pos.x]){
                r[pos.y][pos.x] = rRoom(false, true);
                filled[pos.y][pos.x] = true;
            }
            else{
                r[pos.y][pos.x] = Room(r[pos.y][pos.x].exit(), r[pos.y][pos.x].event(), false, true);
            }
            r[pos.y][pos.x].addExit(Flow::Direct::reverse(direct));
        }
        else{
            if(!filled[pos.y][pos.x]){
                r[pos.y][pos.x] = rRoom();
                filled[pos.y][pos.x] = true;
            }
            r[pos.y][pos.x].addExit(Flow::Direct::reverse(direct));
            do{
                direct = rDirect();
            } while(!r.move(pos, direct));
            r[last.y][last.x].addExit(direct);
        }
    }

    return r;
}

Flow::Item Flow::GmRand::rItem(bool ident){
    unsigned char value = rand() % 256;
    unsigned char elem = rand() % 256;
    int tInt = rand() % 100;
    if(tInt < 50){
        tInt = 1;
    }
    else if(tInt >= 50 && tInt < 70){
        tInt = 2;
    }
    else{
        tInt = 3;
    }
    Flow::ItmType type = static_cast<Flow::ItmType>(tInt);

    std::string uiName = Game::nItems[tInt - 1][rand() % Game::nItems[tInt - 1].size()];

    return Item(Item::mkName(elem, type), uiName, Item::mkDesc(elem, type, value), elem, type, value, ident);

}

Flow::Actor Flow::GmRand::rActor(){
    unsigned char drops = 0;
    int hp = rand() % (Game::player.hp().max() * 2);
    int mp = rand() % (Game::player.mp().max() * 2);
    unsigned char atk = rand() % (Game::player.atk().value() + 2);
    unsigned char def = rand() % (Game::player.atk().value() + 2);
    std::string name = Game::nMons[rand() % Game::nMons.size()];
    Flow::Item weap = Item("", "", "", rElem(), Flow::ItmType::Weapon, rand() % (Game::player.weap().value() + 10), true);
    Flow::Item armr = Item("", "", "", rElem(), Flow::ItmType::Weapon, rand() % (Game::player.armr().value() + 10), true);
    Flow::Actor r;

    r.equip(weap, false);
    r.equip(armr, false);
    r.setName(name);
    r.setAtk(atk);
    r.setDef(def);
    r.setHp(Flow::IStat(std::string("HP"), std::string("Hit Points"), hp, hp));
    r.setMp(Flow::IStat(std::string("MP"), std::string("Magic Points"), mp, mp));

    drops = (rand() % 4);
    for(int i = 0; i < drops; ++i){
        r.addItem(rItem());
    }

    return r;
}

unsigned int Flow::GmRand::seed(){
    return _seed;
}

void Flow::GmRand::srand(){
    std::srand(_seed);
    _pos = 0;
}

void Flow::GmRand::srand(unsigned int seed){
    std::srand(seed);
    _seed = seed;
    _pos = 0;
}

unsigned int Flow::GmRand::pos(){
    return _pos;
}

void Flow::GmRand::seek(unsigned int pos){
    std::srand(_seed);
    for(int i = 0; i < pos; ++i){
        std::rand();
    }
    _pos = pos;
}

Flow::GmRand::GmRand(){
    _pos = 0;
    _seed = static_cast<int>(time(0));
    srand();
}