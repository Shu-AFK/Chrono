#ifndef CHRONO_ROPE
#define CHRONO_ROPE

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

// Length of string allowed to be stored in one leaf string
#define LEAF_LEN 2

typedef struct ropeNode {
    struct ropeNode *left;
    struct ropeNode *right;
    struct ropeNode *parent;
    char *str;
    size_t lCount;
} ropeNode;

typedef struct {
    ropeNode *root;
    size_t length;
} Rope;

/**
 * @brief Creates a rope node with the given parameters and recursively constructs the rope structure.
 *
 * This function constructs a rope structure from the given string and range of indices. It recursively
 * divides the string into smaller substrings until the leaf nodes contain strings of length <= LEAF_LEN.
 * Each node in the rope structure represents either a substring or an internal node.
 *
 * @param node Pointer to the pointer to the current node being constructed.
 * @param parent Pointer to the parent node of the current node being constructed.
 * @param str Pointer to the string from which the rope is constructed.
 * @param l Index of the left boundary of the substring represented by the current node.
 * @param r Index of the right boundary of the substring represented by the current node.
 * @return Returns 0 if the rope structure is successfully constructed, -1 if an error occurs (e.g., memory allocation failure).
 */
int createRope(ropeNode **node, ropeNode *parent, char *str, int l, int r) {
    ropeNode *tmp = malloc(sizeof(ropeNode));

    if(tmp == NULL) return -1;

    tmp->left = tmp->right = NULL;
    tmp->parent = parent;
    tmp->str = NULL;

    // Non leaf nodes
    if((r - l + 1) > LEAF_LEN) {
        tmp->lCount = (r - l + 1) / 2;
        *node = tmp;

        int middle = l + (r - l) / 2;
        if(createRope(&((*node)->left), *node, str, l, middle) == -1 || createRope(&((*node)->right), *node, str, middle + 1, r) == -1) {
            return -1;
        }
    } else { // Leaf nodes (containing a string)
        *node = tmp;
        tmp->lCount = r - l + 1;
        tmp->str = malloc(sizeof(char) * (r - l + 2));

        if(tmp->str == NULL) return -1;

        int j = 0;
        for(int i = l; i <= r; i++) {
            tmp->str[j++] = str[i];
        }

       tmp->str[j] = '\0';
    }

    return 0;
}

/**
 * @brief Constructs a rope data structure from a substring defined by indices l and r.
 *
 * @param node A double pointer to the current rope node being constructed or modified.
 * @param parent A pointer to the parent of the current node; NULL if it is the root.
 * @param str The original string from which the rope is constructed.
 * @param l The left index (inclusive) of the current segment of the string being processed.
 * @param r The right index (inclusive) of the current segment of the string being processed.
 * @return An integer value: 0 if the node was successfully created or -1 if an error occurred (such as a failure in memory allocation).
 */
int initRope(char *str, Rope *root) {
    size_t len = strlen(str);
    root->length = len;
    root->root = NULL;

    return createRope(&(root->root), NULL, str, 0, len - 1);
}

int concatenateRopes(Rope **root, Rope **rope1, Rope **rope2) {
    return 0;
}

#endif // CHRONO_ROPE
