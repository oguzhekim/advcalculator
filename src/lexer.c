#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
#include "lexer.h"

bool isOp(char ch){
    if (ch=='+' || ch=='-' || ch=='*' || ch=='=' || ch=='&' || ch=='|') return true;
    return false;
}

bool isFunction(char* ch){
    if (strcmp(ch, "xor")==0 || strcmp(ch, "ls")==0 || strcmp(ch, "rs")==0 || strcmp(ch, "lr")==0 || strcmp(ch, "rr")==0 || strcmp(ch, "not")==0) return true;
    return false;
}

bool isDelimiter(char ch){
    if (ch=='(' || ch==')' || isOp(ch)  || ch=='%'  || ch==' ' || ch=='\0' || ch==',') return true;
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

Token* lexer(char* input, int* tokenCount, bool *error){
    Token *tokens = malloc(sizeof(Token)*256);
    int len = strlen(input);
    int left = 0;
    int right = 0;
    // Two pointers to input string is defined as left and right.
    while (right<=len) {
        // If current character is not a delimiter, right pointer is incremented.
        if (!isDelimiter(input[right])){
            right++;
        }
        else if (isDelimiter(input[right]) && left==right){
            char current = input[right];
            if (current==' '){
                right++;
                left++;
                continue;
            }
            else if (current=='%'){
                return tokens;
            }
            else if (current=='\0'){
                return tokens;
            }
            Token tk;
            tk.value = malloc(2);
            tk.value[0] = input[right];
            tk.value[1] = '\0';
            if (isOp(current)){
                switch (current)
                {                
                case '+':
                    tk.type = TOKEN_ADD;
                    break;
                case '-':
                    tk.type = TOKEN_SUB;
                    break;
                case '*':
                    tk.type = TOKEN_MUL;
                    break;
                case '&':
                    tk.type = TOKEN_AND;
                    break;
                case '|':
                    tk.type = TOKEN_OR;
                    break;
                case '=':
                    tk.type = TOKEN_EQUAL;
                    break;                
                }
            }
            else if (current == ','){
                tk.type = TOKEN_COMMA;
            }
            else if (current == '('){
                tk.type = TOKEN_LP;
            }
            else if (current == ')'){
                tk.type = TOKEN_RP;                
            }
            *(tokens + *tokenCount) = tk;
            (*tokenCount)++;
            right++;
            left++;
        }
        // If current character is a delimiter and pointers are not equal, that means the string between two pointers must be captured
        // and used to decide whether the substring is a function, integer or variable.
        else if (isDelimiter(input[right]) && left != right){
            // Get the substring between two indices
            char *substr = malloc((right-left+1)*sizeof(char));
            for (int i = left; i < right; i++)
                *(substr+i-left) = input[i];            
            *(substr+right-left) = '\0';            

            if (isFunction(substr)){
                Token tk;
                tk.value = malloc(strlen(substr)+1);
                strcpy(tk.value, substr);
                tk.type = TOKEN_FUNC;
                *(tokens + *tokenCount) = tk;
                (*tokenCount)++;
            }
            else if (isInteger(substr))
            {
                Token tk;
                tk.value = malloc(strlen(substr)+1);
                strcpy(tk.value, substr);
                tk.type = TOKEN_INT;
                *(tokens + *tokenCount) = tk;
                (*tokenCount)++;
            }
            else if (isVariable(substr))
            {
                Token tk;
                tk.value = malloc(strlen(substr)+1);
                strcpy(tk.value, substr);
                tk.type = TOKEN_VARIABLE;
                *(tokens + *tokenCount) = tk;
                (*tokenCount)++;
            }            
            // Invalid character.
            else {
                free(substr);
                *error = true;
                break;
            }
            free(substr);      
            // After the decision pointers can be set equal.
            left = right;
        }
    }
    return tokens;
}