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
    stackNode* top = NULL;
    for (int i = 0; i < count; i++)
    {
        Token tk = *(postfix+i);
        if (tk.type == TOKEN_INT || tk.type == TOKEN_VARIABLE){
            top = push(tk, top);
            continue;
        } 
        else if (tk.type == TOKEN_FUNC && strcmp(tk.value, "not")==0){
            int fac = atoi(pop(&top)->tk.value);
            int num = ~fac;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};
            free(str);
            top = push(newtk, top);
            
        }
        else if (tk.type == TOKEN_EQUAL){
            int fac = atoi(pop(&top)->tk.value);
            char* var = pop(&top)->tk.value;
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
        Token tk2 = pop(&top)->tk;
        Token tk1 = pop(&top)->tk;
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
                fac2 = *(valueList+*varCount);
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
        if (tk.type == TOKEN_ADD){            
            int num = fac1+fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};
            free(str);
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_SUBS){
            int num = fac1-fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};    
            free(str);        
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_MUL){
            int num = fac1*fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};     
            free(str);       
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_DIV){
            int num = fac1/fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};           
            free(str); 
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_AND){
            int num = fac1&fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};      
            free(str);      
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_OR){
            int num = fac1|fac2;
            int length = snprintf( NULL, 0, "%d", num );
            char* str = malloc( length + 1 );
            snprintf( str, length + 1, "%d", num );
            Token newtk = {str, TOKEN_INT};       
            free(str);     
            top = push(newtk, top);
        }
        else if (tk.type == TOKEN_FUNC){  
            if (strcmp(tk.value, "xor")==0){
                int num = fac1^fac2;
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};      
                free(str);      
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "ls")==0){
                int num = fac1<<fac2;
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};          
                free(str);  
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "rs")==0){
                int num = fac1>>fac2;
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};      
                free(str);      
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "lr")==0){
                int num = (fac1 << fac2)|(fac1 >> (sizeof(int)*CHAR_BIT - fac2));
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};         
                free(str);   
                top = push(newtk, top);
            }
            else if (strcmp(tk.value, "rr")==0){
                int num = (fac1 >> fac2)|(fac1 << (sizeof(int)*CHAR_BIT - fac2));
                int length = snprintf( NULL, 0, "%d", num );
                char* str = malloc( length + 1 );
                snprintf( str, length + 1, "%d", num );
                Token newtk = {str, TOKEN_INT};            
                free(str);
                top = push(newtk, top);
            }
        }    
    }
    return atoi((*top).tk.value);
}