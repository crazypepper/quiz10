#include <stdbool.h>
#include "tailored_stack.h"
#include "tailored_tree.h"

bool is_correct_postfix_expression(Stack *const);
void transfer_from_stack_to_tree(Stack *const, Node *const);
