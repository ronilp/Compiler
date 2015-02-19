#include<string.h>
#define numTokens 43
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
#define BUFFER_LENGTH 1000

struct table
{
  char symbols[numTokens][20];
  char tokens[numTokens][20];
};

struct table TokenTable;

void readTokens();

void search(char c[], FILE *f);

void dfa();

// invalid chars : !,$ etc
// 2 decimal points
