#include "dbgalloc.h"


void *dbg_malloc(struct alloc_register_t *alloc_reg, size_t size, char const *file, size_t const line){
	alloc_reg += reg_counter;
	alloc_reg->line = line;
	strcpy(alloc_reg->file_name, file);
	alloc_reg->is_deallocated = false;
	void *alloc_ptr = malloc(size);
	alloc_reg->allocation_address = alloc_ptr;
	reg_counter++;
	return alloc_ptr;
}

void dbg_free(struct alloc_register_t * const alloc_reg, void const * const to_be_freed){
	for(int i=0; i<reg_counter; ++i){
		if((alloc_reg+i)->allocation_address == to_be_freed){
			free((alloc_reg+i)->allocation_address);
			(alloc_reg+i)->is_deallocated = true;
			return;
		}
	}
}

void not_freed(struct alloc_register_t * const alloc_reg){
	for(int i=0; i<reg_counter; ++i){
		if((alloc_reg+i)->is_deallocated == false){
			printf("NOT FREED %p at %s:%ld\n", (alloc_reg+i)->allocation_address, (alloc_reg+i)->file_name
			, (alloc_reg+i)->line);
		}
	}
}

