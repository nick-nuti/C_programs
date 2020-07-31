#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack_list
{
    char input[25];
    struct list *next;
} stack_list;

int main()
{
    char user_input[512];
    //char *input_transfer;
    int array_track = 0;
    
    stack_list *number_stack, *input_parsing;
    number_stack = NULL;

    printf("REVERSE POLISH NOTATION CALCULATOR (Postfix Notation)\nPlease enter an operation and adhere to the order of operations rules (ex: 12345*/+-)\n");
    fflush(stdout);
    memset(&user_input[0], 0, sizeof(user_input));
    fgets(&user_input[0], sizeof(user_input), stdin);

    char *string_data;
    string_data = user_input;

    int i = 0;

    //while((*string_data) != '\0')
    while(user_input[i] != '\0')
    {
        printf("%c\n", user_input[i]);

        if((user_input[i]) == '1')
        {
            printf("comparison passed\n");
        }
        //printf("%s", string_data);
        //string_data++;
        i++;

        if((user_input[i]) == '\0')
        {
            printf("program exiting\n");
        }
    }
    //text_parse(&user_input[0]);

}

