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

stackNode* push(Token tk, stackNode *top)
{
    stackNode *node = newstackNode(tk);
    node->next = top;
    top = node;
    return top;
}

stackNode* pop(stackNode **top)
{
    stackNode *node = *top;
    *top = (**top).next;
    return node;
};

bool isEmpty(struct stackNode *top)
{
    return !top;
}