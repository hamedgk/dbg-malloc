#include <stdlib.h>
#include <stddef.h>
#include "dbgalloc.h"
#include "dbg_list.h"

struct alloc_register_node *insert_reg_node(struct alloc_register_node* alloc_regs, struct alloc_register_t reg){
    struct alloc_register_node *new_node = malloc(sizeof(struct alloc_register_node));
    new_node->data = reg;
    new_node->next = NULL;
    
    if(!alloc_regs)
        return new_node; 
    
    struct alloc_register_node *current = alloc_regs;
    while (current->next)
    {
        current = current->next;
    }
    current->next = new_node;
    return alloc_regs; 
}