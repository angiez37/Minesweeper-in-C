#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#include "minesweeper.h"

#define DEBUG 0

int main() { 
    
    int rows = 4;
    int columns = 5;
	
    // this all just to hard code array for testing
    char minefield_array[4][5] = { {'X', '.', '.', '.', '.'}, {'X', '.', '.', '.', '.'}, {'.', '.', '.', '.', '.'}, {'.', '.', '.', '.', 'X'} };

    char **minefield = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        minefield[i] = minefield_array[i];
    }
    // end of hard coding array
    
    
    // generate boards
    char ** numbermap = generateNumberMap(4, 5, minefield);
    char ** board = generateGameboard(4, 5);



    if (DEBUG) { // make sure that minefield and numbermap generated properly
        printf("DEV - Printing Minefield:\n");
        for (int i = 0; i < rows; i++) { // printing for dev purposes
                for (int j = 0; j < columns; j++) { 
                    printf("%c ", minefield[i][j]);
            }
            printf("\n");
        }

        printf("\nDEV - Printing NumberMap:\n");
        for (int i = 0; i < rows; i++) { // only for dev testing
                for (int j = 0; j < columns; j++) {
                        printf("%c ", numbermap[i][j]);
            }
            printf("\n");
        }
    }

    int flags = 0;
    int squares_revealed = 0;
    int specified_row, specified_column, change;

    scanf("%d %d %d", &specified_row, &specified_column, &change); // take input from test input

    processMove(specified_row, specified_column, change, 4, 5, board, minefield, numbermap, 3, &flags, &squares_revealed);

    // print board
    for (int i = 0; i < rows; i++) { // only for dev testing
            for (int j = 0; j < columns; j++) {
                    printf("%c ", board[i][j]);
        }
        printf("\n");
    }


    free(minefield);
    free(numbermap);
    free(board);
}