#ifndef CHRONO_CONFIG
#define CHRONO_CONFIG

#include <termios.h>

struct editorConfig {
    struct termios orig_termios; // Original terminal state

    int cx, cy; // Cursor position
    int screenrows;
    int screencols;
};

enum arrowKeys {
    ARROW_LEFT = 1000,
    ARROW_RIGHT = 1001,
    ARROW_UP = 1002,
    ARROW_DOWN = 1003
};

typedef struct {
    int input;
    void (*action)();
} Keybinding;



#endif // CHRONO_CONFIG
