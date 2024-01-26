#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "printMap.h"
#include "wireSim.h"
#include "newSleep.h"

/*
Title:      		main.c
Author:     		Jet Ng
Date/LastModified:  11/06/2023
Description:       	Uses wireSim.c and printMap.c and user provided parameters via an input file with dimensions and 2D array values
                    to create a WireWorld animation for electrons moving within a closed system/logic gate.

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

int main(int argc, char* argv[])
{
    system("clear");
    if (argc == 4)
    { 
        FILE* file;
        file = fopen(argv[1], "r");

        /*  If check for invalid file or no file found */
        if (file == NULL)
        {
            printf("File failed to open or doesn't not exist, please check filename spelling/content and try again.\n");
        } 
        /* check for negative (invalid) cycles amount */
        else if (atoi(argv[2]) < 0)
        {
            printf("Please specify a number of cycles greater than or equal to 0, 0 will display the initial state from the text file.\n");
        }
        /* check for negative (invalid) values for sleep amount */
        else if (atof(argv[3]) < 0)
        {
            printf("Please specify a sleep/pause period longer than 0 seconds for the animation to run properly. 0.5 is recommended.\n");
        }        
        /* Else, the command line arguments have passed checks above and therefore are appropriate parameters and we start the display of the wireworld program */
        else
        {
            char currentLine[1000];
            char mapRow[5];
            char mapCol[5];
            int mapRowSize, mapColSize, i, j, k, cycles;
            float sleepTime;
            int** wireMap;

            fgets(currentLine, sizeof(currentLine), file);
            sscanf(currentLine, "%s %s", mapRow, mapCol);

            mapRowSize = atoi(mapRow);
            mapColSize = atoi(mapCol);
            cycles = atoi(argv[2]);
            sleepTime = atof(argv[3]);

            /* set up 2D array for WireWorld map */
            wireMap = (int**)malloc((mapRowSize)*sizeof(int*));
            for (i = 0; i < (mapRowSize); i++)
            {
                wireMap[i] = (int*)malloc((mapColSize)*sizeof(int));
                for (j = 0; j < (mapColSize); j++)
                {
                    wireMap[i][j] = 0; /* initialise wireMap to all 0's */
                }
            }
            i = 0;

            /* get WireWorld cell state information from file and assign to wireMap */
            while (((fgets(currentLine, sizeof(currentLine), file)) != NULL) && (i <= mapRowSize))
            {
                int value;
                char* token = strtok(currentLine, " ");

                j = 0;

                while (token != NULL && j < mapColSize) 
                {
                    sscanf(token, "%d", &value);
                    wireMap[i][j] = value;
                    j++;
                    token = strtok(NULL, " ");
                }
                i++;
            }

            fclose(file);

            printMap(wireMap, mapRowSize, mapColSize);
            newSleep(sleepTime);
            /* get all initial info from file, close file, print initial wire map state to terminal*/

            /* loop for WireWorld animation/simulation, based on cycles entered by user */
            for (k = 0; k < cycles; k++)
            {
                /* initialise temp map to store updates */
                int** newMap = (int**)malloc((mapRowSize)*sizeof(int*)); 
                system("clear");
                for (i = 0; i < (mapRowSize); i++)
                {
                    newMap[i] = (int*)malloc((mapColSize)*sizeof(int));
                    for (j = 0; j < (mapColSize); j++)
                    {
                        newMap[i][j] = wireMap[i][j];
                    }
                }

                /* run wireSim to get values assigned to wireMap for next iteration */
                wireSim(wireMap, newMap, mapRowSize, mapColSize);

                /* free newMap, print new wireMap array to terminal, pause for chosen sleep length by user */
                for (i = 0; i < mapRowSize; i++)
                {
                    free(newMap[i]);
                }
                free(newMap);
                printMap(wireMap, mapRowSize, mapColSize);
                newSleep(sleepTime);
            }
            
            /* at end of animation/simulation, free wireMap and end program */
            for (i = 0; i < (mapRowSize); i++) 
            {
                free(wireMap[i]);
            }
            free(wireMap);
        }
    }
    /* End program if parameters are != 4, print usage to terminal to show how to execute ./box */
    else
    {
        printf("Please execute the program with 4 parameters as follows in the terminal: \nusage: ./wireworld <MAPFILENAME> <STEPS_AMOUNT> <SLEEP_LENGTH>(in seconds)\n");
    }
    return 0;
}