#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "minesweeper.h"

int main(int argc, char *argv[]) {

    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        help();
        return 0;
    }

    void help() { 
        printf("Minesweeper v1.0.0");
        printf(""); 
        printf("This is a Star-Wars themed Minesweeper game intended to be played in the command line.");
        printf(""); 
        printf("Usage:");
        printf(" --help       Display this help message and exit\n");
        printf(""); 
        printf("Before the game:");
        printf("1       Starts the game\n");
        printf("2       Allows user to select difficulty\n");
        printf("3       Displays instructions\n");
        printf("4       Exits the game\n");
        printf("");
        printf("During the game:");
        printf("d       To dig a square.\n");
        printf("f       To flag or unflag a square.\n");
    } // dhruv you can add on to here
    
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
    int flags = 0;
    int gameOver = 0;

    printf("\nThe mission begins, %s!\n", playerName);
    printf("Good luck defusing the mines.\n");

    printf("\nCurrent Board:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", gameBoard[i][j]);
        }
        printf("\n");
    }
    int state_of_game = 0;
    while (state_of_game == 0) {
        // Ask the user if they want to dig or flag
        int change;
        char action;
        printf("Enter 'd' to dig or 'f' to flag/unflag: ");
        scanf(" %c", &action);
        printf("\n");
        if (action == 'f') {
            change = 1;
        } else if (action == 'd') {
            change = 0;
        } else {
            printf("Invalid action. Please enter 'd' or 'f'.\n");
            continue;
        }
        int row, col;
        printf("Enter your move (row): ");
        scanf("%d", &row);
        printf("Enter your move (column): ");
        scanf("%d", &col);

        row--;
        col--;

        if (row < 0 || row >= rows || col < 0 || col >= columns) {
            printf("Invalid move! Stay within the board.\n");
            continue;
        }

        // Reveal the square and apply ripple effect if necessary
        state_of_game = processMove(row, col, change, rows, columns, gameBoard, minefield, numberMap, mines, &flags, &squaresRevealed);

        printf("\nCurrent Board:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                printf("%c ", gameBoard[i][j]);
            }
            printf("\n");
        }
    }

    // END OF GAME MAKE NICE DHRUV / IRFAN
    if (state_of_game == 1) { // win
        printf("PLAYER HAS WON");
        // trigger win based things
    }
    if (state_of_game == 2) { // lose
        printf("PLAYER HAS LOST");
        // trigger loss based conditions
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
