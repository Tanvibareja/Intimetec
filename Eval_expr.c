#define MAX 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int Op_eval(int a, int b, char op) {
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

int op_Check(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int Exp_sol(char* expr) {
    int val[MAX], tp_val = -1;
    char ops[MAX], tp_op = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isspace(expr[i])) continue;

        if (op_Check(expr[i])) {
            while (tp_op >= 0 && (
                (expr[i] == '+' || expr[i] == '-') || 
                ((expr[i] == '*' || expr[i] == '/') && (ops[tp_op] == '*' || ops[tp_op] == '/'))
            )) {
                if (tp_val < 1) {
                    printf("Error occured : You have entered an invalid expression.\n");
                    exit(1);
                }
                int b = val[tp_val--];
                int a = val[tp_val--];
                val[++tp_val] = Op_eval(a, b, ops[tp_op--]);
            }
            ops[++tp_op] = expr[i];  
        } 
        else if (isdigit(expr[i])) {
            int num = 0;
            while (isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            val[++tp_val] = num;
        } 
        else {
            printf("Error occured : You have entered an invalid expression.\n");
            exit(1);
        }
    }

    while (tp_op >= 0) {
        if (tp_val < 1) {
            printf("Error occured : You have entered an invalid expression.\n");
            exit(1);
        }
        int b = val[tp_val--];
        int a = val[tp_val--];
        val[++tp_val] = Op_eval(a, b, ops[tp_op--]);
    }

    return val[tp_val];
}

int main() {
    char expression[MAX];
    printf("Enter the expression: ");
    fgets(expression, MAX, stdin);

    int result = Exp_sol(expression);

    printf("The result is : %d\n", result);

    return 0;
}
