#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


char** outputMinefield(char **minefield, int rows, int columns) {

    printf("Location of Mines");

    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            printf("%c ", minefield[i][j]);
        }
        printf("\n");
    }
}




