#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "token.h"
#include "stack.h"
#include "variables.h"

long long evaluate (int count, Token *postfix, char **varList, int *varCount, long long *valueList, bool *error){
    if (count==0) return INT_MIN+1;
    // If there is an error issued before, exit the function.
    if (*error) return INT_MIN+1;
    stackNode* top = NULL;
    for (int i = 0; i < count; i++)
    {
        Token tk = *(postfix+i);
        // Unmatched left parenthesis. Postfix expression cannot contain parenthesis.
        if (tk.type == TOKEN_LP){
            *error = true;
            return INT_MIN+1;
        }
        // Push integers and variables to the stack.
        else if (tk.type == TOKEN_INT || tk.type == TOKEN_VARIABLE){
            top = push(tk, top);
            continue;
        }
        // If next token is the not function pop one element and evaluate.
        else if (tk.type == TOKEN_FUNC && strcmp(tk.value, "not")==0){
            free(tk.value);
            stackNode* node = pop(&top);
            long long fac;
            // If the popped token is variable get its value.
            if (node->tk.type == TOKEN_INT){
                fac = atoll(node->tk.value);
            }
            else {
                int index = search(varList, node->tk.value, *varCount);
                if (index==-1){
                    fac = 0;
                    *(valueList+*varCount) = 0;
                    addVar(varList, node->tk.value, varCount);
                }
                else {
                    fac = *(valueList+index);
                }
            }
            free(node->tk.value);
            free(node);
            long long num = ~fac;
            int length = snprintf( NULL, 0, "%lld", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%lld", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
            continue;
        }
        else if (tk.type == TOKEN_EQUAL){
            free(tk.value);
            stackNode* node2 = pop(&top);
            long long fac = atoll(node2->tk.value);
            free(node2->tk.value);
            free(node2);
            stackNode* node1 = pop(&top);
            char* var = node1->tk.value;
            free(node1);
            int index = search(varList, var, *varCount);
            // If variable not defined before, add it to varList and update its value.
            if (index == -1){ 
                *(valueList+*varCount) = fac;
                addVar(varList, var, varCount);
            }
            // If variable defined before update its value.
            else {
                *(valueList+index) = fac;
            }        
            return INT_MIN+1;
        }
        // For all other operations pop 2 elements from the stack and get their values if they are variables.
        stackNode* node2;
        stackNode* node1;
        // If there are not 2 elements in the stack. Give an error.
        if (!isEmpty(top) && top->next != NULL){
            node2 = pop(&top);
            node1 = pop(&top);
        }
        else{
            *error = true;
            return INT_MIN+1;
        }
        Token tk2 = node2->tk;
        Token tk1 = node1->tk;
        free(node2);
        free(node1);
        long long fac2;
        long long fac1;
        if (tk2.type == TOKEN_INT){
            fac2 = atoll(tk2.value);
        }
        else {
            int index = search(varList, tk2.value, *varCount);
            if (index==-1){
                fac2 = 0;
                *(valueList+*varCount) = 0;
                addVar(varList, tk2.value, varCount);
            }
            else {
                fac2 = *(valueList+index);
            }
        }
        if (tk1.type == TOKEN_INT){
            fac1 = atoll(tk1.value);
        }
        else {
            int index = search(varList, tk1.value, *varCount);
            if (index==-1){
                fac1 = 0;
                *(valueList+*varCount) = 0;
                addVar(varList, tk1.value, varCount);
            }
            else {
                fac1 = *(valueList+index);
            }
        }
        free(tk2.value);
        free(tk1.value);
        if (tk.type == TOKEN_ADD){            
            long long num = fac1+fac2;
            int length = snprintf( NULL, 0, "%lld", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%lld", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_SUB){
            long long num = fac1-fac2;
            int length = snprintf( NULL, 0, "%lld", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%lld", num );
            Token newtk = {str, TOKEN_INT};    
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_MUL){
            long long num = fac1*fac2;
            int length = snprintf( NULL, 0, "%lld", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%lld", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_AND){
            long long num = fac1&fac2;
            int length = snprintf( NULL, 0, "%lld", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%lld", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_OR){
            long long num = fac1|fac2;
            int length = snprintf( NULL, 0, "%lld", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%lld", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_FUNC){  
            if (strcmp(tk.value, "xor")==0){
                long long num = fac1^fac2;
                int length = snprintf( NULL, 0, "%lld", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%lld", num );
                Token newtk = {str, TOKEN_INT};
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "ls")==0){
                long long num = fac1<<fac2;
                int length = snprintf( NULL, 0, "%lld", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%lld", num );
                Token newtk = {str, TOKEN_INT};
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "rs")==0){
                long long num = fac1>>fac2;
                int length = snprintf( NULL, 0, "%lld", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%lld", num );
                Token newtk = {str, TOKEN_INT};
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "lr")==0){
                long long num = (fac1 << fac2 % (sizeof(long long)*CHAR_BIT))|(fac1 >> (sizeof(long long)*CHAR_BIT - fac2) % (sizeof(long long)*CHAR_BIT));
                int length = snprintf( NULL, 0, "%lld", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%lld", num );
                Token newtk = {str, TOKEN_INT};
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "rr")==0){
                long long num = (fac1 >> fac2 % (sizeof(long long)*CHAR_BIT))|(fac1 << (sizeof(long long)*CHAR_BIT - fac2) % (sizeof(long long)*CHAR_BIT));
                int length = snprintf( NULL, 0, "%lld", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%lld", num );
                Token newtk = {str, TOKEN_INT};
                top = push(newtk, top);
            }
        }
        free(tk.value);
    }

    Token tk = (*top).tk;
    long long res;
    if (tk.type == TOKEN_INT){
        res = atoll(tk.value);
    }
    // If the input is just a variable.
    else {
        int index = search(varList, tk.value, *varCount);
        if (index==-1){
            res = 0;
            *(valueList+*varCount) = 0;
            addVar(varList, tk.value, varCount);
        }
        else {
            res = *(valueList+index);
        }
    }    
    free(top->tk.value);
    free(top);
    return res;
}