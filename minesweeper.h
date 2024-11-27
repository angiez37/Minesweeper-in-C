#include <stdbool.h>

// ESHA'S FUNCTIONS
char** generateMinefield(int rows, int columns, int mines);
int surroundingMines(int rows, int columns, char **minefield, int i, int j);
char** generateNumberMap(int rows, int columns, char **minefield);
char** generateGameboard(int rows, int columns);

// JACK'S FUNCTIONS
int processMove(int specified_row, int specified_column, int change, int rows, int columns, char ** board, char ** minefield, char ** numbermap, int mines, int * flags, int * squares_revealed);
void digSquare(int r, int c, int rows, int columns, char ** board, char ** numbermap, int * squares_revealed);
bool gameEndCheck(int rows, int columns, char ** board, char ** minefield, int mines, int * flags);

// ANGEL'S FUNCTIONS
char *welcomePage();
int Menu();
void Instructions(char *name);
void Difficulty(int *rows, int *columns, int *mines);
void parseInput(char *name, int choice, int *rows, int *columns, int *mines);

// DHRUV'S FUNCTIONS
void calculateScore(int squaresRevealed, int rows, int columns);
void revealAllMines(int rows, int columns, char **gameBoard, char **minefield);