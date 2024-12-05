#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "minesweeper.h"

void testSurroundingMines() {
    char* minefield[5][5] = {
        {".", ".", ".", ".", "."},
        {".", "X", ".", "X", "."},
        {".", ".", ".", ".", "."},
        {".", ".", "X", ".", "."},
        {".", ".", ".", ".", "."}
    };

    // Test cases for surroundingMines function
    int outcome1 = surroundingMines(5, 5, minefield, 1, 1);  // 0
    int outcome2 = surroundingMines(5, 5, minefield, 0, 0);  // 1
    int outcome3 = surroundingMines(5, 5, minefield, 2, 1);  // 2

    // Print results
    printf("Test 1 result: %d (Expected: 0)\n", outcome1);
    printf("Test 2 result: %d (Expected: 1)\n", outcome2);
    printf("Test 3 result: %d (Expected: 2)\n", outcome3);
}

void testGenerateMinefield() {
    int rows = 5, columns = 5, mines = 3;

    // Generate minefield
    char** minefield = generateMinefield(rows, columns, mines);

    // Print minefield
    printf("Generated minefield:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", minefield[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(minefield[i]);
    }
    free(minefield);
}

void testGenerateNumberMap() {
    int rows = 5, columns = 5;

    char* minefield[5][5] = {
        {".", ".", ".", ".", "."},
        {".", "X", ".", "X", "."},
        {".", ".", ".", ".", "."},
        {".", ".", "X", ".", "."},
        {".", ".", ".", ".", "."}
    };

    // Generate number map based on minefield
    char** numberMap = generateNumberMap(rows, columns, minefield);

    // Print generated number map
    printf("Generated number map:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", numberMap[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(numberMap[i]);
    }
    free(numberMap);
}

void testGenerateGameboard() {
    int rows = 5, columns = 5;

    // Generate gameboard
    char** gameboard = generateGameboard(rows, columns);

    // Print generated gameboard
    printf("Generated gameboard:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%c ", gameboard[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(gameboard[i]);
    }
    free(gameboard);
}

int main() {
    srand(time(NULL)); 

    testSurroundingMines();
    testGenerateMinefield();
    testGenerateNumberMap();
    testGenerateGameboard();

    return 0;
}
