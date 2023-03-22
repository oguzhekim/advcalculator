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
        int tokenCount = 0;  
        line[strcspn(line, "\n")] = 0;
        Token *infixTokens = lexer(line, &tokenCount);
        Token *postfixTokens = shunting(infixTokens, tokenCount);
        printf("%d", evaluate(tokenCount, postfixTokens, varList, &varCount, valueList));
        free(infixTokens);
        free(postfixTokens);
        printf("> ");
    }
    free(varList);
    free(valueList);
    return 0;
}