/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Description: 
 *                                                                             *
 * Written by AnpengChen for COMP9021                                          *
 *                                                                             *
 * Other source files, if any, one per line, starting on the next line:        *
 *       tailored_stack.c                                                      *
 *       tailored_tree.c                                                       *
 *       quiz10.c                                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* THIS IS THE ONLY FILE YOU HAVE TO SUBMIT.
 * IT WILL BE COMPILED WITH THE OTHER FILES YOU HAVE BEEN PROVIDED WITH. */

#include "my_code.h"
bool is_operator(int);


bool is_correct_postfix_expression(Stack *const pt_to_stack) {
    int count=2;
    Value currentValue;
    pop(pt_to_stack,&currentValue);
    if(isdigit(currentValue)){
        empty_stack(pt_to_stack);
        return false;
    }
    while(!is_empty_stack(pt_to_stack)&&count!=0){
        pop(pt_to_stack,&currentValue);
        if(isdigit(currentValue))
            count--;
        if(is_operator(currentValue))
            count++;
    }
    if(is_empty_stack(pt_to_stack)&&count==0){
        empty_stack(pt_to_stack);
        return true;
    }
    else{
        empty_stack(pt_to_stack);
        return false;
    }
    
}

void transfer_from_stack_to_tree(Stack *const pt_to_stack, Node *const pt_to_node) {
    if(is_empty_stack(pt_to_stack))
        return 0;
    Value currentValue;
    //There must be a flag which represent whether it is the first node(root node)
    static root_flag=0;
    Node *root=pt_to_node;
    //If it is the first node,establish the root of the tree(without 2 childrens)
    if(root_flag==0){
        pop(pt_to_stack,&currentValue);
        root->value=currentValue;
        root->pt_to_right_node=NULL;
        root->pt_to_left_node=NULL;
        ++root_flag;
        transfer_from_stack_to_tree(pt_to_stack,root);
    }
    //We go right side firstly
    if(root->pt_to_right_node==NULL){
        pop(pt_to_stack,&currentValue);
        root->pt_to_right_node= create_node(currentValue);
        //If this node is a operator,it must have two children, so we give
        //address of the right side of this node as a new root node to this function
        //Otherwise it must be a digit,it already occupy right side child
        //so we give left side address to this function
        //we cannot give digit node address as a root node,otherwise it would have children.
        if(is_operator(currentValue))
            transfer_from_stack_to_tree(pt_to_stack,root->pt_to_right_node);
        else
            transfer_from_stack_to_tree(pt_to_stack,root);
    }
    //Then we go to left side
    if(root->pt_to_left_node==NULL){
        pop(pt_to_stack,&currentValue);
        root->pt_to_left_node=create_node(currentValue);
        if(is_operator(currentValue))
            transfer_from_stack_to_tree(pt_to_stack,root->pt_to_left_node);
    }
    
    
    
}

bool is_operator(int c){
    if(c=='+'||c=='-'||c=='/'||c=='*')
        return true;
    else
        return false;
}
