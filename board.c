#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

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
    					numberMap[i][j] = ' ';
				} else {
					numberMap[i][j] = '0' + touching_mines;    			
				}
			} else { 
				numberMap[i][j] = 'X';
		}
	}
}
	for (int i = 0; i < rows; i++) { // only for dev testing - need to print only the square player selects 
        	for (int j = 0; j < columns; j++) {
            		printf("%c ", numberMap[i][j]);
        }
        printf("\n");
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

int main() { 

	srand(time(NULL)); 

    	int rows = 5; // for testing - Angel's code
    	int columns = 7;
    	int mines = 10;
	
	char** minefield = generateMinefield(rows, columns, mines);
	char** numberMap = generateNumberMap(rows, columns, minefield);
	char** gameboard = generateGameboard(rows, columns);

	free(minefield);
	free(numberMap);
	free(gameboard);

}
