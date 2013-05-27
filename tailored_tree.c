/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: Defines tree processing functions for binary trees and         *
 *              binary search trees whose nodes store values of type Value,    *
 *              by default defined as int in tailored_tree.h, but that can     *
 *              be changed to another type to accomodate other needs; the      *
 *              functions compare_values() and print_value(), also defined     *
 *              in tailored_list.h, should then be changed accordingly.        *
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "tailored_tree.h"

static int subtree_height(const Node *const);
static Node *lift_left(Node *);
static Node *lift_right(Node *);
static void print_subtree(const Node *const, const int, const int);
static void print_preorder_subtree(const Node *const);
static void print_inorder_subtree(const Node *const);
static void print_postorder_subtree(const Node *const);
static void delete_subtree(Node *);

Node *create_node(const Value value) {
    Node *const pt_to_node = malloc(sizeof(Node));
    assert(pt_to_node);
    pt_to_node->value = value;
    pt_to_node->pt_to_left_node = NULL;
    pt_to_node->pt_to_right_node = NULL;
    return pt_to_node;
}

/* Both the empty tree and a tree consisting of a single node have a height of 0. */
int tree_height(const Node *const pt_to_node) {
    if (!pt_to_node)
        return 0;
    return fmax(subtree_height(pt_to_node->pt_to_left_node),
                subtree_height(pt_to_node->pt_to_right_node));
}

int tree_size(const Node *const pt_to_node) {
    if (!pt_to_node)
        return 0;
    return 1 + tree_size(pt_to_node->pt_to_left_node) +
        tree_size(pt_to_node->pt_to_right_node);
}

bool occurs_in_tree(const Value val, const Node *const pt_to_node) {
    if (!pt_to_node)
        return false;
    if (compare_values(val, pt_to_node->value) == 0)
        return true;
    return occurs_in_tree(val, pt_to_node->pt_to_left_node) ||
        occurs_in_tree(val, pt_to_node->pt_to_right_node);
}

bool occurs_in_bst(const Value val, const Node *const pt_to_node) {
    if (!pt_to_node)
        return false;
    if (compare_values(val, pt_to_node->value) == 0)
        return true;
    if (compare_values(val, pt_to_node->value) < 0)
        return occurs_in_tree(val, pt_to_node->pt_to_left_node);
    return occurs_in_tree(val, pt_to_node->pt_to_right_node);
}

bool is_bst(const Node *const pt_to_node) {
    if (!pt_to_node)
        return true;
    if (pt_to_node->pt_to_left_node &&
        compare_values(pt_to_node->pt_to_left_node->value, pt_to_node->value) >= 0)
        return false;
    if (pt_to_node->pt_to_right_node &&
        compare_values(pt_to_node->value, pt_to_node->pt_to_right_node->value) >= 0)
        return false;
    return is_bst(pt_to_node->pt_to_left_node) && is_bst(pt_to_node->pt_to_right_node);
}

bool insert_in_bst(const Value value, Node **const pt_to_pt_to_node) {
    if (!*pt_to_pt_to_node) {
        *pt_to_pt_to_node = create_node(value);
        return true;
    }
    Node *pt_to_node = *pt_to_pt_to_node;
    if (compare_values(pt_to_node->value, value) == 0)
        return false;
    if (compare_values(value, pt_to_node->value) < 0) {
        if (!pt_to_node->pt_to_left_node) {
            pt_to_node->pt_to_left_node = create_node(value);
            return true;
        }
        return insert_in_bst(value, &pt_to_node->pt_to_left_node);
    }
    if (!pt_to_node->pt_to_right_node) {
        pt_to_node->pt_to_right_node = create_node(value);
        return true;
    }
    return insert_in_bst(value, &pt_to_node->pt_to_right_node);
}

bool delete_in_bst(const Value value, Node **const pt_to_pt_to_node, const bool choose_left) {
    if (!*pt_to_pt_to_node)
        return false;
     Node *pt_to_node = *pt_to_pt_to_node;
     if (compare_values(value, pt_to_node->value) == 0)
         if (choose_left)
             *pt_to_pt_to_node = lift_left(pt_to_node);
         else
             *pt_to_pt_to_node = lift_right(pt_to_node);
     if (compare_values(value, pt_to_node->value) < 0) {
         if (!pt_to_node->pt_to_left_node)
             return false;
         if (compare_values(value, pt_to_node->pt_to_left_node->value))
             return delete_in_bst(value, &pt_to_node->pt_to_left_node, choose_left);
         if (choose_left)
             (*pt_to_pt_to_node)->pt_to_left_node = lift_left(pt_to_node->pt_to_left_node);
         else
             (*pt_to_pt_to_node)->pt_to_left_node = lift_right(pt_to_node->pt_to_left_node);
         return true;
     }
     if (!pt_to_node->pt_to_right_node)
         return false;
     if (compare_values(value, pt_to_node->pt_to_right_node->value))
         return delete_in_bst(value, &pt_to_node->pt_to_right_node, choose_left);
     if (choose_left)
         (*pt_to_pt_to_node)->pt_to_right_node = lift_left(pt_to_node->pt_to_right_node);
     else
         (*pt_to_pt_to_node)->pt_to_right_node = lift_right(pt_to_node->pt_to_right_node);         
     return true;
}

void print_binary_tree(const Node *const pt_to_node) {
    if (!pt_to_node) {
        putchar('\n');
        return;
    }
    const int height = tree_height(pt_to_node);
    if (height == 0)
        print_value(pt_to_node->value), putchar('\n');
    else
        print_subtree(pt_to_node, height, 0);
}

void preorder_traverse_tree_and_print(const Node *const pt_to_node) {
    if (!pt_to_node) {
        printf("()\n");
        return;
    }
    putchar('(');
    print_preorder_subtree(pt_to_node);
    printf("\b\b)\n");
}

void inorder_traverse_tree_and_print(const Node *const pt_to_node) {
    if (!pt_to_node) {
        printf("()\n");
        return;
    }
    putchar('(');
    print_inorder_subtree(pt_to_node);
    printf("\b\b)\n");
}

void postorder_traverse_tree_and_print(const Node *const pt_to_node) {
    if (!pt_to_node) {
        printf("()\n");
        return;
    }
    putchar('(');
    print_postorder_subtree(pt_to_node);
    printf("\b\b)\n");
}

void delete_tree(Node **const pt_to_pt_to_node) {
    delete_subtree(*pt_to_pt_to_node);
    *pt_to_pt_to_node = NULL;
}

static int subtree_height(const Node *const pt_to_node) {
    if (!pt_to_node)
        return 0;
    return 1 + fmax(subtree_height(pt_to_node->pt_to_left_node),
                    subtree_height(pt_to_node->pt_to_right_node));
}

static Node *lift_left(Node *pt_to_node) {
    Node *pt_to_new_root;
    if (!pt_to_node->pt_to_left_node) {
        pt_to_new_root = pt_to_node->pt_to_right_node;
        free(pt_to_node);
        return pt_to_new_root;
    }
    pt_to_new_root = pt_to_node->pt_to_left_node;
    Node *pt_to_right_subtree = pt_to_node->pt_to_right_node;
    free(pt_to_node);
    pt_to_node = pt_to_new_root;
    while (pt_to_node->pt_to_right_node)
        pt_to_node = pt_to_node->pt_to_right_node;
    pt_to_node->pt_to_right_node = pt_to_right_subtree;
    return pt_to_new_root;
}

static Node *lift_right(Node *pt_to_node) {
    Node *pt_to_new_root;
    if (!pt_to_node->pt_to_right_node) {
        pt_to_new_root = pt_to_node->pt_to_left_node;
        free(pt_to_node);
        return pt_to_new_root;
    }
    pt_to_new_root = pt_to_node->pt_to_right_node;
    Node *pt_to_left_subtree = pt_to_node->pt_to_left_node;
    free(pt_to_node);
    pt_to_node = pt_to_new_root;
    while (pt_to_node->pt_to_left_node)
        pt_to_node = pt_to_node->pt_to_left_node;
    pt_to_node->pt_to_left_node = pt_to_left_subtree;
    return pt_to_new_root;
}

static void print_subtree(const Node *const pt_to_node, const int height, const int level) {
    if (level > height)
        return;
    if (!pt_to_node) {
        print_subtree(NULL, height, level + 1);
        putchar('\n');
        print_subtree(NULL, height, level + 1);
        return;
    }
    print_subtree(pt_to_node->pt_to_right_node, height, level + 1);        
    for (int i = 0; i < level * 4; ++i)
        putchar(' ');
    print_value(pt_to_node->value), putchar('\n');
    print_subtree(pt_to_node->pt_to_left_node, height, level + 1);
}

static void print_preorder_subtree(const Node *const pt_to_node) {
    if (!pt_to_node)
        return;
    print_value(pt_to_node->value), printf(", ");
    print_preorder_subtree(pt_to_node->pt_to_left_node);        
    print_preorder_subtree(pt_to_node->pt_to_right_node);
}

static void print_inorder_subtree(const Node *const pt_to_node) {
    if (!pt_to_node)
        return;
    print_inorder_subtree(pt_to_node->pt_to_left_node);
    print_value(pt_to_node->value), printf(", ");
    print_inorder_subtree(pt_to_node->pt_to_right_node);
}

static void print_postorder_subtree(const Node *const pt_to_node) {
    if (!pt_to_node)
        return;
    print_postorder_subtree(pt_to_node->pt_to_left_node);        
    print_postorder_subtree(pt_to_node->pt_to_right_node);
    print_value(pt_to_node->value), printf(", ");
}

static void delete_subtree(Node *pt_to_node) {
    if (!pt_to_node)
        return;
    delete_subtree(pt_to_node->pt_to_left_node);
    delete_subtree(pt_to_node->pt_to_right_node);
    free(pt_to_node);
}
