#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int evaluateSingleOperation(int a, int b, char op) {  // This function evaluates a single operation like a+b
    switch (op)
    {
    case '+': return a+b;
        break;
    case '-': return a-b;
        break;
    case '*': return a*b;
        break;
    case '/': if (b == 0) {
            printf("Error: Division by zero.\n");
            exit(1);
        }
        return a / b;
        break;
    default: return 0;
        
    }
}

int isOperator(char ch) {                                         // Checks if a character from the string is an operator
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int solveCompleteExpression(char* expr) {
    int value_stack[MAX], value_stack_top = -1;
    char operator_stack[MAX], operator_stack_top = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) continue;


// if operator stack empty then push the operator into the operator stack

// if operator stack not empty and current operator is '+'or '-' then pop value stack -> pop operator -> perform operation -> push value and operator

/* if operator stack not empty and current operator is '*'or '/' check:
        if top of operator stack is '+' or '-' then push the operator in the operator stack
        
        else if top of operator stack is '*' or '/' then pop value stack -> pop operator -> perform operation -> push value and operator*/


        if (isOperator(expr[i])) {      
            while (operator_stack_top >= 0 && ((expr[i] == '+' || expr[i] == '-') || ((expr[i] == '*' || expr[i] == '/') && (operator_stack[operator_stack_top] == '*' || operator_stack[operator_stack_top] == '/')) )) {
                if (value_stack_top < 1) {
                    printf("Error: Invalid expression.\n");
                    exit(1);                                        
                }
                int b = value_stack[value_stack_top--];
                int a = value_stack[value_stack_top--];
                value_stack[++value_stack_top] = evaluateSingleOperation(a, b, operator_stack[operator_stack_top--]);
            }
            operator_stack[++operator_stack_top] = expr[i];  
        } 
        else if (isdigit(expr[i])) {
            int num = 0;

            // To consider a multidigit nnumber example - 586
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }

            i--;
            value_stack[++value_stack_top] = num;
        } 
        else {
            printf("Error: Invalid expression.\n");
            exit(1);
        }
    }

    while (operator_stack_top >= 0) {
        if (value_stack_top < 1) {
            printf("Error: Invalid expression.\n");
            exit(1);
        }
        int b = value_stack[value_stack_top--];
        int a = value_stack[value_stack_top--];
        value_stack[++value_stack_top] = evaluateSingleOperation(a, b, operator_stack[operator_stack_top--]);
    }

    return value_stack[value_stack_top];
}

int main() {
    char expression[MAX];
    printf("Enter the expression: ");
    scanf("%s", expression);

    int result = solveCompleteExpression(expression);

    printf("The result is : %d\n", result);

    return 0;
}
