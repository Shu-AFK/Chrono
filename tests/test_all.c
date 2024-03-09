#include "Unity/src/unity.h"

#include "test_rope.h"

void setUp(void) {
    // Prepare stuff before each test, if needed
}

void tearDown(void) {
    // Clean up stuff after each test, if needed
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_initRope_EmptyString);
    RUN_TEST(test_initRope_NonEmptyString);

    return UnityEnd();
}