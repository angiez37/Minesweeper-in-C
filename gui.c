#include <gtk/gtk.h> // USING GTK API VERSION 3.0
#include <stdlib.h>
#include <time.h>
#include "minesweeper.h"

// Currently the board size and mine count are Macros and cannot be changed.
#define BOARD_SIZE 18
#define MINE_COUNT 40

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

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| reveal_all_bombs - Displays all bombs on the board when the game is over, disables buttons, and shows the "Game Over" message.
| 
| Arguments: None
| 
| Pointers / Side Effects: Updates the board to display all bomb positions and disables user interaction.
| Outputs: Displays "Game Over" message and revealed bomb positions on the GUI.
| Returns: None
| Functions Called: gtk_label_set_text, gtk_button_set_label, gtk_widget_set_sensitive
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

void reveal_all_bombs() {
    // Show the Game Over message
    // Imported function from gtk - it sets the text for the label and overwrites any text that was there before
    gtk_label_set_text(GTK_LABEL(game_over_label), "Game Over! You hit a mine! \n Please Exit the game now!");


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

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| on_cell_clicked - Handles user clicks on the 2d array cell. Left-click digs the cell to reveal a number whereas right-click toggles a flag. 
| Recursively reveals adjacent cells if no mines are nearby.
| 
| Arguments: widget = Pointer to the clicked widget (cell button)
|            event = Event containing button press details (left or right-click)
|            coords = Array of integers containing the row and column indices of the clicked cell
| 
| Pointers / Side Effects: Updates the board with revealed numbers or flags. Terminates the game if a mine is clicked.
| Outputs: Updates GUI to reflect revealed cells, flags, or game end.
| Returns: None
| Functions Called: gtk_button_set_label, gtk_widget_set_sensitive, reveal_all_bombs, g_print
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

void on_cell_clicked(GtkWidget *widget, GdkEventButton *event, int *coords) {
    int row = coords[0];
    int col = coords[1];

    // For all lines of code with -> implementation:
    // Initially I used . to access the member of a struct but my code kept giving errors that I didn't understand
    // Usage of arrow operater never crossed my mind, but after some searching online I found out that it is used to access the member of a struct using a pointer
    // Since the gtk button is defined using a pointer, the only way to access it, is using -> instead of . 

    if (event->button == GDK_BUTTON_SECONDARY) { // Right-click to toggle flag
        board[row][col].flagged = !board[row][col].flagged;
    
        if (board[row][col].flagged) {
            gtk_button_set_label(GTK_BUTTON(widget), "🚩");
        } 
        else {
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

    // Ripple reveal if the cell has no adjacent mines
    if (numberMap[row][col] == '0') {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                // Skip the current cell
                if (dr == 0 && dc == 0){
                    continue;
                }

                int newRow = row + dr;
                int newCol = col + dc;

                if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
                    if (!board[newRow][newCol].revealed && !board[newRow][newCol].flagged) {
                        int newCoords[2] = {newRow, newCol};
                        //Call recursively
                        on_cell_clicked(board[newRow][newCol].button, event, newCoords);
                    }
                }
            }
        }
    }
}

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| initialize_gui_board - Initializes the GUI representation of the game board by creating buttons for each cell and linking them to click events.
| 
| Arguments: grid = GTK widget grid where buttons will be placed.
| 
| Pointers / Side Effects: Dynamically allocates memory for cell coordinates. Associates buttons with their respective cells.
| Outputs: Buttons displayed on the GUI grid.
| Returns: None
| Functions Called: gtk_button_new, gtk_grid_attach, g_signal_connect
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

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
            g_signal_connect(board[i][j].button, "button-press-event", G_CALLBACK(on_cell_clicked), coords);
        }
    }
}

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| activate - Sets up the main game window and initializes the board and game logic.
| 
| Arguments: app = GTK application pointer
| 
| Pointers / Side Effects: Creates and displays the game window, initializes the board and minefield.
| Outputs: Initialized game GUI.
| Returns: None
| Functions Called: gtk_application_window_new, gtk_window_set_title, initialize_gui_board
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

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

/*
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
| launch_gui - Launches the GTK application and sets up the game window. Handles the main game loop and exit conditions.
| 
| Arguments: None
| 
| Pointers / Side Effects: Manages application lifecycle, allowing for replay or exit after a game ends.
| Outputs: Game window and replay/exit options.
| Returns: None
| Functions Called: activate, g_application_run, g_object_unref
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

void launch_gui() {
    // Opens the GUI window
    GtkApplication *app = gtk_application_new("com.example.minesweeper", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), 0, NULL);
    g_object_unref(app);

    int playAgain = end_menu(status);

    while (playAgain == 1) {
        launch_gui();
    }
    if (playAgain == 2) {
        outputMessage();
        exit(0);
    }
}