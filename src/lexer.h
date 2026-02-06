#ifndef LEXER_H
#define LEXER_H


/* ======== Macros ======== */
#define MAX_KEYWORDS 20
#define MAX_TOKEN_SIZE 100
#define TRUE 1
#define FALSE 0


/* ======== Token Types ======== */
typedef enum {
    KEYWORD,
    OPERATOR,
    SPECIAL_CHARACTER,
    CONSTANT,
    IDENTIFIER,
    UNKNOWN
} TokenType;


/* ======== Token Type Names ======== */
extern const char *tokenTypeNames[];


/* ======== Token Structure ======== */
typedef struct {
    char lexeme[MAX_TOKEN_SIZE];
    TokenType type;
} Token;


/* ======== Lexer Interface ======== */
void initializeLexer(const char* filename);
Token getNextToken();


/* ======== Token Classification ======== */
void categorizeToken(Token* token);
int isKeyword(const char* str);
int isOperator(const char* str);
int isSpecialCharacter(char ch);
int isConstant(const char* str);
int isIdentifier(const char* str);


/* ======== Constant Helpers ======== */
int isInteger(const char*str);
int isFloat(const char *str);
int isCharliteral(const char*str);
int isStringliteral(const char*str);


#endif
