#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int precedence(char op) {
    if ( op == '-') return 1;
    if (op == '+' ) return 2;
    if (op == '*' ) return 3;
    if ( op == '/') return 4;
    return 0;
}


int apply_operation(int a, int b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) {
            printf("Error: Division by zero.\n");
            exit(0);
        }
        return a / b;
    }
    return 0;
}


int evaluate_expression(char* expression) {
    int values[100]; 
    int value_top = -1;
    char ops[100];   
    int ops_top = -1;

    for (int i = 0; expression[i]; i++) {
        if (isspace(expression[i])) continue;

       
        if (isdigit(expression[i])) {
            int value = 0;
            while (i < strlen(expression) && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            values[++value_top] = value;
            i--; 
        }
       
        else if (expression[i] == '(') {
            ops[++ops_top] = expression[i];
        }
       
        else if (expression[i] == ')') {
            while (ops_top >= 0 && ops[ops_top] != '(') {
                int b = values[value_top--];
                int a = values[value_top--];
                char op = ops[ops_top--];
                values[++value_top] = apply_operation(a, b, op);
            }
            ops_top--; 
        }
       
        else {
            while (ops_top >= 0 && precedence(ops[ops_top]) >= precedence(expression[i])) {
                int b = values[value_top--];
                int a = values[value_top--];
                char op = ops[ops_top--];
                values[++value_top] = apply_operation(a, b, op);
            }
            ops[++ops_top] = expression[i];
        }
    }

   
    while (ops_top >= 0) {
        int b = values[value_top--];
        int a = values[value_top--];
        char op = ops[ops_top--];
        values[++value_top] = apply_operation(a, b, op);
    }

    return values[0]; 
}

int main() {
    char expression[100];
    printf("Enter the expression: ");
    fgets(expression, 100, stdin);

    for (int i = 0; expression[i]; i++) {
        if (!isdigit(expression[i]) && !isspace(expression[i]) && expression[i] != '+' &&
            expression[i] != '-' && expression[i] != '*' && expression[i] != '/' &&
            expression[i] != '(' && expression[i] != ')') {
            printf("Error: Invalid expression.\n");
            return 0;
        }
    }

    
    int result = evaluate_expression(expression);
    printf("Result: %d\n", result);

    return 0;
}
