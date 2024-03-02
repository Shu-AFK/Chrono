#ifndef CHRONO_APPEND_BUFFER
#define CHRONO_APPEND_BUFFER

#include <string.h>
#include <stdlib.h>

#define ABUF_INIT {NULL, 0}

struct abuf {
    char *buf;
    int len;
};

void appendBuf(struct abuf *ab, const char *s, int len) {
    char *new = realloc(ab->buf, ab->len + len);

    if(new == NULL) return; // out of memory
    memcpy(&new[ab->len], s, len);
    ab->buf = new;
    ab->len += len;
}

void freeBuf(struct abuf *ab) {
    free(ab->buf);
}

#endif
