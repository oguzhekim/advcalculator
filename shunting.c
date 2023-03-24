#include <stdio.h>
#include <stdlib.h>
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

//TODO: & | precedence ???????????
int getPrecedence(Token tk){
    int type = tk.type;
    if (type==TOKEN_EQUAL) return 0;
    else if (type==TOKEN_AND || type==TOKEN_OR) return 1;
    else if (type==TOKEN_ADD || type==TOKEN_SUBS) return 2;
    else if (type==TOKEN_DIV || type==TOKEN_MUL) return 3;
    else if (type==TOKEN_FUNC) return 4;
    return -1;
}

Token* shunting(Token *infix, int tokenCount, int *newTokenCount, bool *error)
{   
    Token *postfixTokens = malloc(sizeof(Token)*256);
    stackNode* top = NULL;
    for (int i = 0; i < tokenCount; i++){
        Token currentToken = *(infix+i);
        // If the incoming symbols is an operand, print it..
        if (isOperand(currentToken)){
            //printf("%s", currentToken.value);
            *(postfixTokens+(*newTokenCount)) = currentToken;
            (*newTokenCount)++;
        }
        else if (currentToken.type == TOKEN_FUNC){
            top = push(currentToken, top);
        } 
        // If the incoming symbol is a left parenthesis, push it on the stack.
        else if (currentToken.type == TOKEN_LP) {
            top = push(currentToken, top);
        }
        // If the incoming symbol is a right parenthesis: discard the right parenthesis, pop and print the stack symbols until you see a left parenthesis. 
        // Pop the left parenthesis and discard it.
        else if (currentToken.type == TOKEN_RP){            
            // Unmatched right paranthesis.
            if (isEmpty(top)){
                *error = true;
                return postfixTokens;
            }
            Token tk = pop(&top)->tk;
            while (tk.type!=TOKEN_LP){
                //printf("%s", tk.value);
                *(postfixTokens+(*newTokenCount)) = tk;
                (*newTokenCount)++;
                tk = pop(&top)->tk;
            }
            // If function comes next in stack after left paranthesis, pop and print it.
            if (!isEmpty(top) && (*top).tk.type == TOKEN_FUNC) {
                tk = pop(&top)->tk;
                //printf("%s", tk.value);
                *(postfixTokens+(*newTokenCount)) = tk;
                (*newTokenCount)++;
            }
        }
        // If token is comma, pop until left paranthesis.
        else if (currentToken.type == TOKEN_COMMA){
            Token tk = (*top).tk;
            while (tk.type!=TOKEN_LP){            
                tk = pop(&top)->tk;
                //printf("%s", tk.value);
                *(postfixTokens+(*newTokenCount)) = tk;
                (*newTokenCount)++;
                tk = (*top).tk;
            }
            // If function comes next in stack after left paranthesis, pop and print it.
            if ((*top).tk.type == TOKEN_FUNC) {
                tk = pop(&top)->tk;
                //printf("%s", tk.value);
                *(postfixTokens+(*newTokenCount)) = tk;
                (*newTokenCount)++;
            }
        }
        // If the incoming symbol is an operator and the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack.
        else if (isOperator(currentToken) && (isEmpty(top) || (*top).tk.type == TOKEN_LP)) {
            top = push(currentToken, top);
        }
        // If the incoming symbol is an operator and has either higher precedence than the operator on the top of the stack, 
        // or has the same precedence as the operator on the top of the stack and is right associative -- push it on the stack.
        else if (isOperator(currentToken) && (getPrecedence(currentToken)>getPrecedence((*top).tk))) {
            top = push(currentToken, top);
        }
        // If the incoming symbol is an operator and has either lower precedence than the operator on the top of the stack, 
        // or has the same precedence as the operator on the top of the stack and is left associative -- continue to pop the stack until this is not true. 
        // Then, push the incoming operator.
        else if (isOperator(currentToken) && (getPrecedence(currentToken)<=getPrecedence((*top).tk))){
            int i = getPrecedence(currentToken);
            while (!isEmpty(top) && i<=getPrecedence((*top).tk)){
                Token tk = pop(&top)->tk;
                //printf("%s", tk.value);
                *(postfixTokens+(*newTokenCount)) = tk;
                (*newTokenCount)++;
            }
            top = push(currentToken, top);
        }
    }
    while (!isEmpty(top)){
        stackNode* node = pop(&top);
        Token tk = node->tk;
        free(node);
        *(postfixTokens+(*newTokenCount)) = tk;
        (*newTokenCount)++;
        //printf("%s", tk);
    }
    return postfixTokens;
}