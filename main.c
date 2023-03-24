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
#include "hashtable.h"
#include "validator.h"

int main(int argc, char const *argv[])
{
    
    char **varList = malloc(sizeof(char)*130); // 130 max variables that is 19 chars long
    int varCount = 0;
    int *valueList = malloc(sizeof(int)*130);
    char line[257];
    printf("> ");

    while (fgets(line, sizeof(line), stdin)) {
        if (line==NULL) break;
        bool error = false;
        int tokenCount = 0;
        int newTokenCount = 0; // Number of tokens in postfix expression. It might be different than the infix expression because it doesn't contain any paranthesis.
        line[strcspn(line, "\n")] = 0;
        Token *infixTokens = lexer(line, &tokenCount, &error);
        validate(&error, infixTokens, tokenCount);
        Token *postfixTokens = NULL;
        if (!error) postfixTokens = shunting(infixTokens, tokenCount, &newTokenCount, &error);
        // Shunting function can change the state of error.
        if (!error){
            int res = evaluate(newTokenCount, postfixTokens, varList, &varCount, valueList, &error);
            if (res != INT_MIN) printf("%d\n", res);            
        }
        if (error) printf("Error!\n");
        free(postfixTokens);        
        free(infixTokens);        
        printf("> ");
    }
    free(varList);
    free(valueList);
    return 0;
}