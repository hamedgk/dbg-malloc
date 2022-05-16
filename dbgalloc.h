#ifndef DBGALLOC_H__ 
#define DBGALLOC_H__ 
#include <stdbool.h>
#include <stddef.h>

#ifndef FILE_SIZE
#define FILE_SIZE 32
#endif

struct alloc_register_node;

struct alloc_register_t{
	void  *allocation_address;
	size_t line;
	bool   is_deallocated;
	char   file_name[FILE_SIZE];
};



#define INIT_ALLOC_REGS() struct alloc_register_node *regs = NULL; 

void *dbg_malloc(struct alloc_register_node **alloc_reg, size_t size, char const *file, size_t const line);

#define DBGALLOC(size) dbg_malloc(&regs, size, __FILE__, __LINE__)

void dbg_free(struct alloc_register_node *alloc_reg, void const * const to_be_freed);

#define DBGFREE(ptr_to_be_freed) dbg_free(regs, ptr_to_be_freed)

void not_freed(struct alloc_register_node *alloc_reg);

#define NOT_FREED() not_freed(regs)

void invoke_callback(struct alloc_register_node *alloc_reg, void (*callback) (struct alloc_register_t*));

#define INVOKE_CALLBACK(callback) invoke_callback(regs, callback)

#endif
