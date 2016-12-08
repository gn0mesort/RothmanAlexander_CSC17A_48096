/*
 * File:   game.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 5, 2016
 */

#include "functions.h"
#include "game.h"

/**
 * Game constructor. Serves to initialize a game
 */
Flow::Game::Game(){
    _player;
    _gmRand.srand();
    _pos;
    _config.asciiArt = true;
    _config.saveGame = "GameData/";
    _floor;
    _gameOver = false;

    _itmNames.addBack(ItemType::Potion, Collections::LinkedList<std::string>());
    _itmNames.addBack(ItemType::Armor, Collections::LinkedList<std::string>());
    _itmNames.addBack(ItemType::Weapon, Collections::LinkedList<std::string>());
    _weapNames.addBack(Job::Knight, Collections::LinkedList<std::string>());
    _weapNames.addBack(Job::Cleric, Collections::LinkedList<std::string>());
    _weapNames.addBack(Job::Lancer, Collections::LinkedList<std::string>());
    _weapNames.addBack(Job::Mage, Collections::LinkedList<std::string>());

    _indexPath = "GameData/index.sav";
    _confPath = "GameData/game.conf";

    rdTxt("GameData/monsters.txt", _monNames);
    rdTxt("GameData/uidpotionnames.txt", _itmNames[ItemType::Potion]);
    rdTxt("GameData/uidarmornames.txt", _itmNames[ItemType::Armor]);
    rdTxt("GameData/uidweaponnames.txt", _itmNames[ItemType::Weapon]);
    rdTxt("GameData/knightweapons.txt", _weapNames[Job::Knight]);
    rdTxt("GameData/clericweapons.txt", _weapNames[Job::Cleric]);
    rdTxt("GameData/lancerweapons.txt", _weapNames[Job::Lancer]);
    rdTxt("GameData/mageweapons.txt", _weapNames[Job::Mage]);
}

Flow::Config Flow::Game::config() const{
    return _config;
}

void Flow::Game::config(const Config &conf){
    _config = conf;
}

std::string Flow::Game::configPath() const{
    return _confPath;
}

Flow::Floor Flow::Game::floor() const{
    return _floor;
}

void Flow::Game::floor(const Floor &nFloor){
    _floor = nFloor;
}

Flow::GmRand Flow::Game::gmRand() const{
    return _gmRand;
}

std::string Flow::Game::indexPath() const{
    return _indexPath;
}

bool Flow::Game::isGameOver() const{
    return _gameOver;
}

Collections::Dictionary<Flow::ItemType, Collections::LinkedList<std::string>> Flow::Game::itemNames() const{
    return _itmNames;
}

Collections::LinkedList<std::string> Flow::Game::monsterNames() const{
    return _monNames;
}

Flow::Actor Flow::Game::player() const{
    return _player;
}

void Flow::Game::player(const Actor &nPlayer){
    _player = nPlayer;
}

Flow::Point Flow::Game::pos() const{
    return _pos;
}

void Flow::Game::pos(const Point &pos){
    _pos = pos;
}

void Flow::Game::setGameOver(bool gameOver){
    _gameOver = gameOver;
}

Collections::Dictionary<Flow::Job, Collections::LinkedList<std::string>> Flow::Game::weaponNames() const{
    return _weapNames;
}

void Flow::Game::play(){
    _floor = _gmRand.rFloor(_player.difficulty()); //Get a new random floor
    _pos = _floor.start(); //Move the player to the start cell
    _floor[_pos.y][_pos.x].event(Flow::RmEvent::None); //Set the start cell event to none
    do{ //While the game isn't over
        trigger(_floor[_pos.y][_pos.x]); //Trigger the cell event
        std::cout << std::endl;
    } while(!_gameOver);
    _gameOver = false; //Toggle the game over flag
}

bool Flow::Game::encounter(Actor &enemy){
    bool turn = false,
            r = false;

    do{
        enemy.hit(_player);
        if(_player.hp().value() > 0){
            do{
                std::cout << enemy.name() << ": " << enemy.hp().value() << "/" << enemy.hp().max() << " ";
                std::cout << enemy.hp().name() << std::endl;
                std::cout << _player.name() << ": " << _player.hp().value() << "/" << _player.hp().max() << " ";
                std::cout << _player.hp().name() << std::endl;
                turn = true;
                char input = menu({"Attack", "Inventory", "Player Status"}, 5);
                switch(input){
                    case 'A':
                    {
                        _player.hit(enemy);
                        turn = false;
                        break;
                    }
                    case 'I':
                    {
                        int index = _player.selectItem();
                        if(index > -1){
                            turn = false;
                        }
                        break;
                    }
                    case 'P':
                    {
                        stats(_player);
                        break;
                    }
                }
            } while(turn);
        }
    } while(_player.hp().value() > 0 && enemy.hp().value() > 0);
    if(_player.hp().value() > 0){
        _player.addItems(enemy);
        r = true;
    }
    else{
        if(_config.asciiArt){ //If ASCII art is on
            rdTxt("GameData/gameover.txt"); //Display game over screen
        }
        else{ //Otherwise
            std::cout << "GAME OVER!" << std::endl;
        }
        r = false;
    }

    return r;
}

void Flow::Game::trigger(Room &room){
    bool moved = false; //If the player has moved
    std::stringstream convert; //String stream for conversion
    convert << "GameData/desc" << (to_int(room.event()) * 3) + ((GmRand().rand() % 3) + 1) << ".txt"; //Get description path
    rdTxt(convert.str()); //Display Room description
    std::cout << std::endl;

    if(room.event() != RmEvent::None){ //If the RmEvent is not none
        if(room.event() == RmEvent::Encounter){ //If encounter
            Actor enem = rActor(*this); //Create enemy
            std::cout << "A " << enem.name() << " attacks!" << std::endl;
            _gameOver = !encounter(enem); //Process encounter
        }
        else if(room.event() == RmEvent::Treasure){ //If treasure;
            unsigned char tCount = (GmRand().rand() % 3) + 1; //Generate between 1 and 3 treasures

            for(int i = 0; i < tCount; ++i){ //For each treasure
                rItem(_player, *this); //Generate a treasure
            }
        }
        else if(room.event() == RmEvent::Spring){ //If spring
            _player.hp(_player.hp().max()); //Heal player
            _player.mp(_player.mp().max()); //Heal player
            std::cout << _player.name() << " is fully restored!" << std::endl;
            for(int i = 0; i < _player.invSize(); ++i){ //Identify Items
                _player.identify(i); //Identify
            }
            std::cout << "Items identified!" << std::endl;
        }
        room.event(RmEvent::None); //Clear room event
    }
    else{ //If the event is None
        std::cout << "There are exits to the ( " << Direct::toString(room.exit()) << ")" << std::endl; //Display Exits
        if(room.isEnd()){ //If this is the end Room
            std::cout << "You can see a flight of stairs in the far corner!" << std::endl; //Display End message
        }
        Collections::LinkedList<std::string> tmpMenu = {"Player Status", "Inventory", "Options", "Map"}; //Add exits to game menu
        if(FlagUtil::hasFlag(room.exit(), Direct::NORTH)){
            tmpMenu.addBack("North");
        }
        if(FlagUtil::hasFlag(room.exit(), Direct::EAST)){
            tmpMenu.addBack("East");
        }
        if(FlagUtil::hasFlag(room.exit(), Direct::SOUTH)){
            tmpMenu.addBack("South");
        }
        if(FlagUtil::hasFlag(room.exit(), Direct::WEST)){
            tmpMenu.addBack("West");
        }
        if(room.isEnd()){
            tmpMenu.addBack("Down");
        }
        do{ //While the player hasn't moved Rooms
            char input = menu(tmpMenu, 4); //Display the game menu
            switch(input){
                case 'P': //Player Status
                {
                    stats(_player);
                    break;
                }
                case 'I': //Inventory
                {
                    _player.selectItem();
                    break;
                }
                case 'O': //Options
                {
                    gameOptionsMenu();
                    if(_gameOver){ //If quitting
                        moved = true;
                    }
                    break;
                }
                case 'M': //Map
                {
                    _floor.draw(_pos); //Draw map
                    break;
                }
                default: //For anything else
                {
                    if(input == 'N' && FlagUtil::hasFlag(room.exit(), Direct::NORTH)){ //If moving North
                        _floor.move(_pos, Direct::NORTH);
                        moved = true;
                    }
                    else if(input == 'E' && FlagUtil::hasFlag(room.exit(), Direct::EAST)){ //If moving East
                        _floor.move(_pos, Direct::EAST);
                        moved = true;
                    }
                    else if(input == 'S' && FlagUtil::hasFlag(room.exit(), Direct::SOUTH)){ //If moving South
                        _floor.move(_pos, Direct::SOUTH);
                        moved = true;
                    }
                    else if(input == 'W' && FlagUtil::hasFlag(room.exit(), Direct::WEST)){ //If moving West
                        _floor.move(_pos, Direct::WEST);
                        moved = true;
                    }
                    else if(input == 'D' && room.isEnd()){ //If exiting the Floor
                        _gameOver = true; //Quit game
                        if(_config.asciiArt){ //If ASCII art is on
                            rdTxt("GameData/win.txt"); //Win message
                        }
                        else{ //Otherwise
                            std::cout << "YOU WIN!" << std::endl;
                        }
                        save(_config.saveGame + _player.name() + ".sav", *this); //Save the game
                        moved = true;
                    }
                }
            }
        } while(!moved);
    }
}

void Flow::Game::stats(const Actor &actor){
    std::cout << actor.name() << std::endl;
    std::cout << "Job: " << toString(actor.job()) << std::endl;
    std::cout << actor.hp().name() << ": " << actor.hp().value() << "/" << actor.hp().max() << std::endl;
    std::cout << actor.mp().name() << ": " << actor.mp().value() << "/" << actor.mp().max() << std::endl;
    std::cout << actor.attack().name() << ": " << to_int(actor.attack().value()) << std::endl;
    std::cout << actor.defense().name() << ": " << to_int(actor.defense().value()) << std::endl;
    std::cout << "Weapon: " << actor.weapon().name() << std::endl;
    std::cout << "\t" << actor.weapon().description() << std::endl;
    std::cout << "Armor: " << actor.armor().name() << std::endl;
    std::cout << "\t" << actor.armor().description() << std::endl;
}

void Flow::Game::gameOptionsMenu(){
    bool back = false; //Whether or not to go back
    Config nConf = _config; //Create a copy of the game config

    do{ //While not going back
        std::cout << "ASCII ART: " << (nConf.asciiArt ? "ON" : "OFF") << std::endl; //Display whether or not ASCII art is on
        std::cout << "GAME SAVE PATH: " << nConf.saveGame << std::endl; //Display the save game path
        std::cout << "MAX FLOOR SIZE: " << to_int(_player.difficulty()) << std::endl; //Display the maximum floor size. This is equal to the difficulty
        char input = menu({"Ascii Art", "Save Game", "Quit to menu", "Back"}, 4); //Do options menu processing
        switch(input){
            case 'A': //ASCII art
            {
                std::cout << "Toggle game ASCII art on or off" << std::endl;
                input = menu({"1 On", "2 Off"}, 2); //On off menu processing
                if(input == '1'){ //If on
                    nConf.asciiArt = true; //Turn on
                }
                else if(input == '2'){ //If off
                    nConf.asciiArt = false; //Turn off
                }
                break;
            }
            case 'S': //Save game
            {
                save(nConf.saveGame + _player.name() + ".sav", *this); //Save the game
                //Display where the game was saves to
                std::cout << "GAME SAVED to " << nConf.saveGame << _player.name() << ".sav" << std::endl;
                std::cout << std::endl;
                break;
            }
            case 'Q': //Quit to the menu
            {
                save(nConf.saveGame + _player.name() + ".sav", *this); //Save the game
                _gameOver = true; //end the game
                back = true; //go back
                break;
            }
            case 'B': //Back
            {
                back = true; //Go back
                break;
            }
        }
    } while(!back);
    _config = nConf; //Copy edited config back to the game config
}

void Flow::updateSaveIndex(const std::string &path, const Game &game){
    std::ofstream out;
    std::ifstream in;
    Collections::LinkedList<std::string> list;

    in.open(game.indexPath().c_str());
    if(in.is_open()){
        std::string input;
        while(getline(in, input)){
            list.addBack(input);
        }
    }
    in.close();

    out.open(game.indexPath().c_str(), std::fstream::trunc);
    if(out.is_open()){
        if(list.size() > 0){
            for(int i = 0; i < list.size(); ++i){
                out << list[i] << std::endl;
            }
        }
        out << path << std::endl;
    }
    out.close();
}

void Flow::save(const std::string &path, const Game &game){
    int header = HEADER;
    std::ofstream out;
    Actor player = game.player();

    if(!checkFile(path, HEADER)){
        updateSaveIndex(path, game);
    }
    out.open(path.c_str(), (std::ios::trunc | std::ios::binary));
    if(out.good()){

        Job job = player.job();
        int maxHp = player.hp().max(),
                maxMp = player.mp().max();
        unsigned char atk = player.attack().value(),
                def = player.defense().value(),
                diff = player.difficulty();
        RNGPoint weap = player.weapon().generationPoint(),
                armor = player.armor().generationPoint();


        out.write(to_bin(header), sizeof (header));
        out.write(to_bin(diff), sizeof (diff));
        writeBinary(player.name(), out);
        out.write(to_bin(job), sizeof (job));
        out.write(to_bin(maxHp), sizeof (maxHp));
        out.write(to_bin(maxMp), sizeof (maxMp));
        out.write(to_bin(atk), sizeof (atk));
        out.write(to_bin(def), sizeof (def));
        out.write(to_bin(weap.seed), sizeof (weap.seed));
        out.write(to_bin(weap.pos), sizeof (weap.pos));
        out.write(to_bin(armor.seed), sizeof (armor.seed));
        out.write(to_bin(armor.pos), sizeof (armor.pos));
    }
    else{
        out.close();
        throw Error::FileException();
    }
    out.close();
}

void Flow::Game::mainMenuOptions(){
    bool back = false; //Whether or not to go back

    Config nConf = _config;

    do{ //While not back
        std::cout << "ASCII ART: " << (nConf.asciiArt ? "ON" : "OFF") << std::endl; //Display whether or not ASCII art is on
        std::cout << "GAME SAVE PATH: " << nConf.saveGame << std::endl; //Display game save path
        char input = menu({"Ascii Art", "Save Path", "Back"}, 3); //Display option's menu
        switch(input){
            case 'A': //ASCII Art
            {
                std::cout << "Toggle game ASCII art on or off" << std::endl;
                char input = menu({"1 On", "2 Off"}, 2); //On off menu processing
                if(input == '1'){ //If on
                    nConf.asciiArt = true; //Turn on
                }
                else if(input == '2'){ //If off
                    nConf.asciiArt = false; //Turn off
                }
                break;
            }
            case 'S': //Save Path
            {
                std::cout << "Enter the new path to save to:" << std::endl;
                std::cout << "> ";
                std::getline(std::cin, nConf.saveGame); //Get the new save path
                break;
            }
            case 'B': //Back
            {
                back = true; //go back
                break;
            }
        }
    } while(!back);
    _config = nConf; //Copy the new config back to the game config
}

void Flow::load(const std::string &path, Game &game){
    Actor player;
    std::ifstream in;

    if(checkFile(path, HEADER)){
        in.open(path.c_str(), (std::ios::binary));
        if(in.good()){
            Job job;
            int maxHp,
                    maxMp;
            unsigned char atk,
                    def,
                    diff;
            RNGPoint weap,
                    armor;

            in.seekg(std::ios::beg + sizeof (HEADER));
            in.read(to_bin(diff), sizeof (diff));
            player.name(readBinary(in));
            in.read(to_bin(job), sizeof (job));
            in.read(to_bin(maxHp), sizeof (maxHp));
            in.read(to_bin(maxMp), sizeof (maxMp));
            in.read(to_bin(atk), sizeof (atk));
            in.read(to_bin(def), sizeof (def));
            in.read(to_bin(weap.seed), sizeof (weap.seed));
            in.read(to_bin(weap.pos), sizeof (weap.pos));
            in.read(to_bin(armor.seed), sizeof (armor.seed));
            in.read(to_bin(armor.pos), sizeof (armor.pos));

            player.difficulty(diff);
            player.job(job);
            IStat hp = player.hp();
            hp.max(maxHp);
            hp.value(hp.max());
            player.hp(hp);
            IStat mp = player.mp();
            mp.max(maxMp);
            mp.value(mp.max());
            player.mp(mp);
            player.attack(atk);
            player.defense(def);
            game.player(player);

            RNGPoint cache;
            cache.pos = GmRand().pos();
            cache.seed = GmRand().seed();
            if(weap.seed != 0){
                GmRand().seek(weap);
                rItem(player, game, ItemType::Weapon, false);
                player.use(0, false);
                player.removeItem(0);
            }
            else{
                Weapon weap = player.weapon();
                weap.name(game.weaponNames()[player.job()][GmRand().rand() % game.weaponNames()[player.job()].size()]);
                player.equip(weap, false);
            }
            if(armor.seed != 0){
                GmRand().seek(armor);
                rItem(player, game, ItemType::Armor, false);
                player.use(0, false);
                player.removeItem(0);
            }
            else{
                player.equip(Armor(DmgElem::NONE, 10), false);
            }
            GmRand().seek(cache);

            game.player(player);
        }
        else{
            in.close();
            throw Error::FileException();
        }
    }
    else{
        throw Error::FileException("Invalid File");
    }
}

bool Flow::Game::loadMenu(){
    bool r = false, //Return value
            back = false; //Whether or not to go back
    int input = 0; //The selected file
    Collections::LinkedList<std::string> paths, //Save file paths
            lMenu; //A menu of files to load
    try{
        rdTxt(_indexPath, paths); //Load save paths from index
    }
    catch(Error::FileException e){

    }
    for(int i = 0; i < paths.size(); ++i){ //Create the load menu
        lMenu.addBack(paths[i]);
    }
    lMenu.addBack("Back");

    do{ //While not going back
        input = intMenu(lMenu, 1); //Do load menu processing
        if(input > 0 && checkFile(paths[input - 1], HEADER)){ //If not going back and the file is valid
            char cInput = menu({"Load", "Delete", "Back"}, 3); //Do action menu processing
            switch(cInput){
                case 'L': //Load
                {
                    load(paths[input - 1], *this);
                    r = true; //Loaded a file
                    back = true; //Go back
                    break;
                }
                case 'D': //Delete
                {
                    std::remove(paths[input - 1].c_str()); //Remove the selected file
                    paths.remove(input - 1); //Erase the file from the loaded paths
                    lMenu.remove(input - 1); //Erase the file from the menu
                    std::ofstream out; //A file output stream

                    out.open(_indexPath, std::ios::trunc); //Open the save index
                    for(int i = 0; i < paths.size(); ++i){ //Output paths back into index
                        out << paths[i] << std::endl;
                    }
                    out.close(); //Close the index file
                    break;
                }
            }
        }
        else{
            back = true; //Go back
        }
    } while(!back);

    return r;
}

void Flow::Game::createCharacter(){
    std::string name; //An input string
    _player = Actor();

    //Get the player's name
    std::cout << "What's your name?" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, name);
    _player.name(name); //Set the name

    //Get the player's job
    std::cout << "Choose your class:" << std::endl;
    char input = menu({"Knight", "Cleric", "Mage", "Lancer"}, 4); //Display Job menu
    switch(input){
        case 'K': //Knight
        {
            _player.job(Job::Knight);
            break;
        }
        case 'C': //Cleric
        {
            _player.job(Job::Cleric);
            break;
        }
        case 'M': //Mage
        {
            _player.job(Job::Mage);
            break;
        }
        case 'L': //Lancer
        {
            _player.job(Job::Lancer);
            break;
        }
    }
    Weapon weap = _player.weapon();
    weap.name(_weapNames[_player.job()][GmRand().rand() % _weapNames[_player.job()].size()]);
    _player.equip(weap, false);
    _player.removeItem(0);
    _player.equip(Armor(DmgElem::NONE, 10), false);
    _player.removeItem(0);

    //Get the game difficulty
    std::cout << "Choose a difficulty:" << std::endl;
    input = menu({"Stroll" /*8*/, "Mosey" /*16*/, "Journey" /*32*/, "Adventure" /*40*/, "Quest" /*48*/,
                 "Epic" /*56*/}, 1);
    switch(input){
        case 'S': //Stroll the easiest difficulty
        {
            _player.difficulty(Diff::EASY);
            break;
        }
        case 'M': //Mosey the medium difficulty
        {
            _player.difficulty(Diff::MEDIUM);
            break;
        }
        case 'J': //Journey harder than medium easier than hard
        {
            _player.difficulty(Diff::EASY | Diff::MEDIUM);
            break;
        }
        case 'A': //Adventure the hard difficulty
        {
            _player.difficulty(Diff::HARD);
            break;
        }
        case 'Q': //Quest even harder
        {
            _player.difficulty(Diff::EASY | Diff::HARD);
            break;
        }
        case 'E': //Epic the hardest difficulty
        {
            _player.difficulty(Diff::EASY | Diff::MEDIUM | Diff::HARD);
            break;
        }
    }
}

Flow::Config Flow::loadConfig(const std::string &path){
    Config r;
    r.asciiArt = true;
    r.saveGame = "GameData/";

    std::ifstream in;
    if(checkFile(path, HEADER)){
        in.open(path, std::ios::binary);
        if(in.good()){
            in.seekg(std::ios::beg + sizeof (HEADER));
            in.read(to_bin(r.asciiArt), sizeof (r.asciiArt));
            r.saveGame = readBinary(in);
        }
    }
    in.close();

    return r;
}

void Flow::saveConfig(const std::string &path, Config config){
    int header = HEADER;
    std::ofstream out;

    out.open(path, std::ios::binary);
    if(out.good()){
        out.write(to_bin(header), sizeof (header));
        out.write(to_bin(config.asciiArt), sizeof (config.asciiArt));
        writeBinary(config.saveGame, out);
    }
    else{
        out.close();
        throw Error::FileException();
    }
    out.close();
}

Flow::Actor Flow::rActor(Game &game){
    unsigned char drops = 0; //The number of drop items
    int hp = GmRand().rand() % (game.player().hp().max() * 2) + 1; //HP is between 1 and 2 * the player's max HP
    int mp = GmRand().rand() % (game.player().mp().max() * 2) + 1; //MP is between 1 and 2 * the player's max MP
    unsigned char atk = GmRand().rand() % (game.player().attack().value() + 2); //Attack is between 0 and the player's attack + 2
    unsigned char def = GmRand().rand() % (game.player().attack().value() + 2); //Defense is between 0 and the player's defense + 2
    std::string name = game.monsterNames()[GmRand().rand() % game.monsterNames().size()]; //Generate the name
    //Generate weapons and armor
    //Both may have values between 0 and the player's bonus + 10
    Actor r; //The return Actor
    rItem(r, game, ItemType::Weapon, false);
    r.use(0, false);
    r.removeItem(0);
    rItem(r, game, ItemType::Armor, false);
    r.use(0, false);
    r.removeItem(0);

    r.name(name); //Set the name
    r.attack(atk); //Set the atk
    r.defense(def); //Set the def
    r.hp(IStat(hp, "HP", "Hit Points", hp, 0, 9999, 0)); //Set HP
    r.mp(IStat(mp, "MP", "Magic Points", mp, 0, 9999, 0)); //Set MP

    drops = (GmRand().rand() % 4); //Generate number of Item drops
    for(int i = 0; i < drops; ++i){ //For each drop
        rItem(r, game, ItemType::None, false); //Add a random Item
    }

    return r;
}

void Flow::rItem(Actor &target, Game &game, ItemType type, bool output){
    RNGPoint gen;
    gen.pos = GmRand().pos();
    gen.seed = GmRand().seed();
    unsigned char value = GmRand().rand() % (game.player().attack().value() + 50);
    unsigned char elem = GmRand().rElem();
    int percent = GmRand().rand() % 100;
    std::string uiName = "";

    if(type == ItemType::None){
        if(percent < 50){
            uiName = game.itemNames()[ItemType::Potion][GmRand().rand() % game.itemNames().size()];
            Potion itm("", uiName, "", elem, value);
            itm.generationPoint(gen);
            target.addItem(itm);
        }
        else if(percent >= 50 && percent < 70){
            uiName = game.itemNames()[ItemType::Armor][GmRand().rand() % game.itemNames().size()];
            Armor itm("", uiName, "", elem, value);
            itm.generationPoint(gen);
            target.addItem(itm);
        }
        else{
            uiName = game.itemNames()[ItemType::Weapon][GmRand().rand() % game.itemNames().size()];
            Weapon itm("", uiName, "", elem, value, false, &game.weaponNames()[game.player().job()]);
            itm.generationPoint(gen);
            target.addItem(itm);
        }
    }
    else{
        switch(type){
            case ItemType::Potion:
            {
                uiName = game.itemNames()[ItemType::Potion][GmRand().rand() % game.itemNames().size()];
                Potion itm("", uiName, "", elem, value);
                itm.generationPoint(gen);
                target.addItem(itm);
                break;
            }
            case ItemType::Weapon:
            {
                uiName = game.itemNames()[ItemType::Weapon][GmRand().rand() % game.itemNames().size()];
                Weapon itm("", uiName, "", elem, value, false, &game.weaponNames()[game.player().job()]);
                itm.generationPoint(gen);
                target.addItem(itm);
                break;
            }
            case ItemType::Armor:
            {
                uiName = game.itemNames()[ItemType::Armor][GmRand().rand() % game.itemNames().size()];
                Armor itm("", uiName, "", elem, value);
                itm.generationPoint(gen);
                target.addItem(itm);
                break;
            }
        }
    }
    if(output){
        std::cout << uiName << " acquired!" << std::endl;
    }
}