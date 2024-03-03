#ifndef CHRONO_TERMINAL
#define CHRONO_TERMINAL

#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdio.h>

#include "keybinds.h"
#include "config.h"

struct editorConfig E;

/* terminal */
void die(const char *s) {
    write(STDIN_FILENO, "\x1b[2J", 4); // Clears the screen
    write(STDIN_FILENO, "\x1b[H", 3); // Moves the cursor to the top right of the screen

    perror(s);
    exit(1);
}

void disableRawMode() {
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &E.orig_termios) == -1) die("tcsetattr");
}

void enableRawMode() {
    if(tcgetattr(STDIN_FILENO, &E.orig_termios) == -1) die("tcgetattr");
    atexit(disableRawMode);

    struct termios raw = E.orig_termios;
    raw.c_iflag &= ~(ICRNL | IXON | ISTRIP | INPCK | BRKINT);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= (CS8);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) die("tcgetattr");
}

int editorReadKey() {
    int nread;
    char c;
    while((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if(nread == -1 && errno != EAGAIN) die("read");
    }

    if(c == '\x1b') {
        char seq[3];

        if(read(STDIN_FILENO, &seq[0], 1) != 1) return '\x1b';
        if(read(STDIN_FILENO, &seq[1], 1) != 1) return '\x1b';

        // Arrow key sequence
        if(seq[0] == '[') {
            switch(seq[1]) {
                case 'A' : return ARROW_UP;
                case 'B' : return ARROW_DOWN;
                case 'C' : return ARROW_RIGHT;
                case 'D' : return ARROW_LEFT;
            }
        }

        return '\x1b';
    } else {
        return (int) c;
    }

}

int getCursorPosition(int *rows, int *cols) {
    char buf[32];
    unsigned int i = 0;

    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4) return -1;

    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1) break;
        if (buf[i] == 'R') break;
        i++;

    }
    buf[i] = '\0';

    // Parse it
    if (buf[0] != '\x1b' || buf[1] != '[') return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2) return -1;

    return 0;
}

int getWindowSize(int *rows, int *cols) {
    struct winsize ws;

    if(ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if(write(STDIN_FILENO, "\x1b[999C\x1b[999B", 12) != 12) return -1; // Fall back option (moving the cursor to the bottom right of the screen)
        return getCursorPosition(rows, cols);
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

void initEditor() {
    E.cx = 0;
    E.cy = 0;

    if(getWindowSize(&E.screenrows, &E.screencols) == -1) die("getWindowSize");
    write(STDOUT_FILENO, "\x1b[H", 3); // Moves the cursor to the top right of the screen
}

#endif // CHRONO_TERMINAL
