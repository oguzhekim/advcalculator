#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"
#include "shunting.h"

void validate(bool *error, Token *infixTokens, int tokenCount){
    if (*error) return; //Invalid character. This is checked in lexer.
    for (int i = 0; i < tokenCount; i++)
    {
        Token currentToken = *(infixTokens+i);
        int type = currentToken.type;
        // First token can be integer, variable, function or left paranthesis.
        if (i==0 && type != TOKEN_INT && type != TOKEN_VARIABLE && type != TOKEN_FUNC && type != TOKEN_LP){
                *error=true;
                return;
        }
        // Last token can be integer, variable or right paranthesis.
        else if (i==tokenCount-1 && type != TOKEN_INT && type != TOKEN_VARIABLE && type != TOKEN_RP){
                *error=true;
                return;
        }
        else if (type == TOKEN_EQUAL){
            // Equal sign is in the wrong place.
            if (i!=1){
                *error=true;
                return;
            }
            // Equal sign is in the right place but previous token is non-variable.
            else if ((infixTokens+i-1)->type != TOKEN_VARIABLE){
                *error=true;
                return;
            }
        }
        else if (type == TOKEN_COMMA || isOperator(currentToken)){
            Token next = *(infixTokens+i+1);
            Token prev = *(infixTokens+i-1);
            // Token after the comma or operator can be integer, variable, function or left paranthesis.
            // Token before the comma or operator can be integer, variable or right paranthesis.
            if ((prev.type != TOKEN_VARIABLE && prev.type != TOKEN_INT && prev.type != TOKEN_RP) || (next.type != TOKEN_VARIABLE && next.type != TOKEN_INT && next.type != TOKEN_LP && next.type != TOKEN_FUNC)){
                *error=true;
                return;
            }
        }
        else if (type == TOKEN_FUNC){
            Token next = *(infixTokens+i+1);            
            // Token after the function must be left paranthesis.
            if (next.type != TOKEN_LP){
                *error=true;
                return;
            }
            else if (i!=0){
                Token prev = *(infixTokens+i-1);
                // Token before the function can be operator, comma or left paranthesis .
                if (!isOperator(prev) && prev.type != TOKEN_COMMA && prev.type != TOKEN_LP){
                    *error=true;
                    return;
                }
            }
        }
        else if (type == TOKEN_INT || type == TOKEN_VARIABLE){                        
            // Token after the integer or variable cannot be integer, variable, function or left paranthesis.
            if (i != tokenCount-1){
                Token next = *(infixTokens+i+1);
                if (next.type == TOKEN_INT || next.type == TOKEN_VARIABLE || next.type == TOKEN_FUNC || next.type == TOKEN_LP){
                    *error=true;
                    return;
                }
            }
            // Token before the integer or variable cannot be integer, variable, function or right paranthesis.
            else if (i!=0){
                Token prev = *(infixTokens+i-1);
                // TODO: I can remove int and var check since (probably function too) i checked it above.
                if (prev.type == TOKEN_INT || prev.type == TOKEN_VARIABLE || prev.type == TOKEN_FUNC ||prev.type == TOKEN_RP){
                    *error=true;
                    return;
                }
            }
        }
        // Check for empty paranthesis.
        else if (type == TOKEN_LP && (infixTokens+i+1)->type == TOKEN_RP){
            *error=true;
            return;
        }
    }
}