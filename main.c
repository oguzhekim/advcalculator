#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
//#include "shuntingyard.h"
#include "shunting2.h"

int main(int argc, char const *argv[])
{        
    char line[257];
    printf("> ");
    while (fgets(line, sizeof(line), stdin)) {
        if (line==NULL) break;
        int tokenCount = 0;
        Token *tokens = malloc(sizeof(Token)*256);
        line[strcspn(line, "\n")] = 0;
        lexer(line, &tokenCount, tokens);
        stackNode* top = NULL;
        for (int i = 0; i < tokenCount-1; i++)
        {   
            shunting(&tokens, &top);
        }
        while (!isEmpty(top)){
            printf("%s", pop(&top));
        }
        printf("> ");
    }
    
    return 0;
}