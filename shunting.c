#include <stdio.h>
#include <stdbool.h>
#include "token.h"
#include "stack.h"

bool isOperator(Token tk){
    int type = tk.type;
    if (type == TOKEN_ADD || type == TOKEN_MUL || type == TOKEN_DIV || type == TOKEN_SUBS || type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_EQUAL) return true;
    return false;
}

bool isOperand(Token tk){
    int type = tk.type;
    if (type == TOKEN_INT || type == TOKEN_VARIABLE) return true;
    return false;
}

int getPrecedence(Token tk){
    int type = tk.type;
    if (type==TOKEN_EQUAL) return 0;
    else if (type==TOKEN_ADD || type==TOKEN_SUBS) return 1;
    else if (type==TOKEN_DIV || type==TOKEN_MUL) return 2;
    else if (type==TOKEN_FUNC) return 3;
    return -1;
}

int shunting(Token **infix, stackNode **top, Token *postfix, int *tokenCount)
{
    Token nextToken = **infix;
    // If the incoming symbols is an operand, print it..
    if (isOperand(nextToken)){
        printf("%s", nextToken.value);
        *(postfix+*tokenCount) = nextToken;
        (*tokenCount)++;
        (*infix)++;
    }
    else if (nextToken.type == TOKEN_FUNC){
        push(**infix, top);
        (*infix)++;
    } 
    // If the incoming symbol is a left parenthesis, push it on the stack.
    else if (nextToken.type == TOKEN_LP) {
        push(**infix, top);
        (*infix)++;
    }
    // If the incoming symbol is a right parenthesis: discard the right parenthesis, pop and print the stack symbols until you see a left parenthesis. 
    // Pop the left parenthesis and discard it.
    else if (nextToken.type == TOKEN_RP){
        (*infix)++;
        Token tk = pop(top);
        while (tk.type!=TOKEN_LP){
            printf("%s", tk.value);
            *(postfix+*tokenCount) = tk;
            (*tokenCount)++;
            tk = pop(top);
        }
        // If function comes next in stack after left paranthesis, pop and print it.
        if (!isEmpty(*top) && (**top).tk.type == TOKEN_FUNC) {
            Token tk = pop(top);
            printf("%s", tk.value);
            *(postfix+*tokenCount) = tk;
            (*tokenCount)++;
        }
    }
    // If token is comma, pop until left paranthesis.
    else if (nextToken.type == TOKEN_COMMA){
        (*infix)++;
        Token tk = (**top).tk;
        while (tk.type!=TOKEN_LP){            
            tk = pop(top);
            printf("%s", tk.value);
            *(postfix+*tokenCount) = tk;
            (*tokenCount)++;
            tk = (**top).tk;
        }
        // If function comes next in stack after left paranthesis, pop and print it.
        if ((**top).tk.type == TOKEN_FUNC) {
            Token tk = pop(top);
            printf("%s", tk.value);
            *(postfix+*tokenCount) = tk;
            (*tokenCount)++;
        }
    }
    // If the incoming symbol is an operator and the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack.
    else if (isOperator(nextToken) && (isEmpty(*top) || (**top).tk.type == TOKEN_LP)) {
        push(**infix, top);
        (*infix)++;
    }
    // If the incoming symbol is an operator and has either higher precedence than the operator on the top of the stack, 
    // or has the same precedence as the operator on the top of the stack and is right associative -- push it on the stack.
    else if (isOperator(nextToken) && (getPrecedence(nextToken)>getPrecedence((**top).tk))) {
        push(**infix, top);
        (*infix)++;
    }
    // If the incoming symbol is an operator and has either lower precedence than the operator on the top of the stack, 
    // or has the same precedence as the operator on the top of the stack and is left associative -- continue to pop the stack until this is not true. 
    // Then, push the incoming operator.
    else if (isOperator(nextToken) && (getPrecedence(nextToken)<=getPrecedence((**top).tk))){
        int i = getPrecedence(nextToken);
        while (!isEmpty(*top) && i<=getPrecedence((**top).tk)){
            Token tk = pop(top);
            printf("%s", tk.value);
            *(postfix+*tokenCount) = tk;
            (*tokenCount)++;
        }
        push(**infix, top);
        (*infix)++;
    }
}