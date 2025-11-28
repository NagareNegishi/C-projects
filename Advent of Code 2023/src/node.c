#include <stdio.h>
#include <string.h>
#include "node.h"


/**
 * Generates a unique hash code for a given 3-letter name.
 * @param name A string representing the name (must be exactly 3 letters).
 * @return An integer hash code if the name is valid; otherwise, -1.
 */
int hash_code(const char* name){
    if (strlen(name) != 3){
        return -1;
    }
    int code = (name[0] - 'A') * 676 + (name[1] - 'A') * 26 + (name[2] - 'A');
    if (code < 0 || 17575 < code){
        return -1;
    }
    return code;
}


/**
 * Creates a Node from a given name.
 * @param name A string representing the node
 * @return A Node structure populated with the parsed data.
 */
Node create_node(const char* name){
    Node node = {0};
    node.code = hash_code(name);
    if (node.code == -1){
        return node;
    }
    strncpy(node.name, name, 4);
    node.is_valid = true;
    return node;
}


/**
 * Checks if the node's name ends with the specified character.
 * @param node Pointer to the Node structure.
 * @param c The character to check against the end of the node's name.
 * @return true if the node's name ends with the character c, false otherwise.
 */
bool is_end_with(Node* node, const char c){
    if (node == NULL || !node->is_valid) {
        return false;
    }
    return node->name[2] == c;
}
