/* includes */
#include "keybinds.h"
#include "terminal.h"
#include "output.h"
#include "input.h"
#include "rope_wrapper.h"

/* init */
int main(int argc, char **argv) {
    if(argc > 2) return -1;

    Rope rope;

    if(argc == 2) {
        if(openFile(&rope, argv[1]) == -1) return -1;
    }

    write(STDIN_FILENO, "\x1b[2J", 4); // Clears the screen
    write(STDIN_FILENO, "\x1b[H", 3); // Moves the cursor to the top left of the screen

    enableRawMode();
    setDefaultKeybinds();
    initEditor();

    while(1) {
        editorRefreshScreen(argc - 1, rope);
        editorProcessKeypress(rope);
    }

    return 0;
}
