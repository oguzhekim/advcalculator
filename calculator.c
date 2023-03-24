#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "token.h"
#include "stack.h"
#include "hashtable.h"

int evaluate (int count, Token *postfix, char **varList, int *varCount, int *valueList){
    if (count==0) return INT_MIN;
    stackNode* top = NULL;
    for (int i = 0; i < count; i++)
    {
        Token tk = *(postfix+i);
        if (tk.type == TOKEN_INT || tk.type == TOKEN_VARIABLE){
            top = push(tk, top);
            continue;
        }
        else if (tk.type == TOKEN_FUNC && strcmp(tk.value, "not")==0){
            free(tk.value);
            stackNode* node = pop(&top);
            int fac = atoi(node->tk.value);
            free(node->tk.value);
            free(node);            
            int num = ~fac;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
            continue;
        }
        else if (tk.type == TOKEN_EQUAL){
            free(tk.value);
            stackNode* node2 = pop(&top);
            int fac = atoi(node2->tk.value);
            free(node2->tk.value);
            free(node2);
            stackNode* node1 = pop(&top);
            char* var = node1->tk.value;
            //free(node1->tk.value);
            free(node1);
            int index = search(varList, var, *varCount);
            if (index == -1){ //var not defined before
                *(valueList+*varCount) = fac;
                addVar(varList, var, varCount);
            }
            else {
                *(valueList+index) = fac;
            }
            return INT_MIN;
        }
        stackNode* node2 = pop(&top);
        stackNode* node1 = pop(&top);
        Token tk2 = node2->tk;
        Token tk1 = node1->tk;
        free(node2);
        free(node1);
        int fac2;
        int fac1;
        if (tk2.type == TOKEN_INT){
            fac2 = atoi(tk2.value);
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
            fac1 = atoi(tk1.value);
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
            int num = fac1+fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_SUBS){
            int num = fac1-fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};    
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_MUL){
            int num = fac1*fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_DIV){
            int num = fac1/fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_AND){
            int num = fac1&fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_OR){
            int num = fac1|fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_FUNC){  
            if (strcmp(tk.value, "xor")==0){
                int num = fac1^fac2;
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "ls")==0){
                int num = fac1<<fac2;
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "rs")==0){
                int num = fac1>>fac2;
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "lr")==0){
                int num = (fac1 << fac2)|(fac1 >> (sizeof(int)*CHAR_BIT - fac2));
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "rr")==0){
                int num = (fac1 >> fac2)|(fac1 << (sizeof(int)*CHAR_BIT - fac2));
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};
                top = push(newtk, top);
            }
        }
        free(tk.value);
    }
    int res = atoi((*top).tk.value);
    free(top->tk.value);
    free(top);
    return res;
}