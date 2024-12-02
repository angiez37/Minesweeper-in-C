#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>


int endMenu(int state) { // Outputting end menu messages
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
        // Printing defeat message
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
    printf("2. Exit\n"); // Play again or exit options
    printf("\n");
    while (correct_input == 0) { // While loop to care for incorrect inputs
        printf("Enter your choice:");
        scanf("%d", &choice);
        printf("\n");
        if (choice == 1 || choice == 2) { // Checking if user input correct
            correct_input = 1; // Breaking out of loop
        }
        else {
            printf("Not in range! Pick either option 1 or 2.\n");
        }
    }
    
    return choice; // return user choice
}


char** outputMinefield(char **minefield, int rows, int columns) { // Outputting minefield

    printf("Location of Mines\n");
    printf("\n");

    int count = 0;

    printf("   ");
    for (int k=0; k<columns; k++) { // Printing top numbers
        if (k<9) {
            printf("   %d  ", (k+1));
        }
        else {
            printf("  %d  ", (k+1));
        }
    }
    printf("\n");

    for (int i=0; i<rows; i++) {
        printf("   ");
        for(int i=0; i<columns; i++) { 
            printf(" —————"); // Printing a line above each row for top border
        }
        printf("\n");
        printf("%d ", (i+1)); // Printing side numbers
        if ((i+1)<10) {
            printf(" |");
        }
        else {
            printf("|");
        }
        for (int j=0; j<columns; j++) {
            printf("  %c  |", minefield[i][j]); // Printing each row with side border
        }
        //printf("|"); 
        printf("\n");

        count = 0;
        printf("   ");
        for(int i=0; i<columns; i++) {
            printf(" —————"); // Printing row of lines at bottom of each row for bottom border
        }
        printf("\n");
    }
    printf("\n");
    count = 0;
}

// Testing purposes, remove before submitting
/*int main() {
    // Sample minefield for testing
    int rows = 11, columns = 10;
    
    // Allocating memory for a 2D array dynamically to simulate the minefield
    char *minefield[11] = {
    "*..........",
    ".*.........",
    "..*........",
    "...*.......",
    "....*......",
    ".....*.....",
    "......*....",
    ".......*...",
    "........*..",
    ".........*.",
    "..........."
    };

    // Call the function to print the minefield
    outputMinefield(minefield, rows, columns);

    //int tc1 = endMenu(1);
    //printf("%d\n", tc1);

    return 0;
}*/