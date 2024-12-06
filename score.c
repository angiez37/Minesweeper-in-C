#include <stdio.h>
#include "minesweeper.h"

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| calculateScore - Calculates and displays the percentage of the board that has been revealed based on the number of squares revealed.
| 
| Arguments: squaresRevealed = Total number of squares revealed by the player
|            rows = Total number of rows in the board
|            columns = Total number of columns in the board
| 
| Pointers / Side Effects: None
| Outputs: Prints the percentage of the board revealed to the console.
| Returns: None
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

void calculateScore(int squaresRevealed, int rows, int columns) {
    float percentage = (float)squaresRevealed / (rows * columns) * 100;
    printf("Progress: %.3f%% of the board revealed.\n", percentage);
}
