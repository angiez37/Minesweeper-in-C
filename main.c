#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "minesweeper.h"

int main() {
    // random number generator
    srand(time(NULL));

    // Welcome page
    char *playerName = welcomePage();

    int rows, columns, mines; // Default settings
    int choice = Menu(); // Get menu choice
    parseInput(playerName, choice, &rows, &columns, &mines); // Adjust settings based on input

    // Initialize the boards
    char **minefield = generateMinefield(rows, columns, mines);
    char **numberMap = generateNumberMap(rows, columns, minefield);
    char **gameBoard = generateGameboard(rows, columns);

    int squaresToReveal = rows * columns - mines;
    int squaresRevealed = 0;
    int gameOver = 0;

    printf("\nThe mission begins, %s!\n", playerName);
    printf("Good luck defusing the mines.\n");

    while (!gameOver && squaresRevealed < squaresToReveal) {
        printf("\nCurrent Board:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                printf("%c ", gameBoard[i][j]);
            }
            printf("\n");
        }

        int row, col;
        printf("Enter your move (row): ");
        scanf("%d ", &row);
        printf("Enter your move (column): ");
        scanf("%d ", &col);

        row--;
        col--;

        if (row < 0 || row >= rows || col < 0 || col >= columns) {
            printf("Invalid move! Stay within the board.\n");
            continue;
        }

        if (gameBoard[row][col] != '.') {
            printf("Tile already revealed. Choose another one.\n");
            continue;
        }

        if (minefield[row][col] == 'X') {
            printf("\nBOOM! You hit a mine. Game over, %s.\n", playerName);
            gameOver = 1;
            break;
        }

        // Reveal the square and apply ripple effect if necessary
        digSquare(row, col, rows, columns, gameBoard, numberMap, &squaresRevealed);

        if (squaresRevealed == squaresToReveal) {
            printf("\nCONGRATULATIONS, %s! You have defused all the mines and saved the galaxy!\n", playerName);
            gameOver = 1;
        }
    }

    // Clean up memory
    free(playerName);
    for (int i = 0; i < rows; i++) {
        free(minefield[i]);
        free(numberMap[i]);
        free(gameBoard[i]);
    }
    free(minefield);
    free(numberMap);
    free(gameBoard);

    return 0;
}