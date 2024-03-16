#include "Unity/src/unity.h"
#include "../src/rope_wrapper.h"

void test_rope_functions() {
    Rope rope = Rope_create("abcdefg");
    TEST_ASSERT_NOT_NULL(rope);

    char *content = Rope_get_entire_content(rope);
    TEST_ASSERT_NOT_NULL(content);
    TEST_ASSERT_EQUAL_STRING(content, "abcdefg");

    free(content);
    Rope_push_back(rope, 'h');
    content = Rope_get_entire_content(rope);
    TEST_ASSERT_NOT_NULL(content);
    TEST_ASSERT_EQUAL_STRING(content, "abcdefgh");

    free(content);
    Rope_pop_back(rope);
    content = Rope_get_entire_content(rope);
    TEST_ASSERT_NOT_NULL(content);
    TEST_ASSERT_EQUAL_STRING(content, "abcdefg");

    free(content);
    Rope_insert(rope, 2, 'H');
    content = Rope_get_entire_content(rope);
    TEST_ASSERT_NOT_NULL(content);
    TEST_ASSERT_EQUAL_STRING(content, "abHcdefg");

    free(content);
    Rope_erase(rope, 1, 5);
    content = Rope_get_entire_content(rope);
    TEST_ASSERT_NOT_NULL(content);
    TEST_ASSERT_EQUAL_STRING(content, "afg");

    Rope_delete(rope);
}

void setUp(void) {
    // Prepare stuff before each test, if needed
}

void tearDown(void) {
    // Clean up stuff after each test, if needed
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_rope_functions);

    return UnityEnd();
}
