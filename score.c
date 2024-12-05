#include <stdio.h>
#include "minesweeper.h"

void calculateScore(int squaresRevealed, int rows, int columns) {
    float percentage = (float)squaresRevealed / (rows * columns) * 100;
    printf("Progress: %.3f%% of the board revealed.", percentage);
}
