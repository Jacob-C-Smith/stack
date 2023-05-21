
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
	struct stack_s  *next;
};

// Type definitions
typedef struct stack_s stack;

// Allocators
/** !
 * Allocate memory for a stack
 * 
 * @param pp_stack : ret
 * 
 * @sa destroy_stack
 * 
 * @return 1 on success, 0 on error
*/
int create_stack ( stack **pp_stack );

// Constructors 
/** !
 * Construct a stack of a specified size
 * 
 * @param pp_stack : ret
 * 
 * @sa destroy_stack
 * 
 * @return 1 on success, 0 on error
*/
int construct_stack ( stack **pp_stack, size_t size );

/** !
 * Construct a stack frame from a stack
 * 
 * @param p_base : the base of the stack
 * @param ret : return
 * 
 * @sa destroy_stack
 * 
 * @return 1 on success, 0 on error
*/
int construct_stack_frame ( stack *p_base, stack *ret );

// Mutators opeations
/** !
 * Push a value onto a stack
 * 
 * @param p_stack : the stack
 * @param p_operand : the value
 * 
 * @sa stack_pop
 * 
 * @return 1 on success, 0 on error
*/
int stack_push ( stack *p_stack, const void *p_operand );

/** !
 * Pop a value off a stack
 * 
 * @param p_stack : the stack
 * @param ret : return
 * 
 * @sa stack_push
 * 
 * @return 1 on success, 0 on error
*/
int stack_pop ( stack *p_stack, void **ret );

/** !
 * Make a shallow copy of a stack
 * 
 * @param p_stack : the stack
 * @param ret : return
 * 
 * @sa stack_push
 * 
 * @return 1 on success, 0 on error
*/
int stack_copy ( stack *p_stack, stack **ret );

// Destructors
/** !
 * Deallocate a stack
 * 
 * @param pp_stack : pointer to stack pointer
 * 
 * @sa stack_create
 * 
 * @return 1 on success, 0 on error
*/
int destroy_stack ( stack **pp_stack );
