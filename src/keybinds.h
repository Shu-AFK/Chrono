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

void openAction() {}

void cursorUpAction() {
    E.cy--;
}

void cursorDownAction() {
    E.cy++;
}

void cursorLeftAction() {
    E.cx--;
}

void cursorRightAction() {
    E.cx++;
}

void setMultibyteKeybinds(const int pos, const int buf, void (*action)()) {
    keybinds[pos].input = buf;
    keybinds[pos].action = action;
}

/* Set Keybinds */
void setDefaultKeybinds() {
    setMultibyteKeybinds(0, (int) CTRL_KEY('q'), quitAction);
    setMultibyteKeybinds(1, (int) CTRL_KEY('o'), openAction);
    setMultibyteKeybinds(2, ARROW_UP, cursorUpAction);
    setMultibyteKeybinds(3, ARROW_LEFT, cursorLeftAction);
    setMultibyteKeybinds(4, ARROW_DOWN, cursorDownAction);
    setMultibyteKeybinds(5, ARROW_RIGHT, cursorRightAction);
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
