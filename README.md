# Lexical Analyzer in C

This project is a simple lexical analyzer written in C.
It reads a C source file and identifies tokens such as
keywords, identifiers, constants, operators, and special characters.

## How to Compile
gcc main.c lexer.c -o lexer

## How to Run
./lexer test.c

## Sample Output
Token: int             Type: KEYWORD
Token: main            Type: IDENTIFIER
Token: =               Type: OPERATOR
Token: 10              Type: CONSTANT
Token: ;               Type: SPECIAL_CHARACTER
