Token* shunting(Token *infix, int tokenCount, int *newTokenCount, bool *error);
bool isOperator(Token tk);