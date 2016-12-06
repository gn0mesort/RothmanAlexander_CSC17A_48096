///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///*
// * File:   game.cpp
// * Author: Alexander Rothman <alexander@megate.ch>
// * Purpose:
// * Created on December 2, 2016
// */
//
//#include "game.h"
//
//
//Collections::Dictionary<std::string, std::shared_ptr<void>> Flow::Game::_data;
//
///**
// * Set a pointer to a value in the game
// * @param key The key to the input pointer
// * @param ptr The pointer to set
// */
//void Flow::Game::set(const std::string &key, const std::shared_ptr<void> &ptr){
//    _data.addBack(key, ptr);
//}
//
///**
// * Remove a pointer to a value from the game
// * @param key The key to the pointer to remove
// */
//void Flow::Game::unset(const std::string &key){
//    _data.remove(key);
//}
//
///**
// * Return a pointer to a value in the game
// * @param key The key to the pointer to get
// */
////std::shared_ptr<void> Flow::Game::get(const std::string &key){
////    return _data[key];
////}
//
///**
// * Get the size of the underlying Dictionary
// * @return The current size of the Dictionary
// */
//unsigned int Flow::Game::size(){
//    return _data.size();
//}
//
///**
// * Eliminates any pointer in the Dictionary which points to 0
// */
//void Flow::Game::recover(){
//    Collections::LinkedList<std::string> keys = _data.keys();
//    for(unsigned int i = 0; i < _data.size(); ++i){
//        if(_data[keys[i]] == 0){
//            _data.remove(keys[i]);
//        }
//    }
//}
//
//void Flow::init(){
//    std::shared_ptr<Collections::Dictionary<ItemType, Collections::LinkedList < std::string>>> itmNames =
//            std::make_shared<Collections::Dictionary<ItemType, Collections::LinkedList < std::string>>>();
//    itmNames->addBack(ItemType::Armor, Collections::LinkedList<std::string>());
//    itmNames->addBack(ItemType::Weapon, Collections::LinkedList<std::string>());
//    itmNames->addBack(ItemType::Potion, Collections::LinkedList<std::string>());
//    std::shared_ptr<Collections::Dictionary<Job, Collections::LinkedList < std::string>>> weapNames =
//            std::make_shared<Collections::Dictionary<Job, Collections::LinkedList < std::string>>>();
//    weapNames->addBack(Job::Knight, Collections::LinkedList<std::string>());
//    weapNames->addBack(Job::Cleric, Collections::LinkedList<std::string>());
//    weapNames->addBack(Job::Lancer, Collections::LinkedList<std::string>());
//    weapNames->addBack(Job::Mage, Collections::LinkedList<std::string>());
//    Game::set("player", std::make_shared<Actor>());
//    Game::set("rand", std::make_shared<GmRand>());
//    Game::set("player_pos", std::make_shared<Point>());
//    Game::set("game_config", std::make_shared<Config>());
//    Game::set("floor", std::make_shared<Floor>());
//    Game::set("game_over", std::make_shared<bool>(false));
//    Game::set("monster_names", std::make_shared<Collections::LinkedList < std::string >> ());
//    Game::set("item_names", itmNames);
//    Game::set("weapon_names", weapNames);
//    Game::set("save_index", std::make_shared<std::string>("GameData/index.sav"));
//
//    //Game Menus
//    Game::set("game_menu", std::make_shared <Collections::LinkedList < std::string >> ());
//    Game::set("battle_menu", std::make_shared<Collections::LinkedList < std::string >> ());
//
//    Game::get<GmRand>("rand")->srand();
//    rdTxt("GameData/uidarmornames.txt", (*itmNames)[ItemType::Armor]);
//    rdTxt("GameData/uidweaponnames.txt", (*itmNames)[ItemType::Weapon]);
//    rdTxt("GameData/uidpotionnames.txt", (*itmNames)[ItemType::Potion]);
//    rdTxt("GameData/knightweapons.txt", (*weapNames)[Job::Knight]);
//    rdTxt("GameData/clericweapons.txt", (*weapNames)[Job::Cleric]);
//    rdTxt("GameData/lancerweapons.txt", (*weapNames)[Job::Lancer]);
//    rdTxt("GameData/mageweapons.txt", (*weapNames)[Job::Mage]);
//    rdTxt("GameData/monsters.txt", *Game::get<Collections::LinkedList < std::string >> ("monster_names"));
//}
//
//void Flow::cleanup(){ }
//
//void Flow::rdTxt(const std::string &path){
//    std::ifstream in;
//
//    in.open(path.c_str());
//    if(in.good()){
//        std::string str;
//        while(getline(in, str)){
//            std::cout << str << std::endl;
//        }
//    }
//    else{
//        in.close();
//        throw Error::FileException("File Not Found");
//    }
//    in.close();
//}
//
//void Flow::rdTxt(const std::string &path, Collections::LinkedList<std::string> &data){
//    std::ifstream in;
//
//    in.open(path.c_str());
//    if(in.good()){
//        std::string str;
//        while(getline(in, str)){
//            if(str[str.size() - 1] == '\r'){ //This is needed to clean Windows line endings
//                //Windows ends lines with \r\n rather than just \n
//                str.erase(str.end() - 1); //Clean line ending
//            }
//            if(!str.empty()){ //If the input is not an empty string
//                data.addBack(str); //Add the input to the vector
//            }
//        }
//    }
//    else{
//        in.close();
//        throw Error::FileException("File Not Found");
//    }
//    in.close();
//}
//
//bool Flow::encounter(Actor &enemy){
//    bool turn = false,
//            r = false;
//    std::shared_ptr<Actor> player = Game::get<Actor>("player");
//    std::shared_ptr<Collections::LinkedList < std::string>> bMenu =
//            Game::get<Collections::LinkedList < std::string >> ("battle_menu");
//    std::shared_ptr<Config> conf = Game::get<Config>("game_config");
//    do{
//        enemy.hit(*player);
//
//        if(player->hp().value() > 0){
//            do{
//                std::cout << enemy.name() << ": " << enemy.hp().value() << "/" << enemy.hp().max() << " ";
//                std::cout << enemy.hp().name() << std::endl;
//                std::cout << player->name() << ": " << player->hp().value() << "/" << player->hp().max() << " ";
//                std::cout << player->hp().name() << std::endl;
//                turn = true;
//                char input = menu(*bMenu, 5);
//                switch(input){
//                    case 'A':
//                    {
//                        player->hit(enemy);
//                        turn = false;
//                        break;
//                    }
//                    case 'I':
//                    {
//                        int index = player->selectItem();
//                        if(index > -1){
//                            turn = false;
//                        }
//                        break;
//                    }
//                    case 'P':
//                    {
//                        stats(*player);
//                        break;
//                    }
//                }
//            } while(turn);
//        }
//    } while(player->hp().value() > 0 && enemy.hp().value() > 0);
//    if(player->hp().value() > 0){
//        player->addItems(enemy);
//        r = true;
//    }
//    else{
//        if(conf->asciiArt){ //If ASCII art is on
//            rdTxt("GameData/gameover.txt"); //Display game over screen
//        }
//        else{ //Otherwise
//            std::cout << "GAME OVER!" << std::endl;
//        }
//    }
//}
//
//char Flow::menu(const Collections::LinkedList<std::string> &opts, int perLine){
//    std::string input = "";
//
//    do{
//        for(int i = 0; i < opts.size(); ++i){
//            if(i % perLine != 0 && i != 0){
//                std::cout << "     ";
//            }
//            if(i % perLine == 0){
//                std::cout << std::endl;
//            }
//            std::cout << formatOption(opts[i]) << " ";
//        }
//        std::cout << std::endl << "> ";
//        getline(std::cin, input);
//    } while(!isValid(opts, input[0]));
//
//    return std::toupper(input[0]);
//}
//
//void Flow::stats(const Actor &actor){
//    std::cout << actor.name() << std::endl;
//    std::cout << actor.hp().name() << ": " << actor.hp().value() << "/" << actor.hp().max() << std::endl;
//    std::cout << actor.mp().name() << ": " << actor.mp().value() << "/" << actor.mp().max() << std::endl;
//    std::cout << actor.attack().name() << ": " << to_int(actor.attack().value()) << std::endl;
//    std::cout << actor.defense().name() << ": " << to_int(actor.defense().value()) << std::endl;
//    std::cout << "Weapon: " << actor.weapon().name() << std::endl;
//    std::cout << "\t" << actor.weapon().description() << std::endl;
//    std::cout << "Armor: " << actor.armor().name() << std::endl;
//    std::cout << "\t" << actor.armor().description() << std::endl;
//}
//
//void Flow::getOptionsMenu(){ }
//
//void Flow::save(const std::string &path, const Actor &player){
//    int header = HEADER;
//    std::ofstream out;
//
//    if(!checkFile(path)){
//        updateSaveIndex(path);
//    }
//    out.open(path.c_str(), (std::ios::trunc | std::ios::binary));
//    if(out.good()){
//
//        Job job = player.job();
//        int maxHp = player.hp().max(),
//                maxMp = player.mp().max();
//        unsigned char atk = player.attack().value(),
//                def = player.defense().value(),
//                diff = player.difficulty();
//        RNGPoint weap = player.weapon().generationPoint(),
//                armor = player.armor().generationPoint();
//
//
//        out.write(to_bin(header), sizeof (header));
//        out.write(to_bin(diff), sizeof (diff));
//        writeBinary(player.name(), out);
//        out.write(to_bin(job), sizeof (job));
//        out.write(to_bin(maxHp), sizeof (maxHp));
//        out.write(to_bin(maxMp), sizeof (maxMp));
//        out.write(to_bin(atk), sizeof (atk));
//        out.write(to_bin(def), sizeof (def));
//        out.write(to_bin(weap.seed), sizeof (weap.seed));
//        out.write(to_bin(weap.pos), sizeof (weap.pos));
//        out.write(to_bin(armor.seed), sizeof (armor.seed));
//        out.write(to_bin(armor.pos), sizeof (armor.pos));
//    }
//    else{
//        out.close();
//        throw Error::FileException();
//    }
//    out.close();
//}
//
//void Flow::load(const std::string &path, Actor &player){
//    std::ifstream in;
//
//    if(checkFile(path)){
//        in.open(path.c_str(), (std::ios::binary));
//        if(in.good()){
//            Job job;
//            int maxHp,
//                    maxMp;
//            unsigned char atk,
//                    def,
//                    diff;
//            RNGPoint weap,
//                    armor;
//
//            in.seekg(std::ios::beg + sizeof (HEADER));
//            in.read(to_bin(diff), sizeof (diff));
//            player.name(readBinary(in));
//            in.read(to_bin(job), sizeof (job));
//            in.read(to_bin(maxHp), sizeof (maxHp));
//            in.read(to_bin(maxMp), sizeof (maxMp));
//            in.read(to_bin(atk), sizeof (atk));
//            in.read(to_bin(def), sizeof (def));
//            in.read(to_bin(weap.seed), sizeof (weap.seed));
//            in.read(to_bin(weap.pos), sizeof (weap.pos));
//            in.read(to_bin(armor.seed), sizeof (armor.seed));
//            in.read(to_bin(armor.pos), sizeof (armor.pos));
//
//            player.difficulty(diff);
//            player.job(job);
//            IStat hp = player.hp();
//            hp.max(maxHp);
//            hp.value(hp.max());
//            player.hp(hp);
//            IStat mp = player.mp();
//            mp.max(maxMp);
//            mp.value(mp.max());
//            player.mp(mp);
//            player.attack(atk);
//            player.defense(def);
//
//
//            std::shared_ptr<GmRand> gmRand = Game::get<GmRand>("rand");
//            RNGPoint cache;
//            cache.pos = gmRand->pos();
//            cache.seed = gmRand->seed();
//            gmRand->seek(weap);
//            gmRand->rItem(player, ItemType::Weapon);
//            player.use(0);
//            gmRand->seek(armor);
//            gmRand->rItem(player, ItemType::Armor);
//            player.use(0);
//            gmRand->seek(cache);
//        }
//        else{
//            in.close();
//            throw Error::FileException();
//        }
//    }
//    else{
//        throw Error::FileException("Invalid File");
//    }
//}
//
//bool Flow::checkFile(const std::string &path){
//    bool r = false;
//    int header = 0;
//    std::ifstream in;
//
//    in.open(path.c_str(), std::ios::binary);
//    if(in.is_open()){
//        in.read(to_bin(header), sizeof (header));
//    }
//    r = in.is_open() && header == HEADER;
//    in.close();
//
//    return r;
//}
//
//void Flow::updateSaveIndex(const std::string &path){
//    std::shared_ptr<std::string> index = Game::get<std::string>("save_index");
//    std::ofstream out;
//
//    out.open(index->c_str(), std::ios::app);
//    if(out.good()){
//        out << path << std::endl;
//    }
//    else{
//        out.close();
//        throw Error::FileException();
//    }
//    out.close();
//}
//
//void Flow::saveConfig(){
//    std::shared_ptr<Config> conf = Game::get<Config>("game_config");
//    int header = HEADER;
//    std::ofstream out;
//
//    out.open("GameData/game.conf", (std::ios::trunc | std::ios::binary));
//    if(out.good()){
//        out.write(to_bin(header), sizeof (header));
//        out.write(to_bin(conf->asciiArt), sizeof (conf->asciiArt));
//        writeBinary(conf->saveGame, out);
//    }
//    else{
//        out.close();
//        throw Error::FileException();
//    }
//    out.close();
//}
//
//void Flow::loadConfig(){
//    std::shared_ptr<Config> conf = Game::get<Config>("game_config");
//    std::ifstream in;
//    if(checkFile("GameData/game.conf")){
//        in.open("GameData/game.conf", std::ios::binary);
//        if(in.good()){
//            in.seekg(std::ios::beg + sizeof (HEADER));
//            in.read(to_bin(conf->asciiArt), sizeof (conf->asciiArt));
//            conf->saveGame = readBinary(in);
//        }
//    }
//    in.close();
//}
//
//Flow::Actor Flow::createCharacter(){
//    std::string name; //An input string
//    Actor r; //The return Actor
//
//    //Get the player's name
//    std::cout << "What's your name?" << std::endl;
//    std::cout << "> ";
//    std::getline(std::cin, name);
//    r.name(name); //Set the name
//
//    //Get the player's job
//    std::cout << "Choose your class:" << std::endl;
//    char input = menu({"Knight", "Cleric", "Mage", "Lancer"}, 4); //Display Job menu
//    switch(input){
//        case 'K': //Knight
//        {
//            r.job(Job::Knight);
//            break;
//        }
//        case 'C': //Cleric
//        {
//            r.job(Job::Cleric);
//            break;
//        }
//        case 'M': //Mage
//        {
//            r.job(Job::Mage);
//            break;
//        }
//        case 'L': //Lancer
//        {
//            r.job(Job::Lancer);
//            break;
//        }
//    }
//    Game::get<Actor>("player")->job(r.job());
//    r.equip(Weapon("", "", "", DmgElem::NONE, 10, true), false);
//    r.equip(Armor("", "", "", DmgElem::NONE, 10, true), false);
//
//    //Get the game difficulty
//    std::cout << "Choose a difficulty:" << std::endl;
//    input = menu({"Stroll" /*8*/, "Mosey" /*16*/, "Journey" /*32*/, "Adventure" /*40*/, "Quest" /*48*/,
//                 "Epic" /*56*/}, 1);
//    switch(input){
//        case 'S': //Stroll the easiest difficulty
//        {
//            r.difficulty(Flow::Diff::EASY);
//            break;
//        }
//        case 'M': //Mosey the medium difficulty
//        {
//            r.difficulty(Flow::Diff::MEDIUM);
//            break;
//        }
//        case 'J': //Journey harder than medium easier than hard
//        {
//            r.difficulty(Flow::Diff::EASY | Flow::Diff::MEDIUM);
//            break;
//        }
//        case 'A': //Adventure the hard difficulty
//        {
//            r.difficulty(Flow::Diff::HARD);
//            break;
//        }
//        case 'Q': //Quest even harder
//        {
//            r.difficulty(Flow::Diff::EASY | Flow::Diff::HARD);
//            break;
//        }
//        case 'E': //Epic the hardest difficulty
//        {
//            r.difficulty(Flow::Diff::EASY | Flow::Diff::MEDIUM | Flow::Diff::HARD);
//            break;
//        }
//
//    }
//
//    return r;
//}
//
//void Flow::play(){
//    std::shared_ptr<Floor> floor = Game::get<Floor>("floor");
//    std::shared_ptr<GmRand> gmRand = Game::get<GmRand>("rand");
//    std::shared_ptr<Point> pos = Game::get<Point>("player_pos");
//
//    *floor = gmRand->rFloor(Game::get<Actor>("player")->difficulty()); //Get a new random floor
//    *pos = floor->start(); //Move the player to the start cell
//    (*floor)[pos->y][pos->x].event(Flow::RmEvent::None); //Set the start cell event to none
//    do{ //While the game isn't over
//        (*floor)[pos->y][pos->x].trigger(); //Trigger the cell event
//        std::cout << std::endl;
//    } while(!(*Game::get<bool>("game_over")));
//    *Game::get<bool>("game_over") = false; //Toggle the game over flag
//}
//
//bool Flow::loadMenu(){
//    bool r = false, //Return value
//            back = false; //Whether or not to go back
//    int input = 0; //The selected file
//    Collections::LinkedList<std::string> paths, //Save file paths
//            lMenu, //A menu of files to load
//            aMenu = {"Load", "Delete", "Back"}; //A menu for choosing file actions
//    try{
//        rdTxt("GameData/index.sav", paths); //Load save paths from index
//    }
//    catch(Error::FileException e){
//
//    }
//    for(int i = 0; i < paths.size(); ++i){ //Create the load menu
//        lMenu.addBack(paths[i]);
//    }
//    lMenu.addBack("Back");
//
//    do{ //While not going back
//        input = intMenu(lMenu, 1); //Do load menu processing
//        if(input > 0 && checkFile(paths[input - 1])){ //If not going back and the file is valid
//            char cInput = menu(aMenu, 3); //Do action menu processing
//            switch(cInput){
//                case 'L': //Load
//                {
//                    load(paths[input - 1], *Game::get<Actor>("player"));
//                    r = true; //Loaded a file
//                    back = true; //Go back
//                    break;
//                }
//                case 'D': //Delete
//                {
//                    std::remove(paths[input - 1].c_str()); //Remove the selected file
//                    paths.remove(input - 1); //Erase the file from the loaded paths
//                    lMenu.remove(input - 1); //Erase the file from the menu
//                    std::ofstream out; //A file output stream
//
//                    out.open("GameData/index.sav", std::ios::trunc); //Open the save index
//                    for(int i = 0; i < paths.size(); ++i){ //Output paths back into index
//                        out << paths[i] << std::endl;
//                    }
//                    out.close(); //Close the index file
//                    break;
//                }
//            }
//        }
//        else{
//            back = true; //Go back
//        }
//    } while(!back);
//
//    return r;
//}
//
//int Flow::intMenu(const Collections::LinkedList<std::string> &opts, int perLine){
//    int r = 0; //The return value
//    std::string input = ""; //Input string
//
//    do{ //While r is within the bounds of the options
//        std::stringstream convert; //Conversion stringstream
//        for(int i = 0; i < opts.size(); ++i){ //Display the menu
//            if(i % perLine != 0 && i != 0){ //Insert spacing
//                std::cout << "     ";
//            }
//            if(i % perLine == 0){ //Insert line breaks
//                std::cout << std::endl;
//            }
//            if(i + 1 < opts.size()){ //Display options
//                std::cout << formatOption(i + 1) << " " << opts[i];
//            }
//            else{ //Display final 0 option
//                std::cout << formatOption(0) << " " << opts[i];
//            }
//        }
//        std::cout << std::endl << "> "; //Display prompt
//        std::getline(std::cin, input); //Get input
//        convert << input; //insert input into stream
//        convert >> r; //Convert input to int
//    } while(r < 0 || r > opts.size() + 1);
//
//    return r;
//}
//
//std::string Flow::formatOption(const std::string &option){
//    std::string r = option;
//
//    r.insert(0, 1, '(');
//    r.insert(2, 1, ')');
//
//    return r;
//}
//
//std::string Flow::formatOption(int option){
//    std::stringstream r;
//
//    r << '(' << option << ')';
//
//    return r.str();
//}
//
//bool Flow::isValid(const Collections::LinkedList<std::string> &options, char key){
//    for(int i = 0; i < options.size(); ++i){ //For every option
//        if(std::toupper(options[i][0]) == std::toupper(key)){ //Check the option's first char against the the key
//            return true; //If they match return true
//        }
//    }
//}
//
//void Flow::mainMenuOptions(){
//    bool back = false; //Whether or not to go back
//    Config nConf = *Game::get<Config>("game_config"); //Create a copy of the game config
//
//    do{ //While not back
//        std::cout << "ASCII ART: " << (nConf.asciiArt ? "ON" : "OFF") << std::endl; //Display whether or not ASCII art is on
//        std::cout << "GAME SAVE PATH: " << nConf.saveGame << std::endl; //Display game save path
//        char input = menu({"Ascii Art", "Save Path", "Back"}, 3); //Display option's menu
//        switch(input){
//            case 'A': //ASCII Art
//            {
//                std::cout << "Toggle game ASCII art on or off" << std::endl;
//                char input = menu({"1 On", "2 Off"}, 2); //On off menu processing
//                if(input == '1'){ //If on
//                    nConf.asciiArt = true; //Turn on
//                }
//                else if(input == '2'){ //If off
//                    nConf.asciiArt = false; //Turn off
//                }
//                break;
//            }
//            case 'S': //Save Path
//            {
//                std::cout << "Enter the new path to save to:" << std::endl;
//                std::cout << "> ";
//                std::getline(std::cin, nConf.saveGame); //Get the new save path
//                break;
//            }
//            case 'B': //Back
//            {
//                back = true; //go back
//                break;
//            }
//        }
//    } while(!back);
//    *Game::get <Config>("game_config") = nConf; //Copy the new config back to the game config
//}