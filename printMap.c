#include <stdio.h>
#include <stdlib.h>
#include "printMap.h"

/*
Title:      		printMap.c
Author:     		Jet Ng
Date/LastModified:  11/06/2023
Description:       	printMap.c file with one function, printMap() which is used to print colours to the terminal for the display
                    of the WireWorld animation.
*/


/*
METHOD: 	printMap
IMPORT: 	wireMap (int**), pRow (int), pCol (int)
            
EXPORT: 	none, prints/displays colours to terminal for the WireWorld animation
ASSERTION: 	Imports the 2D array with integer information from wireMap, and prints colours based on the values of the cells in the array
ALGORITHM:
			Takes in wireMap, checks each index for the integer value, prints a colour based on the value to terminal for display.
            0 = black (map filler, not part of the moving display)
            1 = blue (electron head)
            2 = red (electron tail
            3 = yellow (conductor)

*/

void printMap(int** wireMap, int pRow, int pCol)
{
    int i,j;

    for (i = 0; i < pRow; i++) 
    {
        for (j = 0; j < pCol; j++) 
        {
            /* iterate through all of the array (wireMap) and print colours to terminal based on value in index.*/
            if (wireMap[i][j] == 0)
            {
                printf("\033[40m ");
                printf("  ");
                printf("\033[49m");
            }
            else if (wireMap[i][j] == 1)
            {
                printf("\033[44m ");
                printf("  ");
                printf("\033[49m");
            }
            else if (wireMap[i][j] == 2)
            {
                printf("\033[41m ");
                printf("  ");
                printf("\033[49m");
            }
            else if (wireMap[i][j] == 3)
            {
                printf("\033[43m ");
                printf("  ");
                printf("\033[49m");
            }
        }
        printf("\n");
    }
}

