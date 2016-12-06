/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   functions.cpp
 * Author: Alexander Rothman <alexander@megate.ch>
 * Purpose:
 * Created on December 5, 2016
 */
#include "game.h"
#include "actor.h"
#include "functions.h"

Flow::Config Flow::loadConfig(const std::string &path){
    Config r;
    r.asciiArt = true;
    r.saveGame = "GameData/";

    std::ifstream in;
    if(checkFile(path)){
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

void Flow::rdTxt(const std::string &path){
    std::ifstream in;

    in.open(path.c_str());
    if(in.good()){
        std::string str;
        while(getline(in, str)){
            std::cout << str << std::endl;
        }
    }
    else{
        in.close();
        throw Error::FileException("File Not Found");
    }
    in.close();
}

void Flow::rdTxt(const std::string &path, Collections::LinkedList<std::string> &data){
    std::ifstream in;

    in.open(path.c_str());
    if(in.good()){
        std::string str;
        while(getline(in, str)){
            if(str[str.size() - 1] == '\r'){ //This is needed to clean Windows line endings
                //Windows ends lines with \r\n rather than just \n
                str.erase(str.end() - 1); //Clean line ending
            }
            if(!str.empty()){ //If the input is not an empty string
                data.addBack(str); //Add the input to the vector
            }
        }
    }
    else{
        in.close();
        throw Error::FileException("File Not Found");
    }
    in.close();
}

char Flow::menu(const Collections::LinkedList<std::string> &opts, int perLine){
    std::string input = "";

    do{
        for(int i = 0; i < opts.size(); ++i){
            if(i % perLine != 0 && i != 0){
                std::cout << "     ";
            }
            if(i % perLine == 0){
                std::cout << std::endl;
            }
            std::cout << formatOption(opts[i]) << " ";
        }
        std::cout << std::endl << "> ";
        getline(std::cin, input);
    } while(!isValid(opts, input[0]));

    return std::toupper(input[0]);
}

bool Flow::checkFile(const std::string &path){
    bool r = false;
    int header = 0;
    std::ifstream in;

    in.open(path.c_str(), std::ios::binary);
    if(in.is_open()){
        in.read(to_bin(header), sizeof (header));
    }
    r = in.is_open() && header == HEADER;
    in.close();

    return r;
}

std::string Flow::formatOption(const std::string &option){
    std::string r = option;

    r.insert(0, 1, '(');
    r.insert(2, 1, ')');

    return r;
}

std::string Flow::formatOption(int option){
    std::stringstream r;

    r << '(' << option << ')';

    return r.str();
}

bool Flow::isValid(const Collections::LinkedList<std::string> &options, char key){
    for(int i = 0; i < options.size(); ++i){ //For every option
        if(std::toupper(options[i][0]) == std::toupper(key)){ //Check the option's first char against the the key
            return true; //If they match return true
        }
    }
}

void Flow::createCharacter(Game &game){
    std::string name; //An input string
    Actor r; //The return Actor

    //Get the player's name
    std::cout << "What's your name?" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, name);
    r.name(name); //Set the name

    //Get the player's job
    std::cout << "Choose your class:" << std::endl;
    char input = menu({"Knight", "Cleric", "Mage", "Lancer"}, 4); //Display Job menu
    switch(input){
        case 'K': //Knight
        {
            r.job(Job::Knight);
            break;
        }
        case 'C': //Cleric
        {
            r.job(Job::Cleric);
            break;
        }
        case 'M': //Mage
        {
            r.job(Job::Mage);
            break;
        }
        case 'L': //Lancer
        {
            r.job(Job::Lancer);
            break;
        }
    }
    game.player(r);
    r.equip(Weapon(game, "", "", "", DmgElem::NONE, 10, true), false);
    r.equip(Armor("", "", "", DmgElem::NONE, 10, true), false);

    //Get the game difficulty
    std::cout << "Choose a difficulty:" << std::endl;
    input = menu({"Stroll" /*8*/, "Mosey" /*16*/, "Journey" /*32*/, "Adventure" /*40*/, "Quest" /*48*/,
                 "Epic" /*56*/}, 1);
    switch(input){
        case 'S': //Stroll the easiest difficulty
        {
            r.difficulty(Diff::EASY);
            break;
        }
        case 'M': //Mosey the medium difficulty
        {
            r.difficulty(Diff::MEDIUM);
            break;
        }
        case 'J': //Journey harder than medium easier than hard
        {
            r.difficulty(Diff::EASY | Diff::MEDIUM);
            break;
        }
        case 'A': //Adventure the hard difficulty
        {
            r.difficulty(Diff::HARD);
            break;
        }
        case 'Q': //Quest even harder
        {
            r.difficulty(Diff::EASY | Diff::HARD);
            break;
        }
        case 'E': //Epic the hardest difficulty
        {
            r.difficulty(Diff::EASY | Diff::MEDIUM | Diff::HARD);
            break;
        }
    }

    game.player(r);
}

bool Flow::loadMenu(Game &game){
    bool r = false, //Return value
            back = false; //Whether or not to go back
    int input = 0; //The selected file
    Collections::LinkedList<std::string> paths, //Save file paths
            lMenu; //A menu of files to load
    try{
        rdTxt(game.indexPath(), paths); //Load save paths from index
    }
    catch(Error::FileException e){

    }
    for(int i = 0; i < paths.size(); ++i){ //Create the load menu
        lMenu.addBack(paths[i]);
    }
    lMenu.addBack("Back");

    do{ //While not going back
        input = intMenu(lMenu, 1); //Do load menu processing
        if(input > 0 && checkFile(paths[input - 1])){ //If not going back and the file is valid
            char cInput = menu({"Load", "Delete", "Back"}, 3); //Do action menu processing
            switch(cInput){
                case 'L': //Load
                {
                    load(paths[input - 1], game);
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

                    out.open(game.indexPath(), std::ios::trunc); //Open the save index
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

void Flow::load(const std::string &path, Game &game){
    Actor player;
    std::ifstream in;

    if(checkFile(path)){
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
            cache.pos = game.gmRand().pos();
            cache.seed = game.gmRand().seed();
            if(weap.seed != 0){
                game.gmRand().seek(weap);
                game.gmRand().rItem(player, game, ItemType::Weapon, false);
                player.use(0, false);
                player.removeItem(0);
            }
            else{
                player.equip(Weapon(game, "", "", "", DmgElem::NONE, 10, true), false);
            }
            if(armor.seed != 0){
                game.gmRand().seek(armor);
                game.gmRand().rItem(player, game, ItemType::Armor, false);
                player.use(0, false);
                player.removeItem(0);
            }
            else{
                player.equip(Armor("", "", "", DmgElem::NONE, 10, true), false);
            }
            game.gmRand().seek(cache);

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

void Flow::mainMenuOptions(Game &game){
    bool back = false; //Whether or not to go back

    Config nConf = game.config();

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
    game.config(nConf); //Copy the new config back to the game config
}

void Flow::save(const std::string &path, const Game &game){
    int header = HEADER;
    std::ofstream out;
    Actor player = game.player();

    if(!checkFile(path)){
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

void Flow::getOptionsMenu(Game &game){
    bool back = false; //Whether or not to go back
    Config nConf = game.config(); //Create a copy of the game config

    do{ //While not going back
        std::cout << "ASCII ART: " << (nConf.asciiArt ? "ON" : "OFF") << std::endl; //Display whether or not ASCII art is on
        std::cout << "GAME SAVE PATH: " << nConf.saveGame << std::endl; //Display the save game path
        std::cout << "MAX FLOOR SIZE: " << to_int(game.player().difficulty()) << std::endl; //Display the maximum floor size. This is equal to the difficulty
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
                save(game.config().saveGame + game.player().name() + ".sav", game); //Save the game
                //Display where the game was saves to
                std::cout << "GAME SAVED to " << nConf.saveGame << game.player().name() << ".sav" << std::endl;
                std::cout << std::endl;
                break;
            }
            case 'Q': //Quit to the menu
            {
                save(game.config().saveGame + game.player().name() + ".sav", game); //Save the game
                game.setGameOver(true); //end the game
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
    game.config(nConf); //Copy edited config back to the game config
}

void Flow::stats(const Actor &actor){
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

int Flow::intMenu(const Collections::LinkedList<std::string> &opts, int perLine){
    int r = 0; //The return value
    std::string input = ""; //Input string

    do{ //While r is within the bounds of the options
        std::stringstream convert; //Conversion stringstream
        for(int i = 0; i < opts.size(); ++i){ //Display the menu
            if(i % perLine != 0 && i != 0){ //Insert spacing
                std::cout << "     ";
            }
            if(i % perLine == 0){ //Insert line breaks
                std::cout << std::endl;
            }
            if(i + 1 < opts.size()){ //Display options
                std::cout << formatOption(i + 1) << " " << opts[i];
            }
            else{ //Display final 0 option
                std::cout << formatOption(0) << " " << opts[i];
            }
        }
        std::cout << std::endl << "> "; //Display prompt
        std::getline(std::cin, input); //Get input
        convert << input; //insert input into stream
        convert >> r; //Convert input to int
    } while(r < 0 || r > opts.size() + 1);

    return r;
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