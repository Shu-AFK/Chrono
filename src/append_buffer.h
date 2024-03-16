#ifndef CHRONO_APPEND_BUFFER
#define CHRONO_APPEND_BUFFER

#include <string.h>
#include <stdlib.h>

#define ABUF_INIT {NULL, 0}

struct abuf {
    char *buf;
    int len;
};

void appendBuf(struct abuf *ab, const char *s, int len);
void freeBuf(struct abuf *ab);

#endif
