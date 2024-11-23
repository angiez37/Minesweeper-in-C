// ESHA'S FUNCTIONS
char** generateMinefield(int rows, int columns, int mines);
int surroundingMines(int rows, int columns, char **minefield, int i, int j);
char** generateNumberMap(int rows, int columns, char **minefield);
char** generateGameboard(int rows, int columns);

// JACK'S FUNCTIONS
void processMove(int specified_row, int specified_column, int change, int rows, int columns, char ** board, char ** minefield, char ** numbermap, int mines, int * flags, int * squares_revealed);
void digSquare(int r, int c, int rows, int columns, char ** board, char ** numbermap, int * squares_revealed);
void gameEndCheck(int rows, int columns, char ** board, char ** minefield, int mines, int * flags);
