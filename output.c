#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <unistd.h>


void win_lose_message(int state) { // Outputting end menu messages
    if (state == 1) {
        // Printing victory message (ignore format, when printed it works as expected)
        printf("\n   __        __    __    __ __ __    __ __ __     __ __ __     __ __    __    __\n");
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
        printf("\n   __ __ __     __ __ __    __ __ __    __ __ __         ___     __ __ __            \n");
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
}

int end_menu() {
    int choice;
    int correct_input = 0;
    printf("1. Play Again\n");
    printf("2. Exit\n"); // Play again or exit options
    printf("\n");
    while (correct_input == 0) { // While loop to care for incorrect inputs
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        if (choice == 1) { // If user plays again reprint the minesweeper header
            correct_input = 1; // Breaking out of loop
            printf("\033[2J"); // Clear the screen
            printf("\033[0;0H"); // Reset cursor to the top
            printf("\n.___  ___.  __  .__   __.  _______         _______.____    __    ____  _______  _______ .______    _______ .______      \n");
            printf("|   \\/   | |  | |  \\ |  | |   ____|       /       |\\   \\  /  \\  /   / |   ____||   ____||   _  \\  |   ____||   _  \\     \n");
            printf("|  \\  /  | |  | |   \\|  | |  |__         |   (----` \\   \\/    \\/   /  |  |__   |  |__   |  |_)  | |  |__   |  |_)  |    \n");
            printf("|  |\\/|  | |  | |  . `  | |   __|         \\   \\      \\            /   |   __|  |   __|  |   ___/  |   __|  |      /     \n");
            printf("|  |  |  | |  | |  |\\   | |  |____    .----)   |      \\    /\\    /    |  |____ |  |____ |  |      |  |____ |  |\\  \\----.\n");
            printf("|__|  |__| |__| |__| \\__| |_______|   |_______/        \\__/  \\__/     |_______||_______|| _|      |_______|| _| `._____|\n\n");
            sleep(1);
        }
        else if (choice == 2) { // user chose exit
            correct_input = 1; // break  out of loop
        }
        else {
            printf("Not in range! Pick either option 1 or 2.\n");
        }
    }
    
    return choice; // return user choice

}


char** printBoard(char **board, int rows, int columns) { // Outputting board

    // print number headers
    printf("   "); // spacer
    for (int k=0; k<columns; k++) { // Printing top numbers
        if (k<9) {
            printf("  %d ", (k+1));
        }
        else {
            printf("  %d", (k+1));
        }
    }

    // print each row
    for (int i=0; i<rows; i++) {
        printf("\n   "); // spacer
        for(int i=0; i<columns; i++) { 
            printf(" ———"); // Printing a line above each row for top border
        }

        printf("\n");

        // Printing side numbers
        if ((i+1)<10) {
            printf(" %d |", (i+1)); 
        }
        else {
            printf("%d |", (i+1)); 
        }


        for (int j=0; j<columns; j++) {
            printf(" %c |", board[i][j]); // Printing each row with side border
        }

    } // end of for rows in board loop

    // print bottom line of board
    printf("\n   "); // spacer
    for(int i=0; i<columns; i++) {
            printf(" ———"); // Printing bottom line of board
        }
        printf("\n");

} // end of printBoard

/*char** outputMinefield(char **minefield, int rows, int columns) { // Outputting minefield

    printf("\n   ");
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
        printf("\n");

        printf("   ");
        for(int i=0; i<columns; i++) {
            printf(" —————"); // Printing row of lines at bottom of each row for bottom border
        }
        printf("\n");
    }
    printf("\n");
}*/

void outputMessage(){
    // Game ending message
    printf("Thank you for joining us on this brave journey\n");
    sleep(1);
    printf("Until our paths cross again in the vast expanse of the cosmos,\n");
    sleep(1);
    printf("keep your lightsaber close and your heart open to the mysteries of the universe.\n");
    sleep(2);
    printf("May the Force be with you.\n");
}

// Testing purposes, remove before submitting
int main() {
    // Sample minefield for testing
    int rows = 11, columns = 10;
    
    // Allocating memory for a 2D array dynamically to simulate the minefield
    /*char *minefield[11] = {
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
    };*/

    // Call the function to print the minefield

    win_lose_message(2);
    //int tc1 = end_menu();
    //printf("%d\n", tc1);
    outputMessage();

    return 0;
}