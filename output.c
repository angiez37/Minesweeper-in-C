#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>


int endMenu(int state) {
    int choice;
    if (state == 1) {
        printf("The Force is strong with you, Jedi!\n");
        printf("The mines have been defused, and peace has returned to the galaxy!\n");
    }
    else {
        printf("You have failed me for the last time, Commander.\n");
        printf("The mines have detonated, and the galaxy is in ruins.\n");
    }
    printf("\n");
    printf("1. Play Again\n");
    printf("2. Exit\n");
    printf("Enter your choice:");
    printf("%d", &choice);
    return choice;
}


char** outputMinefield(char **minefield, int rows, int columns) {

    printf("Location of Mines");

    int count = 0;
    for (int i=0; i<rows; i++) {
        while(count != columns) {
            printf("—");
        }
        printf("\n");
        count = 0;

        for (int j=0; j<columns; j++) {
            printf("|");
            printf("%c ", minefield[i][j]);
        }
        printf("|");
        printf("\n");
    }

    while(count != columns) {
        printf("—");
    }
    printf("\n");
    count = 0;
}