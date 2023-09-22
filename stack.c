/** !
 * stack library
 * 
 * @file stack.c 
 * 
 * @author Jacob Smith
 */

// Include
#include <stack/stack.h>

// Structures
struct stack_s
{
	size_t    _size;   // The quantity of elements that could fit in the stack
	size_t    _offset; // The quantity of elements in the stack
	const void **_data;   // The stack elements
	mutex     _lock;   // Locked when reading/writing values
};

int stack_create ( stack **const pp_stack )
{
	
	// Argument check
	if ( pp_stack == (void *) 0 ) goto no_stack;

	// Initialized data
	stack *p_stack = STACK_REALLOC(0, sizeof(stack));

	// Error check
	if ( p_stack == (void *) 0 ) goto no_mem;

	// Zero set
	memset(p_stack, 0, sizeof(stack));

	// Return a pointer to the caller
	*pp_stack = p_stack;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_stack:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"pp_stack\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int stack_construct ( stack **const pp_stack, size_t size )
{

	// Argument check
	if ( pp_stack == (void *) 0 ) goto no_stack;
	if ( size < 1 ) goto no_size;

	// Initialized data
	stack *p_stack = 0;

	// Allocate a stack
	if ( stack_create(pp_stack) == 0 ) goto failed_to_allocate_stack;
	
	// Get a pointer to the stack
	p_stack = *pp_stack;

	// Allocate space for the stack
	p_stack->_data = STACK_REALLOC(0, size * sizeof(void *));

	// Zero set
	memset(p_stack->_data, 0, size * sizeof(void *));
	
	// Error check
	if ( p_stack->_data == (void *) 0 ) goto no_mem;

	// Set the size
	p_stack->_size = size;

	// Create a mutex
    if ( mutex_create(&p_stack->_lock) == 0 ) goto failed_to_mutex_create;

	// Success
	return 1;
	
	// Error handling
	{

		// Argument errors
		{
			no_stack:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"pp_stack\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

			no_size:
				#ifndef NDEBUG
					printf("[stack] No size provided in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// stack errors
		{
			failed_to_allocate_stack:
				#ifndef NDEBUG
					printf("[stack] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

			failed_to_mutex_create:
                #ifndef NDEBUG
                    printf("[stack] Failed to create mutex in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error 
                return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}

	}
}

int stack_push ( stack *const p_stack, const void *const p_value )
{

	// Argument check
	if ( p_stack == (void *) 0 ) goto no_stack;
	if ( p_value == (void *) 0 ) goto no_value;

	// Error checking
	if ( p_stack->_size == p_stack->_offset ) goto stack_overflow;

	// Lock
    mutex_lock(p_stack->_lock);

	// Push the data onto the stack
	p_stack->_data[p_stack->_offset++] = p_value;

	// Unlock
    mutex_unlock(p_stack->_lock);

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_stack:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"p_stack\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

			no_value:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

		}
		
		// stack errors
		{
			stack_overflow:
				#ifndef NDEBUG
					printf("[stack] Stack overflow!\n");
				#endif

				// Error
				return 0;
		}
	}
}

int stack_pop ( stack *const p_stack, const void **const ret )
{

	// Argument check
	if ( p_stack == (void *) 0 ) goto no_stack;

	// Error checking
	if ( p_stack->_offset < 1 ) goto stack_underflow;

	// Lock
	mutex_lock(p_stack->_lock);

	// Return the value to the caller
	if ( ret )

		// Pop the stack and write the return
		*ret = p_stack->_data[--p_stack->_offset];
	
	// Don't return a value to the caller
	else
		--p_stack->_offset;

	// Unlock
	mutex_unlock(p_stack->_lock);

	// Success
	return 1;

	// Error handling
	{

		// stack errors
		{
			stack_underflow:
				#ifndef NDEBUG
					printf("[stack] Stack Underflow!\n");
				#endif

				// Error
				return 0;
		}

		// Argument errors
		{
			no_stack:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"p_stack\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int stack_peek ( const stack *const p_stack, const void **const ret )
{

	// Argument check
	if ( p_stack == (void *) 0 ) goto no_stack;
	if ( ret     == (void *) 0 ) goto no_ret;

	// Error checking
	if ( p_stack->_offset < 1 ) goto stack_underflow;

	// Lock
	mutex_lock(p_stack->_lock);

	// Peek the stack and write the return
	*ret = p_stack->_data[p_stack->_offset-1];
	
	// Unlock
	mutex_unlock(p_stack->_lock);

	// Success
	return 1;

	// Error handling
	{

		// stack errors
		{
			stack_underflow:
				#ifndef NDEBUG
					printf("[stack] Stack Underflow!\n");
				#endif

				// Error
				return 0;
		}

		// Argument errors
		{
			no_stack:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"p_stack\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

			no_ret:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"ret\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}
	}
}

int stack_destroy ( stack **const pp_stack )
{

	// Argument check
	if ( pp_stack == (void *) 0 ) goto no_stack;

	// Initialized data
	stack *p_stack = *pp_stack;

	// Error checking
	if ( p_stack == (void *) 0 ) goto pointer_to_null_pointer;

	// Lock
    mutex_lock(p_stack->_lock);

	// No more pointer for caller
	*pp_stack = 0;

	// Unlock
    mutex_unlock(p_stack->_lock);

	// Free stack data
	if ( STACK_REALLOC(p_stack->_data, 0) ) goto failed_to_free;

	// Destroy the mutex
    mutex_destroy(&p_stack->_lock);
	
	// Free the stack
	if ( STACK_REALLOC(p_stack, 0) ) goto failed_to_free;

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_stack:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"pp_stack\" in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;

			pointer_to_null_pointer:
				#ifndef NDEBUG
					printf("[stack] Parameter \"pp_stack\" points to null pointer in call to function \"%s\"\n", __FUNCTION__);
				#endif

				// Error
				return 0;
		}

		// Standard library errors
        {
            failed_to_free:
                #ifndef NDEBUG
                    printf("[Standard Library] Call to \"realloc\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
	}
}
