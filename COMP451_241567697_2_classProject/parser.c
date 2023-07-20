/*
PROJECT TASK - 2
COURSE CODE AND Section - COMP 451 - (B)
Group Members:
1. Junaid Imran - 241567697
2. Hassan Ali - 

*/



#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_VALUES 100
#define MAX_SIZE 200

#define SENTINEL '$'

// There are 6 tokens for which we need to check precedence.
// 0. id, 1. +, 2. -, 3. *, 4. /, 5. $. = 6 tokens
int prec_table[6][6] = {
    {-1, 1, 1, 1, 1, 1}, // id
    {0, 1, 1, 0, 0, 1},  // +
    {0, 1, 1, 0, 0, 1},  // -
    {0, 1, 1, 1, 1, 1},  // *
    {0, 1, 1, 1, 1, 1},  // '/'
    {0, 0, 0, 0, 0, -1}  // $
};

int operand(char c) {
    return (c >= 'a' && c <= 'z');
}

typedef struct {
    int data[MAX_SIZE];
    int top;
} IntStack;

typedef struct {
    char data[MAX_SIZE];
    int top;
} CharStack;

void initializeIntStack(IntStack* stack) {
    stack->top = -1;
}

int isIntStackEmpty(IntStack* stack) {
    return stack->top == -1;
}

int isIntStackFull(IntStack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void pushInt(IntStack* stack, int value) {
    if (isIntStackFull(stack)) {
        printf("Integer Stack overflow!\n");
        exit(1);
    }

    stack->top++;
    stack->data[stack->top] = value;
}

int peekInt(IntStack* stack) {
    if (isIntStackEmpty(stack)) {
        printf("Integer Stack is empty!\n");
        exit(1);
    }

    return stack->data[stack->top];
}

int popInt(IntStack* stack) {
    if (isIntStackEmpty(stack)) {
        printf("Integer Stack underflow!\n");
        exit(1);
    }

    int value = stack->data[stack->top];
    stack->top--;
    return value;
}

int getIntStackSize(IntStack* stack) {
    return stack->top + 1;
}

void initializeCharStack(CharStack* stack) {
    stack->top = -1;
}

int isCharStackEmpty(CharStack* stack) {
    return stack->top == -1;
}

int isCharStackFull(CharStack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void pushChar(CharStack* stack, char value) {
    if (isCharStackFull(stack)) {
        printf("Character Stack overflow!\n");
        exit(1);
    }

    stack->top++;
    stack->data[stack->top] = value;
}

char peekChar(CharStack* stack) {
    if (isCharStackEmpty(stack)) {
        printf("Character Stack is empty!\n");
        exit(1);
    }

    return stack->data[stack->top];
}

char popChar(CharStack* stack) {
    if (isCharStackEmpty(stack)) {
        printf("Character Stack underflow!\n");
        exit(1);
    }

    char value = stack->data[stack->top];
    stack->top--;
    return value;
}

void printCharStack(const CharStack* stack) {
    for (int i = stack->top; i >= 0; i--) {
        char element = stack->data[i];
        printf("%c", element);
    }
}

int getCharStackSize(CharStack* stack) {
    return stack->top + 1;
}

int getPrecedence(char element1, char element2) {
    int row, col;

    if (operand(element1)) {
        row = 0;
    } else if (element1 == '+') {
        row = 1;
    } else if (element1 == '-') {
        row = 2;
    } else if (element1 == '*') {
        row = 3;
    } else if (element1 == '/') {
        row = 4;
    } else if (element1 == '$') {
        row = 5;
    } else {
        return -1;
    }

    if (operand(element2)) {
        col = 0;
    } else if (element2 == '+') {
        col = 1;
    } else if (element2 == '-') {
        col = 2;
    } else if (element2 == '*') {
        col = 3;
    } else if (element2 == '/') {
        col = 4;
    } else if (element2 == '$') {
        col = 5;
    } else {
        return -1;
    }

    return prec_table[row][col];
}

void calculate(IntStack* stack2, char operator) {
    int operand2 = popInt(stack2);
    int operand1 = popInt(stack2);
    int result = 0;

    if (operator == '+') {
        result = operand1 + operand2;
    } else if (operator == '-') {
        result = operand1 - operand2;
    } else if (operator == '*') {
        result = operand1 * operand2;
    } else if (operator == '/') {
        if (operand2 == 0) {
            printf("Error: Division by zero!\n");
            exit(1);
        }
        result = operand1 / operand2;
    }

    pushInt(stack2, result);
}

void operatorPrecedenceParser(const char* expression, int* values, char* operands, int numValues) {
    CharStack stack1;	//This stack is the output stack
    IntStack stack2;	//This stack is for calculations ONLY
    
    initializeCharStack(&stack1);
    initializeIntStack(&stack2);

    pushChar(&stack1, '$'); //Stack1 has $

    int i = 0;
    char currentChar = expression[i];	//Get first input symbol
    char topOfStack = peekChar(&stack1);	//Check what is at top of stack
    int relation = getPrecedence(topOfStack, currentChar);	//Check precedence
    int var_number = 0;	//A variable that stores value of a variable.

    printf("Stack\t\t\tInput\t\t\tAction\n");
    printCharStack(&stack1);
    printf("\t\t\t%s\t\t\t\t\n", expression);

    int j = i;  // Declare and initialize j

     // Loop until the current character is not the sentinel character or the top of the stack is not the sentinel character
    while (currentChar != '$' || topOfStack != '$') {
        if (relation == 1) {
            topOfStack = popChar(&stack1); // Pop the top of the stack
            printCharStack(&stack1);
            printf("\t\t\t");

            for (j = i; j < strlen(expression); j++) {  // Use j in the loop
                printf("%c", expression[j]);

            }
            j--; //Get to the end of input string!
            printf("\t\t\tPop\n");

            if (operand(topOfStack)) {
                for (int k = 0; k < numValues; k++) {
                    if (topOfStack == operands[k]) {
                        var_number = values[k]; // Get the corresponding value for the operand
                    }
                }
                pushInt(&stack2, var_number); // Push the value to the stack
            } 

            else if (getIntStackSize(&stack2) >= 2) {
                calculate(&stack2, topOfStack); // Perform calculation for the operator
            }
        } 
        else if (relation == 0) {
            pushChar(&stack1, currentChar); // Push the current character to the stack
            i++;
            currentChar = expression[i];
            printCharStack(&stack1);
            printf("\t\t\t");

            for (j = i; j < strlen(expression); j++) {  // Use j in the loop
                printf("%c", expression[j]);
            }
            j--;//To get to the end of the input string '$'!
            printf("\t\t\tPush\n");
        }
        else {
            printf("Error: Invalid expression!\n");
            exit(1);
        }

        topOfStack = peekChar(&stack1);
        relation = getPrecedence(topOfStack, currentChar);
    }
    //Printing final state of state table!
    printCharStack(&stack1);
    printf("\t\t\t");

    //Checking that we've exhausted input string!
    if (expression[j] == '$') {  // Use j here as well
        printf("%c", expression[j]);
    }

    //Check that we're done processing input string and reached sentinel value.
    if (peekChar(&stack1) == '$' && expression[j] == '$') {
        printf("\t\t\tAccepted\n");
    } 

    //Otherwise arithmetic expression has error!
    else {
        printf("\t\t\tRejected\n");
    }

    printf("\nValue at top of stack in stack2 is %d\n", peekInt(&stack2)); // Print the final result
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("No command-line argument provided.\n");
        return 1;
    }

    int values[MAX_VALUES];
    char operands[MAX_VALUES];
    int j = 0;

    char* arithmetic_expr = argv[1];

    for (int i = 0; i < strlen(argv[1]); i++) {
        if (operand(argv[1][i])) {
            printf("\nValue of %c: ", argv[1][i]);
            operands[j] = argv[1][i];
            scanf("%d", &values[j]);
            j++;
        }
    }

    printf("\nValues in the array:\n");
    for (int i = 0; i < j; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    operatorPrecedenceParser(arithmetic_expr, values, operands, j);

    return 0;
}
