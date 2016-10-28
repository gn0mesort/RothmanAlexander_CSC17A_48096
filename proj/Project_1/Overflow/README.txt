*********************************************************
* ████▄     ▄   ▄███▄   █▄▄▄▄ ▄████  █    ████▄   ▄ ▄   *
* █   █      █  █▀   ▀  █  ▄▀ █▀   ▀ █    █   █  █   █  *
* █   █ █     █ ██▄▄    █▀▀▌  █▀▀    █    █   █ █ ▄   █ *
* ▀████  █    █ █▄   ▄▀ █  █  █      ███▄ ▀████ █  █  █ *
*         █  █  ▀███▀     █    █         ▀       █ █ █  *
*          █▐            ▀      ▀                 ▀ ▀   *
*          ▐                                            *
*********************************************************
Version: 1.0
ABOUT:
    Overflow is small Role-playing game in the style of Rogue. The objective
    of the game is to reach the end of the board while collecting as much 
    treasure as you can.
OUTPUT CONFIGURATION:
    Overflow looks best in windows with at least 80 character columns and
    is meant to be displayed in the 12 pt Lucida Console font. If you prefer
    another font any monospace font should work well.
SAVING AND LOADING GAMES:
    Overflow will save your data automatically if you choose to quit from
    the options menu or reach the end of a board. You may also choose to
    save at any point during the game. Game saves store only your immediate
    character information (name, statistics, current equipment). On reloading
    the game you will lose any items in your inventory and a new board will be
    generated.
    The only supported way to delete saves is using the Load menu's delete
    function. Deleting game saves outside of this will corrupt the index.sav
    file. If you wish to fix your index.sav file manually you may open it as
    a text file and remove the invalid paths.
FILE ENCODINGS
    The default game data files for Overflow are all encoded using UTF-8. A
    set of ANSI encoded ASCII art files can be found in the GameData/ANSI
    folder. A copy of the default UTF-8 encoded art files can be found in
    GameData/UTF8
    
    It is safe to switch between these different encodings (even while the
    game is running) but it is not necessary to switch unless you're 
    experiencing display issues.
.SAV FILE FORMAT:
    Overflow's .sav files are formatted as follows.
    *****PLAYER_NAME.SAV*******************************************************
    *HEADER VALUE (4 BYTES)                                                   *
    *GAME DIFFICULTY (1 BYTE)                                                 *
    *SIZE OF THE PLAYER'S NAME IN CHARACTERS (4 BYTES)                        *
    *PLAYER NAME (SIZE DETERMINED BY NUMBER OF CHARACTERS)                    *
    *PLAYER JOB (4 BYTES)                                                     *
    *PLAYER MAX HP (4 BYTES)                                                  *
    *PLAYER MAX MP (4 BYTES)                                                  *
    *PLAYER ATTACK POWER (1 BYTE)                                             *
    *PLAYER DEFENSE POWER (1 BYTE)                                            *
    *SIZE OF WEAPON'S NAME (4 BYTES)                                          *
    *WEAPON'S NAME (SIZE DETERMINED BY NUMBER OF CHARACTERS)                  *
    *SIZE OF WEAPON'S UNIDENTIFIED NAME (4 BYTES)                             *
    *WEAPON'S UNIDENTIFIED NAME (SIZE DETERMINED BY NUMBER OF CHARACTERS)     *
    *SIZE OF WEAPON'S DESCRIPTION (4 BYTES)                                   *
    *WEAPON'S DESCRIPTION (SIZE DETERMINED BY NUMBER OF CHARACTERS)           *
    *WEAPON'S ELEMENT (1 BYTE)                                                *
    *WEAPON'S ATTACK BONUS (1 BYTE)                                           *
    *WEAPON'S ITMTYPE (4 BYTES)                                               *
    *WEAPON'S IDENTIFIACTION STATUS (1 BYTE)                                  *
    *SIZE OF ARMOR'S NAME (4 BYTES)                                           *
    *ARMOR'S NAME (SIZE DETERMINED BY NUMBER OF CHARACTERS)                   *
    *SIZE OF ARMOR'S UNIDENTIFIED NAME (4 BYTES)                              *
    *ARMOR'S UNIDENTIFIED NAME (SIZE DETERMINED BY NUMBER OF CHARACTERS)      *
    *SIZE OF ARMOR'S DESCRIPTION (4 BYTES)                                    *
    *ARMOR'S DESCRIPTION (SIZE DETERMINED BY NUMBER OF CHARACTERS)            *
    *ARMOR'S ELEMENT (1 BYTE)                                                 *
    *ARMOR'S ATTACK BONUS (1 BYTE)                                            *
    *ARMOR'S ITMTYPE (4 BYTES)                                                *
    *ARMOR'S IDENTIFIACTION STATUS (1 BYTE)                                   *
    ***************************************************************************
    All stored strings are null terminated.
READING THE MAP:
    The game map uses the following symbols
    ' ' : indicating a visitable cell on the board
    'X' : indicating an unvisitable cell
    '@' : indicating the player's location
    'S' : indicating the starting location
    No other map data is available to the player. Debug Map data can be
    displayed by altering the game source and calling the 
    Flow::Floor::drawDbg() function. Debug map data is displayed cell by
    cell as follows
    A block of 4 characters (N, E, S, and W) indicating which exits the cell
    does or does not have
    
    An integer value (1 or 0) indicating whether or not the cell is the start
    cell
    
    An integer value (1 or 0) indicating whether or not the cell is the end
    cell
    
    An integer value (0, 1, 2, or 3) indicating the cell event.
    0 : No event
    1 : Encounter a monster
    2 : Discover treasure
    3 : Discover a spring (heals the player and identifies items)
MODIFYING:
    Most of the content in Overflow can be modified by the user. In general
    it is safe to modify any of the .txt files found in the GameData
    directory. It is not safe to add or delete files to GameData. Content in
    these files is read into the program sequentially, one line at a time.
    Therefore any content not given its own line will be considered part of
    the line it's on.
    
    It is never safe to modify binary game files of the types: .sav, and .conf
KNOWN ISSUES:
    The game title or other ASCII art is displaying incorrectly.
        Overflow looks best in a window with at least 80 columns and is
        intended to be displayed in the Lucida Console font. If you prefer
        to use other settings you may disable ASCII art at any time in the
        options menu.
        This issue may also be caused by terminals that display UTF-8 encoded
        text incorrectly. This is especially the case in Windows. By default
        all Overflow text files are encoded in UTF-8. However ANSI encoded
        ASCII art files can be found in the GameData/ANSI folder. If you
        wish to use these instead of the default simply copy them into
        GameData.