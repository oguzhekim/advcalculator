#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"
#include "lexer.h"
#include "stack.h"
#include "shunting.h"
#include "calculator.h"
#include "hashtable.h"

int main(int argc, char const *argv[])
{
    
    char **varList = malloc(sizeof(char)*130); // 130 max variables that is 19 chars long
    int varCount = 0;
    int *valueList = malloc(sizeof(int)*130);

    char line[257];
    printf("> ");
    while (fgets(line, sizeof(line), stdin)) {
        if (line==NULL) break;
        int tokenCount1 = 0;
        int tokenCount2 = 0;
        Token *infixTokens = malloc(sizeof(Token)*256);
        Token *postfixTokens = malloc(sizeof(Token)*256);
        line[strcspn(line, "\n")] = 0;
        lexer(line, &tokenCount1, infixTokens);
        stackNode* top = NULL;
        for (int i = 0; i < tokenCount1-1; i++)
        {   
            shunting(&infixTokens, &top, postfixTokens, &tokenCount2);
        }
        while (!isEmpty(top)){
            Token tk = pop(&top);
            *(postfixTokens+tokenCount2) = tk;
            tokenCount2++;
            printf("%s", tk);
        }
        printf("\n");
        for (int i = 0; i < tokenCount2; i++)
        {   
            printf("%s", *(postfixTokens+i));
        }
        printf("\n");
        printf("%d", evaluate(tokenCount2, postfixTokens, varList, &varCount, valueList));
        printf("> ");
    }    
    return 0;
}