typedef struct OperatorStackNode
{
    Token tk;
    struct OperatorStackNode *next;
} OperatorStackNode;

typedef struct OperandStackNode
{
    Token tk;
    struct OperandStackNode *next;
} OperandStackNode;

bool isEmpty(struct OperandStackNode *top)
{
    return !top;
}

OperandStackNode *newOperandNode(Token tk)
{
    OperandStackNode *node = malloc(sizeof(OperandStackNode));
    node->tk = tk;
    node->next = NULL;
    return node;
}

void pushOperand(Token **pt, OperandStackNode **top)
{
    OperandStackNode *node = newOperandNode(**pt);
    node->next = *top;
    *top = node;
    printf("%s pushed to operand stack\n", (**pt).value);
    (*pt)++;
}

Token popOperand(OperandStackNode **top)
{
    // ADD ISEMPTY
    OperandStackNode *node = *top;
    *top = (*top)->next;
    Token tk = node->tk;
    free(node);
    printf("%s popped from operand stack\n", tk.value);
    return tk;
}

OperatorStackNode *newOperatorNode(Token tk)
{
    OperatorStackNode *node = malloc(sizeof(OperatorStackNode));
    node->tk = tk;
    node->next = NULL;
    return node;
}

void pushOperator(Token **pt, OperatorStackNode **top)
{
    OperatorStackNode *node = newOperatorNode(**pt);
    node->next = *top;
    *top = node;
    printf("%s pushed to operator stack\n", (**pt).value);
    (*pt)++;
}

Token popOperator(OperatorStackNode **top)
{
    // ADD ISEMPTY
    OperatorStackNode *node = *top;
    *top = (*top)->next;
    Token tk = node->tk;
    free(node);
    printf("%s popped from operator stack\n", tk.value);
    return tk;
}

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
    return -1;
}


int shunting(OperatorStackNode **operatorTop, OperandStackNode **operandTop, Token **pt, bool isEnd)
{
    Token nextToken = **pt;
    if (isOperator(nextToken) || isEnd){
        while (*operatorTop!=NULL){
            // If next token has lower precedence execute operation currently on top of stack.
            if (getPrecedence(nextToken)<=getPrecedence((**operatorTop).tk)){
                Token op = popOperator(operatorTop);
                int fac2 = atoi(popOperand(operandTop).value);
                int fac1 = atoi(popOperand(operandTop).value);
                if (op.value[0]=='+') return fac1+fac2;
                else if (op.value[0]=='-') return fac1-fac2;
                else if (op.value[0]=='/') return fac1/fac2;
                else if (op.value[0]=='*') return fac1*fac2;
            }
            else {
            pushOperator(pt, operatorTop);
            return 0;
        }
        }
        pushOperator(pt, operatorTop);
        return 0;         
    }
    else if (isOperand(nextToken))
    {
        pushOperand(pt, operandTop);
        return 0;
    }
}