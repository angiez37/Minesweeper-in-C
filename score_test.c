#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdbool.h>

#include "minesweeper.h"

#define DEBUG 0

char **test_gameboard(int rows, int columns) {

	char minefield_array[4][5] = {
    {'X', '.', '.', '.', '.'},
    {'X', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', 'X'}
        };

        char **minefield = malloc(rows * sizeof(char *));
        for (int i = 0; i < rows; i++) {
        	minefield[i] = malloc(columns * sizeof(char));
        	for (int j = 0; j < columns; j++) {
                	minefield[i][j] = minefield_array[i][j];
    }
}

        return minefield;
}

int main() { 
    
	int rows = 4;
	int columns = 5;
		
	char **minefield = test_gameboard(rows, columns);
	char **numbermap = generateNumberMap(rows, columns, minefield);
	char **board = generateGameboard(rows, columns);

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

    calculateScore(squares_revealed, rows, columns);

    if (result == 1) {
        printf("User WON\n");
    }
    else if (result == 2) {
        printf("User LOST\n");
    }

	for (int i = 0; i < rows; i++) {
	    free(minefield[i]);
	    free(numbermap[i]);
	    free(board[i]);
	}
	free(minefield);
	free(numbermap);
	free(board);
}