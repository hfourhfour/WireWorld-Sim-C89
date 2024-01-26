/*
Title:      		WireWorld Terminal Sim
Author:     		Jet Ng
Date/LastModified:        11/06/2023
Description:       	Uses wireSim.c and printMap.c and user provided parameters via an input file with dimensions and 2D array values
                    to create a WireWorld animation for electrons moving within a closed system/logic gate.

                    1. Starting configurations for each system are shown in the associated text files such as XOR_NOT.txt

                        0 - empty cell/nothing
                        1 - electron HEAD
                        2 - electron TAIL
                        3 - conductor/medium (path)

                    2. To run the graphical simulation, run the makefile and type the following into terminal:

                    ./wireworld <MAPFILENAME> <STEPS_AMOUNT> <SLEEP_LENGTH>(in seconds)

                    e.g ./wireworld OR.txt 400 0.5


                    The file is read open and dimensions are gathered from the first line of the file.
                    2D array is malloc'd and created to hold values which are to come, from the text file.
                    Integer values in the text file are then mapped into the 2D array as they are shown, 1 to 1.

                    This initial 2D array (wireMap) is then printed to terminal in colour using printMap().
                    The wireMap will then cycle through the amount of times the user has requested, updating itself
                    as per WireWorld logic using wireSim() and printing to terminal after each iteration using printMap().

                    The pause between each iteration being shown on terminal is chosen by the user from the command line arguments
                    as the sleep length, and this pause occurs after each printMap() by calling newSleep().

                    The iterations will then run through the cycles specified and stop, then which the wireMap 2D array is free'd and
                    the program/animation ends.

*/
