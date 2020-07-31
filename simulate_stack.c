#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct linked_list{
	int stack_value;
	struct linked_list *next;
} linked_list;


linked_list *push(linked_list *stack_current, int input) // process is called with the type->struct so that we can point to the linked-list, add to it, and output it back to main; "stack_current" linkedlist is our most updated linkedlist
{
	linked_list *add_to_stack = (linked_list *) malloc(sizeof(linked_list)); // allocate memory for push entry

	if (add_to_stack != NULL) // if the memory allocation didn't work, then we exit returning "NULL" to the stack
	{
		add_to_stack->stack_value = input; // add_to_stack is a struct pointer to the linked_list, we're using this to push an inputted value to the linked-list
		add_to_stack->next = stack_current; // what this does is puts our new entry at the beginning of the list so that we can get a "last in first out" kind of deal; and this line adds the rest of the currently existing linked list to the "next" pointer
	}

	return add_to_stack; // return it back to the stack in main
}


linked_list *pop(linked_list *stack_current) // process is called with the type->struct so that we can point to the linked-list, pop from it, and output the linked-list back to main
{
	linked_list *take_off_stack; // struct pointer used as a buffer to temporarily store

	if (stack_current != NULL) // if we're not at the tale of the stack
	{
		take_off_stack = stack_current; // set pointer equal to current head of stack
		stack_current = stack_current->next; // set head of stack = to the next value in the stack
		free(take_off_stack); // free the memory of pointer that used to hold old head of stack
	}

	return stack_current; // return modified stack
}


void print(linked_list *stack_current) // function is of the void type because we're not returning anything
{
	linked_list *iterate_thru_stack = stack_current; // set struct pointer equal to current stack
	
	if(iterate_thru_stack != NULL)
	{
		printf("Current Stack:\n   -------------\n"); 
	}
	
	else
	{
		printf("You have an empty stack!\n"); 
	}
	
	while(iterate_thru_stack != NULL)
	{
		if(((iterate_thru_stack->stack_value) >= 0)&&((iterate_thru_stack->stack_value) < 10))
		{
		printf("   |     %d     |\n", iterate_thru_stack->stack_value); // print the current stack value
		}
		
		else if(((iterate_thru_stack->stack_value) >= 10)&&((iterate_thru_stack->stack_value) < 100))
		{
		printf("   |     %d    |\n", iterate_thru_stack->stack_value); // print the current stack value
		}
		
		else if(((iterate_thru_stack->stack_value) >= 100)&&((iterate_thru_stack->stack_value) <= 255))
		{
		printf("   |     %d   |\n", iterate_thru_stack->stack_value); // print the current stack value
		}
		
		iterate_thru_stack = iterate_thru_stack->next; // set the current stack pointer to the next place in the list
		
		printf("   -------------\n");
	}
	
	printf("\n");
}

/*
-------------
|     1     |
-------------
|     1     |
-------------
|     1     |
-------------
|     1     |
-------------
|     1     |
-------------
|     1     |
-------------
*/

// need to add:
	// - pop and top check if stack is empty, return NULL
	// - stack contains one value then pop should return NULL
	// - push needs to use malloc, check to see if malloc returns a valid memory address (if not return null), should return current stack pointer location (whatever is inside)

int main()
{
	// grows upward
	// make a stack filled with 6 numbers
	// push  -> pushes number to stack and moves on to next address, returns address
	// pop   -> pops the current address moves back, returns address
	// top   -> retrieves topmost element from stack, returns contents
	// print -> prints current stack
	
	linked_list *stack = NULL;

	char stack_input[10], stack_action[8];
	int case_place, buff;
	int exit_flag = 1;

	while(exit_flag)
	{

		switch(case_place)
		{
			case 0: // recieve
				printf("push, pop, top, print, or exit\n");
				memset(&stack_input[0], 0, sizeof(stack_input)); // clear input array
				memset(&stack_action[0], 0, sizeof(stack_action)); // clear input array
				fgets(&stack_input[0], sizeof(stack_input), stdin);
				//stack_input[strcspn(stack_input, "\n")] = '\0'; // replace the newline with null-terminal
				
				sscanf(stack_input, "%s %d", &stack_action, &buff);

				printf("\n");
				
				if(strcmp("push", stack_action) == 0)
				{
					if(buff == -12816)
					{
						printf("Number not entered for push operation, try again (ex: push 100)\n\n");
					}
					
					else
					{
						case_place = 1;
					}
				}

				else if(strcmp("pop", stack_action) == 0)
				{
					case_place = 2;
				}

				else if(strcmp("top", stack_action) == 0)
				{
					case_place = 3;
				}

				else if(strcmp("print", stack_action) == 0)
				{
					case_place = 4;
				}
				
				else if(strcmp("exit", stack_action) == 0)
				{
					printf("Goodbye!\n");
					linked_list *delete_linked_list;
					
					while(stack != NULL)
					{
						delete_linked_list = stack;
						stack = stack->next;
						free(delete_linked_list);
					}
					
					exit_flag = 0;
				}
				
				else
				{
					printf("Could not recognize command, try again\n\n");
				}
				break;
			
			case 1: // push
				if(buff > 255)
				{
					printf("Value entered bigger than a byte, try again\n");
					case_place = 0;
				}

				else
				{
					stack = push(stack, buff);
				}

				case_place = 0;
				break;

			case 2: // pop
				stack = pop(stack);
				case_place = 0;
				break;

			case 3: // top
				if(stack == NULL)
				{
					printf("NULL");
				}

				else
				{
					printf("Top of Stack is: %d\n\n", stack->stack_value);
				}
				case_place = 0;
				break;
			
			case 4: // print
				print(stack);
				case_place = 0;
				break;
	
			default:
				case_place = 0;
		}	
	}	
}
