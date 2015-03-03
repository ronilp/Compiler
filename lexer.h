#include<string.h>
#define numTokens 42
#define start 0
#define keyword_identifier 1
#define symbol 2
#define space 3
#define newline 4
#define number 5
#define string_literal 6
#define comment 7
#define MAX_STRING_LENGTH 200
#define MAX_IDENTIFIER_LENGTH 200
#define BUFFER_LENGTH 4096
#define MAX_NUMBER_LENGTH 100

struct table
{
  char symbols[numTokens][MAX_IDENTIFIER_LENGTH];
  char tokens[numTokens][MAX_IDENTIFIER_LENGTH];
};

struct table TokenTable;

void readTokens();

void search(char c[], FILE *f);

void dfa();

int line = 1;

// invalid chars : !,$ etc
// 2 decimal points DONE
// identifier length exceeds max
// number length exceeds max
// 12abc DONE
// ab.c || ab@c
// Non matching "" DONE
