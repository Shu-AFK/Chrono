#include <ext/rope>
#include "rope_wrapper.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace __gnu_cxx;

Rope Rope_create(char *str) {
    return static_cast<Rope>(new rope<char>(str));
}

void Rope_delete(Rope rope) {
    delete static_cast<rope<char>*>(rope);
}

void Rope_push_back(Rope rope, char c) {
    static_cast<rope<char>*>(rope)->push_back(c);
}

void Rope_pop_back(Rope rope) {
    static_cast<rope<char>*>(rope)->pop_back();
}

void Rope_insert_rope(Rope rope, size_t pos, Rope insert) {
    static_cast<rope<char>*>(rope)->insert(pos, static_cast<rope<char>*>(insert));
}

void Rope_insert_str(Rope rope, size_t pos, char *str) {
    static_cast<rope<char>*>(rope)->insert(pos, str);
}

void Rope_erase(Rope rope, size_t begin, size_t length) {
    static_cast<rope<char>*>(rope)->erase(begin, length);
}

Rope Rope_substr(Rope rope, size_t begin, size_t length) {
    return static_cast<void *>(static_cast<rope<char>*>(rope)->substr(begin, length));
}

void Rope_concat(Rope rope1, Rope rope2) {
    static_cast<rope<char>*>(rope1) += static_cast<rope<char>*>(rope2);
}

void Rope_replace_rope(Rope rope, size_t beginning, size_t length, Rope toReplaceWith) {
    static_cast<rope<char>*>(rope)->replace(beginning, length, static_cast<rope<char>*>(toReplaceWith));
}

void Rope_replace_str(Rope rope, size_t beginning, size_t length, char *str) {
    static_cast<rope<char>*>(rope)->replace(beginning, length, str);
}

size_t Rope_get_length(Rope rope) {
    return static_cast<rope<char>*>(rope)->size();
}

size_t Rope_get_maxlen(Rope rope) {
    return static_cast<rope<char>*>(rope)->max_size();
}

#ifdef __cplusplus
}
#endif
