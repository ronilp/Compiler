#include<string.h>
#define numTokens 16
#define start 0
#define keyword_identifier 1
#define symbol 2
#define trap 3

struct table
{
  char symbols[numTokens][20];
  char tokens[numTokens][20];
};

struct table TokenTable;

void readTokens();

void search(char c[]);

void dfa();