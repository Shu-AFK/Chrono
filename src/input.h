#ifndef CHRONO_INPUT
#define CHRONO_INPUT

#include <stdio.h>

#include "keybinds.h"
#include "rope_wrapper.h"
#include "helper.h"

/* input */
void editorProcessKeypress(Rope rope) {
    int c = editorReadKey();

    if(c >= ' ' && c <= '~')
        Rope_push_back(rope, c);
    else
        executeAction(c);
}

int openFile(Rope *rope, char *filename) {
    FILE *input = fopen(filename, "r");
    if(input == NULL) return -1;

    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    size_t rope_len = 0;

    while((read = my_getline(&line, &len, input)) != -1) {
        rope_len = Rope_get_length(*rope);
        Rope_insert_str(*rope, rope_len, line);
    }

    free(line);
    fclose(input);
    return 0;
}

#endif // CHRONO_INPUT
