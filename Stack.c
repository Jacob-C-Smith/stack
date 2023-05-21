#include <stack/stack.h>

int create_stack ( stack **pp_stack )
{
	
	// Argument check
	{
		#ifndef NDEBUG
			if ( pp_stack == (void *) 0 ) goto no_stack;
		#endif
	}

	// Initialized data
	stack *p_stack = calloc( 1, sizeof(stack) );

	// Error check
	if ( p_stack == (void *) 0 )
		goto no_mem;

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
					printf("[stack] Null pointer provided for \"pp_stack\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;
		}
	}
}

int construct_stack ( stack **pp_stack, size_t size )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( pp_stack == (void *) 0 ) goto no_stack;
			if ( size < 1 ) goto no_size;
		#endif
	}

	// Initialized data
	stack *p_stack = 0;

	// Allocate a stack
	if ( create_stack(pp_stack) == 0 ) 
		goto failed_to_allocate_stack;
	
	// Get a pointer to the stack
	p_stack = *pp_stack;

	// Allocate space for the stack
	p_stack->stack_data = calloc(size, sizeof(void *));
	
	// Error check
	if ( p_stack->stack_data == (void *) 0 )
		goto no_mem;

	// Set the stack size
	p_stack->stack_size = size;
	
	// Success
	return 1;
	
	// Error handling
	{

		// Argument errors
		{
			no_stack:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"pp_stack\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;

			no_size:
				#ifndef NDEBUG
					printf("[stack] No size provided in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;
		}

		// Stack errors
		{
			failed_to_allocate_stack:
				#ifndef NDEBUG
					printf("[stack] Failed to allocate memory in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;
		}

		// Standard library errors
		{
			no_mem:
				#ifndef NDEBUG
					printf("[Standard Library] Failed to allocate memory in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;
		}

	}
}

int stack_push ( stack *p_stack, const void *p_operand )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_stack   == (void *) 0 ) goto no_stack;
			if ( p_operand == (void *) 0 ) goto no_operand;
		#endif
	}

	// Check for overflow
	if ( p_stack->stack_size < p_stack->stack_offset )
		goto stack_overflow;

	// Push the data onto the stack
	p_stack->stack_data[p_stack->stack_offset++] = p_operand;

	// Success
	return 1;

	// Error handling
	{

		// Stack errors
		{
			stack_overflow:
				#ifndef NDEBUG
					printf("[stack] Stack overflow!\n");
				#endif

				// Error
				return 0;
		}

		// Argument errors
		{
			no_stack:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"p_stack\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;

			no_operand:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"p_operand\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;

		}
	}
}

int stack_pop ( stack *p_stack , void **ret )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( p_stack == (void *) 0 ) goto no_stack;
			if ( ret     == (void *) 0 ) goto no_ret;
		#endif
	}

	// Check for underflow
	if ( p_stack->stack_offset < 1 )
		goto stack_underflow;

	// Pop the stack and write the return
	*ret = p_stack->stack_data[--p_stack->stack_offset];

	// Success
	return 1;

	// Error handling
	{

		// Stack errors
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
					printf("[stack] Null pointer provided for \"p_stack\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;

			no_ret:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"ret\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;
		}
	}
}

int destroy_stack ( stack **pp_stack )
{

	// Argument check
	{
		#ifndef NDEBUG
			if ( pp_stack == (void *) 0 ) goto no_stack;
		#endif
	}

	// Initialized data
	stack *p_stack = *pp_stack;

	// Error checking
	if ( p_stack == (void *) 0 )
		goto pointer_to_null_pointer;

	// No more pointer for caller
	*pp_stack = p_stack;

	// (Recursively) destroy the next stack
	if ( p_stack->next )
		destroy_stack(p_stack->next);

	// Free stack data
	free(p_stack->stack_data);

	// Free the stack
	free(p_stack);

	// Success
	return 1;

	// Error handling
	{

		// Argument errors
		{
			no_stack:
				#ifndef NDEBUG
					printf("[stack] Null pointer provided for \"pp_stack\" in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;

			pointer_to_null_pointer:
				#ifndef NDEBUG
					printf("[stack] Parameter \"pp_stack\" points to null pointer in call to function \"%s\"\n", __FUNCSIG__);
				#endif

				// Error
				return 0;
		}
	}
}
