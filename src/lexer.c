/* ==============================
 *         Header Files
 * ============================== */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"


/* ==============================
 *     Keyword & Symbol Tables
 * ============================== */
static const char* keywords[MAX_KEYWORDS] = 
{
    "int", "float", "return", "if", "else", "while", "for", "do", "break", "continue",
    "char", "double", "void", "switch", "case", "default", "const", "static", "sizeof", "struct"
};

static const char* operators = "+-*/%=!<>|&";
static const char* specialCharacters = ",;{}()[]";


/* ==============================
 *        File Pointer
 * ============================== */
FILE*Sourcefile;


/* ==============================
 *     Lexer Initialization
 * ============================== */
void initializeLexer(const char* filename)
{
    FILE*fptr = fopen(filename,"r");
    if(fptr == NULL)
    {
        printf("Failed to open the file\n");
        return;
    }
   Sourcefile=fptr;
}


/* ==============================
 *     Token Generation
 * ============================== */
Token getNextToken()
{
      Token token;
      token.lexeme[0]='\0';
      char ch;
      ch = fgetc(Sourcefile);
      if(ch == EOF)
      {
           token.type=UNKNOWN;
          return token;
      }
   while(isspace((unsigned char)ch))
   {
      ch=fgetc(Sourcefile);
   }
   if(ch == EOF)
    {
        token.type=UNKNOWN;
        return token;
    }
   if(ch == '_' || isalpha(ch))
   { 
       int i=0;
       token.lexeme[0]=ch;
       i++;
       ch = fgetc(Sourcefile);
       while(isalnum((unsigned char)ch) || ch =='_')
       {
           token.lexeme[i]=ch;
           i++;
           ch = fgetc(Sourcefile);
       }
       ungetc(ch, Sourcefile);
        token.lexeme[i]='\0';
       categorizeToken(&token);
       return token;
   }
   else if (isdigit((unsigned char)ch))
   {
      int i=0,dot_count=0;
      token.lexeme[0]=ch;
      i++;
      ch = fgetc(Sourcefile);
      while(isdigit((unsigned char)ch) || (ch =='.' &&  ( dot_count==0)))
      {
        if(ch == '.')
        {
            dot_count++;
        }
          token.lexeme[i]=ch;
          i++;
          ch = fgetc(Sourcefile);
      }
      ungetc(ch,Sourcefile);
      token.lexeme[i]='\0';
      categorizeToken(&token);
      return token;
   }
   else if(ch=='"')
   {
        int i=0;
        token.lexeme[i]=ch;
        i++;
        ch=fgetc(Sourcefile);
        while(ch != '"' && ch!=EOF)
        {
             token.lexeme[i]=ch;
             i++;
            ch = fgetc(Sourcefile);
        }
        if(ch!=EOF)
        {
            token.lexeme[i]=ch;
        }
        else
        {
            categorizeToken(&token);
            return token;
        }
        i++;
        token.lexeme[i]='\0';
        categorizeToken(&token);
        return token;

   }
   else if(ch=='\'')
   {
       token.lexeme[0]='\'';
       ch=fgetc(Sourcefile);
       token.lexeme[1]=ch;
        ch=fgetc(Sourcefile);
        if(ch =='\'')
        {
            token.lexeme[2]='\'';
            token.lexeme[3]='\0';
            categorizeToken(&token);
            return token;
        }
        else
        {
            token.lexeme[2]='\0';
            categorizeToken(&token);
            return token;
        }

   }
   token.lexeme[0]=ch;
   token.lexeme[1]='\0';
   categorizeToken(&token);
   return token;
}


/* ==============================
 *     Token Categorization
 * ============================== */
void categorizeToken(Token* token)
{
    if(isKeyword(token->lexeme))
    {
        token->type=KEYWORD;
    }
    else if(isConstant(token->lexeme))
    {
        token->type=CONSTANT;
    }
    else if(isIdentifier(token->lexeme))
    {
        token->type= IDENTIFIER;
    }
    else if(isOperator(token->lexeme))
    {
        token->type = OPERATOR;
    }
    else if(isSpecialCharacter(token->lexeme[0]))
    {
        token->type = SPECIAL_CHARACTER;
    }
    else
    {
        token->type = UNKNOWN;
    }
}


/* ==============================
 *     Keyword & Identifier Checks
 * ============================== */
int isKeyword(const char* str)
{
    for(int i=0;i<MAX_KEYWORDS;i++)
    {
        if(strcmp(str,keywords[i])==0)
        {
            return TRUE;
        }
       
    }
     return FALSE;
}

int isIdentifier(const char* str)
{
    if((!(isalpha(str[0]))) && str[0]!='_')
    {
          return FALSE;
    }
    for(int i=1;str[i]!='\0';i++)
    {
         if((!isalnum(str[i])) && str[i]!='_')
         {
               return FALSE;
         }
    }
    return TRUE;
}


/* ==============================
 *     Constant Classification
 * ============================== */
int isConstant(const char*str)
{
    if(strlen(str)==0)
    {
        return FALSE;
    }
     if(isCharliteral(str))
    {
        return TRUE;
    }
     else if(isStringliteral(str))
    {
        return TRUE;
    }
    else if(isInteger(str))
    {
        return TRUE;
    }
    else if(isFloat(str))
    {
        return TRUE;
    }
    
   
    return FALSE;
}


/* ==============================
 *     Numeric Constants
 * ============================== */
int isInteger(const char*str)
{
    if(str[0]=='\0')
    {
        return FALSE;
    }
    for(int i=0;str[i]!='\0';i++)
    {
        if(!(isdigit((unsigned char)str[i])))
        {
            return FALSE;
        }
    }
    return TRUE;
}

int isFloat(const char*str)
{
    int count =0;
    if(str[0]=='\0' || str[0] == '.')
    {
        return FALSE;
    }
     for(int i=0;str[i]!='\0';i++)
    {
        if(str[i]=='.')
        {
            count++;
            if( str[i+1] !='\0')
            {
                continue;
            }
            else
            {
               return FALSE;
            }
        }
        
        if(!(isdigit((unsigned char)str[i])) || count>1)
        {
            return FALSE;
        }
    }
    if(count == 0)
    {
        return FALSE;
    }
    return TRUE;
}


/* ==============================
 *     Literal Constants
 * ============================== */
int isCharliteral(const char *str)
{
    if(strlen(str)!=3 )
    {
        return FALSE;
    }
    if(str[0]!='\'' || str[2]!='\'')
    {
        return FALSE;
    }
    return TRUE;
}

int isStringliteral(const char *str)
{
    int len = strlen(str) -1;
    if(str[0]!='"' || str[len]!='"')
    {
        return FALSE;
    }
    return TRUE;
}


/* ==============================
 *     Operators & Symbols
 * ============================== */
int isOperator(const char* str)
{
    if(strlen(str)!=1)
    {
        return FALSE;
    }
    for(int i=0;operators[i];i++)
    {
        if(*str == operators[i])
        {
            return TRUE;
        }
    }
    return FALSE;
}

int isSpecialCharacter(char ch)
{
    for(int i=0;specialCharacters[i];i++)
    {
        if(ch == specialCharacters[i])
        {
            return TRUE;
        }
    }
    return FALSE;
}
