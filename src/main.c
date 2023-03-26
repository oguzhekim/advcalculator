#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "token.h"
#include "lexer.h"
#include "stack.h"
#include "shunting.h"
#include "calculator.h"
#include "variables.h"
#include "validator.h"

int main(int argc, char const *argv[])
{
    
    char **varList = malloc(sizeof(char)*130);
    int varCount = 0;
    long long *valueList = malloc(sizeof(long long)*130);
    char line[257];
    printf("%% ./advcalc\n");
    printf("> ");

    while (fgets(line, sizeof(line), stdin)) {
        if (line==NULL) break;
        bool error = false;
        int tokenCount = 0;
        // Number of tokens in postfix expression. It might be different than the infix expression because it doesn't contain any parenthesis.
        int newTokenCount = 0; 
        line[strcspn(line, "\n")] = 0;
        Token *infixTokens = lexer(line, &tokenCount, &error);
        validate(&error, infixTokens, tokenCount);
        Token *postfixTokens = shunting(infixTokens, tokenCount, &newTokenCount, &error);
        long long res = evaluate(newTokenCount, postfixTokens, varList, &varCount, valueList, &error);
        if (res != INT_MIN+1) printf("%lld\n", res);
        if (error) printf("Error!\n");
        free(postfixTokens);        
        free(infixTokens);        
        printf("> ");
    }
    
    printf("\n%%\n");
    free(varList);
    free(valueList);
    return 0;
}