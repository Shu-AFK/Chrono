// TODO: Implement Rope_get_screenbuffer function
// TODO: Handle exceptions inside each function

#ifndef CHRONO_ROPE_WRAPPER
#define CHRONO_ROPE_WRAPPER

#ifdef __cplusplus
extern "C" {
#endif

typedef void* Rope;

Rope Rope_create(char *str);
void Rope_delete(Rope rope);
void Rope_push_back(Rope rope, char c);
void Rope_pop_back(Rope rope);
void Rope_insert_rope(Rope rope, size_t pos, Rope insert);
void Rope_insert_str(Rope rope, size_t pos, char *str);
void Rope_erase(Rope rope, size_t begin, size_t length);
Rope Rope_substr(Rope rope, size_t begin, size_t length);
void Rope_concat(Rope rope1, Rope rope2);
void Rope_replace_rope(Rope rope, size_t beginning, size_t length, Rope toReplaceWith);
void Rope_replace_str(Rope rope, size_t beginning, size_t length, char *str);
size_t Rope_get_length(Rope rope);
size_t Rope_get_maxlen(Rope rope);

#ifdef __cplusplus
}
#endif

#endif // CHRONO_ROPE_WRAPPER
