typedef struct stackNode
{
    Token tk;
    struct stackNode *next;
} stackNode;


bool isEmpty(struct stackNode *top)
{
    return !top;
}

stackNode *newstackNode(Token tk)
{
    stackNode *node = malloc(sizeof(stackNode));
    node->tk = tk;
    node->next = NULL;
    return node;
}

void push(Token **pt, stackNode **top)
{
    stackNode *node = newstackNode(**pt);
    node->next = *top;
    *top = node;
    //printf("%s pushed to stack\n", (**pt).value);
    (*pt)++;
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

bool isOperator(Token tk){
    int type = tk.type;
    if (type == TOKEN_ADD || type == TOKEN_MUL || type == TOKEN_DIV || type == TOKEN_SUBS || type == TOKEN_AND || type == TOKEN_OR) return true;
    return false;
}

bool isOperand(Token tk){
    int type = tk.type;
    if (type == TOKEN_INT || type == TOKEN_VARIABLE) return true;
    return false;
}

int getPrecedence(Token tk){
    int type = tk.type;
    if (type==TOKEN_ADD || type==TOKEN_SUBS) return 1;
    else if (type==TOKEN_DIV || type==TOKEN_MUL) return 2;
    else if (type==TOKEN_FUNC) return 3;
    return -1;
}


int shunting( Token **pt, stackNode **top)
{
    Token nextToken = **pt;
    // If the incoming symbols is an operand, print it..
    if (isOperand(nextToken)){
        printf("%s", nextToken.value);
        (*pt)++;
    } 
    else if (nextToken.type == TOKEN_FUNC) push(pt, top);
    // If the incoming symbol is a left parenthesis, push it on the stack.
    else if (nextToken.type == TOKEN_LP) push(pt, top);
    // If the incoming symbol is a right parenthesis: discard the right parenthesis, pop and print the stack symbols until you see a left parenthesis. 
    // Pop the left parenthesis and discard it.
    // If there is a function on top pop and print it.
    else if (nextToken.type == TOKEN_RP){
        (*pt)++;
        Token tk = pop(top);
        while (tk.type!=TOKEN_LP){
            printf("%s", tk.value);
            tk = pop(top);
        }
        // If function comes next in stack after left paranthesis, pop and print it.
        if (!isEmpty(*top) && (**top).tk.type == TOKEN_FUNC) {
            printf("%s", pop(top).value);
        }
    }
    // If token is comma pop until left paranthesis.
    else if (nextToken.type == TOKEN_COMMA){
        (*pt)++;
        Token tk = (**top).tk;
        while (tk.type!=TOKEN_LP){            
            tk = pop(top);
            printf("%s", tk.value);
            tk = (**top).tk;
        }
        // If function comes next in stack after left paranthesis, pop and print it.
        if ((**top).tk.type == TOKEN_FUNC) {
            printf("%s", pop(top).value);
        }
    }
    // If the incoming symbol is an operator and the stack is empty or contains a left parenthesis on top, push the incoming operator onto the stack.
    else if (isOperator(nextToken) && (isEmpty(*top) || (**top).tk.type == TOKEN_LP)) push(pt, top);
    // If the incoming symbol is an operator and has either higher precedence than the operator on the top of the stack, 
    // or has the same precedence as the operator on the top of the stack and is right associative -- push it on the stack.
    else if (isOperator(nextToken) && (getPrecedence(nextToken)>getPrecedence((**top).tk))) push(pt, top);
    // If the incoming symbol is an operator and has either lower precedence than the operator on the top of the stack, 
    // or has the same precedence as the operator on the top of the stack and is left associative -- continue to pop the stack until this is not true. 
    // Then, push the incoming operator.
    else if (isOperator(nextToken) && (getPrecedence(nextToken)<=getPrecedence((**top).tk))){
        int i = getPrecedence(nextToken);
        while (i<=getPrecedence((**top).tk)) pop(top);
        push(pt, top);
    }
}