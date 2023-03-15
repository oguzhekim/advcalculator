#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lexer.h"


int main(int argc, char const *argv[])
{
    struct Token myToken = {TOKEN_COMMENT, "123"};
    
    printf("My type is %d\n", myToken.type);
    printf("%s\n", myToken.value);

    return 0;
}