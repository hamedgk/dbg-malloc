#ifndef __DBG_LIST_H
#define __DBG_LIST_H

struct alloc_register_t;

struct alloc_register_node{
	struct alloc_register_t data;
	struct alloc_register_node *next;
};

struct alloc_register_node *insert_reg_node(struct alloc_register_node*, struct alloc_register_t);


#endif