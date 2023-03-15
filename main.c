#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"


int main(int argc, char const *argv[])
{
    
    /*for (int i=0; i<20; i++){
        printf("%s", *(tokens+i));
    }*/
        
    char line[257];
    printf("> ");
    while (fgets(line, sizeof(line), stdin)) {
        if (line==NULL) break;
        int tokenCount = 0;
        Token* tokens = malloc(sizeof(Token)*256);
        line[strcspn(line, "\n")] = 0;
        lexer(line, &tokenCount, tokens);
        for (int i = 0; i < tokenCount-1; i++)
        {
            printf("%s\n", (*(tokens + i)).value);
        }
        free(tokens);
        printf("> ");    
    }
    
    return 0;
}