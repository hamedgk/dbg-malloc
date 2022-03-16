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

#define init_allocation_registers(allocation_register_count) struct alloc_register_t *regs = (struct alloc_register_t*) malloc(sizeof(struct alloc_register_t) * allocation_register_count)

void *dbg_malloc(struct alloc_register_t *alloc_reg, size_t size, char const *file, size_t const line);

#define dbg_malloc_macro(size) dbg_malloc(regs, size, __FILE__, __LINE__)

void dbg_free(struct alloc_register_t * const alloc_reg, void const * const to_be_freed);

#define dbg_free_macro(ptr_to_be_freed) dbg_free(regs, ptr_to_be_freed)

void not_freed(struct alloc_register_t * const alloc_reg);

#define not_freed_macro() not_freed(regs)

void invoke_callback(struct alloc_register_t *alloc_reg, void (*callback) (struct alloc_register_t*));

#define invoke_callback_macro(callback) invoke_callback(regs, callback)

#ifdef WITH_LOGGING
int logger(char const *path, struct alloc_register_t *alloc_reg);
#define logger_macro(path) logger(path, regs)
#endif

#endif
