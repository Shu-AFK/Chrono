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

typedef struct {
    char input;
    void (*action)();
} Keybinding;

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

/* Set Keybinds */
void setDefaultKeybinds() {
    keybinds[0] = (Keybinding) { .input = CTRL_KEY('q'), .action = quitAction  };
    keybinds[1] = (Keybinding) { .input = CTRL_KEY('o'), .action = openAction  };
    keybinds[2] = (Keybinding) { .input = 'w', .action = cursorUpAction };
    keybinds[3] = (Keybinding) { .input = 'a', .action = cursorLeftAction };
    keybinds[4] = (Keybinding) { .input = 's', .action = cursorDownAction };
    keybinds[5] = (Keybinding) { .input = 'd', .action = cursorRightAction };
}

// TODO: Load keybinds from settings.json


/* Execute */
void executeAction(char input) {
    for(int i = 0; i < KEYBINDS_LENGTH; i++) {
        if(keybinds[i].input == input) {
            keybinds[i].action();
            break;
        }
    }
}

#endif // CHRONO_KEYBINDS
