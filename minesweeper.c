#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "minesweeper.h"


/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| help - displays the help message
|
| Arguments: None
|
| Returns - None
| Functions Called: None
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
void help() { 
    printf("Minesweeper v1.0.0\n");
    printf("This is a Star-Wars themed Minesweeper game intended to be played in the command line.\n");
    printf("Usage:\n");
    printf(" --help       Display this help message and exit\n");
    printf("Before the game:\n");
    printf("1       Starts the game\n");
    printf("2       Select difficulty\n");
    printf("3       Displays instructions\n");
    printf("4       Exit the game\n");
    printf("During the game:\n");
    printf("d       To dig a square.\n");
    printf("f       To flag or unflag a square.\n");
} // dhruv you can add on to here


/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| main - main function of the program 
|
| Arguments: int argc - number of arguments
|            char *argv[] - array of arguments
|
| Outputs: None
| Returns: 0
| Functions Called: help() - displays the help message
                    welcomePage() - displays the welcome page
                    Menu() - outlines the game options
                    parseInput() - handles user input as selected from the welcome menu
                    generateMinefield() - generates the minefield
                    generateNumberMap() - generates the number map
                    generateGameboard() - generates the gameboard
                    processMove() - processes the users move based on parameters user inputted, handles the flagging process or calls digSquare to reveal the particular square
                    outputMinefield() - outputs the minefield
                    endMenu() - displays the end menu message
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
int main(int argc, char *argv[]) {

    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        help();
        return 0;
    }
    
    // random number generator
    srand(time(NULL));

    int play_again = 1;
    int rows, columns, mines; // Default settings

    char *playerName = welcomePage(); // welcome the player
    
    while (play_again) {
        
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

        time_t starting_time = time(NULL);

        printf("\nThe mission begins, %s!\n", playerName);
        printf("Good luck defusing the mines.\n");

        /*
        printf("\nCurrent Board:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                printf("%c ", gameBoard[i][j]);
            }
            printf("\n");
        }
        */

        int state_of_game = 0;
        int row, col, change;
        char action;
        while (state_of_game == 0) {

            printBoard(gameBoard, rows, columns); // print the board

            calculateScore(squaresRevealed, rows, columns); // print current score


            printf("\nEnter move in the form <'d'/'f'> <row> <column>: ");
            if(scanf(" %c %d %d", &action, &row, &col) != 3) { // scan input and if invalid
                printf("Invalid input format. Please enter again.\n");
                while (getchar() != '\n'); // Clear buffer
                continue; // ask again for valid input
            }

            if (action != 'd' && action != 'f') {
                printf("Invalid action. Please enter 'd' or 'f'.\n");
                while (getchar() != '\n'); // Clear buffer
                continue; // ask again for valid input
            }
            else { // indicate change depending on action flag
                if (action == 'f') {
                    change = 1;
                } 
                else if (action == 'd') {
                    change = 0;
                }
            }

            row--; // decrement for base 0 indexing
            col--;
            if (row < 0 || row >= rows || col < 0 || col >= columns) {
                printf("Invalid move! Stay within the board.\n");
                continue; // ask for new valid input
            }

            // Reveal the square and apply ripple effect if necessary
            state_of_game = processMove(row, col, change, rows, columns, gameBoard, minefield, numberMap, mines, &flags, &squaresRevealed);

        } // end game loop


        time_t ending_time = time(NULL);
        double total_time = difftime(ending_time, starting_time); // Time to find mines

        win_lose_message(state_of_game); // Print win or lose message
        printBoard(gameBoard, rows, columns); // prints final board to user 
        calculateScore(squaresRevealed, rows, columns); // along with their score
        printf("%f", total_time); // Printing time used
        

        int end_choice = end_menu(); // Outputs end menu and asks user if they want to play again or exit
        if (end_choice == 2) {
            play_again = 0; // If user exits, breaks out of while loop;
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
    }
    outputMessage();
    return 0;
}