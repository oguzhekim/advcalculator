#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "ast.h"


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
        Node *root = parseExpr(&tokens);
        //free(tokens);
        printf("> ");    
    }
    
    return 0;
}