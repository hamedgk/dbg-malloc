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

void dbg_free(struct alloc_register_node *alloc_reg, void const * const to_be_freed){
	if(!alloc_reg) return;
	struct alloc_register_node *current = alloc_reg;
	while(current){
		if(current->data.allocation_address == to_be_freed){
			free(current->data.allocation_address);
			current->data.is_deallocated = true;
			return;
		}
		current = current->next;
	}
}

void not_freed(struct alloc_register_node *alloc_reg){
	if(!alloc_reg) return;
	struct alloc_register_node *current = alloc_reg;
	while(current){
		if(current->data.is_deallocated == false){
			printf("NOT FREED " GREEN"%p" RESET" in %s:%ld\n", current->data.allocation_address, current->data.file_name
			, current->data.line);
		}
		current = current->next;	
	}	
}

void invoke_callback(struct alloc_register_node *alloc_reg, void (*callback)(struct alloc_register_t*)){
	if(!alloc_reg) return;
	struct alloc_register_node *current = alloc_reg; 
	while(current){
		if(current->data.is_deallocated == false){
			callback(&current->data);
		}
		current = current->next;
	}
}
