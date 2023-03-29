#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"
#include "stack.h"

bool isOperator(Token tk){
    int type = tk.type;
    if (type == TOKEN_ADD || type == TOKEN_MUL || type == TOKEN_SUB || type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_EQUAL) return true;
    return false;
}

int getPrecedence(Token tk){
    int type = tk.type;
    if (type==TOKEN_EQUAL) return 0;
    else if (type==TOKEN_AND || type==TOKEN_OR) return 1;
    else if (type==TOKEN_ADD || type==TOKEN_SUB) return 2;
    else if (type==TOKEN_MUL) return 3;
    return -1;
}

Token* shunting(Token *infix, int tokenCount, int *newTokenCount, bool *error)
{   
    // If there is an error issued before exit the function.
    if (*error) return NULL;
    Token *postfixTokens = malloc(sizeof(Token)*256);
    stackNode* top = NULL;
    for (int i = 0; i < tokenCount; i++){
        Token currentToken = *(infix+i);
        // If the incoming token is an operand (integer or variable), add it to output.
        if (currentToken.type == TOKEN_VARIABLE || currentToken.type == TOKEN_INT){
            *(postfixTokens+(*newTokenCount)) = currentToken;
            (*newTokenCount)++;
        }
        // If the incoming token is a function or left parenthesis, push it to the stack.
        else if (currentToken.type == TOKEN_FUNC || currentToken.type == TOKEN_LP){
            top = push(currentToken, top);
        }
        // If the incoming token is a right parenthesis: discard the right parenthesis, pop and output the stack symbols until you see a left parenthesis. 
        // Pop the left parenthesis and discard it.
        else if (currentToken.type == TOKEN_RP){
            free(currentToken.value);
            // If the stack is empty give an error (unmatched right parenthesis).
            if (isEmpty(top)){
                *error = true;
                return postfixTokens;
            }
            stackNode* node = pop(&top);
            Token tk = node->tk;
            free(node);
            while (tk.type!=TOKEN_LP){
                *(postfixTokens+(*newTokenCount)) = tk;
                (*newTokenCount)++;
                stackNode* node = pop(&top);
                tk = node->tk;
                free(node);
            }
            free(tk.value);
            // If function comes next in stack after left parenthesis, pop and output it.
            if (!isEmpty(top) && (*top).tk.type == TOKEN_FUNC) {
                stackNode* node = pop(&top);
                tk = node->tk;
                free(node);
                *(postfixTokens+(*newTokenCount)) = tk;
                (*newTokenCount)++;
            }
        }
        // If the incoming token is comma, pop until left parenthesis (excluding left parenthesis).
        else if (currentToken.type == TOKEN_COMMA){
            free(currentToken.value);
            Token tk = (*top).tk;
            while (tk.type!=TOKEN_LP){            
                stackNode* node = pop(&top);
                tk = node->tk;
                free(node);
                *(postfixTokens+(*newTokenCount)) = tk;
                (*newTokenCount)++;
                tk = (*top).tk;
            }
        }
        // If the incoming token is an operator and the stack is empty or contains a left parenthesis on top, push it to the stack.
        else if (isOperator(currentToken) && (isEmpty(top) || (*top).tk.type == TOKEN_LP)) {
            top = push(currentToken, top);
        }
        // If the incoming token is an operator and has higher precedence than the operator on top of the stack, push it to the stack.
        else if (isOperator(currentToken) && (getPrecedence(currentToken)>getPrecedence((*top).tk))) {
            top = push(currentToken, top);
        }
        //If the incoming token is an operator and has lower or same precedence as the operator on top of the stack,
        // pop the stack and add popped tokens to the output until this is not true. Then push the incoming operator.
        else if (isOperator(currentToken) && (getPrecedence(currentToken)<=getPrecedence((*top).tk))){
            int i = getPrecedence(currentToken);
            while (!isEmpty(top) && i<=getPrecedence((*top).tk)){
                stackNode* node = pop(&top);
                Token tk = node->tk;
                free(node);
                *(postfixTokens+(*newTokenCount)) = tk;
                (*newTokenCount)++;
            }
            top = push(currentToken, top);
        }
    }
    // If all the tokens are processed and stack is not empty, pop and output the stack until it is empty. 
    while (!isEmpty(top)){
        stackNode* node = pop(&top);
        Token tk = node->tk;
        free(node);
        *(postfixTokens+(*newTokenCount)) = tk;
        (*newTokenCount)++;
    }
    return postfixTokens;
}