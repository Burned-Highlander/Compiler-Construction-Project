/*
PROJECT TASK - 1
COURSE CODE AND SECTION: COMP 451 - (B)
Group Members:
1. Junaid Imran - 241567697
2. Hassan Ali - 241564087
*/

#include <stdio.h>
//Sentinel value defined with macro head.
#define SENTINEL '$'
//defining max operand count 0--4.
#define MAX_OPERANDS 4

// Function to check if a token is an arithmetic operator
int Operator(char token) {
    return token == '+' || token == '-' || token == '*' || token == '/';
}

// Function to check if a token is a valid operand
int operand(char token) {
    return (token >= 'a' && token <= 'z');
}

int main(int argc, char *argv[]) {
    // Check the number of command line arguments
    if (argc != 2) {
        printf("Input needed on command line\n");
        return 1;
    }

    char *expression = argv[1];
    int operandCount = 0;

    printf("Expression received: %s\n", expression);

    // Process each character in the expression until sentinel symbol is encountered
    for (int i = 0; expression[i] != SENTINEL; i++) {
        char token = expression[i];

        if (Operator(token)) {
            // Token is an arithmetic operator
            printf("Arithmetic operator: %c\n", token);
        } else if (operand(token)) {
             if (operandCount > MAX_OPERANDS) {
                printf("Maximum number of operands exceeded.\n");
                return 1;
            // Token is a valid operand
             }
            printf("int literal found: %c\n", token);
            operandCount++;
        } else {
            // Invalid token encountered.
            printf("Invalid token encountered. Program terminated prematurely.\n");
            return 1;
        }
    }

    return 0;
}
