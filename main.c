#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"
#include "ast.h"
#include "shuntingyard.h"


void traverse(Node* root){
    if (root!=NULL){
        traverse(root->right);
        traverse(root->left);        
        printf("%s ", root->tk.value);
    }
}
int calculate(Node* root){
    if (root!=NULL){
        if (root->tk.type == TOKEN_ADD) return calculate(root->left) + calculate(root->right);
        else if (root->tk.type == TOKEN_SUBS) return calculate(root->left) - calculate(root->right);
        else if (root->tk.type == TOKEN_MUL) return calculate(root->left) * calculate(root->right);
        else if (root->tk.type == TOKEN_DIV) return calculate(root->left) / calculate(root->right);
    }
    return atoi(root->tk.value);
}

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
        //traverse(root);
        printf("%d\n", calculate(root));
        //free(tokens);
        printf("> ");    
    }
    
    return 0;
}