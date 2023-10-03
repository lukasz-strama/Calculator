#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_INPUT_LENGTH 100

// Function to get user input for the mathematical expression
char* stringProvider(char* expression);

// Function to check if a character is an operator (+, -, *, /)
bool isOperator(char c);

// Function to validate if the expression contains valid characters and format
bool isValidExpression(const char* expression);

// Function to perform mathematical operations (+, -, *, /)
double performOperation(double operand1, double operand2, char operator);

// Function to evaluate a mathematical expression and return the result
double evaluateExpression(const char* expression);

int main() {
    bool process = true;

    while (process) {
        char expression[MAX_INPUT_LENGTH];

        printf("\n[Provide mathematical expression]: ");

        // Input validation loop: ensures a valid expression is provided
        while (1) {
            stringProvider(expression);
            if (strcmp(expression, "exit") == 0) {
                process = false; // Exit the program if the user enters "exit"
                break; // Break out of the inner loop
            } else if (isValidExpression(expression)) {
                break;
            } else {
                printf("Invalid expression. Please try again: ");
            }
        }

        if (strcmp(expression, "exit") == 0) {
            process = false;
        } else {
            double result = evaluateExpression(expression);
            printf("Result: %lf\n", result);
        }
    }

    return 0;
}

char* stringProvider(char* expression) {
    do {
        // Read the entire line of input, including spaces
        fgets(expression, MAX_INPUT_LENGTH, stdin);

        // Remove the trailing newline character, if present
        size_t len = strlen(expression);
        if (len > 0 && expression[len - 1] == '\n') {
            expression[len - 1] = '\0';
        }

        if (strlen(expression) == 0) {
            printf("Input cannot be empty. Please try again: ");
        }
    } while (strlen(expression) == 0);

    return expression;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool isValidExpression(const char* expression) {
    int i = 0;
    for (i; expression[i] != '\0'; i++) {
        // Validate that the expression contains valid characters (digits, operators, and spaces)
        if (!isdigit(expression[i]) && !isOperator(expression[i]) && !isspace(expression[i])) {
            return false;
        }
    }
    return true;
}

double evaluateExpression(const char* expression) {
    double result = 0.0;
    double currentOperand = 0.0;
    char currentOperator = '+';

    int i = 0;
    while (expression[i] != '\0') {
        char currentChar = expression[i];
        
        if (isdigit(currentChar) || (currentChar == '.' && isdigit(expression[i + 1]))) {
            char* endptr;
            currentOperand = strtod(&expression[i], &endptr);
            i += endptr - &expression[i] - 1;
        } else if (isOperator(currentChar)) {
            result = performOperation(result, currentOperand, currentOperator);
            currentOperand = 0.0;
            currentOperator = currentChar;
        }

        i++;
    }

    result = performOperation(result, currentOperand, currentOperator);

    return result;
}

// Function to perform the actual calculation
double performOperation(double operand1, double operand2, char operator) {
    switch (operator) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) {
                return operand1 / operand2;
            } else {
                printf("Error: Division by zero.\n");
                exit(1); // Exit the program with an error code
            }
        default:
            printf("Error: Unknown operator.\n");
            exit(1); // Exit the program with an error code
    }
}

