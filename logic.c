#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define DEBUG 0
#define MINEFIELDOUTPUT 1

// COPIED ESHA'S CODE INTO HERE JUST TO GENERATE TESTING INPUT
int surroundingMines(int rows, int columns, char **minefield, int i, int j) { 
	
	int surrounding_mines = 0; 

	if (minefield[i][j] != 'X') {
				
		if (i < (rows - 1) && minefield[i+1][j] == 'X') {
			surrounding_mines++; 
		}	

		if (i > 0 && minefield[i-1][j] == 'X') { 
			surrounding_mines++;
		}
	
		if (j < (columns - 1) && minefield[i][j+1] == 'X') {
                	surrounding_mines++;
            	}

		if (j > 0 && minefield[i][j-1] == 'X') {
                	surrounding_mines++;
		}

		if (i > 0 && j < (columns - 1) && minefield[i-1][j+1] == 'X') { 
                	surrounding_mines++;
            	}
			
		if (i < (rows - 1) && j < (columns - 1) && minefield[i+1][j+1] == 'X') {
                	surrounding_mines++;
            	}

		if (i > 0 && j > 0 && minefield[i-1][j-1] == 'X') {
			surrounding_mines++;
            	}

		if (j > 0 && i < (rows - 1) && minefield[i+1][j-1] == 'X') {
                	surrounding_mines++;
		}
	}	

	return surrounding_mines; 
}

char** generateMinefield(int rows, int columns, int mines) { 	
	
	char** minefield = (char**)malloc(rows * sizeof(char*));
		for (int i = 0; i < rows; i++) {
			minefield[i] = (char*)malloc(columns * sizeof(char));
    	}
	
	for (int i = 0; i < rows; i++) {
        	for (int j = 0; j < columns; j++) {
            		minefield[i][j] = '.';
        }
    }

	int mines_placed = 0; 

	while (mines_placed < mines) { 
		int i = rand() % rows;
		int j = rand() % columns;
		
		if (minefield[i][j] != 'X') { 
			minefield[i][j] = 'X'; 					
			mines_placed++; 
		}
	}

	return minefield;
}

char** generateNumberMap(int rows, int columns, char **minefield) { 
	
	char** numberMap = (char**)malloc(rows * sizeof(char*));
    		for (int i = 0; i < rows; i++) {
        		numberMap[i] = (char*)malloc(columns * sizeof(char));
    		}

	for (int i = 0; i < rows; i++) { 
		for (int j = 0; j < columns; j++) { 
			if (minefield[i][j] != 'X') { 
				int touching_mines = surroundingMines(rows, columns, minefield, i, j);
				if (touching_mines == 0) { 
    					numberMap[i][j] = '0'; // change to '0' from ' '
				} else {
					numberMap[i][j] = '0' + touching_mines;    			
				}
			} else { 
				numberMap[i][j] = 'X';
		}
	}
}
	return numberMap;
}

char** generateGameboard(int rows, int columns) { 

    char** gameboard = malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        gameboard[i] = malloc(columns * sizeof(char));
        for (int j = 0; j < columns; j++) {
            gameboard[i][j] = '.';
        }
    }
    return gameboard;
}

// END OF COPIED CODE FROM ESHA




//void modifyBoard(int r, int c, int rows, int columns, char board[rows][columns], char numbermap[rows][columns], int * squares_revealed) { // RECURSE CALLS WILL BE FUN
void modifyBoard(int r, int c, int rows, int columns, char ** board, char ** numbermap, int * squares_revealed) { // RECURSE CALLS WILL BE FUN
    if (board[r][c] == '.') {
        board[r][c] = numbermap[r][c];
        (*squares_revealed)++;
    }
    else {
        if (DEBUG) {
        printf("[%d][%d] not '.\'\tSkipping\n", r, c); // dev
        }
        return;
    }
    
    if (DEBUG) {
        printf("\nDEV - Printing Board:\n");
        for (int i = 0; i < rows; i++) { // only for dev testing
                for (int j = 0; j < columns; j++) {
                        printf("%c ", board[i][j]);
            }
            printf("\n");
        }
    }

    if (numbermap[r][c] == '0') {
        if (DEBUG) {
            printf("Ripple Revealing around [%d][%d]\n", r, c);
        }

        if (r > 0 && c > 0) { // NW diagonal
            if (DEBUG) {
                printf("Looking NW from [%d][%d] at [%d][%d]\n", r, c, r-1, c-1);
            }
            modifyBoard(r-1, c-1, rows, columns, board, numbermap, squares_revealed);
        }	
        if (r > 0) { // N face
            if (DEBUG) {
                printf("Looking N from [%d][%d] at [%d][%d]\n", r, c, r-1, c);
            }
            modifyBoard(r-1, c, rows, columns, board, numbermap, squares_revealed);
        }
        if (r > 0 && c < (columns-1)) { // NE diagonal
            if (DEBUG) {
                printf("Looking NE from [%d][%d] at [%d][%d]\n", r, c, r-1, c+1);
            }
            modifyBoard(r-1, c+1, rows, columns, board, numbermap, squares_revealed);
        }
        if (c < (columns-1)) { // E face
            if (DEBUG) {
                printf("Looking E from [%d][%d] at [%d][%d]\n", r, c, r, c+1);
            }
            modifyBoard(r, c+1, rows, columns, board, numbermap, squares_revealed);
        }
        if (r < (rows-1) && c < (columns-1)) { // SE diagonal
            if (DEBUG) {
                printf("Looking SE from [%d][%d] at [%d][%d]\n", r, c, r+1, c+1);
            }
            modifyBoard(r+1, c+1, rows, columns, board, numbermap, squares_revealed);
        }
        if (r < (rows-1)) { // S face
            if (DEBUG) {
                printf("Looking S from [%d][%d] at [%d][%d]\n", r, c, r+1, c);
            }
            modifyBoard(r+1, c, rows, columns, board, numbermap, squares_revealed);
        }
        if (r < (rows-1) && c > 0) { // SW diagonal
            if (DEBUG) {
                printf("Looking SW from [%d][%d] at [%d][%d]\n", r, c, r+1, c-1);
            }
            modifyBoard(r+1, c-1, rows, columns, board, numbermap, squares_revealed);
        }
        if (c > 0) { // W face
            if (DEBUG) {
                printf("Looking W from [%d][%d] at [%d][%d]\n", r, c, r, c-1);
            }
            modifyBoard(r, c-1, rows, columns, board, numbermap, squares_revealed);
        }

    }
    

}

// void gameEndCheck(int rows, int columns, char board[rows][columns], char minefield[rows][columns], int mines, int * flags) {
void gameEndCheck(int rows, int columns, char ** board, char ** minefield, int mines, int * flags) {
    printf("IN GAME END CHECK: end of game check:\tmines:%d\tflags%d\n", mines, *flags);
    if (mines == *flags) { // same number of flags as mines, assume flag char is 'F'
        printf("same number of mines as flags\n");
        int correct_flags = 0;
        for (int i = 0; i < rows; i++) { 
                for (int j = 0; j < columns; j++) { 
                    if (minefield[i][j] == 'X' && board[i][j] == 'F') { // if mine maps to flag
                        correct_flags++;
                    }
            }
        } 
        if (correct_flags == mines) { // if every flag maps exactly to a mine
            printf("END OF GAME - WIN\n"); /////////////////////////////////// DHRUV FUCTION
            //scoreboard
        }
    }
}

// void processMove(int specified_row, int specified_column, int change, int rows, int columns, char board[rows][columns], char minefield[rows][columns], char numbermap[rows][columns], int mines, int * flags, int * squares_revealed)

void processMove(int specified_row, int specified_column, int change, int rows, int columns, char ** board, char ** minefield, char ** numbermap, int mines, int * flags, int * squares_revealed) {
    
    if (change == 0) { // 0 for dig
        if (numbermap[specified_row][specified_column] == 'X') {
            printf("TRIGGER END OF GAME - LOSE\n"); /////////////////////////////////// DHRUV FUCTION
            // trigger scoreboard
        }

        else {
            printf("Calling Modify Board\n");
            modifyBoard(specified_row, specified_column, rows, columns, board, numbermap, squares_revealed); // add parameters
        }
    }


    if (change == 1) { // 1 is flag
        printf("flag specified\n");
        if (board[specified_row][specified_column] == '.') {
            printf("flagging\n");
            board[specified_row][specified_column] = 'F';
            *flags+=1;
        }
        else if (board[specified_row][specified_column] == 'F') {
            printf("unflagging\n");
            board[specified_row][specified_column] = '.';
            *flags-=1;
        }
    }

    printf("BEFORE GAME END CHECK:\tmines:%d\tflags%d\n", mines, *flags);
    gameEndCheck(rows, columns, board, minefield, mines, flags);
}





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
    
    char ** numbermap = generateNumberMap(4, 5, minefield);

    //playerboard
    char ** board = generateGameboard(4, 5);

    if (DEBUG) {
        printf("DEV - Printing Minefield:\n");
        for (int i = 0; i < rows; i++) { // printing for dev purposes - remove later  
                for (int j = 0; j < columns; j++) { 
                    printf("%c ", minefield[i][j]);
            }
            printf("\n");
        }

        printf("\nDEV - Printing NumberMap:\n");
        for (int i = 0; i < rows; i++) { // only for dev testing - need to print only the square player selects 
                for (int j = 0; j < columns; j++) {
                        printf("%c ", numbermap[i][j]);
            }
            printf("\n");
        }
    }

    printf("TESTING MOVE PROCESSING\n");
    int flags = 0;
    int squares_revealed = 0;
    printf("\n\n\ntest step 1:\n");
    processMove(2, 2, 0, 4, 5, board, minefield, numbermap, 3, &flags, &squares_revealed);
    printf("\n\n\ntest step 2:\n");
    processMove(3, 4, 1, 4, 5, board, minefield, numbermap, 3, &flags, &squares_revealed);
    printf("\n\n\ntest step 4:\n");
    processMove(0, 0, 1, 4, 5, board, minefield, numbermap, 3, &flags, &squares_revealed);
    printf("\n\n\ntest step 5:\n");
    processMove(1, 0, 1, 4, 5, board, minefield, numbermap, 3, &flags, &squares_revealed);

    printf("Modify Board Tests completed\n\nPrinting Board:\n");

    for (int i = 0; i < rows; i++) { // only for dev testing
            for (int j = 0; j < columns; j++) {
                    printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("Squares Revealed: %d of %d total.\n", squares_revealed, rows*columns);




    printf("End of testing: Freeing all arrays.\n");
    free(minefield);
    free(numbermap);
    free(board);
    printf("End of testing: All arrays freed.\n");
}
