typedef struct stackNode
{
    Token tk;
    struct stackNode *next;
} stackNode;

void push(Token tk, stackNode **top);

Token pop(stackNode **top);

bool isEmpty(struct stackNode *top);