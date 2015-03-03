#define numTerminals 6
#define numNonTerminals 5
#define MAX_TERMINAL_SIZE 100
#define MAX_NONTERMINAL_SIZE 100
#define MAX_RULE_LENGTH 100

char terminal[numTerminals][MAX_TERMINAL_SIZE];

char nonterminal[numNonTerminals][MAX_NONTERMINAL_SIZE];

int parseTable[numNonTerminals][numTerminals];

struct grammar
{
  char rule[MAX_RULE_LENGTH];
  int ruleno;
};

struct grammar Grammar;
