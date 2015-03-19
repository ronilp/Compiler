#include<string.h>
#include<stdbool.h>
#define numTokens 42
#define START 0
#define KEYWORD_IDENTIFIER 1
#define SYMBOL 2
#define SPACE 3
#define NEWLINE 4
#define NUMBER 5
#define STRING_LITERAL 6
#define COMMENT 7
#define MAX_STRING_LENGTH 200
#define MAX_IDENTIFIER_LENGTH 200
#define BUFFER_LENGTH 4096
#define MAX_NUMBER_LENGTH 10

struct table
{
  char symbols[512][MAX_IDENTIFIER_LENGTH];
  char tokens[512][MAX_IDENTIFIER_LENGTH];
};

struct table TokenTable;

extern void readTokens();

extern void searchToken(char c[], FILE *f);

extern void dfa();

extern void lexer();

extern int hash(char c[]);

//int line = 1;

//bool lexicalError = false;

// ERROR TYPES
// invalid chars : !,$ etc ab.c || ab@c DONE
// 2 decimal points DONE
// identifier/string/number length exceeds max DONE
// 12abc DONE
// Non matching "" DONE
