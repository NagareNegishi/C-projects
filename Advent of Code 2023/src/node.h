#ifndef NODE_H
#define NODE_H
#include <stdbool.h>

// if code is unique combination of 3 letters, then max nodes = 26^3 = 17576
// which can be represented as int
typedef struct Node{
    int code;
    char name[4];
    struct Node *left;
    struct Node *right;
    bool is_valid;
} Node;

/**
 * Generates a unique hash code for a given 3-letter name.
 * @param name A string representing the name (must be exactly 3 letters).
 * @return An integer hash code if the name is valid; otherwise, -1.
 */
int hash_code(const char* name);

/**
 * Creates a Node from a given name.
 * @param name A string representing the node
 * @return A Node structure populated with the parsed data.
 */
Node create_node(const char* name);


#endif // NODE_H