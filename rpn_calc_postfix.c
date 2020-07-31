// read: https://boredzo.org/pointers/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct rpn_number_list
{
    char number_entered[21];
    struct rpn_number_list *next;
} rpn_number_list;

rpn_number_list *push(rpn_number_list *stack_current, char *input, int input_track)
{
    rpn_number_list *push_to_stack = (rpn_number_list *) malloc(sizeof(rpn_number_list));
 
    int i = 0;

    if(push_to_stack != NULL)
    {
        while(i < (input_track))
        {
            push_to_stack->number_entered[i] = *input;
            
            i++;
            input++;
        }

        push_to_stack->next = stack_current;
    }

    return push_to_stack;
}

rpn_number_list *pop(rpn_number_list *stack_current, char operator)
{
    rpn_number_list *pop_from_stack;
    char *operand[2];
    char *output;
    operand[0] = (char *) malloc(sizeof(char)*(strlen(stack_current->number_entered)));
    operand[1] = (char *) malloc(sizeof(char)*(strlen(stack_current->number_entered)));
    output = (char *) malloc(sizeof(char)*21);
    //printf("operator: %c\n", operator);

    if((operand[0] != NULL) && (operand[1] != NULL) && output != NULL)
    {
        for(int pop_loop = 0; pop_loop < 2; pop_loop++)
        {
            if(pop_from_stack != NULL)
            {
                strcpy(operand[pop_loop], stack_current->number_entered);
                //printf("operand: %s\n", operand[pop_loop]);
                pop_from_stack = stack_current;
                stack_current = stack_current->next;
                free(pop_from_stack);
                //free(operand[pop_loop]);
            }
        }

        if(operator == '*')
        {
            sprintf(output, "%.2f", ((atof(operand[0]))*(atof(operand[1]))));
        }

        if(operator == '/')
        {
            sprintf(output, "%.2f", ((atof(operand[0]))/(atof(operand[1]))));
        }

        if(operator == '+')
        {
            sprintf(output, "%.2f", ((atof(operand[0]))+(atof(operand[1]))));
        }

        if(operator == '-')
        {
            sprintf(output, "%.2f", ((atof(operand[0]))-(atof(operand[1]))));
        }
        //printf("output = %s", output);
        stack_current = push(stack_current, output, ((int)strlen(output) + 1));

        free(operand[0]);
        free(operand[1]);
        free(output);
    }

    return stack_current;
}

int main()
{
    char user_input[512];
    char number_buff[21];
    int begin_number, end_number, number_tracker;
    int loop_troop = 0;
    int state = 0;
    int i = 0;
    int track = 0;
    int allow_push = 0;
    rpn_number_list *number_stack = NULL;

    printf("REVERSE POLISH NOTATION CALCULATOR (Postfix Notation)\nPlease enter an operation and adhere to the order of operations rules (ex: 12345*/+-)\n");
    fflush(stdout);
    memset(&user_input[0], 0, sizeof(user_input));
    fgets(&user_input[0], sizeof(user_input), stdin);

    while(user_input[i] != '\0')
    {
        //printf("state = %d\n", state);
        switch(state)
        {
            case 0:

                if(isdigit(user_input[i]) || user_input[i] == '-' || user_input[i] == '.')
                {
                    loop_troop = 1;
                    begin_number = i;

                    while(loop_troop == 1)
                    {
                        if(isdigit(user_input[i]) || user_input[i] == '.')
                        {
                            allow_push = 1;
                            end_number = i;
                            i++;
                        }

                        if(user_input[i] == '-')
                        {
                            i++;
                            if(isdigit(user_input[i]))
                            {
                                allow_push = 1;
                                end_number = i;
                                i++;
                            }

                            else
                            {
                                allow_push = 0;
                                state = 1;
                                i--;
                                loop_troop = 0;
                                break;
                            }
                        }   

                        if(((end_number - begin_number) + 1) > 20)
                        {
                            allow_push = 0;
                            printf("Inputted Number too large for 32 bit calculator. Exiting\n");
                            loop_troop = 0;
                            state = 3;
                            break;
                        }

                        if((user_input[i] == ' ') || (user_input[i] == '\t') || (user_input[i] == '\n') || (user_input[i] == '\r') || (user_input[i] == '\0'))
                        {
                            loop_troop = 0;
                            state = 0;
                            i++;
                            break;
                        }

                        if(user_input[i] == '*' || user_input[i] == '/' || user_input[i] == '+')
                        {
                            loop_troop = 0;
                            state = 0;
                            break;
                        }
                    }

                    if(allow_push == 1)
                    {
                        number_tracker = end_number - begin_number + 2;
                        memset(number_buff, '\0', sizeof(number_buff));

                        int a = 0;

                        if(number_buff != NULL)
                        {
                            for(int concatenate = begin_number; concatenate < (end_number + 1); concatenate++)
                            {
                                number_buff[a] = user_input[concatenate];
                                a++; 
                            }

                            number_buff[a] = '\0';

                            number_stack = push(number_stack, number_buff, number_tracker);
                            track++;
                        }
                    }     
                }

                else if(user_input[i] == '*' || user_input[i] == '/' || user_input[i] == '+')
                {
                    state = 1;
                }

                else if(user_input[i] == '\0' || user_input[i] == '\t' || user_input[i] == '\n' || user_input[i] == '\r')
                {
                    state = 2;
                }

                else if(user_input[i] == ' ')
                {
                    state = 0;
                    i++;
                }

                else
                {
                    printf("I dont understand something entered.... Exiting\n");
                    state = 3;
                }
                
                break;

            case 1:
                if (track < 2)
                {
                    printf("Not enough parameters have been entered for mathematical operation... Exiting\n");
                    state = 3;
                }

                else
                {
                    char operator_buffer = user_input[i];
                    number_stack = pop(number_stack, operator_buffer);
                    state = 0;
                    i++;
                }

                break;

            case 2:
                // Exit State
                printf("Final: %s\n", number_stack->number_entered);
                state = 3;
                break;

            case 3:
                i++;
                break;

            default:
                break;
        }    
    }

    rpn_number_list *delete_stack;

    while(number_stack != NULL)
    {
        delete_stack = number_stack;
        number_stack = number_stack->next;
        free(delete_stack);
    }
}
