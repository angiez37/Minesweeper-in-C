#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MIN_BOARD_SIZE 6
#define MAX_BOARD_SIZE 30

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

// Function to display the menu
int Menu() {
    printf("Select an option to begin your mission:\n");
    printf("1. Start Game\n");
    printf("2. Select Difficulty\n");
    printf("3. Instructions\n");
    printf("4. Exit\n\n");

    int choice;
    printf("Option: ");
    scanf("%d", &choice);

    return choice;
}

// Function to display the user instructions
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

// Function to handle difficulty selection
void Difficulty(int *rows, int *columns, int *mines) {
    printf("======================================\n");
    printf("            DIFFICULTY LEVEL          \n");
    printf("======================================\n\n");

    do {
        printf("Input Board Size:\n");
        printf("Rows (6-30): ");
        scanf("%d", rows);
        printf("Columns (6-30): ");
        scanf("%d", columns);

        if (*rows < MIN_BOARD_SIZE || *columns < MIN_BOARD_SIZE || *rows > MAX_BOARD_SIZE || *columns > MAX_BOARD_SIZE) {
            printf("Invalid board size. Please try again.\n");
        }
    } 
    while (*rows < MIN_BOARD_SIZE || *columns < MIN_BOARD_SIZE || *rows > MAX_BOARD_SIZE || *columns > MAX_BOARD_SIZE);

    int grid = (*rows) * (*columns);

    int choice;
    do {
        printf("Select a difficulty level:\n");
        printf("1. Padawan Training (Easy)\n");
        printf("2. Rebel Assault (Medium)\n");
        printf("3. Jedi Master (Hard)\n");
        printf("Level: ");
        scanf("%d", &choice);

        if (choice == 1) { // Easy: 14% mine density
            *mines = grid / 7;
        } else if (choice == 2) { // Medium: 20% mine density
            *mines = grid / 5;
        } else if (choice == 3) { // Hard: 33% mine density
            *mines = grid / 3;
        } else {
            printf("Invalid difficulty level. Please try again.\n\n");
        }
    } while (choice < 1 || choice > 3);

}

void parseInput(char *name, int choice, int *rows, int *columns, int *mines) {

    switch (choice) {
        case 1: *rows = 9; *columns = 9; *mines = 10; break; // start game with default settings
        case 2: Difficulty(rows, columns, mines); break; // select difficulty
        case 3: Instructions(name); parseInput(name, Menu(), rows, columns, mines); break; // display instructions
        case 4: exit(0); // Exit program
        default: printf("Invalid choice.\n"); parseInput(name, Menu(), rows, columns, mines);
    }
    
}

/*
int main() {
    int rows, columns, mines;
    char *name = welcomePage();  // Call welcomeMenu function
    int choice = Menu(); // Call menu function

    parseInput(name, choice, rows, columns, mines); //parse user menu input
    free(name);
    return 0;
}
*/

