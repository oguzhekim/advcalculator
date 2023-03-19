typedef struct OperatorStackNode
{
    Token tk;
    struct* OperatorStackNode;
};

typedef struct OperandStackNode 
{
    Token tk;
    struct* OperandStackNode;
};