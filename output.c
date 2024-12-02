#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>


int endMenu(int state) {
    int choice;
    int correct_input = 0;
    if (state == 1) {
        // Printing victory message (ignore format, when printed it works as expected)
        printf("   __        __    __    __ __ __    __ __ __     __ __ __     __ __    __    __\n");
        printf("  \\  \\      /  /  |  |  |        |  |        |  /    __   \\  |   __  \\  \\ \\  / /\n");
        printf("   \\  \\    /  /   |  |  |  |‾‾ ‾‾    ‾‾|  |‾‾   |  /   \\  |  |  |  )  |  \\ \\/ /\n");
        printf("    \\  \\  /  /    |  |  |  |           |  |     |  |   |  |  |   ‾‾  /    |  |\n");
        printf("     \\  \\/  /     |  |  |  |__ __      |  |     |  \\__ /  |  |  |\\  \\     |  |\n");
        printf("      \\ __ /      |__|  |__ __ __|     |__|     \\__ __ __ /  |__| \\ _\\    |__|\n");

        sleep(2);
        printf("\n");
        printf("The Force is strong with you, Jedi!\n");
        printf("The mines have been defused, and peace has returned to the galaxy!\n");
    }
    else {
        printf("   __ __ __     __ __ __    __ __ __    __ __ __         ___     __ __ __            \n");
        printf("  |   __   \\   |   __ __|  |   __ __|  |   __ __|      / __ \\   |__    __|    \n");
        printf("  |  |  \\   |  |  |__ __   |  |__ __   |  |__ __      / /__\\ \\     |  |       \n");
        printf("  |  |   |  |  |   __ __|  |   __ __|  |   __ __|    /  ___   \\    |  |         \n");
        printf("  |  |__/   |  |  |__ __   |  |        |  |__ __    /  /   \\   \\   |  |          \n");
        printf("  |__ __ __/   |__ __ __|  |__|        |__ __ __|  /__/     \\ __\\  |__|            \n");

        sleep(2);
        printf("\n");
        printf("You have failed me for the last time, Commander.\n");
        printf("The mines have detonated, and the galaxy is in ruins.\n");
    }

    sleep(2);
    printf("\n");
    printf("1. Play Again\n");
    printf("2. Exit\n");
    printf("\n");
    while (correct_input == 0) {
        printf("Enter your choice:");
        scanf("%d", &choice);
        printf("\n");
        if (choice == 1 || choice == 2) {
            correct_input = 1;
        }
        else {
            printf("Not in range! Pick either option 1 or 2.\n");
        }
    }
    
    return choice;
}


void outputMinefield(char **minefield, int rows, int columns) { 

    printf("Location of Mines\n");

    int count = 0;
    for (int i=0; i<rows; i++) {
        for(int i=0; i<columns; i++) {
            printf(" ———");
        }
        printf("\n");

        for (int j=0; j<columns; j++) {
            printf("|");
            printf(" %c ", minefield[i][j]);
        }
        printf("|");
        printf("\n");

        count = 0;
        for(int i=0; i<columns; i++) {
            printf(" ———");
        }
        printf("\n");
    }
    printf("\n");
    count = 0;
}

// Testing purposes, remove before submitting
/*int main() {
    // Sample minefield for testing
    int rows = 3, columns = 4;
    
    // Allocating memory for a 2D array dynamically to simulate the minefield
    char *minefield[3] = {
        "* . . .",
        ". * . .",
        ". . * ."
    };

    // Call the function to print the minefield
    outputMinefield(minefield, rows, columns);

    int tc1 = endMenu(1);
    printf("%d\n", tc1);

    return 0;
}*/