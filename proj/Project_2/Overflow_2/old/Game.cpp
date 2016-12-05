/*
 * ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄
 * █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █
 * █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █
 * ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █
 *         █  █  ▀███▀     █    █         ▀       █ █ █
 *          █▐            ▀      ▀                 ▀ ▀
 *          ▐
 * File:   Game.cpp
 * Author: Alexander Rothman <arothman@student.rcc.edu>
 * Purpose: Source file for Game.h
 * Created on October 15, 2016
 */

//User Libraries
#include "Game.h" //Main game objects and functions

//Static Definitions
const std::string Flow::Config::SAVPATH = "GameData/game.conf"; //Config Save Path

bool Flow::Game::over = false; //Whether or not the game is ending
char Flow::Game::input = 0; //The last char input
Flow::Actor Flow::Game::player; //The game's player character
Flow::Point Flow::Game::pos; //The player's position
Flow::GmRand Flow::Game::gmRand; //The game PRNG
Flow::Config Flow::Game::conf; //The game configuration
Flow::Floor Flow::Game::floor; //The game board
std::vector<std::string> Flow::Game::mMenu; //The game main menu
std::vector<std::string> Flow::Game::bMenu; //The game battle menu
std::vector<std::string> Flow::Game::gMenu; //The game play menu
std::vector<std::string> Flow::Game::nMons; //Monster names
std::vector<std::string> Flow::Game::dMenu; //Difficulty menu
std::vector<std::string> *Flow::Game::nItems = NULL; //Item names array of vectors
std::vector<std::string> *Flow::Game::nWeaps = NULL; //Weapon names array of vectors

//gNWeaps
//Gets the names of weapons in the game. Part of the game init process
//Output:
//A pointer to an array of vectors such that static_cast<int>(Flow::Job) - 1 will result in the index of that job's
//weapon names

std::vector<std::string>* Flow::gNWeaps(){
    std::vector<std::string> *r = new std::vector<std::string>[JOB_CNT]; //Allocate memory for return

    for(int i = 0; i < JOB_CNT; ++i){ //For all jobs that aren't None
        std::string path; //Path to read
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
        rdTxt(r[i], path); //Read the data from the set path
    }

    return r;
}

//gNItems
//Gets the names of unidentified Items in the game. Part of the game init process
//Output:
//A pointer to an array of vectors such that static_cast<int>(Flow::ItmType) - 1 will result in the index of that
//item type's unidentified names.

std::vector<std::string>* Flow::gNItems(){
    std::vector<std::string> *r = new std::vector<std::string>[ITM_CNT]; //Allocate memory for return

    for(int i = 0; i < ITM_CNT; ++i){ //For every item type that isn't None
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
        Flow::rdTxt(r[i], path); //Read the data from the set path
    }

    return r;
}

//rdTxt
//Read and display string data from a file
//Input:
//path
//The path to read data from

void Flow::rdTxt(const std::string &path){
    std::ifstream in; //The input stream

    in.open(path); //Open the file
    while(in.good() && !in.eof()){ //While the file is good and the stream is not at the end of the file
        std::string input; //input string
        getline(in, input); //Get input line
        std::cout << input << std::endl; //Output the line
    }
    in.close(); //Close the file
}

//rdTxt
//Read line by line string data into a string vector
//Input:
//data
//The vector to read strings into
//path
//The path to read data from
//Output:
//The filled data vector

void Flow::rdTxt(std::vector<std::string> &data, const std::string &path){
    std::ifstream in; //The input stream

    in.open(path); //Open the file
    while(in.good() && !in.eof()){ //While the file is good and the stream is not at the end of the file
        std::string input; //input string
        getline(in, input); //Get input line
        if(input[input.size() - 1] == '\r'){ //This is needed to clean Windows line endings
            //Windows ends lines with \r\n rather than just \n
            input.erase(input.end() - 1); //Clean line ending
        }
        if(!input.empty()){ //If the input is not an empty string
            data.push_back(input); //Add the input to the vector
        }
    }
    in.close(); //Close the file
}

//ckFile
//Check whether or not a file is valid for Overflow or not
//Input:
//path
//The path to the file to check
//Output:
//True if the file exists and contains the Game::HEADER value in the first 4 bytes. False otherwise

bool Flow::ckFile(const std::string &path){
    bool r = false; //Return value
    int header = 0; //Header value
    std::ifstream in; //Input file stream

    in.open(path, in.binary); //Open the file in binary mode
    if(in.is_open()){ //If the file opened
        in.read(reinterpret_cast<char*>(&header), sizeof (header)); //Read the header
    }
    r = in.is_open() && header == Game::HEADER; //Calculate r
    in.close(); //Close the file

    return r;
}

//init
//Game initialization function. Should always be run at the start of the program

void Flow::init(){
    Game::nWeaps = gNWeaps(); //Get weapon names
    Game::nItems = gNItems(); //Get item names
    rdTxt(Game::nMons, std::string("GameData/monsters.txt")); //Get monster names
    Game::mMenu = {"New Game", "Load", "Options", "Help", "Exit"}; //Create main menu
    Game::bMenu = {"Attack", "Inventory", "Player Status"}; //Create battle menu
    Game::gMenu = {"Player Status", "Inventory", "Options", "Map"}; //Create game menu
    Game::dMenu = {"Stroll" /*8*/, "Mosey" /*16*/, "Journey" /*32*/, //Create difficulty menu
                   "Adventure" /*40*/, "Quest" /*48*/, "Epic" /*56*/};
    if(ckFile(Config::SAVPATH)){ //If the config file exists
        gConf(); //Load the config
    }
    else{ //Otherwise default the config
        Game::conf.ascArt = true;
        Game::conf.saveGame = "GameData/";
        Game::conf.diff = Diff::EASY;
    }
}

//cleanUp
//Game clean up function. Should always be run at the end of the program

void Flow::cleanUp(){
    delete [] Game::nWeaps; //Clear weapon names
    Game::nWeaps = NULL;
    delete [] Game::nItems; //Clear item names
    Game::nItems = NULL;
}

//binPow
//Recursively calculates the value of 2^pow
//Input:
//pow
//The power to raise 2 to
//Output:
//The value of 2^pow in an unsigned integer

unsigned int Flow::binPow(unsigned int pow){
    if(pow == 0){ //If zero
        return 1; //2^0 = 1
    }
    else{ //Otherwise
        return 2 * binPow(pow - 1); //Recur and calculate 2^(pow - 1)
    }
}

//toInt
//Short hand for static_cast<int>(unsigned char)
//Input:
//value
//The value to convert
//Output:
//The input value as an int

int Flow::toInt(unsigned char value){
    return static_cast<int>(value);
}

//menu
//Do menu processing for menus that should return a character value
//Input:
//opts
//The options for this menu
//perLine
//The number of options to be displayed before a line break
//Output:
//A valid input char from the menu

char Flow::menu(const std::vector<std::string> &opts, unsigned int perLine){
    std::string input = ""; //The input string

    do{ //While the input is invalid
        for(int i = 0; i < opts.size(); ++i){ //Display the menu
            if(i % perLine != 0 && i != 0){ //Insert spacing
                std::cout << "     ";
            }
            if(i % perLine == 0){ //Insert line breaks
                std::cout << std::endl;
            }
            std::cout << frmtOpt(opts[i]) << " "; //Format and display options
        }
        std::cout << std::endl << "> "; //Display prompt
        std::getline(std::cin, input); //Read input
    } while(!isValid(opts, input[0]));

    return std::toupper(input[0]); //Return the first char of the input as uppercase
}

//iMenu
//Do menu processing for menus that should return an integer value
//Input:
//opts
//The options for this menu
//perLine
//The number of options to be displayed before a line break
//Output:
//A valid int from the menu

int Flow::iMenu(const std::vector<std::string> &opts, unsigned int perLine){
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
                std::cout << frmtOpt(i + 1) << " " << opts[i];
            }
            else{ //Display final 0 option
                std::cout << frmtOpt(0) << " " << opts[i];
            }
        }
        std::cout << std::endl << "> "; //Display prompt
        std::getline(std::cin, input); //Get input
        convert << input; //insert input into stream
        convert >> r; //Convert input to int
    } while(r < 0 || r > opts.size() + 1);

    return r;
}

//frmtOpt
//Formats a string option for display
//Input:
//opt
//A string to format
//Output:
//A string with () inserted around the first character

std::string Flow::frmtOpt(const std::string &opt){
    std::string r = opt;

    r.insert(0, 1, '(');
    r.insert(2, 1, ')');

    return r;
}

//frmtOpt
//Formats an int option for display
//Input:
//opt
//The int to format
//Output:
//A string of the form (opt)

std::string Flow::frmtOpt(int opt){
    std::stringstream r;

    r << '(' << opt << ')';

    return r.str();
}

//isValid
//Return whether or not an input is valid for a char menu
//Input:
//opts
//The options for the menu
//key
//The input char to check
//Output:
//True if the key was valid otherwise false

bool Flow::isValid(const std::vector<std::string> &opts, char key){
    for(int i = 0; i < opts.size(); ++i){ //For every option
        if(std::toupper(opts.at(i)[0]) == std::toupper(key)){ //Check the option's first char against the the key
            return true; //If they match return true
        }
    }

    return false; //Otherwise return false
}

//encounter
//Encounter processing for the game. Handles one entire battle
//Input:
//enem
//The player's enemy for this encounter
//Output:
//True if the player wins false otherwise

bool Flow::encounter(Actor &enem){
    bool turn = false, //Whether or not the player has taken their turn
            r = false; //The return value

    do{ //While no one is dead
        //Enemy Turn
        enem.attack(Game::player); //Just attack the player

        //Player Turn
        if(Game::player.hp().value() > 0){ //If the player isn't dead
            do{ //While the player hasn't acted
                //Display status information
                std::cout << enem.name() << ": " << enem.hp().value() << "/" << enem.hp().max() << " ";
                std::cout << enem.hp().name() << std::endl;
                std::cout << Game::player.name() << ": " << Game::player.hp().value() << "/" << Game::player.hp().max();
                std::cout << " " << Game::player.hp().name() << std::endl;
                turn = true; //It's the player's turn
                Game::input = menu(Game::bMenu, 5); //Display the battle menu
                switch(Game::input){
                    case 'A': //Attack
                    {
                        Game::player.attack(enem); //Attack the enemy
                        turn = false; //The player's turn is up
                        break;
                    }
                    case 'I': //Inventory
                    {
                        int index = Game::player.selectItm(); //Select an item
                        if(index > -1){ //If the player selected an item
                            turn = false; //Their turn is up
                        }
                        break;
                    }
                    case 'P': //Player status
                    {
                        Game::player.stat(); //Display player status
                        break;
                    }
                }
            } while(turn);
        }
    } while(Game::player.hp().value() > 0 && enem.hp().value() > 0);
    if(Game::player.hp().value() > 0){ //If the player didn't die
        for(int i = 0; i < enem.invSize(); ++i){ //For the enemy's inventory size
            Game::player.addItem(enem.getItem(i)); //Give that item to the player
            std::cout << enem.getItem(i).uiName() << " acquired!" << std::endl; //Display message for item drops
        }
        r = true; //The player won
    }
    else{ //Otherwise
        if(Game::conf.ascArt){ //If ASCII art is on
            rdTxt(std::string("GameData/gameover.txt")); //Display game over screen
        }
        else{ //Otherwise
            std::cout << "GAME OVER!" << std::endl;
        }
        r = false; //The player died
    }

    return r;
}

//play
//Play the game. The most important 8 lines in the whole program

void Flow::play(){
    Game::floor = Game::gmRand.rFloor(Game::conf.diff); //Get a new random floor
    Game::pos = Game::floor.start(); //Move the player to the start cell
    Game::floor[Game::pos.y][Game::pos.x].setEvent(Flow::RmEvent::None); //Set the start cell event to none
    do{ //While the game isn't over
        Game::floor[Game::pos.y][Game::pos.x].trigger(); //Trigger the cell event
        std::cout << std::endl;
    } while(!Game::over);
    Game::over = false; //Toggle the game over flag
}

//createChar
//Create a character for the player
//Output:
//A new Actor object to set Game::player to

Flow::Actor Flow::createChar(){
    std::string input; //An input string
    std::vector<std::string> jMenu = {"Knight", "Cleric", "Mage", "Lancer"}; //A job menu vector
    Actor r; //The return Actor

    //Get the player's name
    std::cout << "What's your name?" << std::endl;
    std::cout << "> ";
    std::getline(std::cin, input);
    r.setName(input); //Set the name

    //Get the player's job
    std::cout << "Choose your class:" << std::endl;
    Game::input = menu(jMenu, 4); //Display Job menu
    switch(Game::input){
        case 'K': //Knight
        {
            r.setJob(Job::Knight);
            break;
        }
        case 'C': //Cleric
        {
            r.setJob(Job::Cleric);
            break;
        }
        case 'M': //Mage
        {
            r.setJob(Job::Mage);
            break;
        }
        case 'L': //Lancer
        {
            r.setJob(Job::Lancer);
            break;
        }
    }
    Game::player.setJob(r.job()); //Set the job ahead of return so that Item names are correct
    r.equip(Item(Item::mkName(DmgElem::NONE, ItmType::Weapon), //Create weapon
                 Item::mkName(DmgElem::NONE, ItmType::Weapon),
                 Item::mkDesc(DmgElem::NONE, ItmType::Weapon, 10),
                 DmgElem::NONE, ItmType::Weapon, 10, true), false);
    r.equip(Item(Item::mkName(DmgElem::NONE, ItmType::Armor), //Create armor
                 Item::mkName(DmgElem::NONE, ItmType::Armor),
                 Item::mkDesc(DmgElem::NONE, ItmType::Armor, 10),
                 DmgElem::NONE, ItmType::Armor, 10, true), false);

    //Get the game difficulty
    std::cout << "Choose a difficulty:" << std::endl;
    Game::input = menu(Game::dMenu, 1);
    switch(Game::input){
        case 'S': //Stroll the easiest difficulty
        {
            Game::conf.diff = Flow::Diff::EASY;
            break;
        }
        case 'M': //Mosey the medium difficulty
        {
            Game::conf.diff = Flow::Diff::MEDIUM;
            break;
        }
        case 'J': //Journey harder than medium easier than hard
        {
            Game::conf.diff = Flow::Diff::EASY | Flow::Diff::MEDIUM;
            break;
        }
        case 'A': //Adventure the hard difficulty
        {
            Game::conf.diff = Flow::Diff::HARD;
            break;
        }
        case 'Q': //Quest even harder
        {
            Game::conf.diff = Flow::Diff::EASY | Flow::Diff::HARD;
            break;
        }
        case 'E': //Epic the hardest difficulty
        {
            Game::conf.diff = Flow::Diff::EASY | Flow::Diff::MEDIUM | Flow::Diff::HARD;
            break;
        }

    }

    return r;
}

//mMOpts
//Main Menu options menu handling

void Flow::mMOpts(){
    bool back = false; //Whether or not to go back
    Config nConf = Game::conf; //Create a copy of the game config
    std::vector<std::string> optMen = {"Ascii Art", "Save Path", "Back"}; //Option's menu vector

    do{ //While not back
        std::cout << "ASCII ART: " << (nConf.ascArt ? "ON" : "OFF") << std::endl; //Display whether or not ASCII art is on
        std::cout << "GAME SAVE PATH: " << nConf.saveGame << std::endl; //Display game save path
        Game::input = menu(optMen, 3); //Display option's menu
        switch(Game::input){
            case 'A': //ASCII Art
            {
                std::vector<std::string> tmp = {"1 On", "2 Off"}; //On off menu
                std::cout << "Toggle game ASCII art on or off" << std::endl;
                Game::input = menu(tmp, 2); //On off menu processing
                if(Game::input == '1'){ //If on
                    nConf.ascArt = true; //Turn on
                }
                else if(Game::input == '2'){ //If off
                    nConf.ascArt = false; //Turn off
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
    Game::conf = nConf; //Copy the new config back to the game config

}

//gMOpts
//Game Menu options menu handlign

void Flow::gMOpts(){
    bool back = false; //Whether or not to go back
    Config nConf = Game::conf; //Create a copy of the game config
    std::vector<std::string> optMen = {"Ascii Art", "Save Game", "Quit to menu", "Back"}; //Options menu vector

    do{ //While not going back
        std::cout << "ASCII ART: " << (nConf.ascArt ? "ON" : "OFF") << std::endl; //Display whether or not ASCII art is on
        std::cout << "GAME SAVE PATH: " << nConf.saveGame << std::endl; //Display the save game path
        std::cout << "MAX FLOOR SIZE: " << toInt(nConf.diff) << std::endl; //Display the maximum floor size. This is equal to the difficulty
        Game::input = menu(optMen, 4); //Do options menu processing
        switch(Game::input){
            case 'A': //ASCII art
            {
                std::vector<std::string> tmp = {"1 On", "2 Off"}; //On off menu
                std::cout << "Toggle game ASCII art on or off" << std::endl;
                Game::input = menu(tmp, 2); //On off menu processing
                if(Game::input == '1'){ //If on
                    nConf.ascArt = true; //Turn on
                }
                else if(Game::input == '2'){ //If off
                    nConf.ascArt = false; //Turn off
                }
                break;
            }
            case 'S': //Save game
            {
                save(); //Save the game
                //Display where the game was saves to
                std::cout << "GAME SAVED to " << Game::conf.saveGame << Game::player.name() << ".sav" << std::endl;
                std::cout << std::endl;
                break;
            }
            case 'Q': //Quit to the menu
            {
                save(); //Save the game
                Game::over = true; //end the game
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
    Game::conf = nConf; //Copy edited config back to the game config
}

//wConf
//Write the config to a file

void Flow::wConf(){
    unsigned int header = Game::HEADER; //The game header value
    int len = Game::conf.saveGame.size() + 1; //The length of the save game path
    std::ofstream out; //Output stream

    out.open(Game::conf.SAVPATH.c_str(), std::ios::binary | std::ios::trunc); //Open GameData/game.conf in binary mode and clear it
    out.write(reinterpret_cast<char*>(&header), sizeof (header)); //Write the header
    out.write(reinterpret_cast<char*>(&Game::conf.ascArt), sizeof (Game::conf.ascArt)); //Write the ASCII art setting
    out.write(reinterpret_cast<char*>(&len), sizeof (len)); //Write the length of the save path
    out.write(Game::conf.saveGame.c_str(), len); //Write the save path
    out.close(); //Close the file
}

//gConf
//Read the config from a file

void Flow::gConf(){
    unsigned int header = 0; //The game header value
    int len = 0; //The length of the save game path
    char *buffer = NULL; //A buffer to read a string into
    std::ifstream in; //Input stream

    in.open(Game::conf.SAVPATH.c_str(), std::ios::binary); //Open the file in binary mode
    in.read(reinterpret_cast<char*>(&header), sizeof (header)); //Read the header value
    if(header == Game::HEADER){ //If the header is correct
        in.read(reinterpret_cast<char*>(&Game::conf.ascArt), sizeof (Game::conf.ascArt)); //Read the ASCII art setting
        in.read(reinterpret_cast<char*>(&len), sizeof (len)); //Read the length of the save path
        buffer = new char[len]; //Allocate memory to the buffer
        in.read(buffer, len); //Read the save path
        Game::conf.saveGame = buffer; //Set the save path
        delete [] buffer; //Delete the buffer
        buffer = NULL;
    }
    in.close(); //Close the file
}

//save
//Save a game player to the disk

void Flow::save(){
    unsigned int header = Game::HEADER; //Game header value
    std::string path = Game::conf.saveGame; //The save path
    if(path[path.size() - 1] != '/' && path[path.size() - 1] != '\\'){ //If not a valid path
        path += '/'; //Add a path separator
        Game::conf.saveGame += '/'; //Fix the save path
    }
    path += Game::player.name() + ".sav"; //Generate and add the save file name to the path
    std::fstream file; //The file stream

    if(!ckFile(path)){ //If the file doesn't already contain valid data
        std::ofstream create; //Create the file
        create.open(path.c_str(), std::ios::binary); //Open in binary mode
        create.write(reinterpret_cast<char*>(&header), sizeof (header)); //Write the header
        create.close(); //Close the file
        create.open("GameData/index.sav", std::ios::app); //Add the file to the save index
        create << path << std::endl;
        create.close(); //Close the save index
    }

    file.open(path.c_str(), std::ios::binary | std::ios::in | std::ios::out); //Open the save file
    file.seekg(std::ios::beg + sizeof (header)); //Seek past the header
    file.write(reinterpret_cast<char*>(&Game::conf.diff), sizeof (Game::conf.diff)); //Write the difficulty
    Game::player.toBin().write(file); //Write the player binary
    file.close(); //Close the file
}

//load
//Load file processing. Returns whether or not a file was loaded
//Output:
//True if a file was loaded false otherwise

bool Flow::load(){
    bool r = false, //Return value
            back = false; //Whether or not to go back
    int input = 0; //The selected file
    std::vector<std::string> paths, //Save file paths
            lMenu, //A menu of files to load
            aMenu = {"Load", "Delete", "Back"}; //A menu for choosing file actions
    rdTxt(paths, "GameData/index.sav"); //Load save paths from index
    for(int i = 0; i < paths.size(); ++i){ //Create the load menu
        lMenu.push_back(paths[i]);
    }
    lMenu.push_back("Back");

    do{ //While not going back
        input = iMenu(lMenu, 1); //Do load menu processing
        if(input > 0 && ckFile(paths[input - 1])){ //If not going back and the file is valid
            Game::input = menu(aMenu, 3); //Do action menu processing
            switch(Game::input){
                case 'L': //Load
                {
                    std::fstream in; //File input stream
                    BinArray data; //The binary data from the file

                    in.open(paths[input - 1].c_str(), std::ios::binary | std::ios::in | std::ios::ate); //Open file at the end of the file
                    data = BinArray(in.tellg()); //Allocate a new BinArray with the file length
                    in.seekg(std::ios::beg + sizeof (Game::HEADER)); //Seek back to just after the header
                    in.read(reinterpret_cast<char*>(&Game::conf.diff), sizeof (Game::conf.diff)); //Read in the game difficulty
                    data.read(in); //Read in the binary data
                    in.close(); //Close the file

                    Game::player.toActor(data); //Fill the player with the read data
                    r = true; //Loaded a file
                    back = true; //Go back
                    break;
                }
                case 'D': //Delete
                {
                    std::remove(paths[input - 1].c_str()); //Remove the selected file
                    paths.erase(paths.begin() + (input - 1)); //Erase the file from the loaded paths
                    lMenu.erase(lMenu.begin() + (input - 1)); //Erase the file from the menu
                    std::ofstream out; //A file output stream

                    out.open("GameData/index.sav"); //Open the save index
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

//rand
//Generate a random int value
//Output:
//A random number as an int. Equivalent to cstdlib rand()

int Flow::GmRand::rand(){
    ++_pos; //Increment the position
    return std::rand(); //Return a random value
}

//rRoom
//Generate a random Room object
//Input:
//start
//Whether or not this is the start room
//end
//Whether or not this is the end room
//Output:
//A random Room object

Flow::Room Flow::GmRand::rRoom(bool start, bool end){
    unsigned char rVal = rand() % 100; //Generate a percentage
    RmEvent event = RmEvent::None; //Default the even to none

    if(rVal >= 0 && rVal < 50){ //50% chance of an Encounter
        event = RmEvent::Encounter;
    }
    else if(rVal >= 50 && rVal < 70){ //20% chance of Treasure
        event = RmEvent::Treasure;
    }
    else if(rVal >= 70 && rVal < 80){ //10% chance of healing Spring
        event = RmEvent::Spring;
    }

    return Room(Direct::NONE, event, start, end); //Return the new room
}

//rDirect
//Generate a random cardinal direction
//Output:
//An 8-bit direction value containing 1, 2, 4, or 8

unsigned char Flow::GmRand::rDirect(){
    unsigned char r = Direct::NONE; //The return value

    switch(rand() % 4){ //Convert from 0-3 to 2^0, 2^1, 2^2, or 2^3
        case 0:
        {
            r = Direct::NORTH;
            break;
        }
        case 1:
        {
            r = Direct::EAST;
            break;
        }
        case 2:
        {
            r = Direct::SOUTH;
            break;
        }
        case 3:
        {
            r = Direct::WEST;
            break;
        }
    }

    return r;
}

//rElem
//Generate a random element value
//Output:
//An 8-bit element value containing a number 0-255

unsigned char Flow::GmRand::rElem(){
    unsigned char val = rand() % 100; //Generate a percentage
    unsigned char r = 0;

    if(val < 75){ //75% chance of unenchanted item
        r = DmgElem::NONE;
    }
    else if(val >= 75 && val < 90){ //15% chance of single enchanted item
        r = binPow(rand() % 8); //Generate a single element value between 2^0 and 2^7
    }
    else{ ///10% chance of possible multiple enchants
        r = rand() % 256; //Generate a totally random element
    }

    return r;
}

//rFloor
//Generate a random Floor object
//Input:
//size
//The number of rooms for the current floor to hold
//Output:
//A newly generated Floor

Flow::Floor Flow::GmRand::rFloor(unsigned char size){
    Floor r; //The return floor
    Point pos; //The current position of the generator
    Point last; //The previous position
    bool filled[r.sizeY()][r.sizeX()] = {}; //A 2D array indicating if the generator has already filled a room
    unsigned char direct = Direct::NONE; //The direction to move in

    pos.x = rand() % r.sizeX(); //Generate a random x position
    pos.y = rand() % r.sizeY(); //Generate a random y position

    for(int i = 0; i < size; i += filled[last.y][last.x]){ //Until the Floor has reached the correct size
        //Set the last position
        last.x = pos.x;
        last.y = pos.y;

        if(i == 0){ //If this is the first room
            r[pos.y][pos.x] = rRoom(true); //Generate a random room
            filled[pos.y][pos.x] = true; //Set it as filled
            do{ //While the generator hasn't stepped
                direct = rDirect(); //Generate a random direction
            } while(!r.move(pos, direct)); //Attempt to move in that direction
            r[last.y][last.x].addExit(direct); //Add an exit

        }
        else if(i == size - 1){ //If this is the last room
            if(!filled[pos.y][pos.x]){ //If the room hasn't been filled
                r[pos.y][pos.x] = rRoom(false, true); //Generate a random room
                filled[pos.y][pos.x] = true; //Fill it
            }
            else{ //Otherwise
                r[pos.y][pos.x] = Room(r[pos.y][pos.x].exit(), r[pos.y][pos.x].event(), false, true); //Add the stairs down
            }
            r[pos.y][pos.x].addExit(Direct::reverse(direct)); //Add an exit to the last room
        }
        else{ //Otherwise
            if(!filled[pos.y][pos.x]){ //If room hasn't been filled
                r[pos.y][pos.x] = rRoom(); //Generate a random room
                filled[pos.y][pos.x] = true; //Fill it
            }
            r[pos.y][pos.x].addExit(Direct::reverse(direct)); //Add an exit to the last room
            do{ //While the generator hasn't stepped
                direct = rDirect(); //Generate a random direction
            } while(!r.move(pos, direct)); //Attempt to move in that direction
            r[last.y][last.x].addExit(direct); //Add an exit
        }
    }

    return r;
}

//rItem
//Generate a random Item
//Input:
//ident
//Whether or not the item is identified
//Output:
//A randomly generated item

Flow::Item Flow::GmRand::rItem(bool ident){
    unsigned char value = rand() % 256; //Generate the item's effectiveness
    unsigned char elem = rElem(); //Generate the item's element
    int tInt = rand() % 100; //Generate a perecentage
    Item r; //The return value

    if(tInt < 50){ //50% chance of potion
        tInt = 1;
    }
    else if(tInt >= 50 && tInt < 70){ //20% chance of armor
        tInt = 2;
    }
    else{ //30% chance of weapon
        tInt = 3;
    }
    ItmType type = static_cast<ItmType>(tInt); //Create the ItmType

    std::string uiName = Game::nItems[tInt - 1][rand() % Game::nItems[tInt - 1].size()]; //Generate the name
    r = Item("", uiName, "", DmgElem::NONE, type, value, ident); //Generate the Item object
    r.setElem(elem); //Set the element

    return r;
}

//rActor
//Generate a random Actor
//Output:
//A randomly generated Actor object

Flow::Actor Flow::GmRand::rActor(){
    unsigned char drops = 0; //The number of drop items
    int hp = rand() % (Game::player.hp().max() * 2) + 1; //HP is between 1 and 2 * the player's max HP
    int mp = rand() % (Game::player.mp().max() * 2) + 1; //MP is between 1 and 2 * the player's max MP
    unsigned char atk = rand() % (Game::player.atk().value() + 2); //Attack is between 0 and the player's attack + 2
    unsigned char def = rand() % (Game::player.atk().value() + 2); //Defense is between 0 and the player's defense + 2
    std::string name = Game::nMons[rand() % Game::nMons.size()]; //Generate the name
    //Generate weapons and armor
    //Both may have values between 0 and the player's bonus + 10
    Item weap = Item("", "", "", rElem(), ItmType::Weapon, rand() % (Game::player.weap().value() + 10), true);
    Item armr = Item("", "", "", rElem(), ItmType::Weapon, rand() % (Game::player.armr().value() + 10), true);
    Actor r; //The return Actor

    r.equip(weap, false); //Equip the weapon
    r.equip(armr, false); //Equip the armor
    r.setName(name); //Set the name
    r.setAtk(atk); //Set the atk
    r.setDef(def); //Set the def
    r.setHp(Flow::IStat(std::string("HP"), std::string("Hit Points"), hp, hp)); //Set HP
    r.setMp(Flow::IStat(std::string("MP"), std::string("Magic Points"), mp, mp)); //Set MP

    drops = (rand() % 4); //Generate number of Item drops
    for(int i = 0; i < drops; ++i){ //For each drop
        r.addItem(rItem()); //Add a random Item
    }

    return r;
}

//seed
//Return the seed of the GmRand object
//Output:
//The current seed value

unsigned int Flow::GmRand::seed(){
    return _seed;
}

//srand
//Seed the PRNG with the current seed

void Flow::GmRand::srand(){
    std::srand(_seed); //Seed PRNG
    _pos = 0; //Reset position
}

//srand
//Seed the PRNG with the given value
//Input:
//seed
//The seed to use

void Flow::GmRand::srand(unsigned int seed){
    std::srand(seed); //Seed PRNG
    _seed = seed; //Set the seed
    _pos = 0; //Reset the position
}

//pos
//Return the current position (in calls to rand()) of the PRNG
//Output:
//The current value of _pos

unsigned int Flow::GmRand::pos(){
    return _pos;
}

//seek
//Move the current position to the input position
//Input:
//pos
//The position to seek to

void Flow::GmRand::seek(unsigned int pos){
    std::srand(_seed); //Seed the PRNG
    for(int i = 0; i < pos; ++i){ //Call rand() pos times
        std::rand();
    }
    _pos = pos; //Set the position
}

//GmRand
//Default constructor

Flow::GmRand::GmRand(){
    _pos = 0; //Position is 0
    _seed = static_cast<int>(time(0)); //Seed is the current time
    srand(); //Seed PRNG
}