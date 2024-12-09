#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdbool.h>

#include "minesweeper.h"


int main() { 

    // Welcome page
    char *playerName = welcomePage();

    int choice = Menu(); // Get menu choice

    
	int rows, columns, mines; // Default settings

    //scanf("%d %d %d", &rows, &columns, &mines);
    parseInput(playerName, choice, &rows, &columns, &mines); // Adjust settings based on input

    free(playerName);
		
	
}
