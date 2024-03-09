#ifndef CHRONO_TEST_ROPE
#define CHRONO_TEST_ROPE

#include "Unity/src/unity.h"
#include "../src/rope.h"

void test_initRope_EmptyString() {
    Rope myRope;
    char str[] = "";
    int result = initRope(str, &myRope);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(myRope.root);
    TEST_ASSERT_EQUAL_INT(0, myRope.length);
    TEST_ASSERT_EQUAL_INT(0, myRope.root->lCount);
    TEST_ASSERT_NULL(myRope.root->left);
    TEST_ASSERT_NULL(myRope.root->right);
}

void test_initRope_NonEmptyString() {
    Rope myRope;
    char str[] = "abcd";
    int result = initRope(str, &myRope);

    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(myRope.root);
    TEST_ASSERT_EQUAL_INT(strlen(str), myRope.length);

    if (LEAF_LEN == 2 && strlen(str) > LEAF_LEN) {
        TEST_ASSERT_NOT_NULL(myRope.root->left);
        TEST_ASSERT_NOT_NULL(myRope.root->right);
        TEST_ASSERT_EQUAL_INT(2, myRope.root->lCount);

        // Checking that left and right child nodes are leaf nodes with appropriate strings
        TEST_ASSERT_NOT_NULL(myRope.root->left->str);
        TEST_ASSERT_NOT_NULL(myRope.root->right->str);
        TEST_ASSERT_EQUAL_STRING_LEN("ab", myRope.root->left->str, 2);
        TEST_ASSERT_EQUAL_STRING_LEN("cd", myRope.root->right->str, 2);
    }
}

#endif // CHRONO_TEST_ROPE