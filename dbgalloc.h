#ifndef DBGALLOC_H__ 
#define DBGALLOC_H__ 

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALLOC_INFO __FILE__,__LINE__

struct alloc_register_t{
	void  *allocation_address;
	size_t line;
	bool   is_deallocated;
	char   file_name[];
};

static size_t reg_counter = 0;


void *dbg_malloc(struct alloc_register_t *alloc_reg, size_t size, char const *file, size_t line);

void dbg_free(struct alloc_register_t *alloc_reg, void *to_be_freed);

void not_freed(struct alloc_register_t *alloc_reg);


#endif
