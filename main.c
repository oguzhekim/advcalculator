#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"


int main(int argc, char const *argv[])
{
    int substrCount = 0;
    struct Token tokens[10];
    int tokenCount = 0;
    char line[257];
    printf("> ");
    while (fgets(line, sizeof(line), stdin)) {
        if (line==NULL) break;
        line[strcspn(line, "\n")] = 0;
        lexer(line, &tokenCount, tokens);
        printf("> ");        
    }
    
    return 0;
}