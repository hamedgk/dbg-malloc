#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ALLOC_REGS 256

struct alloc_register_t{
	void *allocation_address;
	size_t line;
	bool   is_deallocated;
	char   file_name[];
};

size_t reg_counter = 0;


void *dbg_malloc(struct alloc_register_t *alloc_reg, size_t size, char const *file, size_t line){
	alloc_reg += reg_counter;
	alloc_reg->line = line;
	strcpy(alloc_reg->file_name, file);
	alloc_reg->is_deallocated = false;
	void *alloc_ptr = malloc(size);
	alloc_reg->allocation_address = alloc_ptr;
	reg_counter++;
	printf("allocation    %p in  %s:%ld\n",alloc_ptr, file, line);
	return alloc_ptr;
}

void dbg_free(struct alloc_register_t *alloc_reg, void *to_be_freed){
	for(int i=0; i<MAX_ALLOC_REGS; ++i){
		if((alloc_reg+i)->allocation_address == to_be_freed){
			free((alloc_reg+i)->allocation_address);
			alloc_reg->is_deallocated = true;
			printf("deacllocation %p for %s:%ld\n", alloc_reg->allocation_address, alloc_reg->file_name, alloc_reg->line);
			return;
		}

	}
}

void not_freed(struct alloc_register_t *alloc_reg){
	for(int i=0; i<MAX_ALLOC_REGS; ++i){
		if((alloc_reg+i)->is_deallocated == false && (alloc_reg+i)->allocation_address != NULL){
			printf("NOT FREED     %p in  %s:%ld\n", (alloc_reg+i)->allocation_address, (alloc_reg+i)->file_name
			, (alloc_reg+i)->line);
		}
	}
}

int main(){
	struct alloc_register_t *regs = (struct alloc_register_t*) malloc(sizeof(struct alloc_register_t) * MAX_ALLOC_REGS);
	
	int *handler = (int*) dbg_malloc(regs, sizeof(int)*16, __FILE__, __LINE__);
	int *handler2 = (int*) dbg_malloc(regs, sizeof(int)*16, __FILE__, __LINE__);
	dbg_free(regs, handler);
	dbg_free(regs, handler2);
	not_freed(regs);	
	return 0;
}
