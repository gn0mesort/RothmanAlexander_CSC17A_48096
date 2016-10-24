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
    
    It is never safe to modify binary game files of the types: .sav, .conf,
    and .inv
KNOWN ISSUES:
    The game title or other ASCII art is displaying incorrectly.
        Overflow looks best in a window with at least 80 columns and is
        intended to be displayed in the Lucida Console font. If you prefer
        to use other settings you may disable ASCII art at any time in the
        options menu.