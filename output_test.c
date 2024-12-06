#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdbool.h>

#include "minesweeper.h"

#define DEBUG 0

char **test_gameboard(int rows, int columns) {

	char minefield_array[10][10] = {
    {'X', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'X', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', 'X', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
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

    int rows = 10;
    int columns = 10;
        
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
        result = processMove(specified_row, specified_column, change, 10, 10, board, minefield, numbermap, 3, &flags, &squares_revealed);

        // print board
        printBoard(board, rows, columns);

    }

    win_lose_message(result);

    int end_choice = end_menu(); // Outputs end menu and asks user if they want to play again or exit
    if (end_choice == 2) {
        printf("(Exits)\n"); // If user exits, breaks out of while loop;
    }
    else {
        printf("(Loops to play again)\n");
    }

    for (int i = 0; i < rows; i++) {
        free(minefield[i]);
        free(numbermap[i]);
        free(board[i]);
    }
    free(minefield);
    free(numbermap);
    free(board);

    outputMessage();
    return 0;
}