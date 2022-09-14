
// Preprocessor directives
#pragma once

// Includes
#include <stdio.h>
#include <stdlib.h>

// Struct definitions
struct stack_s
{
	size_t           stack_size;
	size_t           stack_offset;
	void           **stack_data;
	struct stack_s   *next;

};

// Type definitions
typedef struct stack_s stack;

// Allocators
int create_stack          ( stack **pp_stack );

// Constructors 
int construct_stack       ( stack **pp_stack, size_t  size );
int construct_stack_frame ( stack  *p_base  , stack  *ret );

// Stack opeations
int stack_push      ( stack  *p_stack, const void  *p_operand );
int stack_pop       ( stack  *p_stack, void       **ret );
int stack_copy      ( stack  *p_stack, stack      **ret );
int stack_duplicate ( stack  *p_stack, const void  *p_operand );
int stack_peek      ( stack  *p_stack, void       **ret       );
int stack_swap      ( stack  *p_stack, const void  *p_operand );
int stack_rotate    ( stack  *p_stack, const void  *p_operand );

// Deallocators
int destroy_stack   ( stack  *p_stack );
