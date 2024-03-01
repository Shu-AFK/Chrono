#ifndef CHRONO_INPUT
#define CHRONO_INPUT

#include "keybinds.h"
#include "terminal.h"

/* input */
void editorProcessKeypress() {
    char c = editorReadKey();

    executeAction(c);
}

#endif // CHRONO_INPUT