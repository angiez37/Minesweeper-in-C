#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "minesweeper.h"

#define MIN_BOARD_SIZE 6
#define MAX_BOARD_SIZE 30

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| welcomePage - Welcome page to greet the user and introduce them to the game
|
| Arguments: None
|
| Returns - returns the user's name
| Functions Called: None
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
char *welcomePage() {
    printf("\033[2J"); // Clear the screen
    printf("\033[0;0H"); // Reset cursor to the top
    printf("A long time ago in a galaxy far, far away...\n\n");
    sleep(2); // Pause for effect
    printf("It is a period of war. Hidden mines endanger the galaxy...\n");
    printf("\n");
    sleep(2);
    printf("Enter your name: ");
    char *name = malloc(100 * sizeof(char)); // Allocate memory for the name
    if (name == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        exit(1);
    }

    scanf("%99s", name);
    while (getchar() != '\n');

    sleep(2);
    printf("\n.___  ___.  __  .__   __.  _______         _______.____    __    ____  _______  _______ .______    _______ .______      \n");
    printf("|   \\/   | |  | |  \\ |  | |   ____|       /       |\\   \\  /  \\  /   / |   ____||   ____||   _  \\  |   ____||   _  \\     \n");
    printf("|  \\  /  | |  | |   \\|  | |  |__         |   (----` \\   \\/    \\/   /  |  |__   |  |__   |  |_)  | |  |__   |  |_)  |    \n");
    printf("|  |\\/|  | |  | |  . `  | |   __|         \\   \\      \\            /   |   __|  |   __|  |   ___/  |   __|  |      /     \n");
    printf("|  |  |  | |  | |  |\\   | |  |____    .----)   |      \\    /\\    /    |  |____ |  |____ |  |      |  |____ |  |\\  \\----.\n");
    printf("|__|  |__| |__| |__| \\__| |_______|   |_______/        \\__/  \\__/     |_______||_______|| _|      |_______|| _| `._____|\n\n");

    sleep(1);
    printf("Welcome %s!\n\n", name);
    sleep(1);
    return name;
}

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| Menu - Welcome menu outlining game options: 1. Start GUI Game, 2. Start CMD Line Game, 3. Select Difficulty, 4. Instructions
|
| Arguments: None
|
| Returns - returns the user's selected game option
| Functions Called: None
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
int Menu() {
    int choice;
    int valid;

    do {
        printf("Select an option to begin your mission:\n");
        printf("1. Start GUI Game\n");
        printf("2. Start CMD Line Game\n");
        printf("3. Select Difficulty (ONLY FOR CMD LINE GAME)\n");
        printf("4. Instructions\n");
        printf("5. Exit\n\n");

        printf("Option: ");
        valid = scanf("%d", &choice);
        printf("\n");

        if (valid != 1) {
            printf("Invalid input. Please enter a number between 1 and 5.\n");
            while (getchar() != '\n'); // Clear invalid input from buffer
        } else if (choice < 1 || choice > 5) {
            printf("Invalid choice. Please select a valid option.\n");
        }
    } while (valid != 1 || choice < 1 || choice > 5);

    return choice;
}

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| Instruction - User friendly instructions on how to play the game
|
| Arguments: char *name - the user's name
|
| Returns: None
| Functions Called: None
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
void Instructions(const char *name) {
    printf("======================================\n");
    printf("            MISSION BRIEFING          \n");
    printf("======================================\n\n");

    printf("Welcome, %s. The galaxy is in turmoil.\n", name);
    printf("Your task is to defuse hidden mines planted by the Empire.\n\n");

    printf("Rules:\n");
    printf("- Reveal all the safe tiles without detonating a mine.\n");
    printf("- Use clues (numbers) to deduce where mines are.\n");
    printf("- Clear the board to bring balance to the Force!\n\n");

    printf("Controls:\n");

Controls:
    printf("- Enter the row and column number to reveal a tile.\n");
    printf("- Mark suspected mines using flags.\n\n");

    printf("The Force is strong with you... good luck!\n\n");
}

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| Difficulty - Defines the difficulty level of the game inclding board size and mine density
|
| Arguments: int *rows - pointer to the number of rows in the board
|            int *columns - pointer to the number of columns in the board
|            int *mines - pointer to the number of mines in the board
|
| Returns - None
| Functions Called: None
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
void Difficulty(int *rows, int *columns, int *mines) {
    printf("======================================\n");
    printf("            DIFFICULTY LEVEL          \n");
    printf("======================================\n\n");

    int valid;

    do {
        printf("Input Board Size:\n");

        printf("Rows (6-30): ");
        valid = scanf("%d", rows);
        if (valid != 1 || *rows < MIN_BOARD_SIZE || *rows > MAX_BOARD_SIZE) {
            printf("Invalid input. Rows must be a number between 6 and 30.\n");
            while (getchar() != '\n'); // Clear buffer
            continue;
        }

        printf("Columns (6-30): ");
        valid =scanf("%d", columns);
        if (valid != 1 || *columns < MIN_BOARD_SIZE || *columns > MAX_BOARD_SIZE) {
            printf("Invalid input. Columns must be a number between 6 and 30.\n");
            while (getchar() != '\n'); // Clear buffer
        }
    } 
    while (valid != 1 ||*rows < MIN_BOARD_SIZE || *columns < MIN_BOARD_SIZE || *rows > MAX_BOARD_SIZE || *columns > MAX_BOARD_SIZE);

    int grid = (*rows) * (*columns);

    int choice;
    do {
        printf("Select a difficulty level:\n");
        printf("1. Padawan Training (Easy)\n");
        printf("2. Rebel Assault (Medium)\n");
        printf("3. Jedi Master (Hard)\n");
        printf("Level: ");
        valid = scanf("%d", &choice);

        if (valid != 1 || choice < 1 || choice > 3) {
            printf("Invalid difficulty level. Please try again.\n");
            while (getchar() != '\n'); // Clear buffer
        }
    } while (valid != 1 ||choice < 1 || choice > 3);

    if (choice == 1) { // Easy: 14% mine density
        *mines = grid / 7;
    } else if (choice == 2) { // Medium: 20% mine density
        *mines = grid / 5;
    } else if (choice == 3) { // Hard: 33% mine density
        *mines = grid / 3;
    }

}

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| parseInput - Handles user input as selected from the welcome menu
|
| Arguments: char *name - the user's name
|            int choice - the user's selected game option
|            int *rows - pointer to the number of rows in the board
|            int *columns - pointer to the number of columns in the board
|            int *mines - pointer to the number of mines in the board
|
| Returns - None
| Functions Called: launch_gui(), Difficulty(), Instructions(), Menu()
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/
void parseInput(char *name, int choice, int *rows, int *columns, int *mines) {

    switch (choice) {
        case 1: launch_gui(); break;
        case 2: *rows = 9; *columns = 9; *mines = 10; break; // start game with default settings
        case 3: Difficulty(rows, columns, mines); break; // select difficulty
        case 4: Instructions(name); parseInput(name, Menu(), rows, columns, mines); break; // display instructions
        case 5: exit(0); // Exit program
    }
    
}


