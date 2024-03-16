#ifndef CHRONO_HELPER
#define CHRONO_HELPER

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream) {
    if (lineptr == NULL || n == NULL || stream == NULL) {
        return -1;
    }

    if (*lineptr == NULL) {
        *n = 120;  // Initial size
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            return -1;
        }
    }

    size_t i = 0;
    int ch;
    bool done = false;
    while (!done) {
        ch = fgetc(stream);
        if (ch == EOF) {
            if (i == 0) {
                // No characters were read
                return -1;
            }
            done = true;
        } else {
            if (i + 1 >= *n) {
                // Buffer is too small, need to expand it
                size_t new_size = *n * 2;
                char *new_lineptr = (char *)realloc(*lineptr, new_size);
                if (new_lineptr == NULL) {
                    return -1;
                }
                *lineptr = new_lineptr;
                *n = new_size;
            }

            (*lineptr)[i++] = (char)ch;

            if (ch == '\n') {
                done = true;
            }
        }
    }

    // Null-terminate the string
    (*lineptr)[i] = '\0';
    return i;
}

#endif
