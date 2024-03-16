#include "append_buffer.h"

void appendBuf(struct abuf *ab, const char *s, int len) {
    char *newbuf = (char *) realloc(ab->buf, ab->len + len);

    if(newbuf == NULL) return; // out of memory
    memcpy(&newbuf[ab->len], s, len);
    ab->buf = newbuf;
    ab->len += len;
}

void freeBuf(struct abuf *ab) {
    free(ab->buf);
}
