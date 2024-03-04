#ifndef CHRONO_CONFIG
#define CHRONO_CONFIG

#include <termios.h>

struct editorConfig {
    struct termios orig_termios; // Original terminal state

    int cx, cy; // Cursor position
    int screenrows;
    int screencols;
};

enum editorKeys {
    ARROW_LEFT = 1000,
    ARROW_RIGHT = 1001,
    ARROW_UP = 1002,
    ARROW_DOWN = 1003,
    PAGE_UP,
    PAGE_DOWN,
    HOME_KEY,
    END_KEY,
    DEL_KEY
};

typedef struct {
    int input;
    void (*action)();
} Keybinding;



#endif // CHRONO_CONFIG
