
// Available types of token
enum TokenType {
    TOKEN_INT,
    TOKEN_OPERATOR,
    TOKEN_COMMENT,
    TOKEN_VARIABLE,
    TOKEN_LP, // Left paranthesis
    TOKEN_RP, // Right paranthesis
    TOKEN_FUNC,
};

struct Token
{
    enum TokenType type;
    char* value;    
};

bool isLParanthesis(char ch){
    if (ch=='(') return true;
    return false;
}
bool isRParanthesis(char ch){
    if (ch==')') return true;
    return false;
}

bool isOperator(char ch){
    if (ch=='+' || ch=='-' || ch=='*' || ch=='=' || ch=='&' || ch=='|') return true;
    return false;
}

bool isComment(char ch){
    if (ch=='%') return true;
    return false;
}
bool isFunction(char* ch){
    if (strcmp(ch, "xor")==0 || strcmp(ch, "ls")==0 || strcmp(ch, "rs")==0 || strcmp(ch, "lr")==0 || strcmp(ch, "rr")==0 || strcmp(ch, "not")==0) return true;
    return false;
}
bool isDelimiter(char ch){
    if (isRParanthesis(ch) || isLParanthesis(ch) || isOperator(ch)  || isComment(ch)  || ch==' ' || ch=='\0') return true;
    return false;
}
bool isVariable(char* ch){
    for (int i=0; i<strlen(ch);i++){
        if (isalpha(*(ch+i))==0) return false;
    }
    return true;
}

bool isInteger(char* ch){
    for (int i=0; i<strlen(ch);i++){
        if (isdigit(*(ch+i))==0) return false;
    }
    return true;
}

void lexer(char* input, int* tokenCount, struct Token tokens[]){
    int len = strlen(input);
    int left = 0;
    int right = 0;
    while (right<=len){ // TODO: && left<=right??
        if (!isDelimiter(input[right])){
            right++;
        }
        else if (isDelimiter(input[right]) && left==right){
            if (isOperator(input[right])){
                printf("'%c' IS AN OPERATOR\n", input[right]);
            }
            else if (isComment(input[right])){
                printf("'%c' IS A COMMENT\n", input[right]);
            }
            else if (isLParanthesis(input[right])){
                printf("'%c' IS A LPARANTHESIS\n", input[right]);
            }
            else if (isRParanthesis(input[right])){
                printf("'%c' IS A RPARANTHESIS\n", input[right]);
            }
            right++;
            left = right;
        }
        else if (isDelimiter(input[right]) && left != right || (right == len && left != right)){
            // Get the substring between two indices
            char substr[right-left+1];
            for (int i = left; i < right; i++)
            {
                substr[i-left] = input[i];
            }
            substr[right-left] = '\0';

            if (isFunction(substr)){
                printf("'%s' IS A FUNCTION\n", substr);
            }
            else if (isInteger(substr))
            {
                printf("'%s' IS AN INTEGER\n", substr);
            }
            else if (isVariable(substr))
            {
                printf("'%s' IS A VARIABLE\n", substr);
            }
            else {
                printf("%s is invalid character\n", substr);
            }
            left = right;
        }
    }
}
