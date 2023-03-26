
// Available types of token
enum TokenType {
    TOKEN_INT,
    TOKEN_MUL,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_COMMENT,
    TOKEN_VARIABLE,
    TOKEN_LP, // Left parenthesis
    TOKEN_RP, // Right parenthesis
    TOKEN_FUNC,
    TOKEN_COMMA,
    TOKEN_EQUAL
};

typedef struct Token
{
    char *value;
    enum TokenType type;       
} Token;