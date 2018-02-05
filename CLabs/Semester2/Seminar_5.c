#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "inf_s.h"

typedef
    enum
    {
        OP_ADD,
        OP_MIN,
        OP_MULT,
        OP_DIV,
        B_OPEN,
        B_CLOSE,
        NO_SIGN
    }sign_t;

typedef
    enum
    {
        BRACKET,
        OPERATION,
        DIGIT,
        WRONG_TOKEN
    }token_t;

typedef
    struct TOKEN
    {
        sign_t sign;
        token_t type;
        int digit;
    }token;

typedef
    struct STACK
    {
        token data;
        struct STACK *next;
    }stack;

//the set of functions to work with stack

stack *init_stack()
{
    stack *new = (stack *)calloc(1,sizeof(stack));

    return new;
}

token pop(stack **target)
{
    if (*target == NULL)
    {
        return;
    }
    token result = (*target)->data;
    stack *next = (*target)->next;
    free(*target);
    (*target) = next;
    return result;
}

stack *push(token element,stack *target)
{
    stack *new = init_stack();
    new->next = target;
    new->data = element;
    return new;
}

char token_back(token target)
{
    if (OPERATION == target.type)
    {
        switch(target.sign)
        {
            case OP_ADD:
                return '+';
            case OP_MIN:
                return '-';
            case OP_MULT:
                return '*';
            case OP_DIV:
                return '/';
        }
    }
    else
    {
        switch(target.sign)
        {
            case B_OPEN:
                return '(';
            case B_CLOSE:
                return ')';
        }
        return -1;
    }
}

int make_op(int dig_1, int dig_2, int op)
{
    switch(op)
    {
        case OP_ADD:
            return dig_1 + dig_2;
        case OP_MULT:
            return dig_1 * dig_2;
        case OP_DIV:
            return dig_1 / dig_2;
        case OP_MIN:
            return dig_1 - dig_2;
    }
}


//frees all the stack until first "(" sign
int free_stack(stack **target_sign,stack **target_digit,int *result_prev, inf_s *res_str)
{
    int result = 0;
    while((*target_sign != NULL) && ((*target_sign)->data.sign != B_OPEN))
    {
        token current_token = pop(target_sign);
        char sign = token_back(current_token);
        if (sign == 0)
        {
            continue;
        }
        printf("%c ",sign);
        add(res_str,sign);
        add(res_str,' ');
        if (0 == result)
        {
            int digit_1 = (pop(target_digit)).digit;
            int digit_2 = (pop(target_digit)).digit;
            if ((0 == digit_1) && (OP_DIV == current_token.sign))
            {
                fprintf(stderr,"the answer is not correct, 0 found\n");
                return -1;
            }
            result = make_op(digit_2,digit_1,current_token.sign);
        }
        else
        {
            int digit = pop(target_digit).digit;
            result = make_op(result,digit,current_token.sign);
        }
    }
   
    
    return 0;
}

//prints all the stack
void printf_stack(const stack *target)
{
    while(target != NULL)
    {
        printf("%d ",target->data.sign);
        target = target->next;
    }
    printf("\n");
    return;
}

//working with token
//reads the token and gets its charachteristics, return pointer to the next char 
char *next_char(char *main_string,token *next)
{
    if (*main_string == '\0')
    {
        return main_string;
    }

    switch (*main_string)
    {
        case '+':
            next->type = OPERATION;
            next->sign = OP_ADD;
            next->digit = 0;
            break;
        case '-':
            next->type = OPERATION;
            next->sign = OP_MIN;
            next->digit = 0;
            break;
        case '*':
            next->type = OPERATION;
            next->sign = OP_MULT;
            next->digit = 0;
            break;
        case '/':
            next->type = OPERATION;
            next->sign = OP_DIV;
            next->digit = 0;
            break;
        case '(':
            next->type = BRACKET;
            next->sign = B_OPEN;
            next->digit = 0;
            break;
        case ')':
            next->type = BRACKET;
            next->sign = B_CLOSE;
            next->digit = 0;
            break;
        default:
            if ((*main_string <= '9') && (*main_string >= '0'))
            {
                next->type = DIGIT;
                next->digit = atoi(main_string);
                next->sign = NO_SIGN;
            }
            else
            {
                next->type = WRONG_TOKEN;
                next->digit = 0;
                next->sign = NO_SIGN;
            }
            break;
    }
    return ++main_string;
}

char *wait_for_right_sign(char *string,token *next_token ,token_t right_one)
{
    char *result = string;   
    token per_token = *next_token; 
    while (1)
    {
       
        result = next_char(result,&per_token);
    
        if (per_token.type == BRACKET)
        {
            *next_token = per_token;
            return result;
        }
        if (per_token.type == right_one)
        {
            *next_token = per_token;
            return result;
        }
        if (*result == '\0')
        {
            next_token->type = WRONG_TOKEN;
            next_token->sign = NO_SIGN;
            next_token->digit = 0;
            return result;
        }
    }
}


char *convert_to_RPN(char *string)
{
    if (((*string > '9') || (*string < '0')) && (*string != '('))
    {
        fprintf(stderr,"The string should start with digit or open bracket\n");
        return NULL;
    }
    char *current_c = string;
    int result = 0;
    inf_s result_string;
    init_s(&(result_string));
    sign_t current_sign = OP_DIV;
    token next_token = {.type = OPERATION, .sign = 0, .digit = 0};
    stack *stack_of_signes = NULL;
    stack *stack_of_digits = NULL;
    int undefined_sign = 0;
    token undef_token = {0};
    while (1)
    {
        if ((next_token.type == OPERATION) || (next_token.sign == B_OPEN))
        {
            current_c = wait_for_right_sign(current_c,&next_token,DIGIT);
            
            if (next_token.sign == B_CLOSE)
            {
                fprintf(stderr,"\nThe brackets are not set right\nCannot make the right answer\n");
                return NULL;
            }
        }
        else if ((next_token.type == DIGIT) || (next_token.sign == B_CLOSE))
        {
            current_c = wait_for_right_sign(current_c,&next_token,OPERATION);
            if (next_token.sign == B_OPEN)
            {
                fprintf(stderr,"\nThe brakcets are not set right\nCannot make the right answer\n");
                return NULL;
            }
        }

        if (DIGIT == next_token.type)
        {
            stack_of_digits = push(next_token,stack_of_digits);
            printf("%c ",*(current_c-1)); // print if it is digit
            add(&result_string,*(current_c-1));
            add(&result_string,' ');
        }
        else if (OPERATION == next_token.type)
        {
            if (undefined_sign)
            {
                if (next_token.sign < current_sign)
                {
                    stack_of_signes = push(next_token,stack_of_signes);
                    undefined_sign = 0;
                    continue;
                }
            }
            if (next_token.sign < current_sign)
            {
                int rc = free_stack(&stack_of_signes,&stack_of_digits,&result,&result_string);
                if (rc == -1)
                {
                    fprintf(stderr,"\nThe stack is not freed correctly\nThe answer is incorrect\n");
                    return NULL;
                }
            }
            stack_of_signes = push(next_token,stack_of_signes);
            current_sign = next_token.sign;
        }
        else if (BRACKET == next_token.type)
        {
            if (B_OPEN == next_token.sign)
            {
                stack_of_signes = push(next_token,stack_of_signes);
                current_sign = OP_DIV;
            }
            else
            {
                int rc = free_stack(&stack_of_signes,&stack_of_digits,&result,&result_string);
                if (rc == -1)
                {
                    fprintf(stderr,"\nThe stack is not freed correctly\nThe answer is incorrect\n");
                    return NULL;
                }
                undef_token = pop(&stack_of_signes);
                current_sign = undef_token.sign;
                undefined_sign = 1;
            }
        }
        if (*current_c == '\0')
        {
            break;
        }
    }
    int rc = free_stack(&stack_of_signes,&stack_of_digits,&result,&result_string);
    if (rc == -1)
    {
        return ;
    }
    printf("\n");
    add(&result_string,'\0');

    return result_string.s;
}

int get_result(char *answer)
{
    stack *stack_of_digits = NULL;
    token tmp = {0};
    token result = {.type = DIGIT, .sign = NO_SIGN, .digit = 0};
    while(*answer != '\0')
    {
        if ((*answer <= '9') && (*answer >= '0'))
        {
            tmp.type = DIGIT;
            tmp.sign = NO_SIGN;
            tmp.digit = atoi(answer);
            stack_of_digits = push(tmp,stack_of_digits);
        }
        else
        {
            int dig1 = (pop(&stack_of_digits)).digit;
            int dig2 = (pop(&stack_of_digits)).digit;
            switch(*answer)
            {
                case '+':
                    result.digit = dig1+dig2;
                    break;
                case '-':
                    result.digit = dig1-dig2;
                    break;
                case '*':
                    result.digit = dig1 * dig2;
                    break;
                case '/':
                    result.digit = dig1 / dig2;
                    break;
            }
            stack_of_digits = push(result,stack_of_digits);
        }
        answer += 2;
    }
    return (pop(&stack_of_digits)).digit;
}

int main()
{
    inf_s tmp_str;
    init_s(&tmp_str);
    get_inf_s_std(&tmp_str);
    char *string = tmp_str.s;
    char *answer = convert_to_RPN(string);
    if (answer == NULL)
    {
        return -1;
    }
    printf("%s\n",answer);

    int result = get_result(answer);
    printf("the result is : %d\n",result);
    free(answer);
    free(string);
    return 0;
}