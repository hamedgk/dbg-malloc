#ifndef DBGALLOC_H__ 
#define DBGALLOC_H__ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct alloc_register_t{
	void  *allocation_address;
	size_t line;
	bool   is_deallocated;
	char   file_name[];
};

static size_t reg_counter = 0;


void *dbg_malloc(struct alloc_register_t *alloc_reg, size_t size, char const *file, size_t const line);

#define dbg_malloc_macro(alloc_register, size) dbg_malloc(alloc_register, size, __FILE__, __LINE__)

void invoke_callback(struct alloc_register_t *alloc_reg, void (*callback)(struct alloc_register_t*));

void dbg_free(struct alloc_register_t * const alloc_reg, void const * const to_be_freed);

void not_freed(struct alloc_register_t * const alloc_reg);


#endif
