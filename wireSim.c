#include <stdio.h>
#include <stdlib.h>
#include "wireSim.h"

/*
Title:      		wireSim.c
Author:     		Jet Ng
Date/LastModified:  11/06/2023
Description:       	wireSim.c file with one function, wireSim() which is used to calculate all the changes to the map/array
                    as it moves to the next iteration. This function will update the active array, wireMap, which is then fed
                    into printMap in order to show the updated state to the terminal.
*/


/*
METHOD: 	wireSim
IMPORT: 	wireMap (int**), newMap(int**), mapRowSize (int), mapColSize (int)
            
EXPORT: 	none, updates figures in wireMap array as follows in the WireWorld logic described.
ASSERTION: 	Import current map as wireMap and a temp copy as newMap, update newMap, 
            copy new info to wireMap and update map state of wireMap for printing.
ALGORITHM:  Changes electron head/tail/conductor as required for WireWorld functionality:
            - empty cells do not change (black/0 value indexs are not touched)
            - electron head becomes electron tail (array value of 1 is turned to 2)
            - electron tail becomes conductor (array value of 2 is turned to 3)
            - conductor will change to electron head (value of 1) if there are 1 OR 2 electron heads within
            its Moore neighborhood.
			

*/

void wireSim(int** wireMap, int** newMap, int mapRowSize, int mapColSize)
{
    int i, j;

    for (i = 0; i < mapRowSize; i++)
    {
        for (j = 0; j < mapColSize; j++)
        {
            int wireState = wireMap[i][j];
            if (wireState == 1)
            {
                newMap[i][j] = 2; /* head -> tail change*/
            }
            else if (wireState == 2)
            {
                newMap[i][j] = 3; /* tail -> conductor change */
            }
            else if (wireState == 3)
            {
                int headCount = 0;
                int rowCheck, colCheck;

                for (rowCheck = -1; rowCheck <= 1; rowCheck++)
                {
                    for (colCheck = -1; colCheck <= 1; colCheck++)
                    {
                        /* loop to check the Moore neighbourhood of the current cell/index */
                        int adjRow = i + rowCheck;
                        int adjCol = j + colCheck;
                                    
                        if ((adjRow >= 0) && (adjRow < mapRowSize) && (adjCol >= 0) && (adjCol < mapColSize))
                        {
                            if ((rowCheck == 0) && (colCheck == 0))
                            {
                                /* do nothing, skip check for current cell */
                            }

                            if (wireMap[adjRow][adjCol] >= 1) /* only checking valid display cells */
                            {
                                if (wireMap[adjRow][adjCol] == 1)
                                {
                                    headCount++; /* counter for number of electron heads in Moore neighbourhood */
                                }
                            }
                        }
                    }
                }

                if ((headCount == 1) || (headCount == 2))
                {
                    newMap[i][j] = 1; /* conductor to electron head change, if 1 OR 2 heads in Moore neighbourhood */
                }
            }
            else
            {
                newMap[i][j] = wireState;
            } 
        }
    }

    /* assign updated values in newMap to wireMap */
    for (i = 0; i < mapRowSize; i++)
    {
        for (j = 0; j < mapColSize; j++)
        {
            wireMap[i][j] = newMap[i][j];
        }
    }
}