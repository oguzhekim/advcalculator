
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "lexer.h"


bool isLParanthesis(char ch){
    if (ch=='(') return true;
    return false;
}

bool isRParanthesis(char ch){
    if (ch==')') return true;
    return false;
}

bool isOp(char ch){
    if (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='=' || ch=='&' || ch=='|') return true;
    return false;
}

bool isComment(char ch){
    if (ch=='%') return true;
    return false;
}

bool isFunction(char* ch){
    if (strcmp(ch, "xor")==0 || strcmp(ch, "ls")==0 || strcmp(ch, "rs")==0 || strcmp(ch, "lr")==0 || strcmp(ch, "rr")==0 || strcmp(ch, "not")==0) return true;
    return false;
}

bool isDelimiter(char ch){
    if (isRParanthesis(ch) || isLParanthesis(ch) || isOp(ch)  || isComment(ch)  || ch==' ' || ch=='\0' || ch==',') return true;
    return false;
}

bool isVariable(char* ch){
    for (int i=0; i<strlen(ch);i++){
        if (isalpha(*(ch+i))==0) return false;
    }
    return true;
}

bool isInteger(char* ch){
    for (int i=0; i<strlen(ch);i++){
        if (isdigit(*(ch+i))==0) return false;
    }
    return true;
}

void lexer(char* input, int* tokenCount, Token* tokens){
    int len = strlen(input);
    int left = 0;
    int right = 0;
    while (right<=len){ // TODO: && left<=right??
        if (!isDelimiter(input[right])){
            right++;
        }
        else if (isDelimiter(input[right]) && left==right){
            char current = input[right];
            if (current==' '){
                right++;
                left = right;
                continue;
            }
            Token tk;
            tk.value = malloc(2);
            tk.value[0] = input[right];
            tk.value[1] = '\0';
            if (isOp(current)){
                switch (current)
                {                
                case '+':
                    printf("'%c' IS A ADDITION\n", input[right]);
                    tk.type = TOKEN_ADD;
                    break;
                case '-':
                    printf("'%c' IS A SUBSTRACTION\n", input[right]);
                    tk.type = TOKEN_SUBS;
                    break;
                case '*':
                    printf("'%c' IS A MULTIPLICATION\n", input[right]);
                    tk.type = TOKEN_MUL;
                    break;
                case '/':
                    printf("'%c' IS A DIVISION\n", input[right]);
                    tk.type = TOKEN_DIV;
                    break;
                case '&':
                    printf("'%c' IS AND\n", input[right]);
                    tk.type = TOKEN_AND;
                    break;
                case '|':
                    printf("'%c' IS OR\n", input[right]);
                    tk.type = TOKEN_OR;
                    break;
                case '=':
                    printf("'%c' IS EQUAL\n", input[right]);
                    tk.type = TOKEN_EQUAL;
                    break;
                
                }
            }
            else if (current == ','){
                printf("'%c' IS A COMMA\n", input[right]);
                tk.type = TOKEN_COMMA;
            }
            else if (isComment(current)){
                printf("'%c' IS A COMMENT\n", input[right]);
                tk.type = TOKEN_COMMENT;
            }
            else if (isLParanthesis(current)){
                printf("'%c' IS A LPARANTHESIS\n", input[right]);
                tk.type = TOKEN_LP;
            }
            else if (isRParanthesis(current)){
                printf("'%c' IS A RPARANTHESIS\n", input[right]);
                tk.type = TOKEN_RP;                
            }
            *(tokens + *tokenCount) = tk;
            (*tokenCount)++;
            right++;
            left = right;
        }
        else if (isDelimiter(input[right]) && left != right){
            // Get the substring between two indices
            char substr[right-left+1]; //TODO: Check if changing to dynamic memory better
            for (int i = left; i < right; i++)
            {
                substr[i-left] = input[i];
            }
            substr[right-left] = '\0';

            if (isFunction(substr)){
                printf("'%s' IS A FUNCTION\n", substr);
                Token tk;
                tk.value = malloc(strlen(substr)+1);
                strcpy(tk.value, substr);
                tk.type = TOKEN_FUNC;
                *(tokens + *tokenCount) = tk;
                (*tokenCount)++;
            }
            else if (isInteger(substr))
            {
                printf("'%s' IS AN INTEGER\n", substr);
                Token tk;
                tk.value = malloc(strlen(substr)+1);
                strcpy(tk.value, substr);
                tk.type = TOKEN_INT;
                *(tokens + *tokenCount) = tk;
                (*tokenCount)++;
            }
            else if (isVariable(substr))
            {
                printf("'%s' IS A VARIABLE\n", substr);
                Token tk;
                tk.value = malloc(strlen(substr)+1);
                strcpy(tk.value, substr);
                tk.type = TOKEN_VARIABLE;
                *(tokens + *tokenCount) = tk;
                (*tokenCount)++;
            }
            else {
                printf("%s is invalid character\n", substr);
            }
            left = right;
        }
    }
}