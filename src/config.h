#ifndef CHRONO_CONFIG
#define CHRONO_CONFIG

#include <termios.h>

struct editorConfig {
    struct termios orig_termios;

    int screenrows;
    int screencols;
};

#endif // CHRONO_CONFIG
