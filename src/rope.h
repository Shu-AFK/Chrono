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

// node = current node
// parent = parent(initially NULL)
// str = to store
// l = left index of current substring (initially 0)
// r = right index of curren substring (initially n - 1)
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
        if(createRope(&((*node)->left), node, str, l, middle) == -1 || createRope(&((*node)->right), node, str, middle + 1, r) == -1) {
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

int initRope(char *str, Rope *root) {
    size_t len = strlen(str);
    root->length = len;
    root->root = NULL;

    return createRope(&(root->root), NULL, str, 0, len - 1);
}

#endif // CHRONO_ROPE
