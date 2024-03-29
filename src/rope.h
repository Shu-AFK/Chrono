// TODO: Fix split function
// TODO: Implement a insert function
// TODO: Implement a delete function
// TODO: Implement a search function
// TODO: Implement a way to balance the rope
// TODO: Implement a way to simply iterate over a rope
// maybe in the futer, add some sort of modification tracking to allow undo / redo operations

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
    int refCount;
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
int createRope(ropeNode **node, ropeNode *parent, char *str, size_t l, size_t r) {
    if(l > r) return -1;
    ropeNode *tmp = malloc(sizeof(ropeNode));

    if(tmp == NULL) return -1;

    tmp->left = tmp->right = NULL;
    tmp->parent = parent;
    tmp->str = NULL;
    tmp->refCount = 1;

    // Non leaf nodes
    if((r - l + 1) > LEAF_LEN) {
        // Making sure it works when getting passed an empty string
        size_t lcount = 0;
        if(r - l != 0)
            lcount = (r - l + 1) / 2;

        tmp->lCount = lcount;
        *node = tmp;

        size_t middle = l + (r - l) / 2;
        if(createRope(&((*node)->left), *node, str, l, middle) == -1 || createRope(&((*node)->right), *node, str, middle + 1, r) == -1) {
            return -1;
        }
    } else { // Leaf nodes (containing a string)
        *node = tmp;
        tmp->lCount = strlen(str);
        tmp->str = malloc(sizeof(char) * (r - l + 2));

        if(tmp->str == NULL) return -1;

        size_t j = 0;
        for(size_t i = l; i <= r; i++) {
            tmp->str[j++] = str[i];
        }

       tmp->str[j] = '\0';
    }

    return 0;
}

/**
 * @brief creates a new rope node
 *
 * @param str the string getting saved
 * @param parent the parent of the node
 * @return the pointer to the newly created node
 */
ropeNode *createNode(char *str, ropeNode *parent) {
    ropeNode *tmp = malloc(sizeof(ropeNode));
    tmp->str = str;
    tmp->parent = parent;
    tmp->left = tmp->right = NULL;
    tmp->lCount = 0;
    tmp->refCount = 1;

    return tmp;
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
int initRope(char *str, Rope **root) {
    *root = malloc(sizeof(Rope));
    if (*root == NULL) {
        return -1; // Memory allocation failure
    }

    size_t len = strlen(str);
    (*root)->length = len;
    (*root)->root = NULL;

    if(len == 0)
        return createRope(&((*root)->root), NULL, str, 0, len);

    return createRope(&((*root)->root), NULL, str, 0, len - 1);
}

/**
 * @brief Frees all memory associated with a rope.
 *
 * @param root The root node of the rope to be freed. If root is NULL, the function does nothing.
 */
void freeRopeNode(ropeNode *root) {
    if (root == NULL) return;

    root->refCount--;

    if(root->refCount > 0) return;

    freeRopeNode(root->left);
    freeRopeNode(root->right);

    if (root->str != NULL) {
        free(root->str);
    }

    free(root);
}

/**
 * @brief Frees a Rope pointer and assigsnt it to NULL
 *
 * @note Ensure that you free a concatenated rope before freeing the individual ropes
 */
void freeRope(Rope **root) {
    if(root == NULL) return;

    freeRopeNode((*root)->root);
    free(*root);
    *root = NULL;
}

/*
 * @brief gets the substring store inside a ropeNode
 *
 * @param node the node of the string you want to get the substring of
 * @param buffer the char * buffer where the substring will be stored
 * @param index (initially 0)
 */
void getSubstring(ropeNode *node, char *buffer, int *index) {
    if(node == NULL) return;

    getSubstring(node->left, buffer, index);

    size_t length = 0;
    if(node->str != NULL)
        length = strlen(node->str);

    memcpy(buffer + *index, node->str, length);
    *index += length;

    getSubstring(node->right, buffer, index);
}

/*
 * @brief Gets the string inside a rope
 *
 * @param root a pointer to the rope of the string you want to get the string of.
 * @return the char * of the string inside a rope
 */
char *getWholeString(Rope *root) {
    char *str = malloc(root->length + 1);
    if(str == NULL) return NULL;

    int index = 0;
    getSubstring(root->root, str, &index);
    str[root->length] = '\0';
    return str;
}

/**
 * @brief concatenates two ropes
 *
 * @param root The pointer to the new rope, it has to be uninitialised
 * @param rope1 The left side of the new rope
 * @param rope2 The right side of the new rope
 * @return 0 for success, -1 for failure
 */
int concatenateRopes(Rope **root, Rope *rope1, Rope *rope2) {
    *root = malloc(sizeof(Rope));
    if(*root == NULL) return -1;

    (*root)->root = malloc(sizeof(ropeNode));
    if((*root)->root == NULL) return -1;
    (*root)->root->str = NULL;

    (*root)->length = rope1->length + rope2->length;
    (*root)->root->left = rope1->root;
    (*root)->root->right = rope2->root;

    rope1->root->parent = (*root)->root;
    rope2->root->parent = (*root)->root;

    rope1->root->refCount++;
    rope2->root->refCount++;

    (*root)->root->lCount = rope1->length;
    return 0;
}

/**
 * @brief gets the node at a position
 *
 * @param source the root of the node
 * @param the position you want to index into
 * @return a pointer to the ropeNode at the index
 */
ropeNode *getLeafbyCharpos(ropeNode *source, size_t position) {
    if(source == NULL) return NULL;
    if(source->str != NULL) return source;

    if(position < source->lCount) {
        return getLeafbyCharpos(source->left, position);
    } else {
        position -= source->lCount;
        return getLeafbyCharpos(source->right, position);
    }
}

/**
 * @brief this function returns a pointer to a node based on position for splitting a rope
 *
 * @param source the rope you want to index
 * @param position the position of the node you want to get
 * @param offset(initially 0) will contain the position of the character for splitting of the node returned is a leaf node
 * @return the pointer to the node
 */
ropeNode *getNodeByPos(ropeNode *source, size_t position, size_t *offset) {
    if(source == NULL || position == 0) {
        *offset = 0;
        return NULL;
    }

    // Non leaf node
    if(source->left != NULL) {
        if(position <= source->left->lCount) {
            return getNodeByPos(source->left, position, offset);
        } else {
            ropeNode *result = getNodeByPos(source->right, position - source->left->lCount, offset);
            if(result == NULL) {
                *offset = position - source->left->lCount;
                return source;
            }
            return result;
        }
    // Leaf node
    } else if(source->right == NULL) {
        *offset = position;
        return source;
    }

    return NULL;
}

/**
 * @brief spilts one rope into two
 *
 * @param source the source rope you want to split from
 * @param position the position of the node you want to split from
 * @param rope1 the left half of the split (uninitialised)
 * @param rope2 the right half of the split (uninitialised)
 * @return 0 for success, -1 for failure
 */
int splitRope(Rope *source, size_t position, Rope **rope1, Rope **rope2) {
    if(source == NULL || position > source->length) return -1;

    size_t offset = 0;
    ropeNode *index = getNodeByPos(source->root, position, &offset);
    if(index == NULL && offset == 0) return -1;

    *rope1 = malloc(sizeof(Rope));
    *rope2 = malloc(sizeof(Rope));
    if(*rope1 == NULL || *rope2 == NULL) return -1;

    // Non leaf node
    if(offset == 0) {
        (*rope1)->root = index->left;
        (*rope1)->root->refCount++;
        (*rope1)->length = index->left->lCount * 2;

        (*rope2)->root = index->right;
        (*rope2)->root->refCount++;
        (*rope2)->length = index->right->lCount * 2;
        return 0;
    } else { // Leaf node
        // TODO: Need to implement
    }
}

#endif // CHRONO_ROPE
