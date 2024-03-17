#include <ext/rope>
#include "rope_wrapper.h"
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

Rope Rope_create(char *str) {
    __gnu_cxx::rope<char>* rope_ptr = new __gnu_cxx::rope<char>(str);

    return static_cast<Rope>(rope_ptr);
}

void Rope_delete(Rope rope) {
    delete static_cast<__gnu_cxx::rope<char>*>(rope);
}

void Rope_push_back(Rope rope, char c) {
    static_cast<__gnu_cxx::rope<char>*>(rope)->push_back(c);
}

void Rope_pop_back(Rope rope) {
    static_cast<__gnu_cxx::rope<char>*>(rope)->pop_back();
}

void Rope_insert(Rope rope, size_t pos, char c) {
    static_cast<__gnu_cxx::rope<char>*>(rope)->insert(pos, c);
}

void Rope_insert_str(Rope rope, size_t pos, char *str) {
    static_cast<__gnu_cxx::rope<char>*>(rope)->insert(pos, str);
}

void Rope_erase(Rope rope, size_t begin, size_t length) {
    static_cast<__gnu_cxx::rope<char>*>(rope)->erase(begin, length);
}

Rope Rope_substr(Rope rope, size_t begin, size_t length) {
    __gnu_cxx::rope<char>* r = static_cast<__gnu_cxx::rope<char>*>(rope);
    auto* substr_rope = new __gnu_cxx::rope<char>(r->substr(begin, length));
    return static_cast<void *>(substr_rope);
}

void Rope_concat(Rope rope1, Rope rope2) {
    (*static_cast<__gnu_cxx::rope<char>*>(rope1)) += (*static_cast<__gnu_cxx::rope<char>*>(rope2));
}

void Rope_replace_str(Rope rope, size_t beginning, size_t length, char *str) {
    static_cast<__gnu_cxx::rope<char>*>(rope)->replace(beginning, length, str);
}

size_t Rope_get_length(Rope rope) {
    if (!rope)
        return 0;

    return static_cast<__gnu_cxx::rope<char>*>(rope)->size();
}

size_t Rope_get_maxlen(Rope rope) {
    if (!rope)
        return 0;

    return static_cast<__gnu_cxx::rope<char>*>(rope)->max_size();
}

void Rope_get_line_lengths(Rope rope, size_t *lengths[], size_t y1, size_t y2) {
    __gnu_cxx::rope<char>* r = static_cast<__gnu_cxx::rope<char>*>(rope);
    __gnu_cxx::rope<char>::iterator it;
    __gnu_cxx::rope<char>::iterator end = (*r).mutable_end();

    int num_lines = y2 - y1 + 1;
    *lengths = new size_t[num_lines];

    size_t lines = 0;
    size_t length = 0;
    size_t i = 0;

    for(it = (*r).mutable_begin(); it != end; it++) {
        if(lines > y2)
            break;

        if(lines < y1 && (*it) != '\r')
            continue;

        if((*it) == '\r') {
            lines++;
            (*lengths)[i] = length;
            length = 0;
            i++;
            continue;
        }

        length++;
    }
}

int Rope_to_buffer(Rope rope, struct abuf *ab, size_t x1, size_t x2, size_t y1, size_t y2) {
    if (x2 < x1 || y2 < y1) return -1;

    __gnu_cxx::rope<char>* r = static_cast<__gnu_cxx::rope<char>*>(rope);
    __gnu_cxx::rope<char>::iterator it = r->mutable_begin();
    __gnu_cxx::rope<char>::iterator end = r->mutable_end();

    int currentLine = 0, currentColumn = 0;
    size_t *line_lengths = nullptr;
    size_t i = 0;

    int prev_x = -1;

    Rope_get_line_lengths(rope, &line_lengths, y1, y2);

    for (; it != end; ++it) {
        if (currentLine > y2) break;  // Past the end line
        prev_x++;
        if (*it == '\n') {
            if (currentLine >= y1 && currentLine <= y2) {
                appendBuf(ab, "\r\n", 2);  // Append newline for lines within the range
            }
            currentLine++;
            currentColumn = 0;
            i++;
            prev_x = -1;
            continue;
        }

        if (currentLine >= y1 && currentLine <= y2 && currentColumn >= x1 && currentColumn <= x2 - line_lengths[i] && prev_x !=  - line_lengths[i]) {
            char c = *it;
            appendBuf(ab, &c, 1);  // Append character if within specified rectangle
        }
        currentColumn++;
    }

    delete line_lengths;
    return 0;
}

size_t Rope_get_lines(Rope rope) {
    __gnu_cxx::rope<char>* r = static_cast<__gnu_cxx::rope<char>*>(rope);
    __gnu_cxx::rope<char>::iterator it;
    __gnu_cxx::rope<char>::iterator end = (*r).mutable_end();

    size_t lines = 0;

    for(it = (*r).mutable_begin(); it != end; it++) {
        if((*it) == '\n') {
            lines++;
        }
    }

    return lines;
}

size_t Rope_get_lines_lengths(Rope rope, size_t *lengths[]) {
    __gnu_cxx::rope<char>* r = static_cast<__gnu_cxx::rope<char>*>(rope);
    __gnu_cxx::rope<char>::iterator it;
    __gnu_cxx::rope<char>::iterator end = (*r).mutable_end();

    size_t lines = 0;
    size_t length = 0;

    for(it = (*r).mutable_begin(); it != end; it++) {
        if((*it) == '\n') {
            lines++;
            (*lengths)[lines] = length;
            length = 0;
            continue;
        }

        length++;
    }

    return lines;
}

char *Rope_get_entire_content(Rope rope) {
    __gnu_cxx::rope<char>* r = static_cast<__gnu_cxx::rope<char>*>(rope);
    __gnu_cxx::rope<char>::iterator it;
    __gnu_cxx::rope<char>::iterator end = (*r).mutable_end();

    size_t length = r->size();
    char *content = (char *) malloc(length * sizeof(char) + 1);

    size_t i = 0;

    for(it = (*r).mutable_begin(); it != end; it++) {
        content[i] = (*it);
        i++;
    }
    content[i] = '\0';

    return content;
}

#ifdef __cplusplus
}
#endif
