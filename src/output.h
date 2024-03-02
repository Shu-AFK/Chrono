#ifndef CHRONO_OUTPUT
#define CHRONO_OUTPUT

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include "terminal.h"
#include "append_buffer.h"
#include "chrono.h"

#define LOGOLINES 7

char *logo =
"    ___       ___       ___       ___       ___       ___   \r\n"
"   /\\  \\     /\\__\\     /\\  \\     /\\  \\     /\\__\\     /\\  \\  \r\n"
"  /::\\  \\   /:/__/_   /::\\  \\   /::\\  \\   /:| _|_   /::\\  \\ \r\n"
" /:/\\:\\__\\ /::\\/\\__\\ /::\\:\\__\\ /:/\\:\\__\\ /::|/\\__\\ /:/\\:\\__\\\r\n"
" \\:\\ \\/__/ \\/\\::/  / \\;:::/  / \\:\\/:/  / \\/|::/  / \\:\\/:/  /\r\n"
"  \\:\\__\\     /:/  /   |:\\/__/   \\::/  /    |:/  /   \\::/  / \r\n"
"   \\/__/     \\/__/     \\|__|     \\/__/     \\/__/     \\/__/";

char *strdup(const char *s) {
    char *d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

/* output  */
void editorDrawRows(struct abuf *ab) {
    int y;
    for(y = 0; y < E.screenrows; y++) {
        appendBuf(ab, "~", 1);

        appendBuf(ab, "\x1b[K", 3);
        if(y < E.screenrows - 1) {
            appendBuf(ab, "\r\b", 2);
        }
    }
}

int getLogoMaxWidth() {
    int maxWidth = 0;
    int y = 0;
    for(int i = 0, size = strlen(logo); i < size; i++) {
        if(logo[i] == '\r') {
            if(maxWidth < y) maxWidth = y;
            y = 0;
        } else {
            y++;
        }
    }

    if(maxWidth < y) maxWidth = y;
    return maxWidth;
}

void drawWelcome(struct abuf *ab) {
    int logoWidth = getLogoMaxWidth();
    int padding = (E.screencols - logoWidth) / 2;
    if (padding < 0) padding = 0;

    int verticalPadding = (2 * E.screenrows) / 5;

    // Assuming vertical centering in the upper half of the screen, adjust verticalPadding if needed
    for (int i = 0; i < verticalPadding - LOGOLINES / 2; i++) {
        appendBuf(ab, "\x1b[K", 3);
        appendBuf(ab, "\r\n", 2); // Adding vertical padding at the top
    }

    char *logoCopy = strdup(logo);
    if (logoCopy == NULL) {
        die("Allocation failed for logoCopy");
    }

    char *line = strtok(logoCopy, "\r\n");
    while (line != NULL) {
        for (int i = 0; i < padding; ++i) {
            appendBuf(ab, " ", 1); // Apply padding directly without using a buffer
        }

        appendBuf(ab, line, strlen(line));
        appendBuf(ab, "\r\n", 2); // Add newline after the logo line

        line = strtok(NULL, "\r\n");
    }

    free(line);
    free(logoCopy);
}

void editorRefreshScreen() {
    struct abuf ab = ABUF_INIT;

    appendBuf(&ab, "\x1b[?25l", 6); // Hides the cursor
    appendBuf(&ab, "\x1b[H", 3); // Moves the cursor to the top left position

    drawWelcome(&ab);

    appendBuf(&ab, "\x1b[H", 3);
    appendBuf(&ab, "\x1b[?25h", 6); // Displays the cursor again

    write(STDIN_FILENO, ab.buf, ab.len);
    freeBuf(&ab);
}

#endif // CHRONO_OUTPUT
