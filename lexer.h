#include<string.h>
#define numTokens 42
#define start 0
#define keyword_identifier 1
#define symbol 2
#define space 3
#define newline 4
#define number 5

struct table
{
  char symbols[numTokens][20];
  char tokens[numTokens][20];
};

struct table TokenTable;

void readTokens();

void search(char c[]);

void dfa();
