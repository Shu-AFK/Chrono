// TODO: Add a way to specify between ctrl and non ctrl keybinds in custom keybinds

/* Keybinds */
#ifndef CHRONO_KEYBINDS
#define CHRONO_KEYBINDS

#include <unistd.h>
#include <stdlib.h>

#include "config.h"

#define KEYBINDS_LENGTH 2 // Amount of possible keybinds
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


/* Set Keybinds */
void setDefaultKeybinds() {
    keybinds[0] = (Keybinding) { .input = CTRL_KEY('q'), .action = quitAction  };
    keybinds[1] = (Keybinding) { .input = CTRL_KEY('o'), .action = openAction  };
    // TODO: add remaining keybinds
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
