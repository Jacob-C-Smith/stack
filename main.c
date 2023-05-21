#include <stdio.h>

#include <stack/stack.h>

int main ( int argc, const char *argv[] )
{
	stack *p_stack = 0;
	void  *first   = 0;

	construct_stack(&p_stack, 2);

	stack_push(p_stack, 0x123);
	stack_push(p_stack, 0x456);
	stack_push(p_stack, 0x789);

	stack_pop(p_stack, &first);
	stack_pop(p_stack, &first);
	stack_pop(p_stack, &first);
	stack_pop(p_stack, &first);

	destroy_stack(&p_stack);

	return EXIT_SUCCESS;
}