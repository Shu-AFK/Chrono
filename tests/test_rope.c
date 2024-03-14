#include "Unity/src/unity.h"
#include "../src/rope.h"
#include "stdlib.h"

void test_initRope_EmptyString() {
    Rope *myRope = NULL;
    char str[] = "";
    int result = initRope(str, &myRope);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(myRope->root);
    TEST_ASSERT_EQUAL_INT(0, myRope->length);
    TEST_ASSERT_EQUAL_INT(0, myRope->root->lCount);
    TEST_ASSERT_NULL(myRope->root->left);
    TEST_ASSERT_NULL(myRope->root->right);

    freeRope(&myRope);
    TEST_ASSERT_NULL(myRope);
}

void test_initRope_NonEmptyString() {
    Rope *myRope = NULL;
    char str[] = "abcd";
    int result = initRope(str, &myRope);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(myRope->root);
    TEST_ASSERT_EQUAL_INT(strlen(str), myRope->length);

    if (LEAF_LEN == 2 && strlen(str) > LEAF_LEN) {
        TEST_ASSERT_NOT_NULL(myRope->root->left);
        TEST_ASSERT_NOT_NULL(myRope->root->right);
        TEST_ASSERT_EQUAL_INT(2, myRope->root->lCount);

        // Checking that left and right child nodes are leaf nodes with appropriate strings
        TEST_ASSERT_NOT_NULL(myRope->root->left->str);
        TEST_ASSERT_NOT_NULL(myRope->root->right->str);
        TEST_ASSERT_EQUAL_STRING_LEN("ab", myRope->root->left->str, 2);
        TEST_ASSERT_EQUAL_STRING_LEN("cd", myRope->root->right->str, 2);
    }

    freeRope(&myRope);
    TEST_ASSERT_NULL(myRope);
}

void test_getString_NonEmptyString() {
    Rope *myRope = NULL;
    char *str = "abcdefg";
    int result = initRope(str, &myRope);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(myRope->root);
    TEST_ASSERT_EQUAL_INT(strlen(str), myRope->length);

    char *stored = getWholeString(myRope);

    TEST_ASSERT_NOT_NULL(stored);
    TEST_ASSERT_EQUAL_STRING(str, stored);

    free(stored);

    freeRope(&myRope);
    TEST_ASSERT_NULL(myRope);
}

void test_concatenation() {
    Rope *rope1 = NULL;
    Rope *rope2 = NULL;
    int result = initRope("abc", &rope1);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(rope1->root);
    TEST_ASSERT_EQUAL_INT(3, rope1->length);

    result = initRope("def", &rope2);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(rope2->root);
    TEST_ASSERT_EQUAL_INT(3, rope2->length);

    Rope *concatenated = NULL;
    result = concatenateRopes(&concatenated, rope1, rope2);

    TEST_ASSERT_EQUAL_INT(result, 0);
    TEST_ASSERT_NOT_NULL(concatenated->root);
    TEST_ASSERT_EQUAL_INT(6, concatenated->length);

    char *stored = getWholeString(concatenated);

    TEST_ASSERT_NOT_NULL(stored);
    TEST_ASSERT_EQUAL_STRING(stored, "abcdef");

    freeRope(&concatenated);
    TEST_ASSERT_NULL(concatenated);
    freeRope(&rope1);
    TEST_ASSERT_NULL(rope1);
    freeRope(&rope2);
    TEST_ASSERT_NULL(rope2);
}

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
    RUN_TEST(test_getString_NonEmptyString);
    RUN_TEST(test_concatenation);

    return UnityEnd();
}
