#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdbool.h>

#include "minesweeper.h"

#define DEBUG 0

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| digSquare - Recursively ripple reveals unrevealed spaces on the game board.
|               If the [r][c] indicated square on board is unrevealed (indicated by '.' character) replace it with the number of adjacent mines, numbermap[r][j].
|               Then, if there are 0 adjacent mines (to that square), repeat the reveal process at all 8 adjacent squares on board (making sure staying within bounds of board).
|
| Arguments: r = row index of targetted square for reveal
|            c = column index of targetted square for reveal
|            rows = total number of rows in the board (and numbermap)
|            columns = total number of columns in the board (and numbermap)
|            ** board = pointer to 2D array holding the player-shown game board
|            ** numbermap = pointer to 2D array that holds the number of mines adjacent to each square
|            *squares_revealed = scoring metric, increments score counter each time a new square is revealed
|
| Pointers / Side Effects: *squares_revealed - incremented every time an unrevealed square is revealed
|                          ** board - board updated with revealed number(s) from digSquare or updated with added/removed flags (from flagging process)
| Outputs: None
| Returns: None
| Functions Called: digSquare - recursively calls itself to ripple reveal multiple squares
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
void digSquare(int r, int c, int rows, int columns, char ** board, char ** numbermap, int * squares_revealed) {

    if (board[r][c] == '.') {  // if unrevealed reveal square
        board[r][c] = numbermap[r][c];
        (*squares_revealed)++; // scoring metric increment
    }
    else { // skip if not '.' (already revealed)
        if (DEBUG) {
        printf("[%d][%d] not '.\'\tSkipping\n", r, c); // for diagnosing
        }
        return; // skips revealing steps
    }
    

    if (DEBUG) { // For diagnosing
        printf("\nDEV - Printing Board:\n");
        for (int i = 0; i < rows; i++) { // print board
                for (int j = 0; j < columns; j++) {
                        printf("%c ", board[i][j]); 
            }
            printf("\n");
        }
    }

    if (numbermap[r][c] == '0') { // if revealed square was a 0 (no adjacent mines), reveal all 8 adjacent squares
        if (DEBUG) {
            printf("Ripple Revealing around [%d][%d]\n", r, c);
        }

        // 8 if statements, 1 for each adjacent square
        // checks if within bounds of array
        // if yes, then recursively call this function on that square
        if (r > 0 && c > 0) { // NW diagonal
            if (DEBUG) {
                printf("Looking NW from [%d][%d] at [%d][%d]\n", r, c, r-1, c-1);
            }
            digSquare(r-1, c-1, rows, columns, board, numbermap, squares_revealed);
        }	

        if (r > 0) { // N face
            if (DEBUG) {
                printf("Looking N from [%d][%d] at [%d][%d]\n", r, c, r-1, c);
            }
            digSquare(r-1, c, rows, columns, board, numbermap, squares_revealed);
        }

        if (r > 0 && c < (columns-1)) { // NE diagonal
            if (DEBUG) {
                printf("Looking NE from [%d][%d] at [%d][%d]\n", r, c, r-1, c+1);
            }
            digSquare(r-1, c+1, rows, columns, board, numbermap, squares_revealed);
        }

        if (c < (columns-1)) { // E face
            if (DEBUG) {
                printf("Looking E from [%d][%d] at [%d][%d]\n", r, c, r, c+1);
            }
            digSquare(r, c+1, rows, columns, board, numbermap, squares_revealed);
        }

        if (r < (rows-1) && c < (columns-1)) { // SE diagonal
            if (DEBUG) {
                printf("Looking SE from [%d][%d] at [%d][%d]\n", r, c, r+1, c+1);
            }
            digSquare(r+1, c+1, rows, columns, board, numbermap, squares_revealed);
        }
        
        if (r < (rows-1)) { // S face
            if (DEBUG) {
                printf("Looking S from [%d][%d] at [%d][%d]\n", r, c, r+1, c);
            }
            digSquare(r+1, c, rows, columns, board, numbermap, squares_revealed);
        }
        
        if (r < (rows-1) && c > 0) { // SW diagonal
            if (DEBUG) {
                printf("Looking SW from [%d][%d] at [%d][%d]\n", r, c, r+1, c-1);
            }
            digSquare(r+1, c-1, rows, columns, board, numbermap, squares_revealed);
        }
        
        if (c > 0) { // W face
            if (DEBUG) {
                printf("Looking W from [%d][%d] at [%d][%d]\n", r, c, r, c-1);
            }
            digSquare(r, c-1, rows, columns, board, numbermap, squares_revealed);
        }
    }

}



/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| gameEndCheck - determines if player has won game (if every mine has been flagged and there are no additional incorrect flags)
|
| Arguments: rows = total number of rows in the board (and minefield)
|            columns = total number of columns in the board (and minefield)
|            ** board = pointer to 2D array holding the player-shown game board
|            ** minefield = pointer to 2D array that holds the positions of the mines
|            mines = number of mines in play
|            * flags = the number of flags the user has placed
|
| Pointers / Side Effects: None
| Outputs: None
| Returns - Boolean: True - Player has won the game
|                    False - Player has not won the game
| Functions Called: None
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
bool gameEndCheck(int rows, int columns, char ** board, char ** minefield, int mines, int * flags) {
    if (DEBUG) {
        printf("IN GAME END CHECK: end of game check:\tmines:%d\tflags%d\n", mines, *flags);
    }

    if (mines == *flags) { // same number of flags as mines, assume flag char is 'F'
        if (DEBUG) {
            printf("same number of mines as flags\n");
        }

        int correct_flags = 0;
        for (int i = 0; i < rows; i++) {  // parses through the whole array
                for (int j = 0; j < columns; j++) { 
                    if (minefield[i][j] == 'X' && board[i][j] == 'F') { // if mine maps to flag
                        correct_flags++; // increase counter
                    }
            }
        } 
        if (correct_flags == mines) { // if every flag maps exactly to a mine
            printf("END OF GAME - WIN\n");
            return true; // true that game is over and player has won
        }
    }

    return false;

}

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| processMove - processes the users move based on parameters user inputted in ////////////////// READ INPUT FUNCTION
|               depending on user input, handles the flagging process or calls digSquare to reveal the particular square
|
| Arguments: specified_row = the row index of the square the user wants to modify
|            specified_column = the column index of the square the user wants to modify
|            change = indicates the action the user wishes to perform on the targetted square (0 for dig, 1 for flag)
|            row = total number of rows in the board (and minefield and numbermap)
|            columns = total number of columns in the board (and minefield and numbermap)
|            ** board = pointer to 2D array holding the player-shown game board
|            ** minefield = pointer to 2D array that holds the positions of the mines
|            ** numbermap = pointer to 2D array that holds the number of mines adjacent to each square
|            mines = number of mines in play
|            * flags = the number of flags the user has placed
|            * squares_revealed = the number of flags the user has placed
|
| Pointers / Side Effects: * flags - counter for number of flags user has placed, incremented or decremented by flagging process
| Returns - Int: value to represent ongoing game state
|                0 - game is still ongoing
|                1 - player has won
|                2 - player has lost
| Functions Called: digSquare - if user specifies dig (change==0) digSquare is called on [specified_row][specified_column]
|                   gameEndCheck - calls at end of the flag processing to check if user has now won the game
|                   revealAllMines - called when user loses, to reveal to them where all the mines were on the board
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
int processMove(int specified_row, int specified_column, int change, int rows, int columns, char ** board, char ** minefield, char ** numbermap, int mines, int * flags, int * squares_revealed) {
    
    if (change == 0) { // 0 for dig
        if (numbermap[specified_row][specified_column] == 'X') { // if dug up a mine
            if (DEBUG) {
                printf("TRIGGER END OF GAME - LOSE\n");
            }
            revealAllMines(rows, columns, board, minefield);
            return 2; // return value -> player has lost
        }

        else { // if didn't dig a mine
            digSquare(specified_row, specified_column, rows, columns, board, numbermap, squares_revealed);
        }
    }


    if (change == 1) { // 1 is flag
        if (board[specified_row][specified_column] == '.') { // if space was unmarked
            board[specified_row][specified_column] = 'F'; // flag it
            *flags+=1;
            (*squares_revealed)++; // increment score
        }
        else if (board[specified_row][specified_column] == 'F') { // if space was flagged
            board[specified_row][specified_column] = '.'; // remove it
            *flags-=1;
            (*squares_revealed)--; // decrement score

        }

        if (DEBUG) { // for diagnosing
            printf("BEFORE GAME END CHECK:\tmines:%d\tflags%d\n", mines, *flags);
        }

        if (gameEndCheck(rows, columns, board, minefield, mines, flags)) { // check if game ended due to flagging change
            return 1; // return value --> player has won
        }
    }

    return 0; // game is still ongoing
}



// DHRUV WROTE BELOW FUNCTION:
// Reveals all mines on the board (called on game over)
void revealAllMines(int rows, int columns, char **gameBoard, char **minefield) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (minefield[i][j] == 'X') {
                gameBoard[i][j] = 'X';
            }
        }
    }
}