#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define DEBUG 0
#define MINEFIELDOUTPUT 1

// COPIED ESHA'S CODE INTO HERE JUST TO GENERATE TESTING INPUT
int surroundingMines(int rows, int columns, char minefield[rows][columns], int i, int j) { 
	
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

void boardLayout(int rows, int columns, int mines) {
	
	char minefield[rows][columns]; 
	char playerBoard[rows][columns];
	
	int mines_placed = 0; 

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
	            minefield[i][j] = '.';
		    playerBoard[i][j] = '.';
	        }
	    }

	while (mines_placed < mines) { 
		int i = rand() % rows;
		int j = rand() % columns;
		
		if (minefield[i][j] != 'X') { 
			minefield[i][j] = 'X'; 					
			mines_placed++; 
		}
	}

    if (MINEFIELDOUTPUT) {
        printf("DEV - Printing Minefield:\n");
        for (int i = 0; i < rows; i++) { // printing for dev purposes - remove later  
                for (int j = 0; j < columns; j++) { 
                    printf("%c ", minefield[i][j]);
            }
            printf("\n");
        }
    }

	for (int i = 0; i < rows; i++) { 
		for (int j = 0; j < columns; j++) { 
			if (minefield[i][j] != 'X') { 
				int touching_mines = surroundingMines(rows, columns, minefield, i, j);
				if (touching_mines == 0) { 
    					playerBoard[i][j] = '0';
				} else {
				minefield[i][j] = '0' + touching_mines;
				playerBoard[i][j] = '0' + touching_mines;    			
				}
			}
		}
	}

    if (MINEFIELDOUTPUT) {
        printf("\nDEV - Printing PlayerBoard:\n");
        for (int i = 0; i < rows; i++) { // only for dev testing - need to print only the square player selects 
                for (int j = 0; j < columns; j++) {
                        printf("%c ", playerBoard[i][j]);
            }
            printf("\n");
        }
    }

}
// END OF COPIED CODE FROM ESHA




void modifyBoard(int r, int c, int rows, int columns, char board[rows][columns], char numbermap[rows][columns]) { // RECURSE CALLS WILL BE FUN
    if (board[r][c] == '.') {
        board[r][c] = numbermap[r][c];
    }
    else {
        if (DEBUG) {
        printf("[%d][%d] not '.'\tSkipping\n", r, c); // dev
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
            modifyBoard(r-1, c-1, rows, columns, board, numbermap);
        }	
        if (r > 0) { // N face
            if (DEBUG) {
                printf("Looking N from [%d][%d] at [%d][%d]\n", r, c, r-1, c);
            }
            modifyBoard(r-1, c, rows, columns, board, numbermap);
        }
        if (r > 0 && c < (columns-1)) { // NE diagonal
            if (DEBUG) {
                printf("Looking NE from [%d][%d] at [%d][%d]\n", r, c, r-1, c+1);
            }
            modifyBoard(r-1, c+1, rows, columns, board, numbermap);
        }
        if (c < (columns-1)) { // E face
            if (DEBUG) {
                printf("rows:%d cols:%d\tLooking E from [%d][%d] at [%d][%d]\n", rows, columns, r, c, r, c+1);
            }
            modifyBoard(r, c+1, rows, columns, board, numbermap);
        }
        if (r < (rows-1) && c < (columns-1)) { // SE diagonal
            if (DEBUG) {
                printf("Looking SE from [%d][%d] at [%d][%d]\n", r, c, r+1, c+1);
            }
            modifyBoard(r+1, c+1, rows, columns, board, numbermap);
        }
        if (r < (rows-1)) { // S face
            if (DEBUG) {
                printf("Looking S from [%d][%d] at [%d][%d]\n", r, c, r+1, c);
            }
            modifyBoard(r+1, c, rows, columns, board, numbermap);
        }
        if (r < (rows-1) && c > 0) { // SW diagonal
            if (DEBUG) {
                printf("Looking SW from [%d][%d] at [%d][%d]\n", r, c, r+1, c-1);
            }
            modifyBoard(r+1, c-1, rows, columns, board, numbermap);
        }
        if (c > 0) { // W face
            if (DEBUG) {
                printf("Looking W from [%d][%d] at [%d][%d]\n", r, c, r, c-1);
            }
            modifyBoard(r, c-1, rows, columns, board, numbermap);
        }

    }
    

}

void gameEndCheck(int rows, int columns, char board[rows][columns], char minefield[rows][columns], int mines, int * flags) {
    if (mines == *flags) { // same number of flags as mines, assume flag char is 'F'
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

void processMove(int row_guess, int column_guess, int change, int rows, int columns, char board[rows][columns], char minefield[rows][columns], char numbermap[rows][columns], int mines, int * flags) {
    
    if (change == 0) { // 0 for dig
        if (numbermap[row_guess][column_guess] == 'X') {
            printf("TRIGGER END OF GAME - LOSE\n"); /////////////////////////////////// DHRUV FUCTION
            // trigger scoreboard
        }

        else {
            printf("Calling Modify Board\n");
            modifyBoard(row_guess, column_guess, rows, columns, board, numbermap); // add parameters
        }

    }

    if (change == 1) { // 1 is flag
        // toggle flag in location
        *flags++;
        *flags--;
    }

    gameEndCheck(rows, columns, board, minefield, mines, flags);
}





int main() { 

    // eshas test
	// boardLayout(5, 7, 3);
    
    int rows = 4;
    int columns = 5;
	char minefield[4][5] = { {'X', '.', '.', '.', '.'}, {'X', '.', '.', '.', '.'}, {'.', '.', '.', '.', '.'}, {'.', '.', '.', '.', 'X'} };

    char numbermap[4][5];

    //number map
    for (int i = 0; i < rows; i++) { 
		for (int j = 0; j < columns; j++) { 
			if (minefield[i][j] != 'X') { 
				int touching_mines = surroundingMines(rows, columns, minefield, i, j);
				if (touching_mines == 0) { 
    					numbermap[i][j] = '0';
				} else {
				numbermap[i][j] = '0' + touching_mines;    			
				}
			}
            else {
                numbermap[i][j] = 'X'; ////// ESHA ADD THIS
            }
		}
	}

    //playerboard
    char board[4][5];
    for (int i = 0; i < rows; i++) {  // ESHA ADD THIS
		for (int j = 0; j < columns; j++) { 
			board[i][j] = '.'; // assuming we want blank char to be .
		}
	}

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
    int flags = 5;
    processMove(2, 2, 0, 4, 5, board, minefield, numbermap, 2, &flags);
    printf("Modify Board completed\n\nPrinting Board AFTER MOVE PROCESS:\n");

    for (int i = 0; i < rows; i++) { // only for dev testing
            for (int j = 0; j < columns; j++) {
                    printf("%c ", board[i][j]);
        }
        printf("\n");
    }

}
