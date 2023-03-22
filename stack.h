typedef struct stackNode
{
    Token tk;
    struct stackNode *next;
} stackNode;

stackNode* push(Token tk, stackNode *top);

stackNode* pop(stackNode **top);

bool isEmpty(struct stackNode *top);