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
    int mines;

    char **minefield = test_gameboard(rows, columns);
    char **numbermap = generateNumberMap(rows, columns, minefield);
    char **board = generateGameboard(rows, columns);

    if (DEBUG) { 
        printf("DEV - Printing Minefield:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                printf("%c ", minefield[i][j]);
            }
            printf("\n");
        }

        printf("\nDEV - Printing NumberMap:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                printf("%c ", numbermap[i][j]);
            }
            printf("\n");
        }
    }

    scanf("%d %d %d", &rows, &columns, &mines);

    minefield = generateMinefield(rows, columns, mines);
    numbermap = generateNumberMap(rows, columns, minefield);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", numbermap[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(minefield[i]);
        free(numbermap[i]);
        free(board[i]);
    }
    free(minefield);
    free(numbermap);
    free(board);

    return 0;
}
