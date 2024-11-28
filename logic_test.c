#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdbool.h>

#include "minesweeper.h"

#define DEBUG 0

/* char** test_gameboard() { 
	char **minefield = generateGameboard(4,5); 
	char **numbermap = generateNumberMap(4, 5, minefield);
    	char **board = generateGameboard(4, 5);

	return board; 
} // double check if this is what jack meant
*/ 

int main() { 
    
    int rows = 4;
    int columns = 5;
	
    char minefield_array[4][5] = { {'X', '.', '.', '.', '.'}, {'X', '.', '.', '.', '.'}, {'.', '.', '.', '.', '.'}, {'.', '.', '.', '.', 'X'} };

    char **minefield = malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++) {
        minefield[i] = minefield_array[i];
    } 

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
    int result = 0;

    while (result == 0) {
        scanf("%d %d %d", &specified_row, &specified_column, &change); // take input from test input
        result = processMove(specified_row, specified_column, change, 4, 5, board, minefield, numbermap, 3, &flags, &squares_revealed);

        // print board
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                    printf("%c ", board[i][j]);
        }
        printf("\n");
        }

    }

    if (result == 1) {
        printf("User WON\n");
    }
    else if (result == 2) {
        printf("User LOST\n");
    }

    free(minefield);
    free(numbermap);
    free(board);
}
