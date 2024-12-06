#include <stdbool.h>

char** generateMinefield(int rows, int columns, int mines);
int surroundingMines(int rows, int columns, char **minefield, int i, int j);
char** generateNumberMap(int rows, int columns, char **minefield);
char** generateGameboard(int rows, int columns);

