
// Available types of token
enum TokenType {
    TOKEN_INT,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_ADD,
    TOKEN_SUBS,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_COMMENT,
    TOKEN_VARIABLE,
    TOKEN_LP, // Left paranthesis
    TOKEN_RP, // Right paranthesis
    TOKEN_FUNC,
    TOKEN_COMMA,
    TOKEN_EQUAL
};

typedef struct Token
{
    char *value;
    enum TokenType type;       
} Token;