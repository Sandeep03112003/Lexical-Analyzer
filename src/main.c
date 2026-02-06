/* ======== Header Files ======== */
#include <stdio.h>
#include "lexer.h"


/* ======== Token Type Names ======== */
const char *tokenTypeNames[] = 
{
    "KEYWORD",
    "OPERATOR",
    "SPECIAL_CHARACTER",
    "CONSTANT",
    "IDENTIFIER",
    "UNKNOWN"
};


/* ======== Main Function ======== */
int main(int argc, char *argv[])
{
    initializeLexer(argv[1]);

    Token token;
    while ((token = getNextToken()).type != UNKNOWN)
    {
        printf("Token: %-15s Type: %s\n",token.lexeme,tokenTypeNames[token.type]);
    }

    return 0;
}
