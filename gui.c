#include <gtk/gtk.h> // USING GTK API VERSION 3.0
#include <stdlib.h>
#include <time.h>
#include "minesweeper.h"

// Currently the board size and mine count are Macros and cannot be changed. However, only for testing purposes and will implement an option to change these values in the final version.
#define BOARD_SIZE 16
#define MINE_COUNT 20

// Link to GTK documentation for reference: https://docs.gtk.org/gtk3/index.html
// Link to GTK Application for reference: https://docs.gtk.org/gio/class.Application.html#methods
// LInk to GTK Window for reference: https://docs.gtk.org/gtk3/ctor.Window.new.html
// Link to GTK Button for reference: https://docs.gtk.org/gtk3/class.Button.html
// Link to GTK Label for reference: https://docs.gtk.org/gtk3/class.Label.html
// Link to GTK Widget for reference: https://docs.gtk.org/gtk3/class.Widget.html

// One of the coolest things I've learned was this while working on the GUI, struct
// Groups related variables together and can use it similar to objects in OOP
// For example, board[i][j].revealed is much more readable than revealed[i][j]
typedef struct {
    int is_mine;
    int revealed;
    int flagged;
    GtkWidget *button;
} Cell;

Cell board[BOARD_SIZE][BOARD_SIZE]; // 2D array of Cell structs; can be used with previously implemented structs to call and use related variables

char **minefield;
char **numberMap;
int remaining_cells;
GtkWidget *game_over_label; // Global variable for the label - used to display the game over message. Function defined using GTK

// Using functions from previously implemented board.c & logic.c (Not included in this file for testing purposes)
// File has not been combined with the minesweeper.h yet however, the final version will have all implementations of game working together

// // Function to calculate surrounding mines
// int surroundingMines(int rows, int columns, char **minefield, int i, int j) {
//     int surrounding_mines = 0;
//     if (minefield[i][j] != 'X') {
//         if (i < rows - 1 && minefield[i + 1][j] == 'X') surrounding_mines++;
//         if (i > 0 && minefield[i - 1][j] == 'X') surrounding_mines++;
//         if (j < columns - 1 && minefield[i][j + 1] == 'X') surrounding_mines++;
//         if (j > 0 && minefield[i][j - 1] == 'X') surrounding_mines++;
//         if (i > 0 && j < columns - 1 && minefield[i - 1][j + 1] == 'X') surrounding_mines++;
//         if (i < rows - 1 && j < columns - 1 && minefield[i + 1][j + 1] == 'X') surrounding_mines++;
//         if (i > 0 && j > 0 && minefield[i - 1][j - 1] == 'X') surrounding_mines++;
//         if (i < rows - 1 && j > 0 && minefield[i + 1][j - 1] == 'X') surrounding_mines++;
//     }
//     return surrounding_mines;
// }

// // Function to generate the minefield
// char **generateMinefield(int rows, int columns, int mines) {
//     char **minefield = (char **)malloc(rows * sizeof(char *));
//     for (int i = 0; i < rows; i++) {
//         minefield[i] = (char *)malloc(columns * sizeof(char));
//         for (int j = 0; j < columns; j++) {
//             minefield[i][j] = '.';
//         }
//     }

//     int mines_placed = 0;
//     while (mines_placed < mines) {
//         int i = rand() % rows;
//         int j = rand() % columns;
//         if (minefield[i][j] != 'X') {
//             minefield[i][j] = 'X';
//             mines_placed++;
//         }
//     }
//     return minefield;
// }


// // Function to generate the number map
// char** generateNumberMap(int rows, int columns, char **minefield) { 
	
// 	char** numberMap = (char**)malloc(rows * sizeof(char*));
//     		for (int i = 0; i < rows; i++) {
//         		numberMap[i] = (char*)malloc(columns * sizeof(char));
//     		}

// 	for (int i = 0; i < rows; i++) { 
// 		for (int j = 0; j < columns; j++) { 
// 			if (minefield[i][j] != 'X') { 
// 				int touching_mines = surroundingMines(rows, columns, minefield, i, j);
// 				if (touching_mines == 0) { 
//     					numberMap[i][j] = '0';
// 				} else {
// 					numberMap[i][j] = '0' + touching_mines;    			
// 				}
// 			} 
//             else { 
// 				numberMap[i][j] = 'X';
// 		    }
// 	    }
//     }  	
//     return numberMap;
// }


void reveal_all_bombs() {
    // Show the Game Over message
    // Imported function from gtk - it sets the text for the label and overwrites any text that was there before
    gtk_label_set_text(GTK_LABEL(game_over_label), "Game Over! You hit a mine!");

    // Disable all buttons on the board
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (minefield[i][j] == 'X') {
                gtk_button_set_label(GTK_BUTTON(board[i][j].button), "💣"); // Imported function from gtk - sets the label of button to (Mine emoji)
            }
            gtk_widget_set_sensitive(board[i][j].button, FALSE); // Disable the button; imported function from gtk - makes sure the button cannot be clicked
        }
    }

    // g_timeout_add_seconds(2, (GSourceFunc)gtk_main_quit, NULL); // Wait 2 seconds and then quit
}



void on_cell_clicked(GtkWidget *widget, GdkEventButton *event, int *coords) {
    int row = coords[0];
    int col = coords[1];

    // For all lines of code with -> implementation:
    // Initially I used . to access the member of a struct but my code kept giving errors that I didn't understand
    // Usage of arrow operater never crossed my mind, but after some searching online I found out that it is used to access the member of a struct using a pointer
    // Since the gtk button is defined using a pointer, the only way to access it, is using -> instead of . 

    if (board[row][col].revealed || (event->button == GDK_BUTTON_SECONDARY && board[row][col].flagged)) { //If the cell is already revealed or flagged, do nothing; I need to change this so that if it is flagged, it will unflag but this was created for testing purposes in the first release.
        return;
    }

    if (event->button == GDK_BUTTON_SECONDARY) { // Right-click to toggle flag
        board[row][col].flagged = !board[row][col].flagged;

        if (board[row][col].flagged) {
            gtk_button_set_label(GTK_BUTTON(widget), "🚩");
        } else {
            gtk_button_set_label(GTK_BUTTON(widget), "");
        }

        return;
    }

    if (minefield[row][col] == 'X') { // Mine hit
        gtk_button_set_label(GTK_BUTTON(widget), "💣");
        gtk_widget_set_sensitive(widget, FALSE);
        g_print("Game Over!\n");

        // Reveal all bombs and show game over message
        reveal_all_bombs();

        return;
    }

    // Reveal the square
    board[row][col].revealed = 1;
    
    char label[2] = { numberMap[row][col], '\0' };
    gtk_button_set_label(GTK_BUTTON(widget), label);
    remaining_cells--;

    // Check win condition
    if (remaining_cells == 0) {
        g_print("You Win!\n");
        gtk_label_set_text(GTK_LABEL(game_over_label), "You Win!");

        // g_timeout_add_seconds(2, (GSourceFunc)gtk_main_quit, NULL); // Wait 2 seconds and then quit
        return;
    }

    // // Ripple reveal if the cell has no adjacent mines
    // // Not sure why this isnt working
    // if (numberMap[row][col] == '0') {
    //     for (int dr = -1; dr <= 1; dr++) {
    //         for (int dc = -1; dc <= 1; dc++) {
    //             int newRow = row + dr;
    //             int newCol = col + dc;
    //             if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
    //                 if (!board[newRow][newCol].revealed) {
    //                     on_cell_clicked(board[newRow][newCol].button, event, data);
    //                 }
    //             }
    //         }
    //     }
    // }
}

// Initialize the GUI board and link it to the existing logic
void initialize_gui_board(GtkWidget *grid) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            board[i][j].button = gtk_button_new(); // Make each tile/cell a button
            // gtk_widget_set_size_request(board[i][j].button, 30, 30); // Set the size of the button

            gtk_grid_attach(GTK_GRID(grid), board[i][j].button, j, i, 1, 1);

            int *coords = malloc(2 * sizeof(int)); // Allocate memory for all the coordinates

            coords[0] = i;
            coords[1] = j;

            // Was not able to find this on GTK documentation. Weird.
            g_signal_connect(board[i][j].button, "button-press-event", G_CALLBACK(on_cell_clicked), coords); // Not too sure how or what this does. Used gpt generate this line of code and to help me understand but still confused. But without this, the buttons do not work and the game does not function. Very unique and interesting.
        }
    }
}

void activate(GtkApplication *app) {
    // Create the main window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Minesweeper"); // Title of the new window; is a gtk function
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 600); // Sets max size of window

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create and add the Game Over label (initially empty)
    game_over_label = gtk_label_new("");
    gtk_grid_attach(GTK_GRID(grid), game_over_label, 0, BOARD_SIZE, BOARD_SIZE, 1);  // Place it below the grid

    // Use the generated logic to set up the board
    minefield = generateMinefield(BOARD_SIZE, BOARD_SIZE, MINE_COUNT);
    numberMap = generateNumberMap(BOARD_SIZE, BOARD_SIZE, minefield);
    remaining_cells = BOARD_SIZE * BOARD_SIZE - MINE_COUNT;

    initialize_gui_board(grid);
    gtk_widget_show_all(window);
}


int startGUI(int argc, char **argv) {
    // random number generator
    // srand(time(NULL));

    GtkApplication *app = gtk_application_new("com.example.Minesweeper", G_APPLICATION_FLAGS_NONE);

    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    // Free memory
    for (int i = 0; i < BOARD_SIZE; i++) {
        free(minefield[i]);
        free(numberMap[i]);
    }
    free(minefield);
    free(numberMap);

    return status;
}

void launch_gui() {
    GtkApplication *app = gtk_application_new("com.example.minesweeper", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);

    outputMinefield(minefield, BOARD_SIZE, BOARD_SIZE); 
    int playAgain = endMenu(status);

    while (playAgain == 1) {
        launch_gui();
    }
    
    if (playAgain == 2) {
        exit(0);
    }
}