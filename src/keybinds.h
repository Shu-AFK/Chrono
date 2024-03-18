// TODO: Add a way to specify between ctrl and non ctrl keybinds in custom keybinds

/* Keybinds */
#ifndef CHRONO_KEYBINDS
#define CHRONO_KEYBINDS

#include <unistd.h>
#include <stdlib.h>

#include "config.h"
#include "terminal.h"

#define KEYBINDS_LENGTH 6 // Amount of possible keybinds
#define CTRL_KEY(c) ((c) & 0x1f)

Keybinding keybinds[KEYBINDS_LENGTH];

/* Actions */
void quitAction() {
    write(STDIN_FILENO, "\x1b[2J", 4); // Clears the screen
    write(STDIN_FILENO, "\x1b[H", 3); // Moves the cursor to the top right of the screen
    exit(0);
}

void cursorUpAction() {
    if(E.cy != 0) {
        E.cy--;
    } else {
        E.cy = 0;
    }
}

void cursorDownAction() {
    if(E.cy != E.screenrows - 1) {
        E.cy++;
    }
}

void cursorLeftAction() {
    if(E.cx != 0) {
        E.cx--;
    } else {
        E.cx = 0;
    }
}

void cursorRightAction() {
    if(E.cx != E.screencols - 1) {
        E.cx++;
    }
}

void pageUpAction() {
    E.cy = 0;
}

void pageDownAction() {
    E.cy = E.screenrows - 1;
}

void homeKeyAction() {
    E.cx = 0;
}

void endKeyAction() {
    E.cx = E.screencols - 1;
}

void delKeyAction() {}

void setKeybind(const int pos, const int buf, void (*action)()) {
    keybinds[pos].input = buf;
    keybinds[pos].action = action;
}

/* Set Keybinds */
void setDefaultKeybinds() {
    setKeybind(0, (int) CTRL_KEY('q'), quitAction);
    setKeybind(2, ARROW_UP, cursorUpAction);
    setKeybind(3, ARROW_LEFT, cursorLeftAction);
    setKeybind(4, ARROW_DOWN, cursorDownAction);
    setKeybind(5, ARROW_RIGHT, cursorRightAction);
    setKeybind(6, PAGE_UP, pageUpAction);
    setKeybind(7, PAGE_DOWN, pageDownAction);
    setKeybind(8, HOME_KEY, homeKeyAction);
    setKeybind(9, END_KEY, endKeyAction);
    setKeybind(10, DEL_KEY, delKeyAction);
}

// TODO: Load keybinds from settings.json


/* Execute */
void executeAction(int input) {
    for(int i = 0; i < KEYBINDS_LENGTH; i++) {
        if(keybinds[i].input == input) {
            keybinds[i].action();
            break;
        }
    }
}

#endif // CHRONO_KEYBINDS
