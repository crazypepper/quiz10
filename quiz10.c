/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by Eric Martin for COMP9021                                         *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_stack.c                                                      *
 *       tailored_tree.c                                                       *
 *       my_code.c                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_code.h"
#include "tailored_tree.h"
#include "tailored_stack.h"

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Provide at least two command line arguments.\n");
        return EXIT_FAILURE;
    }        
    Stack stack_1, stack_2;
    initialise_stack(&stack_1);
    initialise_stack(&stack_2);
    for (int i = 1; i < argc; ++i) {
        if (strlen(argv[i]) != 1 || !isdigit(argv[i][0]) && argv[i][0] != '+') {
            printf("Command line arguments should be digits or + only.\n");
            return EXIT_FAILURE;
        }
        push(argv[i][0], &stack_1);
        push(argv[i][0], &stack_2);
    }
    if (!is_correct_postfix_expression(&stack_1) || !is_empty_stack(&stack_1))
        printf("Not a correct postfix expression.\n");
    else {
        Node root;
        transfer_from_stack_to_tree(&stack_2, &root);
        print_binary_tree(&root);
    }
    return EXIT_SUCCESS;
}
