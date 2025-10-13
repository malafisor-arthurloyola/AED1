#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1001

char stack[MAX_SIZE];
int top = -1;

int is_empty() {
    return top == -1;
}

void push(char item) {
    top++;
    stack[top] = item;
}

char pop() {
    if (is_empty()) {
        return '\0'; 
    }
    top--;
    return 1;
}

int main() {
    char expr[MAX_SIZE];
    
    while (fgets(expr, MAX_SIZE, stdin) != NULL) {
        top = -1; 
        int correto = 1;

        for (int i = 0; expr[i] != '\0' && expr[i] != '\n'; i++) {
            char current_char = expr[i];

            if (current_char == '(') {
                push(current_char);
            } 
            
            else if (current_char == ')') {
                if (is_empty()) {
                    correto = 0;
                    break; 
                }
                
                pop();
            }
        }

        if (correto && is_empty()) {
            printf("correct\n");
        } else {
            printf("incorrect\n");
        }
    }

    return 0;
}