/** !
 * Include header for stack library
 * 
 * @file stack/stack.h 
 * 
 * @author Jacob Smith 
 */

// Include guard
#pragma once

// Standard library
#include <stdio.h>
#include <stdlib.h>

// sync submodule
#include <sync/sync.h>

// Platform dependent macros
#ifdef _WIN64
#define DLLEXPORT extern __declspec(dllexport)
#else
#define DLLEXPORT
#endif

// Forward declarations
struct stack_s;

// Type definitions
typedef struct stack_s stack;

// Allocators
/** !
 * Allocate memory for a stack
 * 
 * @param pp_stack : ret
 * 
 * @sa stack_destroy
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int stack_create ( stack **pp_stack );

// Constructors 
/** !
 * Construct a stack of a specified size
 * 
 * @param pp_stack : ret
 * 
 * @sa stack_destroy
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int stack_construct ( stack **pp_stack, size_t size );

// Mutators
/** !
 * Push a value onto a stack
 * 
 * @param p_stack : the stack
 * @param p_value : the value
 * 
 * @sa stack_pop
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int stack_push ( stack *p_stack, void *p_value );

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
DLLEXPORT int stack_pop ( stack *p_stack, void **ret );

// Accessors
/** !
 * Peek the top of the stack
 * 
 * @param p_stack : the stack
 * @param ret : return
 * 
 * @sa stack_pop
 * 
 * @return 1 on success, 0 on error
*/
DLLEXPORT int stack_peek ( stack *p_stack, void **ret );

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
DLLEXPORT int stack_destroy ( stack **pp_stack );