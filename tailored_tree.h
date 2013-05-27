#ifndef _TAILORED_TREE_H_
#define _TAILORED_TREE_H_

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tailored_stack.h"

typedef struct node {
    Value value;
    struct node *pt_to_left_node;
    struct node *pt_to_right_node;
} Node;

/* Change if nodes store values of another type. */
static int compare_values(Value value_1, Value value_2) {
    return value_1 - value_2;
}

/* Change if nodes store values of another type. */
static void print_value(Value val) {
    printf("%c", val);
}

/* Returns the address of a newly created node that stores val. */
Node *create_node(const Value val);

/* Returns the height of the binary tree rooted at pt_to_node. */
int tree_height(const Node *const pt_to_node);

/* Returns the number of nodes of the binary tree rooted at pt_to_node. */
int tree_size(const Node *const pt_to_node);

/* Returns true or false, depending on whether or not the binary tree rooted at pt_to_node
 * is a binary search tree. */
bool is_bst(const Node *const pt_to_node);

/* Returns true or false, depending on whether or not the binary tree rooted at pt_to_node
 * has at least one node that stores val. */
bool occurs_in_tree(const Value val, const Node *const pt_to_node);

/* Returns true or false, depending on whether or not the binary search tree
 * rooted at pt_to_node has a (unique) node that stores val. */
bool occurs_in_bst(const Value val, const Node *const pt_to_node);

/* If val occurs in the binary search tree rooted at the value of pt_to_pt_to_node
 * then returns false; otherwise returns true, creates a new leaf into the tree where
 * val can be insered so that the resulting tree remains a binary search tree, and
 * updates the value of pt_to_pt_to_node to the address of the root of the resulting tree. */
bool insert_in_bst(const Value val, Node **const pt_to_pt_to_node);

/* If val does not occurs in the binary search tree rooted at the value of pt_to_pt_to_node
 * then returns false; otherwise returns true, deletes the node N that stores val, and
 * updates the value of pt_to_pt_to_node to the address of the root of the resulting tree;
 * in case N is the root of a nonempty left subtree and a nonempty right subtree, then let
 * the root of the left subtree take the place of N if choose_left is true, and let the root
 * of the right subtree take the place of N if choose_left is false. */
bool delete_in_bst(const Value val, Node **const pt_to_pt_to_node, const bool choose_left);

/* Represents the binary tree rooted at pt_to_node growing east, with an offset of 4 spaces
 * for each level. */
void print_binary_tree(const Node *const pt_to_node);

/* Performs a preorder traversal of the binary tree rooted at pt_to_node and prints out
 * the list of values stored in the nodes as they are visited. */
void preorder_traverse_tree_and_print(const Node *const pt_to_node);

/* Performs an inorder traversal of the binary tree rooted at pt_to_node and prints out
 * the list of values stored in the nodes as they are visited. */
void inorder_traverse_tree_and_print(const Node *const pt_to_node);

/* Performs a postorder traversal of the binary tree rooted at pt_to_node and prints out
 * the list of values stored in the nodes as they are visited. */
void postorder_traverse_tree_and_print(const Node *const pt_to_node);

/* Deletes all nodes of the binary tree rooted at the value of pt_to_pt_to_node,
 * and sets that value to NULL. */
void delete_tree(Node **const pt_to_pt_to_node);

#endif
