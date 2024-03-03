/* includes */
#include "keybinds.h"
#include "terminal.h"
#include "output.h"
#include "input.h"


/* init */
int main() {
    write(STDIN_FILENO, "\x1b[2J", 4); // Clears the screen
    write(STDIN_FILENO, "\x1b[H", 3); // Moves the cursor to the left right of the screen
    enableRawMode();
    setDefaultKeybinds();
    initEditor();

    while(1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
