#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "token.h"
#include "stack.h"

stackNode *newstackNode(Token tk)
{
    stackNode *node = malloc(sizeof(stackNode));
    node->tk = tk;
    node->next = NULL;
    return node;
}

void push(Token tk, stackNode **top)
{
    stackNode *node = newstackNode(tk);
    node->next = *top;
    *top = node;
    //printf("%s pushed to stack\n", (**pt).value);
    //(*pt)++;
}

Token pop(stackNode **top)
{
    // ADD ISEMPTY
    stackNode *node = *top;
    *top = (*top)->next;
    Token tk = node->tk;
    free(node);
    //printf("%s popped from stack\n", tk.value);
    return tk;
};

bool isEmpty(struct stackNode *top)
{
    return !top;
}