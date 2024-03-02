#ifndef CHRONO_OUTPUT
#define CHRONO_OUTPUT

#include <unistd.h>

#include "terminal.h"

/* output  */
void editorDrawRows() {
    int y;
    for(y = 0; y < E.screenrows; y++) {
        write(STDIN_FILENO, "~\r\n", 3); // Writes tildes at the start of every line
        printf("%i : %i\r\n", E.screenrows, E.screencols);
    }
}

void editorRefreshScreen() {
    write(STDIN_FILENO, "\x1b[2J", 4); // Clears the screen
    write(STDIN_FILENO, "\x1b[H", 3); // Moves the cursor to the top right of the screen

    editorDrawRows();
    write(STDIN_FILENO, "\x1b[H", 3);
}

#endif // CHRONO_OUTPUT
