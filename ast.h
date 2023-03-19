typedef struct Node
{
    Token tk;
    struct Node *left;
    struct Node *right;
} Node;

Node* createNode(Token tk) {
  Node *newNode = malloc(sizeof(Node));
  newNode->tk = tk;
  newNode->left = NULL;
  newNode->right = NULL;

  return newNode;
}

Node* parseFactor(Token **pt){ //modify global pointer to tokens array in main function
    int currType = (**pt).type;
    // supports only int for now. add support for paranthesis and var.
    if (currType==0){
        //int val = atoi((**pt).value);      
        Node* node = createNode(**pt);
        (*pt)++;
        return node;
    }
}

Node* parseTermTail(Token **pt){
    //<termtail> => <term> | E
    Node* node = parseFactor(pt);
    Token tk = **pt;
    if (tk.type==1 || tk.type==2){
        Node* newNode = createNode(tk);
        (*pt)++;
        newNode -> left = node;
        newNode -> right = parseFactor(pt);
        return newNode;
    }
    return node;
}

Node* parseTerm(Token **pt){
    //<term> => <factor> * <term> | <factor> / <term> | <factor>
    //<term> => <factor> * <factor> | <factor> / <factor> | <factor>   this is what i do rn.
    //<term> => <factor> * <termtail> | <factor> / <termtail> | <factor>  remove recursion
    Node* node = parseFactor(pt);
    Token tk = **pt;
    if (tk.type==1 || tk.type==2){
        Node* newNode = createNode(tk);
        (*pt)++;
        newNode -> left = node;
        newNode -> right = parseFactor(pt);
        return newNode;
    }
    return node;
}

Node* parseExprTail(Token **pt){
    //<exprtail> => <expr> | E
    Node* node = parseFactor(pt);
    Token tk = **pt;
    if (tk.type==1 || tk.type==2){
        Node* newNode = createNode(tk);
        (*pt)++;
        newNode -> left = node;
        newNode -> right = parseFactor(pt);
        return newNode;
    }
    return node;
}

Node* parseExpr(Token **pt){
    //<expr> => <term> + <expr> | <term> - <expr> | <term>
    //<expr> => <term> + <term> | <term> - <term> | <term>  this is what i do rn.
    //<expr> => <term> + <exprtail> | <term> - <exprtail> | <term>  remove recursion.

    Node* node = parseTerm(pt);
    Token tk = **pt;
    if (tk.type==3 || tk.type==4){  
        Node* newNode = createNode(tk);
        (*pt)++;
        newNode -> left = node;
        newNode -> right = parseExprTail(pt);
        return newNode;
    }
    return node;
}