#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeper.h" 

int main() {
    srand(time(NULL));

    int rows, columns, mines;

    if (scanf("%d %d %d", &rows, &columns, &mines) != 3) {
        fprintf(stderr, "Error: Invalid input format.\n");
        return 1;
    }

    char** minefield = generateMinefield(rows, columns, mines);
    if (!minefield) {
        fprintf(stderr, "Error: Failed to generate minefield.\n");
        return 1;
    }

    char** numberMap = generateNumberMap(rows, columns, minefield);
    if (!numberMap) {
        fprintf(stderr, "Error: Failed to generate number map.\n");
        for (int i = 0; i < rows; i++) free(minefield[i]);
        free(minefield);
        return 1;
   } 

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", numberMap[i][j]);
        }
        printf("\n");
    }

   
    for (int i = 0; i < rows; i++) {
        free(minefield[i]);
        free(numberMap[i]);
    }
    free(minefield);
    free(numberMap);

    return 0;
}

