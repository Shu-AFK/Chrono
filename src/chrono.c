/* includes */
#include "keybinds.h"
#include "terminal.h"
#include "output.h"
#include "input.h"


/* init */
int main(void) {
    enableRawMode();
    setDefaultKeybinds();
    initEditor();

    while(1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }

    return 0;
}
