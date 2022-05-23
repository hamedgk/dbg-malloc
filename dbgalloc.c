#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dbgalloc.h"
#include "dbg_list.h"
#include "colors.h"

void *dbg_malloc(struct alloc_register_node **alloc_reg, size_t size, char const *file, size_t const line){
	struct alloc_register_t alloced;
	alloced.line = line;
	strcpy(alloced.file_name, file);
	alloced.is_deallocated = false;
	void *alloc_ptr = malloc(size);
	alloced.allocation_address = alloc_ptr;
	*alloc_reg = insert_reg_node(*alloc_reg, alloced);	
	return alloc_ptr;
}

struct alloc_register_node *dbg_free(struct alloc_register_node *alloc_reg, void const * const to_be_freed){
	if(!alloc_reg) return NULL;
	
	if(alloc_reg->data.allocation_address == to_be_freed){
		struct alloc_register_node *temp = alloc_reg;
		alloc_reg = alloc_reg->next;
		free(temp->data.allocation_address);
		free(temp);
		return alloc_reg;
	}

	struct alloc_register_node *top  = alloc_reg;
	struct alloc_register_node *down = top->next;

	while(down){
		if(down->data.allocation_address == to_be_freed){
			struct alloc_register_node *temp = down;
			down = down->next;
			top->next = down;	
			free(temp->data.allocation_address);
			free(temp);
			return alloc_reg;
		}
		top = down;
		down = down->next;
	}
	return alloc_reg;
}

void not_freed(struct alloc_register_node *alloc_reg){
	if(!alloc_reg) return;
	struct alloc_register_node *current = alloc_reg;
	while(current){
		printf("NOT FREED " GREEN"%p" RESET" at %s:%ld\n", current->data.allocation_address, current->data.file_name
		, current->data.line);
		current = current->next;	
	}	
}

void invoke_callback(struct alloc_register_node *alloc_reg, void (*callback)(struct alloc_register_t*)){
	if(!alloc_reg) return;
	struct alloc_register_node *current = alloc_reg; 
	while(current){
		callback(&current->data);
		current = current->next;
	}
}
